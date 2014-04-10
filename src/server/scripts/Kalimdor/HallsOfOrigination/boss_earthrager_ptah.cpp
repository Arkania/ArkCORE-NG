//http://www.wowhead.com/npc=40406 - This npc is summoned on the second phase, and does the camera visual.
#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"

enum Yells
{
    SAY_AGGRO          = 0,
    SAY_DEATH          = 1,
    SAY_KILL           = 2,
};

enum Spells
{
    SPELL_FLAME_BOLT                         = 77370, //this does not work! - can't find spells - well i did anyway have a look
    SPELL_FLAME_BOLT_TARGET                  = 73853,
    SPELL_BLAZE_N                            = 93212,
    SPELL_BLAZE_H                            = 93214, //this is gonna have it's own separate script
    SPELL_RAGING_SMASH                       = 83650,
    SPELL_EARTH_SPIKE                        = 94974, // Dummy and if not run die. 95729 is something else.
    SPELL_QUICKSAND_SLOW                     = 75548,
    SPELL_QUICKSAND_DMG                      = 75546,
    SPELL_SMASH                              = 75453,
    SPELL_SAND_VORTEX                        = 78515, // sand vortex casts this on itself - spell link with 79441
    SPELL_SAND_VORTEX_KNOCKBACK              = 83097,
    SPELL_VORTEX_VISUAL                      = 79441,
    SPELL_EARTHQUAKE_VISUAL                  = 73238,
    SPELL_DEAD                               = 81238, // Dead look.
    
    // Earthrager Ptah
    SPELL_SELF_ROOT                          = 42716,
    SPELL_CANNOT_TURN                        = 95544,
};

enum BossPhases
{
    PHASE_NORMAL = 1,
    PHASE_50_PER = 2,
};

const Position SpawnPosition[] =
{
    {-542.85f, -389.745f, 158.871f},
    {-526.344f, -430.457f, 155.513f},
    {-521.232f, -376.484f, 156.975f},
    {-516.064f, -405.301f, 155.591f},
    {-503.511f, -373.971f, 155.352f},
    {-493.174f, -433.977f, 156.578f},
    {-479.587f, -398.807f, 156.877f},
    {-475.642f, -423.303f, 158.438f}
};

class boss_earthrager_ptah : public CreatureScript
{
    public:
        boss_earthrager_ptah() : CreatureScript("boss_earthrager_ptah") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_earthrager_ptahAI(pCreature);
        }
        struct boss_earthrager_ptahAI : public ScriptedAI
        {
            boss_earthrager_ptahAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            std::list<uint64> SummonList;

            InstanceScript *pInstance;

            uint8 Phase;
            bool Phased;
            uint8 SpawnCount;
            uint8 PhaseCount;

            uint32 FlameBoltTimer;
            uint32 RagingSmashTimer;
            uint32 EarthSpikeTimer;
            uint32 QuickSandTimer;

            void Reset()
            {
                if(pInstance)
                   pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, NOT_STARTED);

                Phase = PHASE_NORMAL;
                Phased = false;
                PhaseCount = 0;
                FlameBoltTimer = 7000;
                RagingSmashTimer = 4000;
                EarthSpikeTimer = 12000;
                RemoveSummons();
                if(me->HasAura(SPELL_SELF_ROOT))
                {
                    me->RemoveAura(SPELL_SELF_ROOT);
                    me->RemoveAura(SPELL_CANNOT_TURN);
                }
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
                me->RemoveAurasDueToSpell(SPELL_DEAD); // Dead look
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                switch(summon->GetEntry())
                {
                    case NPC_DUSTBONE_HORROR:
                    case NPC_JEWELED_SCARAB:
                        SpawnCount--;
                        break;
                }
            }

            void RemoveSummons()
            {
                if (SummonList.empty())
                    return;

                for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                {
                    if (Creature* pTemp = Unit::GetCreature(*me, *itr))
                        if (pTemp)
                            pTemp->DisappearAndDie();
                }
                SummonList.clear();
            }

            void JustSummoned(Creature* pSummon)
            {
                switch (pSummon->GetEntry())
                {
                    case NPC_DUSTBONE_HORROR:
                    case NPC_JEWELED_SCARAB:
                        if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            pSummon->AI()->AttackStart(pTarget);
                        SummonList.push_back(pSummon->GetGUID());
                        break;
                }
                SummonList.push_back(pSummon->GetGUID());
            }

            void ChangePhase()
            {
                QuickSandTimer = 1000;
                me->AddAura(SPELL_DEAD, me); // Dead
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                Phased = true;
 
                DoCastAOE(SPELL_EARTHQUAKE_VISUAL);
                me->AddAura(SPELL_SELF_ROOT, me);
                DoCast(me, SPELL_CANNOT_TURN);
                SendWeather(WEATHER_STATE_LIGHT_SANDSTORM, 1.0f);
                SpawnCount = 8;
                
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_EARTH_SPIKE))
                    target->CastSpell(target, SPELL_EARTHQUAKE_VISUAL,1);

                for(uint32 x = 0; x<6; ++x)
                    me->SummonCreature(NPC_JEWELED_SCARAB, SpawnPosition[x], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);

                for(uint32 x = 0; x<2; ++x)
                    me->SummonCreature(NPC_DUSTBONE_HORROR, SpawnPosition[6+x], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);

                me->SummonCreature(42087, me->GetPositionX()+5, me->GetPositionY()+5, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 30000);
                
                PhaseCount++;
                Phase = PHASE_50_PER;
            }

            void SendWeather(WeatherState weather, float grade) const
            {
                WorldPacket data(SMSG_WEATHER, 9);
                data << uint32(weather);
                data << float(grade);
                data << uint8(0);
                SendPacketToPlayers(&data);
            }
            
            // Send packet to all players in Tomb of the Earthrager
            void SendPacketToPlayers(WorldPacket const* data) const
            {
                Map::PlayerList const& players = me->GetMap()->GetPlayers();
                if (!players.isEmpty())
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                            if (player->GetAreaId() == AREA_TOMB_OF_THE_EARTHRAGER)
                                player->GetSession()->SendPacket(data);
            }

            void KilledUnit(Unit* /*Killed*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*Kill*/)
            {
                Talk(SAY_DEATH);
                if (pInstance)
                    pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, DONE);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
            }

            void EnterEvadeMode()
            {
                if (pInstance)
                    pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, FAIL);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
                if(me->HasAura(SPELL_SELF_ROOT))
                {
                    me->RemoveAura(SPELL_SELF_ROOT);
                    me->RemoveAura(SPELL_CANNOT_TURN);
                }
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                Talk(SAY_AGGRO);
                if (pInstance)
                    pInstance->SetData(DATA_EARTHRAGER_PTAH_EVENT, IN_PROGRESS);
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                   return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                   return;
                
                if (me->HealthBelowPct(51) && Phase == PHASE_NORMAL && PhaseCount == 0)
                {
                    ChangePhase();
                }

                if (SpawnCount == 0 && Phase == PHASE_50_PER && PhaseCount == 1)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->RemoveAurasDueToSpell(SPELL_DEAD); // Dead Look
                    me->RemoveAura(SPELL_SELF_ROOT);
                    me->RemoveAura(SPELL_CANNOT_TURN);

                    Phase = PHASE_NORMAL;
                    Phased = false;
                    SendWeather(WEATHER_STATE_SUNNY, 0.0f);
                    FlameBoltTimer = urand(7000, 11000);
                    RagingSmashTimer = 4000;
                    EarthSpikeTimer = 12000;
                }

                if(Phase == PHASE_NORMAL)
                {
                    if (FlameBoltTimer <= diff)
                    {
                        DoCastAOE(SPELL_FLAME_BOLT);
                        me->CastCustomSpell(DUNGEON_MODE<int32>(SPELL_BLAZE_N, SPELL_BLAZE_H), SPELLVALUE_MAX_TARGETS, DUNGEON_MODE<int32>(2, 5), NULL);    
                        FlameBoltTimer = urand(13000, 15000);
                    } else FlameBoltTimer -= diff;
                    
                    if (RagingSmashTimer <= diff)
                    {
                        DoCastVictim(SPELL_RAGING_SMASH);
                        RagingSmashTimer = urand(8000, 11000);
                    } else RagingSmashTimer -= diff;
                    
                    if (EarthSpikeTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_EARTH_SPIKE);
                        EarthSpikeTimer = 15000;
                    } else EarthSpikeTimer -= diff;
                }

                if(Phase == PHASE_50_PER)
                {
                    if (QuickSandTimer <= diff)
                    {
                        if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            Creature* Quicksand = me->SummonCreature(40503, victim->GetPositionX() + urand(3, 9), victim->GetPositionY() + urand(3, 9), victim->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, IsHeroic() ? 15000 : 24000);
                            DoZoneInCombat(Quicksand);
                        }
                        QuickSandTimer = 10000;
                    }
                    else
                        QuickSandTimer -= diff;
                }
                
                DoMeleeAttackIfReady();
            }
        };
};

class npc_horror : public CreatureScript
{
    public:
        npc_horror() : CreatureScript("npc_horror") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_horrorAI(pCreature);
        }
            
        struct npc_horrorAI : public ScriptedAI
        {
            npc_horrorAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiSmashTimer;

            void Reset()
            {
                m_uiSmashTimer = urand(5000, 10000);
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiSmashTimer = urand(5000, 10000);
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiSmashTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), SPELL_SMASH);
                    m_uiSmashTimer = urand(7000, 12000);
                }
                else
                    m_uiSmashTimer -= uiDiff;
                DoMeleeAttackIfReady();
            }
        };
};

class npc_quicksand : public CreatureScript
{
    public:
        npc_quicksand() : CreatureScript("npc_quicksand") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_quicksandAI(pCreature);
        }
            
        struct npc_quicksandAI : public ScriptedAI
        {
            npc_quicksandAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            
            void Reset()
            {
                DoCast(me, SPELL_QUICKSAND_SLOW);
                DoCast(me, SPELL_QUICKSAND_DMG);
            }

            void EnterCombat(Unit* pWho)
            {
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
            }
        };
};
class npc_sandstorm : public CreatureScript
{
    public:
        npc_sandstorm() : CreatureScript("npc_sandstorm") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_sandstormAI(pCreature);
        }
            
        struct npc_sandstormAI : public ScriptedAI
        {
            npc_sandstormAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                me->setFaction(16);
                me->SetSpeed(MOVE_RUN, 0.6f);
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiDamageTimer;
            uint32 m_uiKnockbackTimer;
            
            void Reset()
            {
                m_uiKnockbackTimer = 8000;
                DoCast(me, SPELL_SAND_VORTEX);
                DoCast(me, SPELL_VORTEX_VISUAL);
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiKnockbackTimer = 1000;
                DoCast(me, SPELL_SAND_VORTEX);
                DoCast(me, SPELL_VORTEX_VISUAL);            
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
                if(m_uiKnockbackTimer <= uiDiff)
                {
                    DoCastAOE(SPELL_SAND_VORTEX_KNOCKBACK);
                    m_uiKnockbackTimer = 1000;
                    float x,y,randx,randy;
                    randx = 0.0f + rand()%60;
                    randy = 0.0f + rand()%60;
                    x = 210+ randx ;
                    y = -60- randy ;
                    me->GetMotionMaster()->MovePoint(1,x,y,me->GetPositionZ());
                }
                else
                    m_uiKnockbackTimer -= uiDiff;
            }
        };
};
void AddSC_boss_earthrager_ptah()
{
    new boss_earthrager_ptah();
    new npc_quicksand();
    new npc_horror();
    new npc_sandstorm();
}
