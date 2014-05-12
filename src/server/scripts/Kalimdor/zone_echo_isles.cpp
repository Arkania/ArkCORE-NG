/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Player.h"

enum eZoneEchoIsle
{
    NPC_NOVICE_DARKSPEAR_WARRIOR        = 38268,
    NPC_TIKI_TARGET                     = 38038,
    NPC_DOCILE_ISLAND_BOAR              = 38141,
    NPC_WILDMANE_CAT                    = 38046,
    NPC_DARKSPEAR_JAILOR                = 39062,
    NPC_CAPTIVE_SPIESCALE_SCOUT         = 38142,

    SPELL_LEAPING_RUSH                  = 75002,
    SPELL_SWIPE                         = 31279,
    SPELL_WILD_POUNCE                   = 71232,
};

/*######
## npc_novice_darkspear_warrior
######*/

class npc_novice_darkspear_warrior : public CreatureScript
{
public:
    npc_novice_darkspear_warrior() : CreatureScript("npc_novice_darkspear_warrior") { }

    struct npc_novice_darkspear_warriorAI : public ScriptedAI
    {
        npc_novice_darkspear_warriorAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 _timer;

        void Reset()
        {
            _timer = urand(1800,2200);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (Creature* tiki = me->FindNearestCreature (NPC_TIKI_TARGET, 3.0f))
                {
                    if (_timer <= diff)
                    {
                        me->SetFacingTo (me->GetAngle(tiki));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        _timer = urand(1800,2200);
                    }
                    else 
                        _timer -= diff;
                }
            }
            else 
                DoMeleeAttackIfReady();
            
        }
    };

       CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_novice_darkspear_warriorAI (creature);
    }
};

/*######
## npc_docile_island_boar
######*/

class npc_docile_island_boar : public CreatureScript
{
public:
    npc_docile_island_boar() : CreatureScript("npc_docile_island_boar") { }

    struct npc_docile_island_boarAI : public ScriptedAI
    {
        npc_docile_island_boarAI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;
            else 
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_docile_island_boarAI (creature);
    }
};

/*######
## npc_wildmane_cat
######*/

class npc_wildmane_cat : public CreatureScript
{
public:
    npc_wildmane_cat() : CreatureScript("npc_wildmane_cat") { }

    struct npc_wildmane_catAI : public ScriptedAI
    {
        npc_wildmane_catAI(Creature* creature) : ScriptedAI(creature) {_timer = urand(10000,60000); _phase=0;}

        uint32 _timer;
        uint32 _phase;
        Creature* _boar;

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                if (_timer <= diff)
                    DoWork();
                else 
                    _timer -= diff;
            else 
                DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        { 
            if (id != 33)
                return;

            me->GetMotionMaster()->MoveIdle();
            // ToDo: correct is SPELL_WILD_POUNCE for hold the boar down and giv cat sound
            // me->CastSpell(_boar, SPELL_WILD_POUNCE, false);
            _boar->DespawnOrUnsummon(2000);
            _phase=2;
            _timer=5000;
        }

        void DoWork()
        {
            switch (_phase)
            {
                case 0:
                    if (Creature* _boar = me->FindNearestCreature(NPC_DOCILE_ISLAND_BOAR, 10.0f))
                    {
                        _phase=1;
                        _timer = 10000;
                        // ToDo: Correct is SPELL_LEAPING_RUSH for jumping to boar
                        // me->CastSpell(_boar, SPELL_LEAPING_RUSH, true);
                        me->GetMotionMaster()->MoveJump(_boar->GetPositionX(), _boar->GetPositionY(), _boar->GetPositionZ(), 25.0f ,10.0f, 33);
                        _boar->DealDamage(_boar, _boar->GetHealth()); // kill the boar
                    }
                    else
                        _timer = 60000; // urand(60000,200000);
                    break;
                case 1:
                    _phase=0; _timer=0;
                    break;
                case 2:
                    me->GetMotionMaster()->MoveRandom(10.0f);
                    _phase=0; _timer=0;
                    break;
            }
        }
    };

       CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wildmane_catAI (creature);
    }
};

/*######
## npc_darkspear_jailor
######*/

/*class npc_darkspear_jailor : public CreatureScript
{
public:
    npc_darkspear_jailor() : CreatureScript("npc_darkspear_jailor") { }

    bool OnGossipHello(Player* player, Creature* creature) 
    {

        return true;
    }
};*/

/*######
## npc_captive_spitescale_scout
######*/

class npc_captive_spitescale_scout : public CreatureScript
{
public:
    npc_captive_spitescale_scout() : CreatureScript("npc_captive_spitescale_scout") { }


};

void AddSC_zone_echo_isles()
{
    new npc_novice_darkspear_warrior();
    new npc_docile_island_boar();
    new npc_wildmane_cat();
    // new npc_darkspear_jailor();
    new npc_captive_spitescale_scout();
};
