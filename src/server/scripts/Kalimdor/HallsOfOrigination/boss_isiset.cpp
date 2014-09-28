#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"
#include "WorldPacket.h"

class OrientationCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit OrientationCheck(Unit* _caster) : caster(_caster) { }
        bool operator() (WorldObject* object) const
        {
            Unit* unit = object->ToUnit();
            return !caster->isInFront(unit, 2.5f) ? true : false;
        }

    private:
        Unit* caster;
};

enum Yells
{
    SAY_AGGRO      = 0,
    SAY_SUPERNOVA  = 1,
    SAY_KILL       = 2,
    SAY_DEATH      = 3,
    SAY_SPLIT      = 4
};

enum Spells
{
    SPELL_SUPERNOVA             = 74136,// requires a spell link
    SPELL_ASTRAL_RAIN_P1        = 74135,
    SPELL_ASTRAL_RAIN_P2        = 74366,
    SPELL_ASTRAL_RAIN_P3        = 74370,
    SPELL_CELESTIAL_CALL_P1     = 74362,
    SPELL_CELESTIAL_CALL_P2     = 74355,
    SPELL_CELESTIAL_CALL_P3     = 74364,
    SPELL_VEIL_OF_SKY_P1        = 74133,
    SPELL_VEIL_OF_SKY_P2        = 74372,
    SPELL_VEIL_OF_SKY_P3        = 74373,
    SPELL_ARCANE_BARRAGE        = 74374,
    SPELL_ARCANE_BARRAGE_H      = 89886,
    SPELL_VEIL_SKY              = 74133,
    SPELL_VEIL_SKY_H            = 90760,
    SPELL_FAMILIAR_VISUAL       = 64367,
};

class boss_isiset : public CreatureScript
{
    public:
        boss_isiset() : CreatureScript("boss_isiset") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_isisetAI(creature);
        }

        struct boss_isisetAI : public ScriptedAI
        {
            boss_isisetAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
                SetCombatMovement(true);
            }

            std::list<uint64> SummonList;

            InstanceScript *pInstance;

            uint32 SupernovaTimer;
            uint32 AstralRainPhase3Timer;
            uint32 AstralRainPhase2Timer;
            uint32 AstralRainPhase1Timer;
            uint32 CelestialCallPhase3Timer;
            uint32 CelestialCallPhase2Timer;
            uint32 CelestialCallPhase1Timer;
            uint32 VeilOfSkyPhase3Timer;
            uint32 VeilOfSkyPhase2Timer;
            uint32 VeilOfSkyPhase1Timer;
            uint32 Phase;
            bool Phased;

            bool AstralRain, VeilOfSky, CelestialCall;

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
                RemoveSummons();
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
            }

            void Reset()
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
                RemoveSummons();
                SupernovaTimer = 15000+rand()%5000;
                AstralRainPhase3Timer = 10000;
                AstralRainPhase2Timer = 10000;
                AstralRainPhase1Timer = 10000;
                CelestialCallPhase3Timer = 25000;
                CelestialCallPhase2Timer = 25000;
                CelestialCallPhase1Timer = 25000;
                VeilOfSkyPhase3Timer = 20000;
                VeilOfSkyPhase2Timer = 20000;
                VeilOfSkyPhase1Timer = 20000;
                Phased = false;
                AstralRain = false;
                VeilOfSky = false;
                CelestialCall = false;
                Phase = 0;
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                switch(summon->GetEntry())
                {
                    case 39720: // Astral Rain
                        AstralRain = false;
                        break;
                    case 39721: // Celestial Call
                        CelestialCall = false;
                        break;
                    case 39722: // Veil of Sky
                        VeilOfSky = false;
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
                SummonList.push_back(pSummon->GetGUID());
                pSummon->AI()->DoZoneInCombat();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if(me->GetPower(POWER_MANA) <= 100)
                {
                me->RemoveAurasDueToSpell(SPELL_VEIL_OF_SKY_P1);
                me->RemoveAurasDueToSpell(SPELL_VEIL_OF_SKY_P2);
                me->RemoveAurasDueToSpell(SPELL_VEIL_OF_SKY_P3);
                }

                if (Phased == true)
                    me->SetVisible(false);

                if (Phased == false)
                    me->SetVisible(true);

                if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 66) && Phase == 0)
                {
                    me->SetPhaseMask(3, true);
                    Talk(SAY_SPLIT);
                    Phase = 1;
                    me->SetReactState(REACT_PASSIVE);
                    Phased = true;
                    AstralRain = true;
                    VeilOfSky = true;
                    CelestialCall = true;
                    Position pos = me->GetPosition();
                    me->SummonCreature(39720, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    me->SummonCreature(39721, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                }

                if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 33) && Phase == 1)
                {
                    Talk(SAY_SPLIT);
                    Phase = 2;
                    me->SetReactState(REACT_PASSIVE);
                    Phased = true;
                    Position pos = me->GetPosition();
                    if (AstralRain == false) // Make other two visible again.
                    {
                        me->SummonCreature(39721, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    }
                    if (CelestialCall == false)
                    {
                        me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        me->SummonCreature(39720, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    }
                    if (VeilOfSky == false)
                    {
                        me->SummonCreature(39720, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    }
                }

                if (Phase == 0)
                {
                    Phased = false;
                    
                    if (CelestialCallPhase1Timer <= diff)
                    {
                        DoCast(me, SPELL_CELESTIAL_CALL_P1);
                        CelestialCallPhase1Timer = 45000;
                    } else CelestialCallPhase1Timer -= diff;

                    if (VeilOfSkyPhase1Timer <= diff)
                    {
                        DoCast(me, SPELL_VEIL_OF_SKY_P1);
                        VeilOfSkyPhase1Timer = 45000;
                    } else VeilOfSkyPhase1Timer -= diff;

                    if (AstralRainPhase1Timer <= diff)
                    {
                        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P1);
                        AstralRainPhase1Timer = 10000;
                    } else AstralRainPhase1Timer -= diff;
                }

                if (Phase == 1)
                {
                    if (CelestialCall == false)
                    {
                        if(Creature* veil = me->FindNearestCreature(39722, 300, true))
                            veil->SetPhaseMask(2, true);
                        if(Creature* astral = me->FindNearestCreature(39720, 300, true))
                            astral->SetPhaseMask(2, true);
                        me->SetReactState(REACT_AGGRESSIVE);
                        Phased = false;

                        if (VeilOfSkyPhase2Timer <= diff)
                        {
                            DoCast(me, SPELL_VEIL_OF_SKY_P2);
                            VeilOfSkyPhase2Timer = 45000;
                        } else VeilOfSkyPhase2Timer -= diff;
                        
                        if (AstralRainPhase2Timer <= diff)
                        {
                            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P2);
                            AstralRainPhase2Timer = 10000;
                        } else AstralRainPhase2Timer -= diff;
                    }

                    if (VeilOfSky == false)
                    {
                        if(Creature* celestial = me->FindNearestCreature(39721, 300, true))
                            celestial->SetPhaseMask(2, true);
                        if(Creature* astral = me->FindNearestCreature(39720, 300, true))
                            astral->SetPhaseMask(2, true);
                       me->SetReactState(REACT_AGGRESSIVE);
                       Phased = false;

                        if (CelestialCallPhase2Timer <= diff)
                        {
                            DoCast(me, SPELL_CELESTIAL_CALL_P2);
                            CelestialCallPhase2Timer = 45000;
                        } else CelestialCallPhase2Timer -= diff;

                        if (AstralRainPhase2Timer <= diff)
                        {
                            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P2);
                            AstralRainPhase2Timer = 10000;
                        } else AstralRainPhase2Timer -= diff;
                    }
                    
                    if (AstralRain == false)
                    {
                        if(Creature* celestial = me->FindNearestCreature(39721, 300, true))
                            celestial->SetPhaseMask(2, true);
                        if(Creature* veil = me->FindNearestCreature(39722, 300, true))
                            veil->SetPhaseMask(2, true);
                       me->SetReactState(REACT_AGGRESSIVE);
                       Phased = false;
                       
                        if (CelestialCallPhase2Timer <= diff)
                        {
                            DoCast(me, SPELL_CELESTIAL_CALL_P2);
                            CelestialCallPhase2Timer = 45000;
                        } else CelestialCallPhase2Timer -= diff;
                    
                        if (VeilOfSkyPhase2Timer <= diff)
                        {
                            DoCast(me, SPELL_VEIL_OF_SKY_P2);
                            VeilOfSkyPhase2Timer = 45000;
                        } else VeilOfSkyPhase2Timer -= diff;
                    }
                }

                if (Phase == 2)
                {
                    if (CelestialCall == false)
                    {
                        if(Creature* veil = me->FindNearestCreature(39722, 300, true))
                            veil->SetPhaseMask(2, true);
                        if(Creature* astral = me->FindNearestCreature(39720, 300, true))
                            astral->SetPhaseMask(2, true);
                        
                        me->SetReactState(REACT_AGGRESSIVE);
                        Phased = false;
                        
                        if (VeilOfSkyPhase3Timer <= diff)
                        {
                            DoCast(me, SPELL_VEIL_OF_SKY_P3);
                            VeilOfSkyPhase3Timer = 45000;
                        } else VeilOfSkyPhase3Timer -= diff;
                        
                        if (AstralRainPhase3Timer <= diff)
                        {
                            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P3);
                            AstralRainPhase3Timer = 10000;
                        } else AstralRainPhase3Timer -= diff;
                    }

                    if (VeilOfSky == false)
                    {
                        if(Creature* celestial = me->FindNearestCreature(39721, 300, true))
                            celestial->SetPhaseMask(2, true);
                        if(Creature* astral = me->FindNearestCreature(39720, 300, true))
                            astral->SetPhaseMask(2, true);
                       
                       me->SetReactState(REACT_AGGRESSIVE);
                       Phased = false;

                        if (CelestialCallPhase3Timer <= diff)
                        {
                            DoCast(me, SPELL_CELESTIAL_CALL_P3);
                            CelestialCallPhase3Timer = 45000;
                        } else CelestialCallPhase3Timer -= diff;
                
                        if (AstralRainPhase3Timer <= diff)
                        {
                            DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P3);
                            AstralRainPhase3Timer = 10000;
                        } else AstralRainPhase3Timer -= diff;
                    }
                    
                    if (AstralRain == false)
                    {
                        if(Creature* celestial = me->FindNearestCreature(39721, 300, true))
                            celestial->SetPhaseMask(2, true);
                        if(Creature* veil = me->FindNearestCreature(39722, 300, true))
                            veil->SetPhaseMask(2, true);

                       me->SetReactState(REACT_AGGRESSIVE);                       
                       Phased = false;
                       
                        if (CelestialCallPhase3Timer <= diff)
                        {
                            DoCast(me, SPELL_CELESTIAL_CALL_P3);
                            CelestialCallPhase3Timer = 45000;
                        } else CelestialCallPhase3Timer -= diff;
                    
                        if (VeilOfSkyPhase3Timer <= diff)
                        {
                            DoCast(me, SPELL_VEIL_OF_SKY_P3);
                            VeilOfSkyPhase3Timer = 45000;
                        } else VeilOfSkyPhase3Timer -= diff;
                    }
                }

                if (SupernovaTimer <= diff && Phased == false)
                {
                    Talk(SAY_SUPERNOVA);
                    DoCastVictim(SPELL_SUPERNOVA);
                    SupernovaTimer = urand(25000, 35000);
                } else SupernovaTimer -= diff;

               if (Phased == false)
                DoMeleeAttackIfReady();
            }
        };
};

class spell_isiset_supernova : public SpellScriptLoader
{
    public:
        spell_isiset_supernova() : SpellScriptLoader("spell_isiset_supernova") { }
        class spell_isiset_supernova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_isiset_supernova_SpellScript);

            void FilterTargetsInitial(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(OrientationCheck(GetCaster()));

                uint32 maxSize = uint32(GetCaster()->GetMap()->GetSpawnMode() & 1 ? 5 : 5);
                if (unitList.size() > maxSize)
                    Trinity::Containers::RandomResizeList(unitList, maxSize);
            }

            void Register()
            {
               OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_isiset_supernova_SpellScript::FilterTargetsInitial, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_isiset_supernova_SpellScript();
        }
};

class npc_celestial_familiar : public CreatureScript
{
    public:
        npc_celestial_familiar() : CreatureScript("npc_celestial_familiar") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_celestial_familiarAI(creature);
        }
            
        struct npc_celestial_familiarAI : public ScriptedAI
        {
            npc_celestial_familiarAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiBarrageTimer;

            void Reset()
            {
                m_uiBarrageTimer = 1000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->SetDisplayId(25347);
                me->AddAura(SPELL_FAMILIAR_VISUAL, me);
                m_uiBarrageTimer = 1000;
            }

            void JustDied(Unit* /*killer*/)
            {
                me->RemoveAura(SPELL_FAMILIAR_VISUAL);
                me->RemoveCorpse(false);
            }

            void UpdateAI(uint32 diff)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (!UpdateVictim())
                    return;

                if (m_uiBarrageTimer <= diff)
                {
                    DoCastVictim(IsHeroic() ? SPELL_ARCANE_BARRAGE_H : SPELL_ARCANE_BARRAGE);
                    m_uiBarrageTimer = urand(2000, 3000);
                }
                else
                    m_uiBarrageTimer -= diff;
            }
        };
};

class npc_veil_sky : public CreatureScript
{
    public:
        npc_veil_sky() : CreatureScript("npc_veil_sky") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_veil_skyAI(creature);
        }
            
        struct npc_veil_skyAI : public ScriptedAI
        {
            npc_veil_skyAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiVeilSkyTimer;

            void Reset()
            {
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 100);
                m_uiVeilSkyTimer = 2000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_uiVeilSkyTimer = 2000;
            }
            
            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiVeilSkyTimer <= diff)
                {
                    DoCast(me, IsHeroic() ? SPELL_VEIL_SKY_H : SPELL_VEIL_SKY);
                    m_uiVeilSkyTimer = 60000;
                }
                else
                    m_uiVeilSkyTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_celestial_call : public CreatureScript
{
    public:
        npc_celestial_call() : CreatureScript("npc_celestial_call") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_celestial_callAI(creature);
        }
            
        struct npc_celestial_callAI : public ScriptedAI
        {
            npc_celestial_callAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiBarrageTimer;

            void Reset()
            {
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 100);
                m_uiBarrageTimer = 1000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_uiBarrageTimer = 1000;
            }
            
            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiBarrageTimer <= uiDiff)
                {
                    DoCastVictim(IsHeroic() ? SPELL_ARCANE_BARRAGE_H : SPELL_ARCANE_BARRAGE);
                    m_uiBarrageTimer = 2000;
                }
                else
                    m_uiBarrageTimer -= uiDiff;
            }
        };
};

class npc_astral_rain : public CreatureScript
{
    public:
        npc_astral_rain() : CreatureScript("npc_astral_rain") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_astral_rainAI(creature);
        }
            
        struct npc_astral_rainAI : public ScriptedAI
        {
            npc_astral_rainAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiAstralRainTimer;

            void Reset()
            {
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 100);
                m_uiAstralRainTimer = 2000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_uiAstralRainTimer = 2000;
            }
            
            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiAstralRainTimer <= uiDiff)
                {
                    Creature* CelestialCall = me->FindNearestCreature(39721, 100);
                    Creature* VeilSky = me->FindNearestCreature(39722, 100);
                    if (CelestialCall && VeilSky)
                    {
                        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P1);
                    }
                    else 
                        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN_P2);
                    m_uiAstralRainTimer = 8000;
                }
                else
                    m_uiAstralRainTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_boss_isiset()
{
    new boss_isiset();
    new spell_isiset_supernova();
    new npc_celestial_familiar();
    new npc_celestial_call();
    new npc_veil_sky();
    new npc_astral_rain();
}
