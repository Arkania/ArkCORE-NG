/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Coldridge_Valley
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Coldridge Valley
EndScriptData */

/* ContentData

EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Vehicle.h"

enum zone_coldridge_valley
{
    NPC_ROCKSAW_INVADER = 37070,
    NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT = 37079,
    NPC_WOUNDED_COLDRIDGE_MOUNTAINEER = 37080,
    NPC_COLDRIDGE_DEFENDER = 37177,
    NPC_ROCKJAW_SCAVENGER = 37105,
    NPC_SOOTHSAYER_SHIKALA = 37108,
    NPC_SOOTHSAYER_RIKKARI = 37173,
    NPC_SOOTHSAYER_MIRIMKOA = 37174,
    NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE = 37109,
    NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW = 37110,
    NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W = 37111,

    SPELL_HEAL_WOUNDED_MOUNTAINEER = 69855,
    SPELL_THROW_PRICELESS_ARTIFACT = 69897,

    QUEST_AID_FOR_THE_WOUNDED = 24471,
    QUEST_TROLLING_FOR_INFORMATION = 24489,
    QUEST_MAKE_HAY_WHILE_THE_SUN_SHINES = 24486,
    ITEM_PRICELESS_ROCKJAW_ARTIFACT = 49751,

};

// 37070 npc_rockjaw_invader
class npc_rockjaw_invader : public CreatureScript
{
public:
    npc_rockjaw_invader() : CreatureScript("npc_rockjaw_invader") { }

    struct npc_rockjaw_invaderAI : public ScriptedAI
    {
        npc_rockjaw_invaderAI(Creature *c) : ScriptedAI(c) { }

        uint32 Attack1HTimer;

        void Reset()
        {
            Attack1HTimer = urand(1800, 2200);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (Creature* infantry = me->FindNearestCreature(NPC_COLDRIDGE_DEFENDER, 3.0f))
                {
                    if (Attack1HTimer <= diff)
                    {
                        me->SetFacingTo(me->GetAngle(infantry));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        Attack1HTimer = urand(1800, 2200);
                    }
                    else Attack1HTimer -= diff;
                }
            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rockjaw_invaderAI(creature);
    }
};

// 37177 npc_coldridge_defender
class npc_coldridge_defender : public CreatureScript
{
public:
    npc_coldridge_defender() : CreatureScript("npc_coldridge_defender") { }

    struct npc_coldridge_defenderAI : public ScriptedAI
    {
        npc_coldridge_defenderAI(Creature *c) : ScriptedAI(c) { }

        uint32 Attack1HTimer;

        void Reset()
        {
            Attack1HTimer = urand(1800, 2200);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (Creature* infantry = me->FindNearestCreature(NPC_ROCKSAW_INVADER, 3.0f))
                {
                    if (Attack1HTimer <= diff)
                    {
                        me->SetFacingTo(me->GetAngle(infantry));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        Attack1HTimer = urand(1800, 2200);
                    }
                    else Attack1HTimer -= diff;
                }
            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_coldridge_defenderAI(creature);
    }
};

// 37080 npc_wounded_coldridge_mountaineer
class npc_wounded_coldridge_mountaineer : public CreatureScript
{
public:
    npc_wounded_coldridge_mountaineer() : CreatureScript("npc_wounded_coldridge_mountaineer") { }

    struct npc_wounded_coldridge_mountaineerAI : public ScriptedAI
    {
        npc_wounded_coldridge_mountaineerAI(Creature *creature) : ScriptedAI(creature) { }

        uint32 phase;
        uint32 timer;

        void Reset()
        {
            timer = 0; 
            phase = 0;
        }

        void DoAction(int32 actionID) override
        {
            phase = 1;
            timer = 1000;
        }

        void UpdateAI(uint32 diff)
        {
            if (timer <= diff)
            {
                timer = 1000;
                DoWork();
            }
            else
                timer -= diff;
        }

        void DoWork()
        {
            switch (phase)
            {
            case 1:
                Talk(0);
                timer = 5000;
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_STAND);
                phase = 2;
                break;
            case 2:
                me->GetMotionMaster()->MovePoint(0, me->GetNearPosition(25.0f, me->GetFollowAngle()));
                timer = 3000;
                phase = 3;
                break;
            case 3:
                me->DisappearAndDie();
                phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wounded_coldridge_mountaineerAI(creature);
    }
};

// 69855
class spell_heal_wounded_mountaineer : public SpellScriptLoader
{
public:
    spell_heal_wounded_mountaineer() : SpellScriptLoader("spell_heal_wounded_mountaineer") { }

    class spell_heal_wounded_mountaineer_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_heal_wounded_mountaineer_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return true;
        }

        void HandleDummyEffect(SpellEffIndex /*effIndex*/)
        {
            if (Creature* mountaineer = GetCaster()->FindNearestCreature(37080, 5.0f, true))
                mountaineer->AI()->DoAction(1);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_heal_wounded_mountaineer_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }

    private:
        uint32 _targetCount;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_heal_wounded_mountaineer_SpellScript();
    }
 };

// 37105 npc_rockjaw_scavenger
class npc_rockjaw_scavenger : public CreatureScript
{
public:
    npc_rockjaw_scavenger() : CreatureScript("npc_rockjaw_scavenger") { }

    struct npc_rockjaw_scavengerAI : public ScriptedAI
    {
        npc_rockjaw_scavengerAI(Creature *creature) : ScriptedAI(creature)
        {
            _hasCasted = false;
        }

        bool _hasCasted;

        void DamageTaken(Unit* Hitter, uint32& Damage)
        {
            if (Player* player = Hitter->ToPlayer())
                if (player->GetQuestStatus(QUEST_MAKE_HAY_WHILE_THE_SUN_SHINES) == QUEST_STATUS_INCOMPLETE)
                    if (!_hasCasted)
                        if (me->GetDistance(player) >= 5.0f && me->GetDistance(player) <= 15.0f)
                            switch (urand(0, 3))
                        {
                            case 2:
                                me->CastSpell(player, SPELL_THROW_PRICELESS_ARTIFACT, true);
                                player->AddItem(ITEM_PRICELESS_ROCKJAW_ARTIFACT, 1);
                                _hasCasted = true;
                        }

        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rockjaw_scavengerAI(creature);
    }
};

// 37108 npc_soothsayer_shikala
class npc_soothsayer_shikala : public CreatureScript
{
public:
    npc_soothsayer_shikala() : CreatureScript("npc_soothsayer_shikala") { }

    struct npc_soothsayer_shikalaAI : public ScriptedAI
    {
        npc_soothsayer_shikalaAI(Creature *c) : ScriptedAI(c) { }

        uint32 timer;
        uint32 phase;
        bool TalkSequenceIsStarted;
        Player* player;

        void Reset()
        {
            timer = 0; TalkSequenceIsStarted = false; phase = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
            {
                player = who->ToPlayer();
                if (player)
                {
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {
                        TalkSequenceIsStarted = true;
                        timer = 2000; phase++;
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (TalkSequenceIsStarted)
                {
                    if (!player)
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false;
                        return;
                    }
                    if (timer <= diff)
                    {
                        switch (phase)
                        {
                        case 1:
                        {
                            Talk(0); timer = 5000; phase++;
                            break;
                        }
                        case 2:
                        {
                            Talk(1); timer = 5000; phase++;
                            break;
                        }
                        case 3:
                        {
                            Talk(2); timer = 5000; phase++;
                            break;
                        }
                        case 4:
                        {
                            player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE, 0);
                            timer = 120000; phase++; // cooldown
                            break;
                        }
                        case 5:
                        {
                            timer = 0; phase = 0; TalkSequenceIsStarted = false;
                            break;
                        }
                        }
                    }
                    else
                        timer -= diff;

                    if (!me->IsInRange(player, 0.0f, 15.0F))
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false; // if player gone away, delete cooldown
                    }
                }

            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_soothsayer_shikalaAI(creature);
    }
};

// 37173 npc_soothsayer_rikkari
class npc_soothsayer_rikkari : public CreatureScript
{
public:
    npc_soothsayer_rikkari() : CreatureScript("npc_soothsayer_rikkari") { }

    struct npc_soothsayer_rikkariAI : public ScriptedAI
    {
        npc_soothsayer_rikkariAI(Creature *c) : ScriptedAI(c) { }

        uint32 timer;
        uint32 phase;
        bool TalkSequenceIsStarted;
        Player* player;

        void Reset()
        {
            timer = 0; TalkSequenceIsStarted = false; phase = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
            {
                player = who->ToPlayer();
                if (player)
                {
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {
                        TalkSequenceIsStarted = true;
                        timer = 2000; phase++;
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (TalkSequenceIsStarted)
                {
                    if (!player)
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false;
                        return;
                    }
                    if (timer <= diff)
                    {
                        switch (phase)
                        {
                        case 1:
                        {
                            Talk(0); timer = 5000; phase++;
                            break;
                        }
                        case 2:
                        {
                            Talk(1); timer = 5000; phase++;
                            break;
                        }
                        case 3:
                        {
                            Talk(2); timer = 5000; phase++;
                            break;
                        }
                        case 4:
                        {
                            player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW, 0);
                            timer = 120000; phase++; // cooldown                                                                                                          
                            break;
                        }
                        case 5:
                        {
                            timer = 0; phase = 0; TalkSequenceIsStarted = false;
                            break;
                        }
                        }
                    }
                    else
                        timer -= diff;

                    if (!me->IsInRange(player, 0.0f, 15.0F))
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false; // if player gone away, delete cooldown
                    }
                }

            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_soothsayer_rikkariAI(creature);
    }
};

// 37174 npc_soothsayer_mirimkoa
class npc_soothsayer_mirimkoa : public CreatureScript
{
public:
    npc_soothsayer_mirimkoa() : CreatureScript("npc_soothsayer_mirimkoa") { }

    struct npc_soothsayer_mirimkoaAI : public ScriptedAI
    {
        npc_soothsayer_mirimkoaAI(Creature *c) : ScriptedAI(c) { }

        uint32 timer;
        uint32 phase;
        bool TalkSequenceIsStarted;
        Player* player;

        void Reset()
        {
            timer = 0; TalkSequenceIsStarted = false; phase = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
            {
                player = who->ToPlayer();
                if (player)
                {
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {
                        TalkSequenceIsStarted = true;
                        timer = 2000; phase++;
                    }
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (TalkSequenceIsStarted)
                {
                    if (!player)
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false;
                        return;
                    }
                    if (timer <= diff)
                    {
                        switch (phase)
                        {
                        case 1:
                        {
                            Talk(0); timer = 5000; phase++;
                            break;
                        }
                        case 2:
                        {
                            Talk(1); timer = 5000; phase++;
                            break;
                        }
                        case 3:
                        {
                            Talk(2); timer = 5000; phase++;
                            break;
                        }
                        case 4:
                        {
                            player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W, 0);
                            timer = 120000; phase++; // cooldown                                                                                      
                            break;
                        }
                        case 5:
                        {
                            timer = 0; phase = 0; TalkSequenceIsStarted = false;
                            break;
                        }
                        }
                    }
                    else
                        timer -= diff;

                    if (!me->IsInRange(player, 0.0f, 15.0F))
                    {
                        timer = 0; phase = 0; TalkSequenceIsStarted = false; // if player gone away, delete cooldown
                    }
                }

            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_soothsayer_mirimkoaAI(creature);
    }
};

// Quest: Follow that Gyro-Copter! 24491
enum eQuest24491
{
    QUEST_A_TRIP_TO_IRONFORGE = 24490,
    QUEST_FOLLOW_THAT_GYRO_COPTER = 24491,

    NPC_HANDS_SPRINGSPROCKET = 6782,

    SPELL_SEE_COLDRIGE_TUNNEL_ROCKS_SEE_QUEST_INVIS_1 = 70042,
    SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2 = 70044,
    SPELL_MILO_GEARTWINGE_INVISIBILITY_QUEST_INVIS_2 = 70045,
    SPELL_A_TRIP_TO_IRONFORGE_QUEST_COMLETE = 70046,
};

// 6782 npc_hands_springsprocket
class npc_hands_springsprocket : public CreatureScript
{
public:
    npc_hands_springsprocket() : CreatureScript("npc_hands_springsprocket") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    { 
        if (quest->GetQuestId() == QUEST_A_TRIP_TO_IRONFORGE)
            player->CastSpell(player, SPELL_A_TRIP_TO_IRONFORGE_QUEST_COMLETE, true);
        
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FOLLOW_THAT_GYRO_COPTER)
            if (!player->HasAura(SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2))
            {
                player->CastSpell(player, SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2, true);
            }

        return true;
    }
};

// QUEST_PACK_YOUR_BAGS
enum eQuest24492
{
    QUEST_PACK_YOUR_BAGS = 24492,

    NPC_MILO_GEARTWINGE = 37113,
    NPC_MILO_GEARTWINGE_SPAWNED = 37518,
    NPC_MILOS_GYRO = 37169,
    NPC_MILOS_GYRO_SPAWNED = 37198,

    SPELL_SUMMON_MILOS_GYROCOPTER = 70035,
    SPELL_RIDING_MILOS_GYRO = 70036,
};

// 37198 npc_milos_gyro_spawned
class npc_milos_gyro_spawned : public CreatureScript
{
public:
    npc_milos_gyro_spawned() : CreatureScript("npc_milos_gyro_spawned") { }

    struct npc_milos_gyro_spawnedAI : public VehicleAI
    {
        npc_milos_gyro_spawnedAI(Creature* creature) : VehicleAI(creature) { }

        uint32 _phase;

        void Reset()
        {
           _phase = 0;
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (!apply)
                return;

            if (_phase == 0  && seatId == 0 && apply)
            {
                _phase = 1;
                me->SendGravityDisable();
                me->GetMotionMaster()->MovePath(3719801, false);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != WAYPOINT_MOTION_TYPE || _phase != 1)
                return;

            switch (id)
            {
            case 1:
                Talk(0);
                me->SetSpeed(MOVE_RUN, 3.0f, true);
                break;
            case 3:
                Talk(1);
                break;
            case 4:
                Talk(2);
                break;
            case 5:
                Talk(3);
                break;
            case 6:
                Talk(4);
                break;
            case 7:
                Talk(5);
                break;
            case 8:
                Talk(6);
                break;
            case 10:
                _phase = 2;
                me->ExitVehicle();
                me->DespawnOrUnsummon(5000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_milos_gyro_spawnedAI(creature);
    }

};

// 40991 npc_mountaineer_dunstan
class npc_mountaineer_dunstan : public CreatureScript
{
public:
    npc_mountaineer_dunstan() : CreatureScript("npc_mountaineer_dunstan") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) 
    { 
        if (player && player->GetQuestStatus(313) == QUEST_STATUS_INCOMPLETE)
        {
            creature->AI()->Talk(0);
            player->KilledMonsterCredit(40991);
            player->CLOSE_GOSSIP_MENU();
        }

        return false; 
    }
};

// 40994 npc_mountaineer_lewin
class npc_mountaineer_lewin : public CreatureScript
{
public:
    npc_mountaineer_lewin() : CreatureScript("npc_mountaineer_lewin") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/)
    {
        if (player && player->GetQuestStatus(313) == QUEST_STATUS_INCOMPLETE)
        {
            creature->AI()->Talk(0);
            player->KilledMonsterCredit(40994);
            player->CLOSE_GOSSIP_MENU();
        }

        return false;
    }
};

// 41056 npc_mountaineer_valgrum
class npc_mountaineer_valgrum : public CreatureScript
{
public:
    npc_mountaineer_valgrum() : CreatureScript("npc_mountaineer_valgrum") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/)
    {
        if (player && player->GetQuestStatus(313) == QUEST_STATUS_INCOMPLETE)
        {
            creature->AI()->Talk(0);
            player->KilledMonsterCredit(41056);
            player->CLOSE_GOSSIP_MENU();
        }

        return false;
    }
};


void AddSC_coldridge_valley()
{
    new npc_rockjaw_invader();
    new npc_coldridge_defender();
    new npc_wounded_coldridge_mountaineer();
    new spell_heal_wounded_mountaineer();
    new npc_soothsayer_shikala();
    new npc_soothsayer_rikkari();
    new npc_soothsayer_mirimkoa();
    new npc_rockjaw_scavenger();
    new npc_hands_springsprocket();
    new npc_milos_gyro_spawned();
    new npc_mountaineer_dunstan();
    new npc_mountaineer_lewin();
    new npc_mountaineer_valgrum();
}

