/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2018 ArkCORE <http://www.arkania.net/>
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

#include "script_helper.h"

// npc 40079
class npc_feralas_wisp_40079 : public CreatureScript
{
public:
    npc_feralas_wisp_40079() : CreatureScript("npc_feralas_wisp_40079") { }

    enum eWisp
    {
        NPC_FERALAS_WISP = 40079,
        SPELL_WISP_DETONATE = 6237,
        SPELL_RALLY_WILD_WISP = 74738,
        QUEST_FORCES_OF_NATURE_WISPS = 25407,
    };

    struct npc_feralas_wisp_40079AI : public ScriptedAI
    {
        npc_feralas_wisp_40079AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        bool      _isFollowing;
        uint64    _playerGUID;

        void Initialize()
        {
        }

        void Reset() override
        {
            _isFollowing = false;
            _playerGUID = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!_isFollowing)
                if (Player* player = caster->ToPlayer())
                    if (spell->Id == SPELL_RALLY_WILD_WISP)
                    {
                        _isFollowing = true;
                        _playerGUID = player->GetGUID();
                        me->setActive(true); // the npc hold the sector alive.. no player must be near..
                        player->KilledMonsterCredit(NPC_FERALAS_WISP);
                        me->GetMotionMaster()->Clear();
                        me->SetHover(true);
                        me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, frand(1.8f, 2.2f));
                        me->GetMotionMaster()->MoveFollow(player, frand(8.0f, 12.0f), frand(2.14f, 4.14f));

                        _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID);
                    if (!player)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (player->GetQuestStatus(QUEST_FORCES_OF_NATURE_WISPS) == QUEST_STATUS_REWARDED)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (player->GetQuestStatus(QUEST_FORCES_OF_NATURE_WISPS) == QUEST_STATUS_NONE)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (me->GetDistance2d(player) > 250.0f)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else
                        _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                }
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_feralas_wisp_40079AI(creature);
    }
};

// npc 5300 5304
class npc_feralas_hippogryph_5300 : public CreatureScript
{
public:
    npc_feralas_hippogryph_5300() : CreatureScript("npc_feralas_hippogryph_5300") {}

    enum quest_enums
    {
        SPELL_RALLY_WILD_HIPPOGRYFF = 74674,
        SPELL_FORCE_PLAYER_TO_SUMMON_HORDE_PATCHER = 74728,
        SPELL_AIR_BLAST = 81181,
        SPELL_FEATHERLIGHT = 81179,
        SPELL_WING_BUFFET = 32914,
        NPC_HORDE_POACHER = 40069,
        NPC_FORCES_01_HIPPOGRYPH_KILL_CREDIT_BUNNY = 40072,
    };

    struct npc_feralas_hippogryph_5300AI : public ScriptedAI
    {
        npc_feralas_hippogryph_5300AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        uint64    _playerGUID;
        bool      _hippo_called;

        void Initialize()
        {
        }

        void Reset() override
        {
            _playerGUID = 0;
            _hippo_called = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!_hippo_called)
                if (Player* player = caster->ToPlayer())
                    if (spell->Id == SPELL_RALLY_WILD_HIPPOGRYFF)
                    {
                        _playerGUID = player->GetGUID();
                        _hippo_called = true;
                        me->GetMotionMaster()->MoveIdle();
                        me->setFaction(35);
                        me->SetFacingTo(me->GetAngle(player->GetPositionX(), player->GetPositionY()));
                        player->KilledMonsterCredit(NPC_FORCES_01_HIPPOGRYPH_KILL_CREDIT_BUNNY);

                        _events.ScheduleEvent(EVENT_CHECK_ATTACK, 2000);  // 60 % chance for spawn horde fighter
                        _events.ScheduleEvent(EVENT_START_FLYING, 3000);  // timed start for hippo flying away..
                    }
        }

        void EnterCombat(Unit* victim) override 
        {
            if (_hippo_called)
            {
                me->AttackStop();
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_FLYING:     // me-> fly vertical upwarts, normal speed
                {
                    me->GetMotionMaster()->MovePoint(1002, me->m_positionX, me->m_positionY, me->m_positionZ + 100.0f);
                    _events.ScheduleEvent(EVENT_DESPAWN_PART_00, 5000);
                    break;
                }
                case EVENT_DESPAWN_PART_00:  // me-> despawn with 5 sec delay
                {
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_CHECK_ATTACK:     // me->cast force spell (140) -> spawn horde fighter 66% chance
                {
                    if (urand(0, 100) <= 66)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            me->CastSpell(player, SPELL_FORCE_PLAYER_TO_SUMMON_HORDE_PATCHER, true);

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_feralas_hippogryph_5300AI(creature);
    }
};

// npc 7584
class npc_wandering_forest_walker_7584 : public CreatureScript
{
public:
    npc_wandering_forest_walker_7584() : CreatureScript("npc_wandering_forest_walker_7584") {}

    enum quest_enums
    {
        SPELL_FORCE_PLAYER_TO_SUMMON_HORDE_PATCHER = 74728,
        SPELL_RALLY_WILD_TREANT = 74756,
        SPELL_REGROWTH = 16561,
        SPELL_FORCE_OF_NATURE = 6913,
        NPC_FORCES_03_TREANT_KILL_CREDIT_BUNNY = 40090,
    };

    struct npc_wandering_forest_walker_7584AI : public ScriptedAI
    {
        npc_wandering_forest_walker_7584AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        uint64    _playerGUID;
        bool      _treant_called;

        void Initialize()
        {
        }

        void Reset() override
        {
            _playerGUID = 0;
            _treant_called = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!_treant_called)
                if (Player* player = caster->ToPlayer())
                    if (spell->Id == SPELL_RALLY_WILD_TREANT)
                    {
                        _playerGUID = player->GetGUID();
                        _treant_called = true;
                        me->GetMotionMaster()->Clear();
                        me->SetFacingTo(me->GetAngle(player->GetPositionX(), player->GetPositionY()));
                        player->KilledMonsterCredit(NPC_FORCES_03_TREANT_KILL_CREDIT_BUNNY);

                        _events.ScheduleEvent(EVENT_CHECK_ATTACK, 2000);     // 60 % chance for spawn horde fighter
                        _events.ScheduleEvent(EVENT_DESPAWN_PART_00, 2500);  // despawn
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DESPAWN_PART_00:  // me-> despawn 
                {
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_CHECK_ATTACK:     // me->cast force spell (140) -> spawn horde fighter 66% chance
                {
                    if (urand(0, 100) <= 66)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                            me->CastSpell(player, SPELL_FORCE_PLAYER_TO_SUMMON_HORDE_PATCHER, true);

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wandering_forest_walker_7584AI(creature);
    }
};

// npc 40069
class npc_horde_poacher_40069 : public CreatureScript
{
public:
    npc_horde_poacher_40069() : CreatureScript("npc_horde_poacher_40069") {}

    enum quest_enums
    {
        SPELL_RALLY_WILD_HIPPOGRYFF = 74674,
        SPELL_NET_6533 = 6533,
        SPELL_AIMED_SHOT = 78841,
        SPELL_SHOT = 6660,
        SPELL_FORCE_PLAYER_TO_SUMMON_HORDE_PATCHER = 74728,
        NPC_HORDE_POACHER = 40069,
        NPC_FORCES_01_HIPPOGRYPH_KILL_CREDIT_BUNNY,
    };

    struct npc_horde_poacher_40069AI : public ScriptedAI
    {
        npc_horde_poacher_40069AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        uint64    _playerGUID;
        bool      _cd_spell_net;
        bool      _cd_spell_shot;
        bool      _cd_spell_aimed_shot;
        bool      _talk_done;

        void Initialize()
        {
        }

        void Reset() override
        {
            _playerGUID = 0;
            _cd_spell_net = false;
            _cd_spell_shot = false;
            _cd_spell_aimed_shot = false;
            _talk_done = false;
            me->setFaction(14);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                _playerGUID = player->GetGUID();
                _events.ScheduleEvent(EVENT_START_FIGHT, 500);
                if (me->GetDistance(player) < 20.0f)
                    me->CastSpell(player, SPELL_NET_6533, true);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->GetHealthPct() < 30.0f)
                if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                {
                    if (!_talk_done)
                        Talk(0);
                    _talk_done = true;
                    me->AttackStop();
                    me->GetMotionMaster()->MoveFleeing(player, 5000);
                    _events.RescheduleEvent(EVENT_CHECK_FOR_HEALTH, 5000);
                }
        }

        void EnterEvadeMode() 
        {
            if (_playerGUID)
                me->DespawnOrUnsummon(10);
        };

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId) // manage different abilities
                {
                case EVENT_START_FIGHT:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                    {
                        SpellCastNet(player);
                        me->SetWalk(true);
                        me->Attack(player, true);
                    }
                    break;
                }
                case EVENT_COOLDOWN_00: // net
                {
                    _cd_spell_net = false;
                    break;
                }
                case EVENT_COOLDOWN_01: // aimed shot
                {
                    _cd_spell_aimed_shot = false;
                    break;
                }
                case EVENT_COOLDOWN_02: // normal shot
                {
                    _cd_spell_shot = false;
                    break;
                }
                case EVENT_CHECK_FOR_HEALTH:
                {
                    _events.RescheduleEvent(EVENT_CHECK_ATTACK, 10);
                    break;
                }
                case EVENT_CHECK_ATTACK:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
                        if (!(_cd_spell_net | _cd_spell_aimed_shot | _cd_spell_shot))
                        {
                            if (me->GetDistance(player) > 35.0f)
                                me->Attack(player, false);
                            else if (me->GetDistance(player) > 25.0f)
                                SpellCastAimedShot(player);
                            else if (me->GetDistance(player) > 5.0f)
                                SpellCastShot(player);
                            else
                                me->Attack(player, true);
                            return;
                        }

                    _events.ScheduleEvent(EVENT_CHECK_ATTACK,1000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void SpellCastNet(Player* player)
        {
            if (!_cd_spell_net)
            {
                me->CastSpell(player, SPELL_NET_6533, true);
                _cd_spell_net = true;
                _events.ScheduleEvent(EVENT_COOLDOWN_00, 3000);
            }
        }

        void SpellCastAimedShot(Player* player)
        {
            if (!_cd_spell_aimed_shot)
            {
                me->CastSpell(player, SPELL_AIMED_SHOT, true);
                _cd_spell_aimed_shot = true;
                _events.ScheduleEvent(EVENT_COOLDOWN_01, 11000);
            }
        }

        void SpellCastShot(Player* player)
        {
            if (!_cd_spell_aimed_shot)
            {
                me->CastSpell(player, SPELL_SHOT, true);
                _cd_spell_shot = true;
                _events.ScheduleEvent(EVENT_COOLDOWN_02, 5000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_horde_poacher_40069AI(creature);
    }
};

void AddSC_zone_feralas()
{
    new npc_feralas_wisp_40079();
    new npc_feralas_hippogryph_5300();
    new npc_wandering_forest_walker_7584();
    new npc_horde_poacher_40069();

}

