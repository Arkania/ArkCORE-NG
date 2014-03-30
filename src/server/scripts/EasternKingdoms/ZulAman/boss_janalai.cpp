/*
 * Copyright (C) 2014 Arkania Project
 *
 * This file is NOT free software. You may NOT copy, redistribute it or modify it.
 */

/* ScriptData
SDName: Boss_Janalai 4.1
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman 5 Hc
EndScriptData */

#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"
#include "Weather.h"

#include "zulaman.h"

enum Yells
{
    SAY_AGGRO                   = -1568000,
    SAY_FIRE_BOMBS              = -1568001,
    SAY_SUMMON_HATCHER          = -1568002,
    SAY_ALL_EGGS                = -1568003,
    SAY_BERSERK                 = -1568004,
    SAY_SLAY_1                  = -1568005,
    SAY_SLAY_2                  = -1568006,
    SAY_DEATH                   = -1568007,
    SAY_EVENT_STRANGERS         = -1568008,
    SAY_EVENT_FRIENDS           = -1568009
};

enum Spells
{
// Jan'alai
    SPELL_FLAME_BREATH          = 43140,
    SPELL_SUMMON_BREATH_LINE    = 97497,
    SPELL_FIRE_WALL             = 43113,
    SPELL_ENRAGE                = 44779,
    SPELL_SUMMON_PLAYERS        = 43097,
    SPELL_TELE_TO_CENTER        = 43098,
    SPELL_HATCH_ALL             = 43144,
    SPELL_BERSERK               = 45078,

// -- Fire Bob Spells
    SPELL_FIRE_BOMB_CHANNEL     = 42621, // last forever
    SPELL_FIRE_BOMB_THROW       = 42628, // throw visual
    SPELL_FIRE_BOMB_DUMMY       = 42629, // bomb visual
    SPELL_FIRE_BOMB_DAMAGE      = 42630,

// -- Hatcher Spells
    SPELL_HATCH_EGG             = 43734,
    SPELL_SUMMON_HATCHLING      = 42493,

// -- Hatchling Spells
    SPELL_FLAMEBUFFET           = 43299
};

enum Mobs
{
    MOB_AMANI_HATCHER           = 23818,
    MOB_HATCHLING               = 23598,   // 42493
    MOB_EGG                     = 23817,
    MOB_FIRE_BOMB               = 23920
};

const int area_dx = 44;
const int area_dy = 51;

float JanalainPos[1][3] =
{
    {-33.93f, 1149.27f, 19}
};

float FireWallCoords[4][4] =
{
    {-10.13f, 1149.27f, 19, 3.1415f},
    {-33.93f, 1123.90f, 19, 0.5f*3.1415f},
    {-54.80f, 1150.08f, 19, 0},
    {-33.93f, 1175.68f, 19, 1.5f*3.1415f}
};

float hatcherway[2][5][3] =
{
    {
        {-87.46f, 1170.09f, 6},
        {-74.41f, 1154.75f, 6},
        {-52.74f, 1153.32f, 19},
        {-33.37f, 1172.46f, 19},
        {-33.09f, 1203.87f, 19}
    },
    {
        {-86.57f, 1132.85f, 6},
        {-73.94f, 1146.00f, 6},
        {-52.29f, 1146.51f, 19},
        {-33.57f, 1125.72f, 19},
        {-34.29f, 1095.22f, 19}
    }
};

enum Actions
{
    ACTION_DECREASE_EGG_NUMBER = 1
};

enum Doors
{
    JINALAI_FIRE_DOOR = 186859
};

class boss_janalai : public CreatureScript
{
public:
    boss_janalai() : CreatureScript("boss_janalai") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_janalaiAI(creature);
    }

    struct boss_janalaiAI : public BossAI
    {
        boss_janalaiAI(Creature* creature) : BossAI(creature, DATA_JANALAIEVENT)
        {
            instance = creature->GetInstanceScript();
            introDone = false;
        }

        InstanceScript* instance;

        uint32 FireBreathTimer;
        uint32 BombTimer;
        uint32 BombSequenceTimer;
        uint32 BombCount;
        uint32 HatcherTimer;
        uint32 EnrageTimer;
        uint32 EggNumber;

        bool enraged, isBombing, isFlameBreathing, introDone;

        uint64 FireBombGUIDs[40];

        void Reset()
        {
            if (instance)
                instance->SetData(DATA_JANALAIEVENT, NOT_STARTED);

            FireBreathTimer = 8000;
            BombTimer = 30000;
            BombSequenceTimer = 1000;
            BombCount = 0;
            HatcherTimer = 10000;
            EggNumber = 36;
            EnrageTimer = MINUTE*5*IN_MILLISECONDS;

            isBombing = false;
            enraged = false;

            isFlameBreathing = false;

            for (uint8 i = 0; i < 40; ++i)
                FireBombGUIDs[i] = 0;

            std::list<GameObject*> doorList;
            me->GetGameObjectListWithEntryInGrid(doorList, JINALAI_FIRE_DOOR, 50.0f);
            if (!doorList.empty())
            {
                for (std::list<GameObject*>::const_iterator itr = doorList.begin(); itr != doorList.end(); ++itr)
                    (*itr)->SetGoState(GO_STATE_ACTIVE);
            }

            _Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && me->IsWithinDistInMap(who, 30) && who->GetTypeId() == TYPEID_PLAYER)
            {
                DoScriptText(RAND(SAY_EVENT_STRANGERS, SAY_EVENT_FRIENDS), me);
                introDone = true;
            }
        }

        void DoAction(const int32 action)
        {
            switch(action)
            {
                case ACTION_DECREASE_EGG_NUMBER:
                    EggNumber--;
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            if (instance)
            {
                instance->SetData(DATA_JANALAIEVENT, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            std::list<GameObject*> doorList;
            me->GetGameObjectListWithEntryInGrid(doorList, JINALAI_FIRE_DOOR, 50.0f);
            if (!doorList.empty())
            {
                for (std::list<GameObject*>::const_iterator itr = doorList.begin(); itr != doorList.end(); ++itr)
                    if ((*itr)->GetGoState() == GO_STATE_READY)
                        (*itr)->SetGoState(GO_STATE_ACTIVE);
            }

            _JustDied();
        }

        void EnterEvadeMode()
        {
            Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            DespawnCreatures(MOB_HATCHLING);
            DespawnCreatures(MOB_AMANI_HATCHER);
            RespawnCreatures(MOB_EGG);

            if (instance)
            {
                instance->SetBossState(DATA_JANALAIEVENT, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (instance)
            {
                instance->SetData(DATA_JANALAIEVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            std::list<GameObject*> doorList;
            me->GetGameObjectListWithEntryInGrid(doorList, JINALAI_FIRE_DOOR, 50.0f);
            if (!doorList.empty())
            {
                for (std::list<GameObject*>::const_iterator itr = doorList.begin(); itr != doorList.end(); ++itr)
                    (*itr)->SetGoState(GO_STATE_READY);
            }

            _EnterCombat();
        }

        void DamageDealt(Unit* target, uint32 &damage, DamageEffectType /*damagetype*/)
        {
            if (isFlameBreathing)
            {
                if (!me->HasInArc(M_PI/6, target))
                    damage = 0;
            }
        }

        void FireWall()
        {
            uint8 WallNum;
            Creature* wall = NULL;
            for (uint8 i = 0; i < 4; ++i)
            {
                if (i == 0 || i == 2)
                    WallNum = 3;
                else
                    WallNum = 2;

                for (uint8 j = 0; j < WallNum; j++)
                {
                    if (WallNum == 3)
                        wall = me->SummonCreature(MOB_FIRE_BOMB, FireWallCoords[i][0], FireWallCoords[i][1]+5*(j-1), FireWallCoords[i][2], FireWallCoords[i][3], TEMPSUMMON_TIMED_DESPAWN, 15000);
                    else
                        wall = me->SummonCreature(MOB_FIRE_BOMB, FireWallCoords[i][0]-2+4*j, FireWallCoords[i][1], FireWallCoords[i][2], FireWallCoords[i][3], TEMPSUMMON_TIMED_DESPAWN, 15000);
                    if (wall) wall->CastSpell(wall, SPELL_FIRE_WALL, true);
                }
            }
        }

        void SpawnBombs()
        {
            float dx, dy;
            for (int i(0); i < 40; ++i)
            {
                dx = float(irand(-area_dx/2, area_dx/2));
                dy = float(irand(-area_dy/2, area_dy/2));

                Creature* bomb = DoSpawnCreature(MOB_FIRE_BOMB, dx, dy, 0, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
                if (bomb)
                    FireBombGUIDs[i] = bomb->GetGUID();
            }
            BombCount = 0;
        }

        void HatchAllEggs()
        {
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);

            {
                CellCoord pair(Trinity::ComputeCellCoord(x, y));
                Cell cell(pair);
                cell.SetNoCreate();

                Trinity::AllCreaturesOfEntryInRange check(me, MOB_EGG, 100);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, templist, check);
                TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange>, GridTypeMapContainer> cSearcher(searcher);
                cell.Visit(pair, cSearcher, *me->GetMap(), *me, me->GetGridActivationRange());
            }

            if (templist.empty())
                return;

            for (std::list<Creature*>::const_iterator i = templist.begin(); i != templist.end(); ++i)
                (*i)->CastSpell(*i, SPELL_SUMMON_HATCHLING, false);
        }

        void Boom()
        {
            std::list<Creature*> templist;
            float x, y, z;
            me->GetPosition(x, y, z);

            {
                CellCoord pair(Trinity::ComputeCellCoord(x, y));
                Cell cell(pair);
                cell.SetNoCreate();

                Trinity::AllCreaturesOfEntryInRange check(me, MOB_FIRE_BOMB, 100);
                Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, templist, check);
                TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange>, GridTypeMapContainer> cSearcher(searcher);
                cell.Visit(pair, cSearcher, *me->GetMap(), *me, me->GetGridActivationRange());
            }
            for (std::list<Creature*>::const_iterator i = templist.begin(); i != templist.end(); ++i)
            {
               (*i)->CastSpell(*i, SPELL_FIRE_BOMB_DAMAGE, true);
               (*i)->RemoveAllAuras();
            }
        }

        void HandleBombSequence()
        {
            if (BombCount < 40)
            {
                if (Unit* FireBomb = Unit::GetUnit(*me, FireBombGUIDs[BombCount]))
                {
                    FireBomb->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoCast(FireBomb, SPELL_FIRE_BOMB_THROW, true);
                    FireBomb->CastSpell(FireBomb, SPELL_FIRE_BOMB_DUMMY, true);
                    FireBomb->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
                ++BombCount;
                if (BombCount == 40)
                {
                    BombSequenceTimer = 5000;
                } else BombSequenceTimer = 100;
            }
            else
            {
                Boom();
                isBombing = false;
                BombTimer = urand(20000, 40000);
                me->RemoveAurasDueToSpell(SPELL_FIRE_BOMB_CHANNEL);
                if (EnrageTimer <= 10000)
                    EnrageTimer = 0;
                else
                    EnrageTimer -= 10000;

                std::list<GameObject*> doorList;
                me->GetGameObjectListWithEntryInGrid(doorList, JINALAI_FIRE_DOOR, 50.0f);
                if (!doorList.empty())
                {
                    for (std::list<GameObject*>::const_iterator itr = doorList.begin(); itr != doorList.end(); ++itr)
                        (*itr)->SetGoState(GO_STATE_ACTIVE);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (isFlameBreathing)
            {
                if (!me->IsNonMeleeSpellCasted(false))
                    isFlameBreathing = false;
                else
                    return;
            }

            if (isBombing)
            {
                if (BombSequenceTimer <= diff)
                    HandleBombSequence();
                else
                    BombSequenceTimer -= diff;
                return;
            }

            //enrage if under 25% hp before 5 min.
            if (!enraged && HealthBelowPct(25))
                EnrageTimer = 0;

            if (EnrageTimer <= diff)
            {
                if (!enraged)
                {
                    DoCast(me, SPELL_ENRAGE, true);
                    enraged = true;
                    EnrageTimer = 300000;
                }
                else
                {
                    DoScriptText(SAY_BERSERK, me);
                    DoCast(me, SPELL_BERSERK, true);
                    EnrageTimer = 300000;
                }
            } else EnrageTimer -= diff;

            if (BombTimer <= diff)
            {
                DoScriptText(SAY_FIRE_BOMBS, me);

                std::list<GameObject*> doorList;
                me->GetGameObjectListWithEntryInGrid(doorList, JINALAI_FIRE_DOOR, 50.0f);
                if (!doorList.empty())
                {
                    for (std::list<GameObject*>::const_iterator itr = doorList.begin(); itr != doorList.end(); ++itr)
                        (*itr)->SetGoState(GO_STATE_READY);
                }

                me->AttackStop();
                me->GetMotionMaster()->Clear();
                DoTeleportTo(JanalainPos[0][0], JanalainPos[0][1], JanalainPos[0][2]);
                me->StopMoving();
                DoCast(me, SPELL_FIRE_BOMB_CHANNEL, false);

                FireWall();
                SpawnBombs();
                isBombing = true;
                BombSequenceTimer = 100;

                //Teleport every Player into the middle
                Map* map = me->GetMap();
                if (!map->IsDungeon())
                    return;

                Map::PlayerList const &PlayerList = map->GetPlayers();
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player* i_pl = i->GetSource())
                        if (i_pl->IsAlive())
                            DoTeleportPlayer(i_pl, JanalainPos[0][0]-5+rand()%10, JanalainPos[0][1]-5+rand()%10, JanalainPos[0][2], 0);
                return;
            } else BombTimer -= diff;

            if (HealthBelowPct(35) && EggNumber > 0)
            {
                DoScriptText(SAY_ALL_EGGS, me);

                me->AttackStop();
                me->GetMotionMaster()->Clear();
                DoTeleportTo(JanalainPos[0][0], JanalainPos[0][1], JanalainPos[0][2]);
                me->StopMoving();
                DoCast(me, SPELL_HATCH_ALL, false);
                HatchAllEggs();
                EggNumber = 0;
            }

            if (HatcherTimer <= diff)
            {
                if (EggNumber > 0)
                {
                    DoScriptText(SAY_SUMMON_HATCHER, me);
                    me->SummonCreature(MOB_AMANI_HATCHER, hatcherway[0][0][0], hatcherway[0][0][1], hatcherway[0][0][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    me->SummonCreature(MOB_AMANI_HATCHER, hatcherway[1][0][0], hatcherway[1][0][1], hatcherway[1][0][2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                }
                HatcherTimer = 90000;
            } else HatcherTimer -= diff;

            if (FireBreathTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    me->AttackStop();
                    me->GetMotionMaster()->Clear();

                    for (uint8 i = 0; i < 7; i++)
                    {
                        float x, y, z;
                        me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 1.0f + (4 * i));
                        me->CastSpell(x, y, z, SPELL_SUMMON_BREATH_LINE, true);
                    }

                    DoCast(target, SPELL_FLAME_BREATH);
                    me->StopMoving();
                    isFlameBreathing = true;
                }
                FireBreathTimer = 8000;
            } else FireBreathTimer -= diff;

            EnterEvadeIfOutOfCombatArea(diff);

            DoMeleeAttackIfReady();
        }

        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void RespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                if ((*iter)->IsDead())
                    (*iter)->Respawn();

                if((*iter)->GetDisplayId() == 11686)
                    (*iter)->SetDisplayId(10056);
            }
        }
    };
};

class npc_janalai_firebomb : public CreatureScript
{
public:
    npc_janalai_firebomb() : CreatureScript("npc_janalai_firebomb") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_janalai_firebombAI(creature);
    }

    struct npc_janalai_firebombAI : public ScriptedAI
    {
        npc_janalai_firebombAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;

        void UpdateAI(const uint32 /*diff*/) {}
    };
};

class npc_janalai_hatcher : public CreatureScript
{
public:
    npc_janalai_hatcher() : CreatureScript("npc_janalai_hatcher") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_janalai_hatcherAI(creature);
    }

    struct npc_janalai_hatcherAI : public ScriptedAI
    {
        npc_janalai_hatcherAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 waypoint;
        uint32 WaitTimer;
        uint32 HatchTimer;

        bool side, isHatching;

        void Reset()
        {
            me->SetWalk(true);
            side = (me->GetPositionY() < 1150);
            waypoint = 0;
            isHatching = false;
            WaitTimer = 1;
            HatchTimer = 1500;
        }

        void HatchEgg()
        {
            if (Creature* Egg = me->FindNearestCreature(23817, 40.0f, true))
               Egg->CastSpell(Egg, SPELL_SUMMON_HATCHLING, false);
            else me->DisappearAndDie();
        }

        void MovementInform(uint32, uint32)
        {
            if (waypoint == 5)
            {
                isHatching = true;
                me->SetFacingTo(side ? 1.52f : 4.71f);
            }
            else
                WaitTimer = 1;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance || !(instance->GetData(DATA_JANALAIEVENT) == IN_PROGRESS))
            {
                me->DisappearAndDie();
                return;
            }

            if (!isHatching && WaitTimer)
            {
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(0, hatcherway[side][waypoint][0], hatcherway[side][waypoint][1], hatcherway[side][waypoint][2]);
                ++waypoint;
                WaitTimer = 0;
            }

            if (HatchTimer <= diff)
            {
                if (isHatching)
                {
                    DoCast(me, SPELL_HATCH_EGG);
                    for (uint8 i = 0; i < 3; i++)
                        HatchEgg();
                    HatchTimer = urand(5000, 7500);
                }
                else HatchTimer = 1500;
            } else HatchTimer -= diff;
        }
    };
};

class npc_janalai_hatchling : public CreatureScript
{
public:
    npc_janalai_hatchling() : CreatureScript("npc_janalai_hatchling") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_janalai_hatchlingAI(creature);
    }

    struct npc_janalai_hatchlingAI : public ScriptedAI
    {
        npc_janalai_hatchlingAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 BuffetTimer;

        void Reset()
        {
            BuffetTimer = 7000;
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (me->GetPositionY() > 1150)
                me->GetMotionMaster()->MovePoint(0, hatcherway[0][3][0]+rand()%4-2, 1150.0f+rand()%4-2, hatcherway[0][3][2]);
            else
                me->GetMotionMaster()->MovePoint(0, hatcherway[1][3][0]+rand()%4-2, 1150.0f+rand()%4-2, hatcherway[1][3][2]);
        }

        void EnterCombat(Unit* /*who*/) {/*DoZoneInCombat();*/}

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (BuffetTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_FLAMEBUFFET, false);
                BuffetTimer = 10000;
            } else BuffetTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_janalai_egg : public CreatureScript
{
public:
    npc_janalai_egg(): CreatureScript("npc_janalai_egg") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_janalai_eggAI(creature);
    }

    struct npc_janalai_eggAI : public ScriptedAI
    {
        npc_janalai_eggAI(Creature* creature) : ScriptedAI(creature){}

        void Reset() {}
        void EnterCombat(Unit* /*who*/) {}
        void UpdateAI(const uint32 diff) {}
        void MoveInLineOfSight(Unit* who) {}
    };
};

void AddSC_boss_janalai()
{
    new boss_janalai();
    new npc_janalai_firebomb();
    new npc_janalai_hatcher();
    new npc_janalai_hatchling();
    new npc_janalai_egg();
}