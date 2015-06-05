#include "bot_ai.h"
//#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
/*
Rogue NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - 25% maybe...
TODO:
*/

class rogue_bot : public CreatureScript
{
public:
    rogue_bot() : CreatureScript("rogue_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new rogue_botAI(creature);
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

    struct rogue_botAI : public bot_minion_ai
    {
        rogue_botAI(Creature* creature) : bot_minion_ai(creature)
        {
            Reset();
        }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_ROGUE) != SPELL_CAST_OK)
                return false;
            return bot_ai::doCast(victim, spellId, triggered);
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force, false);
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { comboPoints = 0; tempComboPoints = 0; master->SetNpcBotDied(me->GetGUID()); }
        void DoNonCombatActions(uint32 /*diff*/)
        {}

        //This method should be used to emulate energy usage reduction
        void modenergy(int32 mod, bool set = false)
        {
            //can't set enery to -x (2 cases)
            if (set && mod < 0)
                return;
            if (mod < 0 && energy < uint32(abs(mod)))
            {
                mod = 0;
                set = true;
            }

            if (set)
                energy = mod;
            else
                energy += mod;

            energy = std::min<uint32>(energy, 100);
            me->SetPower(POWER_ENERGY, energy);
        }

        uint32 getenergy()
        {
            energy = me->GetPower(POWER_ENERGY);
            return energy;
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (KidneyTarget)
            {
                //tempComboPoints -= 1;
                if (tempComboPoints)
                {
                    if (Unit* u = sObjectAccessor->FindUnit(KidneyTarget))
                    {
                        if (Aura* kidney = u->GetAura(KIDNEY_SHOT, me->GetGUID()))
                        {
                            uint32 dur = kidney->GetDuration() + tempComboPoints*1000;
                            kidney->SetDuration(dur);
                            kidney->SetMaxDuration(dur);
                        }
                    }
                    else //spell is failed to hit: restore cp
                    {
                        if (comboPoints == 0)
                            comboPoints = tempComboPoints;
                    }
                    tempComboPoints = 0;
                }
                KidneyTarget = 0;
            }
            else if (RuptureTarget)
            {
                //tempComboPoints -= 1;
                if (tempComboPoints)
                {
                    if (Unit* u = sObjectAccessor->FindUnit(RuptureTarget))
                    {
                        if (Aura* rupture = u->GetAura(RUPTURE, me->GetGUID()))
                        {
                            uint32 dur = rupture->GetDuration() + tempComboPoints*2000; //use cp
                            dur += 4000; //Glyph of Rupture
                            rupture->SetDuration(dur);
                            rupture->SetMaxDuration(dur);
                        }
                    }
                    else //spell is failed to hit: restore cp
                    {
                        if (comboPoints == 0)
                            comboPoints = tempComboPoints;
                    }
                    tempComboPoints = 0;
                }
                RuptureTarget = 0;
            }
            else if (tempDICE)
            {
                //tempComboPoints -= 1;
                if (tempComboPoints)
                {
                    if (Aura* dice = me->GetAura(SLICE_DICE))
                    {
                        uint32 dur = dice->GetDuration();
                        dur += tempComboPoints * 3000; //use cp
                        dur += 6000; // Glyph of Slice and Dice
                        dur = (dur * 3) / 2; //Improved Slice and Dice
                        dice->SetDuration(dur);
                        dice->SetMaxDuration(dur);
                    }
                    tempComboPoints = 0;
                }
                tempDICE = false;
            }
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

            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            if (!CheckAttackTarget(CLASS_ROGUE))
                return;

            Attack(diff);
        }

        void Attack(uint32 diff)
        {
            opponent = me->GetVictim();
            if (opponent)
            {
                if (!IsCasting())
                    StartAttack(opponent, true);
            }
            else
                return;

            comboPoints = std::min<uint8>(comboPoints, 5);
            //AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();
            float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);

            //Blade Flurry (434 deprecated)
            if (BLADE_FLURRY && Blade_Flurry_Timer <= diff && meleedist <= 5 &&
                Rand() < 30 && FindSplashTarget(7, opponent))
            {
                temptimer = GC_Timer;
                if (doCast(me, BLADE_FLURRY))
                {
                    Blade_Flurry_Timer = 75000;
                    GC_Timer = temptimer;
                    return;
                }
            }

            if (MoveBehind(*opponent))
                wait = 5;

            //KICK
            if (KICK && Kick_Timer <= diff && meleedist <= 5 && Rand() < 80 && getenergy() >= 15 &&
                opponent->IsNonMeleeSpellCast(false))
            {
                temptimer = GC_Timer;
                if (doCast(opponent, KICK))
                {
                    Kick_Timer = 8000; //improved
                    GC_Timer = temptimer;
                    //return;
                }
            }
            //SHADOWSTEP
            if (SHADOWSTEP && Shadowstep_Timer <= diff && dist < 25 &&
                (opponent->GetVictim() != me || opponent->GetTypeId() == TYPEID_PLAYER) &&
                Rand() < 30 && getenergy() >= 10)
            {
                temptimer = GC_Timer;
                if (doCast(opponent, SHADOWSTEP))
                {
                    Shadowstep_Timer = 20000;
                    GC_Timer = temptimer;
                    //return;
                }
            }
            //BACKSTAB
            if (BACKSTAB && GC_Timer <= diff && meleedist <= 5 && comboPoints < 4 &&
                /*Rand() < 90 && */getenergy() >= 60 && !opponent->HasInArc(M_PI, me))
            {
                if (doCast(opponent, BACKSTAB))
                    return;
            }
            //SINISTER STRIKE
            if (SINISTER_STRIKE && GC_Timer <= diff && meleedist <= 5 && comboPoints < 5 &&
                Rand() < 25 && getenergy() >= 45)
            {
                if (doCast(opponent, SINISTER_STRIKE))
                    return;
            }
            //SLICE AND DICE
            if (SLICE_DICE && Slice_Dice_Timer <= diff && GC_Timer <= diff && dist < 20 && comboPoints > 1 &&
                (b_attackers.size() <= 1 || Blade_Flurry_Timer > 60000) && Rand() < 30 && getenergy() >= 25)
            {
                if (doCast(opponent, SLICE_DICE))
                    return;
            }
            //KIDNEY SHOT
            if (KIDNEY_SHOT && GC_Timer <= diff && Kidney_Timer <= diff && meleedist <= 5 && comboPoints > 0 &&
                !CCed(opponent) && getenergy() >= 25 && ((Rand() < 15 + comboPoints*15 && opponent->GetVictim() == me && comboPoints > 2) || opponent->IsNonMeleeSpellCast(false)))
            {
                if (doCast(opponent, KIDNEY_SHOT))
                {
                    KidneyTarget = opponent->GetGUID();
                    tempComboPoints = comboPoints;
                    Kidney_Timer = 20000;
                    return;
                }
            }
            //EVISCERATE
            if (EVISCERATE && GC_Timer <= diff && meleedist <= 5 && comboPoints > 2 &&
                getenergy() >= 35 && Rand() < comboPoints*15)
            {
                if (doCast(opponent, EVISCERATE))
                    return;
            }
            //MUTILATE
            //if (isTimerReady(Mutilate_Timer) && energy>60)
            //{
            //    // TODO: calculate correct dmg for mutilate (dont forget poison bonus)
            //    // for now use same formula as evicerate
            //    uint32 base_attPower = me->GetUInt32Value(UNIT_FIELD_ATTACK_POWER);
            //    //float minDmg = me->GetFloatValue(UNIT_FIELD_MINDAMAGE);
            //    float minDmg = me->GetWeaponDamageRange(BASE_ATTACK, MINDAMAGE);
            //    int damage = irand(int32(base_attPower*7*0.03f),int32(base_attPower*7*0.08f))+minDmg+me->getLevel();

            //    // compensate for lack of attack power
            //    damage = damage*(rand()%4+1);

            //    me->CastCustomSpell(opponent, MUTILATE, &damage, NULL, NULL, false, NULL, NULL);

            //    //doCast (me, MUTILATE);
            //    Mutilate_Timer = 10;
            //    comboPoints+=3;
            //    energy -= 60;
            //}

            //RUPTURE
            if (RUPTURE && Rupture_Timer <= diff && GC_Timer <= diff && meleedist <= 5 && comboPoints > 3 &&
                opponent->GetHealth() > me->GetMaxHealth()/3 && getenergy() >= 25 && Rand() < (50 + 70 * opponent->isMoving()))
            {
                if (doCast(opponent, RUPTURE))
                    return;
            }
            //DISMANTLE
            if (DISMANTLE && Dismantle_Timer <= diff && meleedist <= 5 && opponent->GetTypeId() == TYPEID_PLAYER &&
                Rand() < 20 && getenergy() >= 25 && !CCed(opponent) && !opponent->HasAuraType(SPELL_AURA_MOD_DISARM) &&
                (opponent->ToPlayer()->GetWeaponForAttack(BASE_ATTACK) || opponent->ToPlayer()->GetWeaponForAttack(RANGED_ATTACK)))
            {
                temptimer = GC_Timer;
                if (doCast(opponent, DISMANTLE))
                {
                    Dismantle_Timer = 60000;
                    GC_Timer = temptimer;
                    return;
                }
            }
        }

        void ApplyClassDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;
                //Puncturing Wounds: 30% additional critical chance for Backstab
                if (lvl >= 15 && spellId == BACKSTAB)
                    aftercrit += 30.f;
                //Puncturing Wounds: 15% additional critical chance for Mutilate
                else if (spellId == MUTILATE)
                    aftercrit += 15.f;
                //Glyph of Eviscerate: 10% additional critical chance for Eviscerate
                else if (spellId == EVISCERATE)
                    aftercrit += 10.f;
                //Improved Ambush: 60% additional critical chance for Ambush
                //else if (spellId == AMBUSH)
                //    crit_chance += 60.f;
                if (lvl >= 50 && spellInfo->HasEffect(SPELL_EFFECT_ADD_COMBO_POINTS) && me->HasAura(TURN_THE_TABLES_EFFECT))
                    aftercrit += 6.f;

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half
                //Lethality: 30% crit damage bonus for Sinister Strike, Backstab, Mutilate and Hemorrhage
                if (lvl >= 10 &&
                    (spellId == SINISTER_STRIKE || spellId == BACKSTAB || spellId == MUTILATE/* || spellId == HEMORRHAGE*/))
                    pctbonus += 0.15f;
            }
            //Shadowstep: 20% bonus damage to all abilities once
            //if (shadowstep == true)
            //{
            //    shadowstep = false;
            //    me->RemoveAurasDueToSpell(SHADOWSTEP_EFFECT_DAMAGE);
            //    pctbonus += 0.2f;
            //}
            //DeathDealer set bonus: 15% damage bonus for Eviscerate
            if (lvl >= 60 && spellId == EVISCERATE)
                pctbonus += 0.15f;
            //Coup de Grace: 20% damage bonus for Eviscerate and Envenom
            if (lvl >= 10 &&(spellId == EVISCERATE/* || spellId == ENVENOM*/))
                pctbonus += 0.2f;
            //Opportunity: 30% damage bonus for Backstab, Mutilate, Garrote and Ambush
            if (lvl >= 20 && (spellId == BACKSTAB || spellId == MUTILATE/* ||
                spellId == GARROTE || spellId == AMBUSH*/))
                pctbonus += 0.3f;
            //Aggression: 20% damage bonus for Sinister Strike, Backstab and Eviscerate
            if (lvl >= 20 && (spellId == SINISTER_STRIKE || spellId == BACKSTAB || spellId == EVISCERATE))
                pctbonus += 0.2f;
            //Surprise Attacks (434 deprecated): 10% bonus damage for Sinister Strike, Backstab, Shiv, Hemmorhage and Gouge
            if (lvl >= 60 && (spellId == SINISTER_STRIKE || spellId == BACKSTAB/* ||
                spellId == SHIV || spellId == HEMORRHAGE || spellId == GOUGE*/))
                pctbonus += 0.1f;
            //434 new
            //Improved Sinister Strike: 30% bonus damage for Sinister Strike
            if (lvl >= 10 && spellId == SINISTER_STRIKE)
                pctbonus += 0.3f;

            //Special
            if (spellId == EVISCERATE)
            {
                float ap = me->GetTotalAttackPowerValue(BASE_ATTACK);
                //434 temp formula - placeholder
                float damageMin = 2 + me->getLevel() * 2;
                float damageMax = me->getLevel() >= 80 ? 10 + me->getLevel() * 5 : 5 + me->getLevel() * 4;
                //base damage
                fdamage = frand(damageMin, damageMax) + (damageMin + damageMax) * comboPoints;

                //ap bonus (Trinity-based)
                fdamage += frand(ap * comboPoints * 0.03f, ap * comboPoints * 0.07f);
            }

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void ApplyClassDamageMultiplierEffect(SpellInfo const* spellInfo, uint8 effect_index, float& value) const
        {
            uint32 spellId = spellInfo->Id;

            //float pct_mod = 1.f;

            if (spellInfo->Effects[effect_index].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE)
            {
                if (spellId == RUPTURE)
                {
                    float ap = me->GetTotalAttackPowerValue(BASE_ATTACK);
                    //434 temp formula - placeholder
                    float flat_mod = float(urand(me->getLevel() * 17, me->getLevel() * 22) * comboPoints);

                    float AP_per_combo[6] = { 0.0f, 0.015f, 0.024f, 0.03f, 0.03428571f, 0.0375f }; //Trinity-based
                    float divider[6] = { 0.0f, 4.f, 5.f, 6.f, 7.f, 8.f }; //base duration/2 = number of ticks

                    value += flat_mod / divider[comboPoints] + ap * AP_per_combo[comboPoints];
                }
            }

            //value *= pct_mod;
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (!WOUND_POISON && !MIND_NUMBING_POISON)
                return;

            if (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE)
            {
                if (victim && me->GetExactDist(victim) <= 40)
                {
                    switch (rand()%2)
                    {
                        case 0:
                            break;
                        case 1:
                        {
                            switch (rand()%2)
                            {
                                case 0:
                                    if (WOUND_POISON)
                                    {
                                        currentSpell = WOUND_POISON;
                                        DoCast(victim, WOUND_POISON, true);
                                    }
                                    break;
                                case 1:
                                    if (MIND_NUMBING_POISON)
                                    {
                                        currentSpell = MIND_NUMBING_POISON;
                                        DoCast(victim, MIND_NUMBING_POISON, true);
                                    }
                                    break;
                            }
                        }
                    }
                }
            }

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

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            OnSpellHit(caster, spell);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (currentSpell == 0)
                return;

            uint32 spellId = spell->Id;

            //temp target holders
            if (spellId == SLICE_DICE)
            {
                tempDICE = true;
                tempComboPoints = comboPoints;
                Slice_Dice_Timer = 15000 + (comboPoints-1)*4500;
            }
            else if (spellId == RUPTURE)
            {
                RuptureTarget = target->GetGUID();
                tempComboPoints = comboPoints;
                Rupture_Timer = 8000 + (comboPoints-1)*2000 + 4000;
                GC_Timer = 800;
            }

            //BONUS CP MANAGEMENT

            //if (spellId == EVISCERATE || spellId == KIDNEY_SHOT || spellId == SLICE_DICE || spellId == RUPTURE/* || spellId == EXPOSE_ARMOR || spellId == ENVENOM*/)
            //Relentless Strikes
            if (spell->NeedsComboPoints())
            {
                //std::ostringstream msg;
                //msg << "casting ";
                //if (spellId == EVISCERATE)
                //    msg << "Eviscerate, ";
                //else if (spellId == RUPTURE)
                //    msg << "Rupture, ";
                //else if (spellId == SLICE_DICE)
                //    msg << "Slice and Dice, ";
                //else if (spellId == KIDNEY_SHOT)
                //    msg << "Kidney Shot, ";
                ////else if (spellId == EXPOSE_ARMOR)
                ////    msg << "Expose Armor, ";
                ////else if (spellId == ENVENOM)
                ////    msg << "Envenom, ";
                //msg << "combo points: " << uint32(std::min<uint32>(comboPoints,5));
                //me->MonsterWhisper(msg.str().c_str(), master->GetGUID());
                if (irand(0, 99) < 20 * (comboPoints > 5 ? 5 : comboPoints))
                {
                    currentSpell = RELENTLESS_STRIKES_EFFECT;
                    DoCast(me, RELENTLESS_STRIKES_EFFECT, true);
                }
                tempComboPoints = comboPoints;
                //CP adding effects are handled before actual finisher so use temp value
                //std::ostringstream msg2;
                //msg2 << "cp set to 0";
                if (tempAddCP)
                {
                    //msg2 << " + " << uint32(tempAddCP) << " (temp)";
                    comboPoints = tempAddCP;
                    tempAddCP = 0;
                }
                else
                    comboPoints = 0;
                //me->MonsterWhisper(msg2.str().c_str(), master->GetGUID());
            }
            else if (spellId == SINISTER_STRIKE ||
                spellId == BACKSTAB/* ||
                spellId == GOUGE ||
                spellId == HEMORRHAGE*/)
            {
                ++comboPoints;
                //std::ostringstream msg;
                //msg << "1 cp generated ";
                //if (spellId == SINISTER_STRIKE)
                //    msg << "(Sinister Strike)";
                //else if (spellId == BACKSTAB)
                //    msg << "(Backstab)";
                //msg << " set to " << uint32(comboPoints);
                //if (tempAddCP)
                //    msg << " + " << uint32(tempAddCP) << " (triggered)";
                //me->MonsterWhisper(msg.str().c_str(), master->GetGUID());
                if (tempAddCP)
                {
                    comboPoints += tempAddCP;
                    tempAddCP = 0;
                }
            }
            else if (spellId == MUTILATE/* ||
                spellId == AMBUSH*/)
            {
                comboPoints += 2;
                //std::ostringstream msg;
                //msg << "2 cp generated (Mutilate), set to " << uint32(comboPoints);
                //if (tempAddCP)
                //    msg << " + " << uint32(tempAddCP) << " (triggered)";
                //me->MonsterWhisper(msg.str().c_str(), master->GetGUID());
                if (tempAddCP)
                {
                    comboPoints += tempAddCP;
                    tempAddCP = 0;
                }
            }
            else if (spellId == SEAL_FATE_EFFECT || spellId == RUTHLESSNESS_EFFECT)
            {
                ++tempAddCP;
                //std::ostringstream msg;
                //msg << "1 temp cp generated ";
                //if (spellId == SEAL_FATE_EFFECT)
                //    msg << "(Seal Fate)";
                //else if (spellId == RUTHLESSNESS_EFFECT)
                //    msg << "(Ruthleness)";
                //me->MonsterWhisper(msg.str().c_str(), master->GetGUID());
            }

            //Glyph of Sinister Strike (20% to add cp on hit)
            //Seal Fate means crit so this glyph is enabled from lvl 35)
            //as addition always add cp on ss crit
            if (currentSpell == SINISTER_STRIKE && (spellId == SEAL_FATE_EFFECT || urand(0,100) >= 20))
            {
                ++tempAddCP;
                //me->MonsterWhisper("1 temp cp generated (glyph of SS)", master->GetGUID());
            }

            //ENERGY COST REDUCTION

            if (spellId == SINISTER_STRIKE)
            {
                //Improved Sinister Strike
                //instead of restoring energy we should override current value
                if (me->getLevel() >= 10)
                    modenergy(-40, true);//45 - 5
            }
            //Slaughter from the Shadows energy restore
            //instead of restoring energy we should override current value
            if (me->getLevel() >= 55)
            {
                if (spellId == BACKSTAB/* || spellId == AMBUSH*/)
                    modenergy(-40, true);
                //else if (spellId == HEMORRHAGE)
                //    modenergy(-30, true);
            }

            //OTHER

            if (spellId == EVISCERATE)
            {
                //Eviscerate speedup
                GC_Timer = 800;

                //Serrated Blades: Eviscerate has 20% chance per cp to refresh Rupture
                //getting cheaty - remove roll
                //getting cheaty - increase duration
                //if (irand(0, 99) < 20 * (comboPoints > 5 ? 5 : comboPoints))
                {
                    if (Aura* rupture = target->GetAura(RUPTURE, me->GetGUID()))
                    {
                        int32 dur = rupture->GetMaxDuration() + 2000;
                        dur = std::min<int32>(dur, 30000);
                        rupture->SetDuration(dur);
                        rupture->SetMaxDuration(dur);
                        Rupture_Timer = dur - 2000;
                    }
                }
            }

            //Cut to the Chase: Eviscerate and Envenom will refresh Slice and Dice duration
            //getting cheaty - increase duration
            if (spellId == EVISCERATE/* || spellId == ENVENOM*/)
            {
                if (Aura* dice = me->GetAura(SLICE_DICE))
                {
                    int32 dur = dice->GetMaxDuration() + 2000;
                    dur = std::min<int32>(dur, 59000);
                    dice->SetDuration(dur);
                    dice->SetMaxDuration(dur);
                    Slice_Dice_Timer = dur - 2000;
                }
            }

            //Murderous Intent: When Backstabbing enemy that is below 35% hp, instantly restoring 30 energy
            if (spellId == BACKSTAB)
            {
                if (target->HealthBelowPct(35))
                {
                    //since talent doesn't work just restore energy manually
                    //DoCast(me, MURDEROUS_INTENT_EFFECT, true);
                    modenergy(30);
                }
            }

            //Waylay
            if (spellId == BACKSTAB/* || spellId == AMBUSH*/)
            {
                DoCast(target, WAYLAY_EFFECT, true);
            }

            //if (spellId == SHADOWSTEP)
            //{
            //    Shadowstep_eff_Timer = 10000;
            //    shadowstep = true;
            //}

            //move behind on Kidney Shot and Gouge (optionally)
            if (spellId == KIDNEY_SHOT/* || spellId == GOUGE*/)
                if (MoveBehind(*target))
                    wait = 3;

            if (spellId == currentSpell)
                currentSpell = 0;
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
            Mutilate_Timer = 0;
            Rupture_Timer = 0;
            Dismantle_Timer = 0;
            Kick_Timer = 0;
            Kidney_Timer = 0;
            Shadowstep_Timer = 0;
            Blade_Flurry_Timer = 0;
            Slice_Dice_Timer = 0;
            //Shadowstep_eff_Timer = 0;

            comboPoints = 0;
            tempComboPoints = 0;
            tempAddCP = 0;

            KidneyTarget = 0;
            RuptureTarget = 0;

            tempDICE = false;
            //shadowstep = false;

            me->setPowerType(POWER_ENERGY);
            //10 energy gained per stack
            RefreshAura(GLADIATOR_VIGOR, 10);

            if (master)
            {
                setStats(CLASS_ROGUE, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_ROGUE);
            }

            me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (Kick_Timer > diff)                  Kick_Timer -= diff;
            if (Rupture_Timer > diff)               Rupture_Timer -= diff;
            if (Shadowstep_Timer > diff)            Shadowstep_Timer -= diff;
            if (Mutilate_Timer > diff)              Mutilate_Timer -= diff;
            if (Kidney_Timer > diff)                Kidney_Timer -= diff;
            if (Dismantle_Timer > diff)             Dismantle_Timer -= diff;
            if (Blade_Flurry_Timer > diff)          Blade_Flurry_Timer -= diff;
            if (Slice_Dice_Timer > diff)            Slice_Dice_Timer -= diff;
            //if (Shadowstep_eff_Timer > diff)        Shadowstep_eff_Timer -= diff;
            //else if (shadowstep)                    shadowstep = false;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            BACKSTAB                                = InitSpell(me, BACKSTAB_1);
            SINISTER_STRIKE                         = InitSpell(me, SINISTER_STRIKE_1);
            SLICE_DICE                              = InitSpell(me, SLICE_DICE_1);
            EVISCERATE                              = InitSpell(me, EVISCERATE_1);
            KICK                                    = InitSpell(me, KICK_1);
            RUPTURE                                 = InitSpell(me, RUPTURE_1);
            KIDNEY_SHOT                             = InitSpell(me, KIDNEY_SHOT_1);
            MUTILATE                    = lvl >= 10 ? MUTILATE_1 : 0;
            SHADOWSTEP                  = lvl >= 15 ? SHADOWSTEP_1 : 0;
            DISMANTLE                               = InitSpell(me, DISMANTLE_1);
            BLADE_FLURRY                = lvl >= 20 ? BLADE_FLURRY_1 : 0;

            WOUND_POISON                            = InitSpell(me, WOUND_POISON_1);
            MIND_NUMBING_POISON                     = InitSpell(me, MIND_NUMBING_POISON_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();

            if (level >= 67)
                RefreshAura(COMBAT_POTENCY3,2);
            else if (level >= 43)
                RefreshAura(COMBAT_POTENCY3);
            else if (level >= 41)
                RefreshAura(COMBAT_POTENCY2);
            else if (level >= 39)
                RefreshAura(COMBAT_POTENCY1);
            if (level >= 40)
                RefreshAura(SEAL_FATE);
            if (level >= 82)
                RefreshAura(VITALITY,4);
            else if (level >= 67)
                RefreshAura(VITALITY,3);
            else if (level >= 58)
                RefreshAura(VITALITY,2);
            else if (level >= 40)
                RefreshAura(VITALITY);
            if (level >= 21)
                RefreshAura(QUICKENING2);
            else if (level >= 19)
                RefreshAura(QUICKENING1);
            if (level >= 57)
                RefreshAura(TURN_THE_TABLES);
            if (level >= 30)
                RefreshAura(DEADLY_BREW);
            if (level >= 39)
                RefreshAura(BLADE_TWISTING1);//allow rank 1 only
            if (level >= 15)
                RefreshAura(QUICK_RECOVERY2);
            if (level >= 35)
                RefreshAura(IMPROVED_KIDNEY_SHOT);
            if (level >= 10)
                RefreshAura(GLYPH_BACKSTAB);
            if (level >= 10)
                RefreshAura(SURPRISE_ATTACKS);
            if (level >= 11)
                RefreshAura(IMPROVED_KICK);

            if (level >= 82)
                RefreshAura(ROGUE_VIGOR,3);
            else if (level >= 35)
                RefreshAura(ROGUE_VIGOR,2);
            else if (level >= 10)
                RefreshAura(ROGUE_VIGOR);
        }

    private:
        uint32
            BACKSTAB, SINISTER_STRIKE, SLICE_DICE, EVISCERATE, KICK, RUPTURE, KIDNEY_SHOT, MUTILATE,
            SHADOWSTEP, DISMANTLE, BLADE_FLURRY,
            WOUND_POISON, MIND_NUMBING_POISON;
        //Timers/other
        uint64 KidneyTarget, RuptureTarget;
        uint32 Rupture_Timer, Dismantle_Timer,
            Kick_Timer, Shadowstep_Timer, Mutilate_Timer, Kidney_Timer,
            Blade_Flurry_Timer, Slice_Dice_Timer/*, Shadowstep_eff_Timer*/;
        uint32 energy;
        uint8 comboPoints, tempComboPoints, tempAddCP;
        bool tempDICE/*, shadowstep*/;

        enum RogueBaseSpells
        {
            BACKSTAB_1                          = 53,
            SINISTER_STRIKE_1                   = 1752,
            SLICE_DICE_1                        = 5171,
            EVISCERATE_1                        = 2098,
            KICK_1                              = 1766,
            RUPTURE_1                           = 1943,
            KIDNEY_SHOT_1                       = 408,
  /*Talent*/MUTILATE_1                          = 1329,
  /*Talent*/SHADOWSTEP_1                        = 36554,
            DISMANTLE_1                         = 51722,
            BLADE_FLURRY_1                      = 33735,
        //Special
            WOUND_POISON_1                      = 13218,
            MIND_NUMBING_POISON_1               = 5760
        };

        enum RoguePassives
        {
            //Talents
            SEAL_FATE                           = 14190,
            COMBAT_POTENCY1                     = 35541,
            COMBAT_POTENCY2                     = 35550,
            COMBAT_POTENCY3                     = 35551,
            //QUICK_RECOVERY1                     = 31244,//deprecated
            QUICK_RECOVERY2                     = 31245,//deprecated
            BLADE_TWISTING1                     = 31124,
            //BLADE_TWISTING2                     = 31126,
            VITALITY                            = 61329,
            DEADLY_BREW                         = 51626,//rank 2
            IMPROVED_KICK                       = 13867,
            //434 talents
            QUICKENING1                         = 31208,
            QUICKENING2                         = 31209,
            //Other
            IMPROVED_KIDNEY_SHOT                = 14176,//3.3.5 talent, deprecated
            TURN_THE_TABLES                     = 51629,//3.3.5 talent, deprecated
            SURPRISE_ATTACKS                    = 32601,//3.3.5 talent, deprecated
            ROGUE_VIGOR                         = 14983,//3.3.5 talent, deprecated
            GLADIATOR_VIGOR                     = 21975,
            GLYPH_BACKSTAB                      = 56800
        };

        enum RogueSpecial
        {
            RELENTLESS_STRIKES_EFFECT           = 14181,
            RUTHLESSNESS_EFFECT                 = 14157,
            SEAL_FATE_EFFECT                    = 14189,
            //SHADOWSTEP_EFFECT_DAMAGE            = 36563,
            TURN_THE_TABLES_EFFECT              = 52910,//'rank 3'
            WAYLAY_EFFECT                       = 51693,
            //434
            MURDEROUS_INTENT_EFFECT             = 79132
        };
    };
};

void AddSC_rogue_bot()
{
    new rogue_bot();
}
