#include "bot_ai.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
/*
Hunter NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - around 35%
TODO:
*/
typedef UNORDERED_MAP<uint32 /*spellId*/, int32 /*manaCost*/> ManaRestoreList;
ManaRestoreList TotH;
class hunter_bot : public CreatureScript
{
public:
    hunter_bot() : CreatureScript("hunter_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new hunter_botAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        return bot_minion_ai::OnGossipHello(player, creature);
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (bot_minion_ai* ai = creature->GetBotMinionAI())
            return ai->OnGossipSelect(player, creature, sender, action);
        return true;
    }

    struct hunter_botAI : public bot_minion_ai
    {
        hunter_botAI(Creature* creature) : bot_minion_ai(creature)
        {
            Reset();
        }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_HUNTER) != SPELL_CAST_OK)
                return false;

            return bot_ai::doCast(victim, spellId, triggered);
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force, true);
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }
        void DoNonCombatActions(uint32 /*diff*/) { }

        void Counter(uint32 diff)
        {
            if (IsCasting() || Rand() > 35)
                return;

            Unit* target = NULL;

            if (SCATTER_SHOT && ScatterShot_cd <= 10000 && Rand() < 40)
            {
                target = FindCastingTarget(15, 0, false, SCATTER_SHOT);
                temptimer = GC_Timer;
                if (target && doCast(target, SCATTER_SHOT))
                {
                    ScatterShot_cd = 20000;
                    GC_Timer = temptimer;
                    return;
                }
            }
            if (!target && WYVERN_STING && WyvernSting_cd <= 20000 && GC_Timer <= diff && Rand() < 70)
            {
                target = FindCastingTarget(35, 5, false, WYVERN_STING);
                if (target && doCast(target, WYVERN_STING))
                {
                    WyvernSting_cd = 40000;
                    return;
                }
            }
            //if (!target && FREEZING_ARROW && Trap_cd <= 10000 && Rand() < 40)
            //{
            //    target = FindCastingTarget(40, 0, false, FREEZING_ARROW);
            //    temptimer = GC_Timer;
            //    if (target && doCast(target, FREEZING_ARROW))
            //    {
            //        Trap_cd = 20000;
            //        GC_Timer = temptimer;
            //        return;
            //    }
            //}
            if (!target && SCARE_BEAST && ScareBeast_cd <= 7500 && GC_Timer <= diff && Rand() < 35)
            {
                target = FindCastingTarget(30, 0, false, SCARE_BEAST);
                if (target && doCast(target, SCARE_BEAST))
                {
                    ScareBeast_cd = 15000;
                    GC_Timer = 800;
                    return;
                }
            }
            if (!target && SILENCING_SHOT && SilencingShot_cd <= 7500 && Rand() < 30)
            {
                target = FindCastingTarget(35, 5, false, SILENCING_SHOT);
                temptimer = GC_Timer;
                if (target && doCast(target, SILENCING_SHOT))
                {
                    SilencingShot_cd = 15000;
                    GC_Timer = temptimer;
                    return;
                }
            }
        }

        void CheckScatter(uint32 diff)
        {
            if (!SCATTER_SHOT || ScatterShot_cd > diff || IsCasting() || Rand() > 50)
                return;

            if (Unit* target = FindStunTarget(15))
            {
                temptimer = GC_Timer;
                if (doCast(target, SCATTER_SHOT))
                {
                    GC_Timer = temptimer;
                    ScatterShot_cd = 20000;
                    return;
                }
            }

            ScatterShot_cd = 1000; //fail
        }

        void CheckWyvernSting(uint32 diff)
        {
            if (!WYVERN_STING || WyvernSting_cd > diff || IsCasting() || Rand() > 50)
                return;

            if (Unit* target = FindStunTarget(35))
            {
                temptimer = GC_Timer;
                if (doCast(target, WYVERN_STING))
                {
                    GC_Timer = temptimer;
                    WyvernSting_cd = 40000;
                    return;
                }
            }

            WyvernSting_cd = 1000; //fail
        }

        void CheckFreezingArrow(uint32 diff)
        {
            //Freezing Trap shares cooldown with traps
            if (!FREEZING_ARROW || Trap_cd > diff || IsCasting() || Rand() > 75)
                return;

            if (Unit* target = FindStunTarget(40))
            {
                temptimer = GC_Timer;
                if (doCast(target, FREEZING_ARROW))
                {
                    GC_Timer = temptimer;
                    Trap_cd = 20000;
                    return;
                }
            }

            Trap_cd = 1000; //fail
        }

        void CheckTraps(uint32 diff)
        {
            if (!FROST_TRAP || Trap_cd > diff || IsCasting() || Rand() > 90)
                return;

            Unit* target = me->GetVictim();
            if (!(target && me->GetDistance(target) < 6 && me->HasInArc(M_PI, target) &&
                IsInBotParty(target->GetVictim())))
                target = NULL;
            if (!target)
                target = FindAOETarget(3.f, true);

            if (target)
            {
                temptimer = GC_Timer;
                if (doCast(target, FROST_TRAP))
                {
                    GC_Timer = temptimer;
                    Trap_cd = 20000;
                    return;
                }
            }

            Trap_cd = 500; //fail
        }

        void CheckScare(uint32 diff)
        {
            if (!SCARE_BEAST || ScareBeast_cd > diff || GC_Timer > diff || IsCasting() || Rand() > 35)
                return;

            if (Unit* scareTarget = FindFearTarget())
            {
                if (doCast(scareTarget, SCARE_BEAST, true))
                {
                    ScareBeast_cd = 15000; //-50% for bot
                    GC_Timer = 800;
                    return;
                }
            }

            ScareBeast_cd = 1500; //fail
        }

        void CheckAspects(uint32 diff)
        {
            if ((!ASPECT_OF_THE_VIPER && !ASPECT_OF_THE_PACK) || Aspect_Timer > diff || GC_Timer > diff ||
                IsCasting() || Feasting() || Rand() > 35)
                return;

            uint8 needaspect = ASPECT_NONE;
            uint8 pct = GetManaPCT(me);

            if (ASPECT_OF_THE_VIPER && pct < 25)
                needaspect = ASPECT_VIPER;
            else if (ASPECT_OF_THE_PACK && (pct > 50 || Aspect == ASPECT_NONE))
                needaspect = ASPECT_PACK;

            if (needaspect == ASPECT_NONE || needaspect == Aspect)
            {
                Aspect_Timer = 1000;
                return;
            }

            switch (Aspect)
            {
                case ASPECT_VIPER:
                    me->RemoveAurasDueToSpell(ASPECT_OF_THE_VIPER);
                    break;
                case ASPECT_PACK:
                    me->RemoveAurasDueToSpell(ASPECT_OF_THE_PACK);
                    break;
                case ASPECT_NONE:
                default:
                    break;
            }

            if (doCast(me, (needaspect == ASPECT_VIPER ? ASPECT_OF_THE_VIPER : ASPECT_OF_THE_PACK)))
            {
                Aspect = needaspect;
                GC_Timer = 800;
                return;
            }
        }

        void doDefend(uint32 diff)
        {
            //No GCD abilities
            if ((!FEIGN_DEATH && !DETERRENCE) || (FeignDeath_cd > diff && Deterrence_cd > diff) ||
                me == tank || Rand() > 35)
                return;

            AttackerSet b_attackers = me->getAttackers();
            bool cast = false;

            if (b_attackers.size() == 1)
            {
                if (Creature* cre = (*b_attackers.begin())->ToCreature())
                {
                    if (cre->isWorldBoss() || cre->IsDungeonBoss() || cre->GetMaxHealth() > me->GetMaxHealth() * 10)
                    {
                        cast = true;
                        //need feign death
                        Deterrence_cd = std::max<uint32>(Deterrence_cd, diff + 500);
                    }
                }
            }
            else
                cast = (uint8(b_attackers.size()) > (GetHealthPCT(me) > 20 ? 1 : 0));

            if (!cast || b_attackers.empty())
            {
                //delay next try
                FeignDeath_cd = std::max<uint32>(FeignDeath_cd, 1000);
                Deterrence_cd = std::max<uint32>(Deterrence_cd, 1000);
                return;
            }

            if (FEIGN_DEATH && FeignDeath_cd <= diff && (*b_attackers.begin())->getAttackers().size() > 1)
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);

                temptimer = GC_Timer;
                if (doCast(me, FEIGN_DEATH))
                {
                    FeignDeath_cd = 20000;
                    GC_Timer = temptimer;
                    return;
                }
            }

            if (DETERRENCE && Deterrence_cd <= diff)
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);

                temptimer = GC_Timer;
                if (doCast(me, DETERRENCE))
                {
                    Deterrence_cd = 60000;
                    GC_Timer = temptimer;
                    return;
                }
            }
        }

        void CheckAutoShot()
        {
            //Auto Shot is always present
            //if (!AUTO_SHOT)
            //    return;

            Unit* target = me->GetVictim();
            if (!target)
                return;

            if (IsCasting())
                return;

            if (Spell* shot = me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
            {
                if (shot->GetSpellInfo()->Id != AUTO_SHOT)
                {
                    ////casting some other autorepeat spell, wtf?
                    //TC_LOG_ERROR("entities.player", "CheckAutoShot(): Bot %s is casting autorepeatable spell %u (%s) during check!",
                    //    me->GetName().c_str(), shot->GetSpellInfo()->Id, shot->GetSpellInfo()->SpellName[0]);

                    return;
                }
                else if (shot->m_targets.GetUnitTarget() != target)
                    me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
            }

            float dist = me->GetExactDist(target);
            if (dist < 5 || dist > 35)
                return;

            temptimer = GC_Timer;
            if (doCast(target, AUTO_SHOT))
            {
                GC_Timer = temptimer;
                return;
            }
        }

        void CheckTranquil(uint32 diff)
        {
            if (!TRANQ_SHOT || TranqShot_cd > diff || Rand() > 35) //No GCD
                return;

            //First check current target
            Unit* target = me->GetVictim();
            if (target)
            {
                Unit::AuraMap const &auras = target->GetOwnedAuras();
                for (Unit::AuraMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                {
                    SpellInfo const* spellInfo = itr->second->GetSpellInfo();
                    if (spellInfo->Dispel != DISPEL_MAGIC && spellInfo->Dispel != DISPEL_ENRAGE) continue;
                    if (spellInfo->Attributes & (SPELL_ATTR0_PASSIVE | SPELL_ATTR0_HIDDEN_CLIENTSIDE)) continue;
                    AuraApplication const* aurApp = itr->second->GetApplicationOfTarget(target->GetGUID());
                    if (aurApp && aurApp->IsPositive())
                    {
                        temptimer = GC_Timer;
                        //me->InterruptNonMeleeSpells(true, AUTO_SHOT);
                        if (doCast(target, TRANQ_SHOT))
                        {
                            TranqShot_cd = 6000; //with glyph
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
            }

            target = FindTranquilTarget();
            if (target)
            {
                temptimer = GC_Timer;
                //me->InterruptNonMeleeSpells(true, AUTO_SHOT);
                if (doCast(target, TRANQ_SHOT))
                {
                    TranqShot_cd = 6000; //with glyph
                    GC_Timer = temptimer;
                    return;
                }
            }

            TranqShot_cd = 2000; //fail
        }

        void CheckSilence(uint32 diff)
        {
            if (!SILENCING_SHOT || SilencingShot_cd > diff || IsCasting() || Rand() > 50) //No GCD
                return;

            Unit* target = me->GetVictim();
            if (target && target->IsNonMeleeSpellCast(false))
            {
                temptimer = GC_Timer;
                if (doCast(target, SILENCING_SHOT))
                {
                    SilencingShot_cd = 15000; //-5 sec for bot
                    GC_Timer = temptimer;
                    //return;
                }

                return; //succeed or failed, our hightest priority target casts spell and it must be interrupted above all else
            }

            target = FindCastingTarget(35, 5);
            if (target)
            {
                temptimer = GC_Timer;
                if (doCast(target, SILENCING_SHOT))
                {
                    SilencingShot_cd = 15000; //-5 sec for bot
                    GC_Timer = temptimer;
                    return;
                }
            }

            SilencingShot_cd = 1000; //fail
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            if (me->GetVictim())
                DoMeleeAttackIfReady();
            else
                Evade();
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            BreakCC(diff);
            if (CCed(me)) return;

            if (GetHealthPCT(me) < 67 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, HEALINGPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }

            if (GetManaPCT(me) < 40 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }

            //Deterrence check
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED))
                return;

            if (!me->IsInCombat())
                DoNonCombatActions(diff);
            else
                doDefend(diff);

            CheckAspects(diff);

            if (master->IsInCombat() || me->IsInCombat())
            {
                CheckTranquil(diff);
                CheckSilence(diff);
            }

            if (!CheckAttackTarget(CLASS_HUNTER))
            {
                me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
                return;
            }

            DoRangedAttack(diff);
        }

        void DoRangedAttack(uint32 diff)
        {
            opponent = me->GetVictim();
            if (opponent)
            {
                if (!IsCasting())
                    StartAttack(opponent, true);
            }
            else
                return;

            Counter(diff);

            CheckAutoShot();
            CheckScare(diff);
            CheckScatter(diff);

            //AttackerSet m_attackers = master->getAttackers();
            //AttackerSet b_attackers = me->getAttackers();
            //float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);

            //special
            if (SCATTER_SHOT && ScatterShot_cd <= diff && meleedist < 15 && Rand() < 60)
            {
                temptimer = GC_Timer;
                if (doCast(opponent, SCATTER_SHOT))
                {
                    ScatterShot_cd = 20000;
                    GC_Timer = temptimer;
                    me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
                    me->AttackStop();
                    return;
                }
            }

            //MELEE SECTION
            if (!(meleedist > 5))
            {
                //TRAPS
                CheckTraps(diff);

                //RAPTOR STRIKE
                if (RAPTOR_STRIKE && RaptorStrike_cd <= diff && Rand() < 50)
                {
                    temptimer = GC_Timer;
                    if (doCast(opponent, RAPTOR_STRIKE, true))
                    {
                        RaptorStrike_cd = 6000;
                        GC_Timer = temptimer;
                        return;
                    }
                }
                //WING CLIP
                if (WING_CLIP && GC_Timer <= diff && (tank != me || opponent->isMoving()) && Rand() < 80 &&
                    !opponent->HasAuraWithMechanic(/*(1<<MECHANIC_SNARE)|*/(1<<MECHANIC_ROOT)))
                {
                    if (doCast(opponent, WING_CLIP))
                    {
                        GC_Timer = 800;
                        return;
                    }
                }
                //DISENGAGE
                if (DISENGAGE && Disengage_cd <= diff && me->IsInCombat() && tank != me &&
                    !me->getAttackers().empty() && me->HasInArc(M_PI, *me->getAttackers().begin()) && Rand() < 30)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, DISENGAGE))
                    {
                        Disengage_cd = 16000; //improved, with glyph
                        GC_Timer = temptimer;
                    }
                }

                return; //don't try to do anything else in melee
            }

            //RANGED SECTION

            //HUNTERS MARK
            if (HUNTERS_MARK && HuntersMark_cd <= diff && Rand() < 25 &&
                !HasAuraName(opponent, HUNTERS_MARK)) //100 yd range so don't check it
            {
                //Hunter's Mark has exclusive GCD
                temptimer = GC_Timer;
                if (doCast(opponent, HUNTERS_MARK))
                {
                    markTarget = opponent;
                    HuntersMark_cd = 2000; //1500 + 500 for bot
                    GC_Timer = temptimer;
                    //return;
                }
            }

            //FREEZING ARROW
            CheckFreezingArrow(diff);
            CheckWyvernSting(diff);

            //attack range check 1
            if (!(meleedist < 45))
                return;

            //KILL SHOT
            if (KILL_SHOT && KillShot_cd <= diff && GetHealthPCT(opponent) < 20 &&
                /*GC_Timer <= diff && */Rand() < 95) //No GCD
            {
                temptimer = GC_Timer;
                if (doCast(opponent, KILL_SHOT))
                {
                    KillShot_cd = 8000; //with glyph
                    GC_Timer = temptimer;
                    return;
                }
            }

            //attack range check 2
            if (!(meleedist < 35))
                return;

            //CONCUSSIVE SHOT
            if (CONCUSSIVE_SHOT && ConcussiveShot_cd <= diff && GC_Timer <= diff && Rand() < 80)
            {
                if (doCast(opponent, CONCUSSIVE_SHOT))
                {
                    ConcussiveShot_cd = 10000; //improved
                    GC_Timer = 800;
                    return;
                }
            }
            //DISTRACTING SHOT
            if (Unit* u = opponent->GetVictim())
            {
                if (DISTRACTING_SHOT && DistractingShot_cd <= diff && tank == me && u != me && Rand() < 75 &&
                    !CCed(opponent) && IsInBotParty(u))
                {
                    temptimer = GC_Timer;
                    if (doCast(opponent, DISTRACTING_SHOT))
                    {
                        DistractingShot_cd = 8000;
                        GC_Timer = temptimer;
                    }
                }
            }
            //BLACK ARROW
            //Black Arrow shares cooldown with traps, but we'll have it only partially
            if (BLACK_ARROW && Trap_cd <= 10000 && GC_Timer <= diff &&
                opponent->GetHealth() > me->GetMaxHealth() / 3 && Rand() < 75)
            {
                if (doCast(opponent, BLACK_ARROW))
                {
                    Trap_cd = 20000;
                    return;
                }
            }
            //RAPID FIRE
            if (RAPID_FIRE && RapidFire_cd <= diff && opponent->GetHealth() > me->GetMaxHealth() / 2 && Rand() < 25)
            {
                temptimer = GC_Timer;
                if (doCast(me, RAPID_FIRE))
                {
                    RapidFire_cd = 90000; //1.5 min for bot
                    GC_Timer = temptimer;
                }
            }
            //EXPLOSIVE SHOT
            if (EXPLOSIVE_SHOT && ExplosiveShot_cd <= diff && GC_Timer <= diff && Rand() < 95)
            {
                if (doCast(opponent, EXPLOSIVE_SHOT))
                {
                    ExplosiveShot_cd = 6000;
                    return;
                }

                ExplosiveShot_cd = 500; //fail
            }
            //SCORPID STING
            if (SCORPID_STING && GC_Timer <= diff &&
                (ScorpidSting_Timer <= diff || stingTargetGuid != opponent->GetGUID()))
            {
                Aura* sSting = opponent->GetAura(SCORPID_STING);
                if (sSting && sSting->GetDuration() > 3000)
                {
                    stingTargetGuid = opponent->GetGUID();
                    ScorpidSting_Timer = std::max<uint32>(ScorpidSting_Timer, 2000);
                }
                else if (Rand() < 40 && doCast(opponent, SCORPID_STING))
                {
                    stingTargetGuid = opponent->GetGUID();
                    ScorpidSting_Timer = 18000;
                    GC_Timer = 800;
                    return;
                }
            }
            //CHIMERA SHOT TODO:
            if (CHIMERA_SHOT && ChimeraShot_cd <= diff && GC_Timer <= diff &&
                stingTargetGuid == opponent->GetGUID() &&
                !opponent->HasAuraType(SPELL_AURA_MOD_DISARM) && Rand() < 30)
            {
                if (doCast(opponent, CHIMERA_SHOT))
                {
                    ChimeraShot_cd = 9000; //with glyph
                    return;
                }
            }
            //MULTI-SHOT
            if (MULTISHOT && MultiShot_cd <= diff && GC_Timer <= diff && Rand() < 60)
            {
                if (Unit* target = FindSplashTarget(35, opponent))
                {
                    if (doCast(target, MULTISHOT))
                    {
                        MultiShot_cd = 8000; //with glyph
                        GC_Timer = 800;
                        return;
                    }
                }

                MultiShot_cd = 1000; //fail
            }
            //VOLLEY
            if (VOLLEY && Volley_cd <= diff && GC_Timer <= diff && !me->isMoving() && Rand() < 25)
            {
                if (Unit* target = FindAOETarget(35, true, false))
                {
                    if (doCast(target, VOLLEY))
                    {
                        Volley_cd = 5000;
                        return;
                    }
                }

                Volley_cd = 1000; //fail
            }
            //AIMED SHOT
            if (AIMED_SHOT && AimedShot_cd <= diff && GC_Timer <= diff && Rand() < 80)
            {
                if (doCast(opponent, AIMED_SHOT))
                {
                    AimedShot_cd = 8000; //with glyph
                    return;
                }
            }
            //ARCANE SHOT
            if (ARCANE_SHOT && ArcaneShot_cd <= diff && GC_Timer <= diff && Rand() < 50)
            {
                if (doCast(opponent, ARCANE_SHOT))
                {
                    ArcaneShot_cd = 6000;
                    return;
                }
            }
        }

        void ApplyClassDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType attackType, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;

                //Glyph of TrueShot Aura (req lvl 40): 10% additional critical chance for Aimed Shot
                if (lvl >= 40 && spellId == AIMED_SHOT)
                    aftercrit += 10.f;
                //Improved Barrage: 12% additional critical chance for Multi-Shot and Aimed Shot
                if (lvl >= 40 && (spellId == AIMED_SHOT || spellId == MULTISHOT))
                    aftercrit += 12.f;
                //Survival Instincts: 4% additional critical chance for Arcane Shot, Steady Shot and Explosive Shot
                if (lvl >= 15 && (spellId == ARCANE_SHOT/* || spellId == STEADY_SHOT*/ || spellId == EXPLOSIVE_SHOT))
                    aftercrit += 4.f;
                //Sniper Training (part 1): 15% additional critical chance for Kill Shot
                if (lvl >= 50 && spellId == KILL_SHOT)
                    aftercrit += 15.f;
                //Point of No Escape: 6% additional critical chance on victims of any kind of frost trap (crew this condition)
                if (lvl >= 50)
                    aftercrit += 6.f;

                //Savage Strikes: 20% additional critical chance for Raptor Strike, Mongoose Bite and Counterattack
                if (lvl >= 10 && (spellId == RAPTOR_STRIKE/* || spellId == MONGOOSE_BITE || spellId == COUNTERATTACK*/))

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half
                //Mortal Shots: 30% crit damage bonus for all ranged abilities
                if (lvl >= 15 && attackType == RANGED_ATTACK)
                    pctbonus += 0.15f;
                //Marked for Death (part 2): 10% crit damage bonus for Aimed Shot, Arcane Shot, Steady Shot, Kill Shot and Chimera Shot
                if (lvl >= 55 &&
                    (spellId == AIMED_SHOT ||
                    spellId == ARCANE_SHOT ||
                    //spellId == STEADY_SHOT ||
                    spellId == KILL_SHOT ||
                    spellId == CHIMERA_SHOT))
                    pctbonus += 0.05f;
            }

            //Ranged Weapon Specialization: 5% bonus damage for ranged attacks
            if (lvl >= 35 && attackType == RANGED_ATTACK)
                pctbonus += 0.05f;
            //Improved Arcane Shot: 15% bonus damage for Arcane Shot
            if (lvl >= 20 && spellId == ARCANE_SHOT)
                pctbonus += 0.15f;
            //Rapid Killing (buff): 20% bonus damage for Aimed Shot, Arcane Shot or Chimera Shot (removed in SpellHitTarget()) 
            if (lvl >= 20 && (spellId == AIMED_SHOT || spellId == ARCANE_SHOT || spellId == CHIMERA_SHOT) &&
                me->HasAura(RAPID_KILLING_BUFF))
                pctbonus += 0.2f;
            //Barrage: 12% bonus damage for Aimed Shot, Multi-Shot or Volley (removed in SpellHitTarget()) 
            if (lvl >= 30 && (spellId == AIMED_SHOT || spellId == MULTISHOT ||
                spellInfo->IsRankOf(sSpellMgr->GetSpellInfo(VOLLEY_DAMAGE_1))))
                pctbonus += 0.12f;
            //Marked for Death (part 1): 5% bonus damage for all ranged shots on marked target
            if (lvl >= 55 && attackType == RANGED_ATTACK && damageinfo.target == markTarget)
                pctbonus += 0.05f;
            //T.N.T: 6% bonus damage for Explosive Shot (handled here) and Black Arrow (can be handler in ApplyClassDamageMultiplierEffect())
            if (lvl >= 25 && spellId == EXPLOSIVE_SHOT)
                pctbonus += 0.06f;
            //Sniper Training (part 2): 6% bonus damage for Steady Shot, Aimed Shot, Black Arrow and Explosive Shot (screw aura stuff, just increase)
            if (lvl >= 50 &&
                (spellId == AIMED_SHOT ||
                //spellId == STEADY_SHOT ||
                //spellId == BLACK_ARROW ||//cannot be handled here
                spellId == EXPLOSIVE_SHOT))

            damage = int32(fdamage * (1.0f + pctbonus));

            //Thrill of the Hunt additive (stage 1): store mana restore value (50%) while ability crits
            if (lvl >= 40)
                TotH[spellId] = crit && attackType == RANGED_ATTACK ? spellInfo->CalcPowerCost(me, spellInfo->GetSchoolMask()) / 2 : 0;
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (target == me)
                return;

            uint32 spellId = spell->Id;

            //Thrill of the Hunt additive (stage 1): store mana restore value while ability crits
            if (me->getLevel() >= 40 && TotH[spellId] > 0 && TotH[spellId] < me->GetMaxPower(POWER_MANA))
            {
                me->EnergizeBySpell(me, THRILL_OF_THE_HUNT_EFFECT, TotH[spellId], POWER_MANA);
                TotH[spellId] = 0;
            }

            if (spellId == WING_CLIP)
            {
                //zzzOLD Improved Wing Clip (only on creatures): 30% to root target with Wing Clip
                //normal creatures are rooted for 10 sec, elites+ for 6 sec
                if (target->GetTypeId() == TYPEID_UNIT)
                {
                    if (urand(1,100) <= 30)
                    {
                        uint32 clip = target->ToCreature()->GetCreatureTemplate()->rank == CREATURE_ELITE_NORMAL ? IMPROVED_WING_CLIP_NORMAL : IMPROVED_WING_CLIP_EX;
                        me->CastSpell(target, clip, true);
                    }
                }
            }
            if (spellId == CONCUSSIVE_SHOT)
            {
                //Improved Concussion Shot rank 2: 2 sec increased daze duration
                if (Aura* concus = target->GetAura(CONCUSSIVE_SHOT, me->GetGUID()))
                {
                    int32 dur = concus->GetDuration() + 2000;
                    concus->SetDuration(dur);
                    concus->SetMaxDuration(dur);
                }

                //zzzOLD Improved Concussion Shot: chance to stun target for 3 sec
                if (urand(1,100) <= 15)
                {
                    me->CastSpell(target, IMPROVED_CONCUSSION, true);
                }
            }

            //Rapid Killing: use up buff manually
            if (spellId == AIMED_SHOT || spellId == ARCANE_SHOT || spellId == CHIMERA_SHOT)
            {
                if (me->HasAura(RAPID_KILLING_BUFF))
                    me->RemoveAura(RAPID_KILLING_BUFF, 0, 0, AURA_REMOVE_BY_EXPIRE);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            if (spellId == RAPID_FIRE)
            {
                //Rapid Fire (id 28755): 4 sec increased duration
                if (Aura* rapid = me->GetAura(RAPID_FIRE))
                {
                    uint32 dur = rapid->GetDuration() + 4000;
                    rapid->SetDuration(dur);
                    rapid->SetMaxDuration(dur);
                }
            }

            OnSpellHit(caster, spell);
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (victim == me)
                return;

            if (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE)
            {
                for (uint8 i = 0; i != MAX_BOT_CTC_SPELLS; ++i)
                {
                    if (_ctc[i].first && !_ctc[i].second)
                    {
                        if (urand(1,100) <= CalcCTC(_ctc[i].first))
                            _ctc[i].second = 1000;

                        if (_ctc[i].second > 0)
                            me->CastSpell(victim, _ctc[i].first, true);
                    }
                }
            }
        }

        void DamageTaken(Unit* u, uint32& /*damage*/)
        {
            OnOwnerDamagedBy(u);
        }

        void OwnerAttackedBy(Unit* u)
        {
            OnOwnerDamagedBy(u);
        }

        void Reset()
        {
            TranqShot_cd = 0;
            SilencingShot_cd = 0;
            ChimeraShot_cd = 0;
            ArcaneShot_cd = 0;
            AimedShot_cd = 0;
            KillShot_cd = 0;
            ExplosiveShot_cd = 0;
            MultiShot_cd = 0;
            Volley_cd = 0;
            ScatterShot_cd = 0;
            ConcussiveShot_cd = 0;
            DistractingShot_cd = 0;
            RapidFire_cd = 0;
            RaptorStrike_cd = 0;
            Disengage_cd = 5000;
            Trap_cd = 0;
            WyvernSting_cd = 10000;
            HuntersMark_cd = 0;
            ScareBeast_cd = 0;
            FeignDeath_cd = 5000;
            Deterrence_cd = 10000;

            ScorpidSting_Timer = 0;
            Aspect_Timer = 0;

            stingTargetGuid = 0;

            markTarget = NULL;

            Aspect = ASPECT_NONE;

            if (master)
            {
                setStats(CLASS_HUNTER, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_HUNTER);
             }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (TranqShot_cd > diff)                TranqShot_cd -= diff;
            if (SilencingShot_cd > diff)            SilencingShot_cd -= diff;
            if (ChimeraShot_cd > diff)              ChimeraShot_cd -= diff;
            if (ArcaneShot_cd > diff)               ArcaneShot_cd -= diff;
            if (AimedShot_cd > diff)                AimedShot_cd -= diff;
            if (KillShot_cd > diff)                 KillShot_cd -= diff;
            if (ExplosiveShot_cd > diff)            ExplosiveShot_cd -= diff;
            if (MultiShot_cd > diff)                MultiShot_cd -= diff;
            if (Volley_cd > diff)                   Volley_cd -= diff;
            if (ScatterShot_cd > diff)              ScatterShot_cd -= diff;
            if (ConcussiveShot_cd > diff)           ConcussiveShot_cd -= diff;
            if (DistractingShot_cd > diff)          DistractingShot_cd -= diff;
            if (RapidFire_cd > diff)                RapidFire_cd -= diff;
            if (RaptorStrike_cd > diff)             RaptorStrike_cd -= diff;
            if (Disengage_cd > diff)                Disengage_cd -= diff;
            if (Trap_cd > diff)                     Trap_cd -= diff;
            if (WyvernSting_cd > diff)              WyvernSting_cd -= diff;
            if (HuntersMark_cd > diff)              HuntersMark_cd -= diff;
            if (ScareBeast_cd > diff)               ScareBeast_cd -= diff;
            if (FeignDeath_cd > diff)               FeignDeath_cd -= diff;
            if (Deterrence_cd > diff)               Deterrence_cd -= diff;

            if (ScorpidSting_Timer > diff)          ScorpidSting_Timer -= diff;
            if (Aspect_Timer > diff)                Aspect_Timer -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            AUTO_SHOT                               = AUTO_SHOT_1;
            TRANQ_SHOT                              = InitSpell(me, TRANQ_SHOT_1);
  /*Talent*/SILENCING_SHOT              = lvl >= 50 ? SILENCING_SHOT_1 : 0;
  /*Talent*/CHIMERA_SHOT                = lvl >= 60 ? CHIMERA_SHOT_1 : 0;
            ARCANE_SHOT                             = InitSpell(me, ARCANE_SHOT_1);
  /*Talent*/AIMED_SHOT                  = lvl >= 20 ? InitSpell(me, AIMED_SHOT_1) : 0;
            KILL_SHOT                               = InitSpell(me, KILL_SHOT_1);
  /*Talent*/EXPLOSIVE_SHOT              = lvl >= 60 ? InitSpell(me, EXPLOSIVE_SHOT_1) : 0;
            MULTISHOT                               = InitSpell(me, MULTISHOT_1);
            VOLLEY                                  = InitSpell(me, VOLLEY_1);
  /*Talent*/SCATTER_SHOT                = lvl >= 20 ? SCATTER_SHOT_1 : 0;
            CONCUSSIVE_SHOT                         = InitSpell(me, CONCUSSIVE_SHOT_1);
            DISTRACTING_SHOT                        = InitSpell(me, DISTRACTING_SHOT_1);
            SCORPID_STING                           = InitSpell(me, SCORPID_STING_1);
            //VIPER_STING                             = InitSpell(me, VIPER_STING_1);
            RAPID_FIRE                              = InitSpell(me, RAPID_FIRE_1);
            WING_CLIP                               = InitSpell(me, WING_CLIP_1);
            RAPTOR_STRIKE                           = InitSpell(me, RAPTOR_STRIKE_1);
            DISENGAGE                               = InitSpell(me, DISENGAGE_1);
            FROST_TRAP                              = InitSpell(me, FROST_TRAP_1);
            FREEZING_ARROW                          = InitSpell(me, FREEZING_ARROW_1);
  /*Talent*/WYVERN_STING                = lvl >= 40 ? InitSpell(me, WYVERN_STING_1) : 0;
  /*Talent*/BLACK_ARROW                 = lvl >= 50 ? InitSpell(me, BLACK_ARROW_1) : 0;
            HUNTERS_MARK                            = InitSpell(me, HUNTERS_MARK_1);
            SCARE_BEAST                             = InitSpell(me, SCARE_BEAST_1);
            FEIGN_DEATH                             = InitSpell(me, FEIGN_DEATH_1);
            DETERRENCE                              = InitSpell(me, DETERRENCE_1);
            ASPECT_OF_THE_VIPER                     = InitSpell(me, ASPECT_OF_THE_VIPER_1);
  /*Custom*/ASPECT_OF_THE_PACK                      = ASPECT_OF_THE_VIPER ? ASPECT_OF_THE_PACK_1 : 0;
            //ASPECT_OF_THE_DRAGONHAWK                = InitSpell(me, ASPECT_OF_THE_DRAGONHAWK_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 20)
                RefreshAura(RAPID_KILLING); //20%
            if (level >= 30)
                RefreshAura(CONCUSSIVE_BARRAGE); //100%
            if (level >= 40)
                RefreshAura(PIERCING_SHOTS); //30%
            if (level >= 40)
                RefreshAura(TRUESHOT_AURA); //10%
            if (level >= 45)
                RefreshAura(RAPID_RECUPERATION); //4%
            if (level >= 45)
                RefreshAura(MASTER_MARKSMAN); //5%
            if (level >= 70)
                RefreshAura(WILD_QUIVER,3); //36%
            else if (level >= 60)
                RefreshAura(WILD_QUIVER,2); //24%
            else if (level >= 50)
                RefreshAura(WILD_QUIVER); //12%
            if (level >= 15)
                RefreshAura(SUREFOOTED); //30%
            if (level >= 15)
                RefreshAura(ENTRAPMENT); //4 sec
            if (level >= 67)
                RefreshAura(MASTER_TACTICIAN5,3); //30%
            else if (level >= 58)
                RefreshAura(MASTER_TACTICIAN5,2); //20%
            else if (level >= 50)
                RefreshAura(MASTER_TACTICIAN5); //10%
            else if (level >= 49)
                RefreshAura(MASTER_TACTICIAN4); //8%
            else if (level >= 48)
                RefreshAura(MASTER_TACTICIAN3); //6%
            else if (level >= 47)
                RefreshAura(MASTER_TACTICIAN2); //4%
            else if (level >= 46)
                RefreshAura(MASTER_TACTICIAN1); //2%
            if (level >= 45)
                RefreshAura(NOXIOUS_STINGS); //50%
            if (level >= 55)
                RefreshAura(HUNTING_PARTY); //100%
        }

    private:
        uint32
        AUTO_SHOT, TRANQ_SHOT, SILENCING_SHOT, CHIMERA_SHOT, ARCANE_SHOT, AIMED_SHOT,
        KILL_SHOT, EXPLOSIVE_SHOT, MULTISHOT, VOLLEY,
        SCATTER_SHOT, CONCUSSIVE_SHOT, DISTRACTING_SHOT, SCORPID_STING/*, VIPER_STING*/, RAPID_FIRE,
        WING_CLIP, RAPTOR_STRIKE, DISENGAGE, FROST_TRAP, FREEZING_ARROW, WYVERN_STING, BLACK_ARROW,
        HUNTERS_MARK, SCARE_BEAST,
        FEIGN_DEATH, DETERRENCE,
        ASPECT_OF_THE_PACK, ASPECT_OF_THE_VIPER/*, ASPECT_OF_THE_DRAGONHAWK*/;
        //Timers
        uint32
            TranqShot_cd, SilencingShot_cd, ChimeraShot_cd, ArcaneShot_cd, AimedShot_cd,
            KillShot_cd, ExplosiveShot_cd, MultiShot_cd, Volley_cd,
            ScatterShot_cd, ConcussiveShot_cd, DistractingShot_cd, RapidFire_cd,
            RaptorStrike_cd, Disengage_cd, Trap_cd, WyvernSting_cd,
            HuntersMark_cd, ScareBeast_cd,
            FeignDeath_cd, Deterrence_cd;
        uint8 Aspect;
        uint32 ScorpidSting_Timer, Aspect_Timer;
        uint64 stingTargetGuid;
        Unit* markTarget;

        enum HunterBaseSpells
        {
            AUTO_SHOT_1                         = 75,
            TRANQ_SHOT_1                        = 19801,
            SILENCING_SHOT_1                    = 34490,
            CHIMERA_SHOT_1                      = 53209,
            ARCANE_SHOT_1                       = 3044,
            AIMED_SHOT_1                        = 19434,
            KILL_SHOT_1                         = 53351,
            EXPLOSIVE_SHOT_1                    = 53301,
            MULTISHOT_1                         = 2643,
            VOLLEY_1                            = 1510,
            SCATTER_SHOT_1                      = 1991,
            CONCUSSIVE_SHOT_1                   = 5116,
            DISTRACTING_SHOT_1                  = 20736,
            SCORPID_STING_1                     = 3043,
            //VIPER_STING_1                       = 3034,
            RAPID_FIRE_1                        = 3045,
            WING_CLIP_1                         = 2974,
            RAPTOR_STRIKE_1                     = 2973,
            DISENGAGE_1                         = 781,
            FROST_TRAP_1                        = 13809,
            FREEZING_ARROW_1                    = 60192,
            WYVERN_STING_1                      = 19386,
            BLACK_ARROW_1                       = 3674,
            HUNTERS_MARK_1                      = 1130,
            SCARE_BEAST_1                       = 1513,
            FEIGN_DEATH_1                       = 5384,
            DETERRENCE_1                        = 19263,
            ASPECT_OF_THE_PACK_1                = 36613,//Aspect of the Spirit Hunter
            ASPECT_OF_THE_VIPER_1               = 34074
            //ASPECT_OF_THE_DRAGONHAWK_1          = 61846
        };

        enum HunterPassives
        {
        //Talents
            RAPID_KILLING                       = 34949,//rank 2
            CONCUSSIVE_BARRAGE                  = 35102,//rank 2
            PIERCING_SHOTS                      = 53238,//rank 3
            TRUESHOT_AURA                       = 19506,
            RAPID_RECUPERATION                  = 53232,//rank 2
            MASTER_MARKSMAN                     = 34489,//rank 5
            WILD_QUIVER                         = 53217,//rank 3
            SUREFOOTED                          = 24283,//rank 3
            ENTRAPMENT                          = 19388,//rank 3
            MASTER_TACTICIAN1                   = 34506,
            MASTER_TACTICIAN2                   = 34507,
            MASTER_TACTICIAN3                   = 34508,
            MASTER_TACTICIAN4                   = 34838,
            MASTER_TACTICIAN5                   = 34839,
            NOXIOUS_STINGS                      = 53297,//rank 3
            HUNTING_PARTY                       = 53292 //rank 3
        };

        enum HunterSpecial
        {
            ASPECT_NONE,
            ASPECT_PACK,
            ASPECT_VIPER,

            IMPROVED_CONCUSSION                 = 28445,
            IMPROVED_WING_CLIP_NORMAL           = 47168,
            IMPROVED_WING_CLIP_EX               = 35963,

            RAPID_KILLING_BUFF                  = 35099,//rank 2
            THRILL_OF_THE_HUNT_EFFECT           = 34720,
            FROST_TRAP_AURA                     = 13810,
            FREEZING_ARROW_EFFECT               = 60210,
            //FREEZING_TRAP_EFFECT_1              = 3355,
            //FREEZING_TRAP_EFFECT_2              = 14308,
            //FREEZING_TRAP_EFFECT_3              = 14309,
            VOLLEY_DAMAGE_1                     = 42243 //rank 1
        };
    };
};

void AddSC_hunter_bot()
{
    new hunter_bot();
}
