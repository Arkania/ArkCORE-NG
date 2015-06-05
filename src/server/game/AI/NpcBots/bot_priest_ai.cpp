#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "WorldSession.h"
/*
Priest NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Around 50%
TODO: maybe remove Divine Spirit or so, too much buffs
*/
class priest_bot : public CreatureScript
{
public:
    priest_bot() : CreatureScript("priest_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new priest_botAI(creature);
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

    struct priest_botAI : public bot_minion_ai
    {
        priest_botAI(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_PRIEST) != SPELL_CAST_OK)
                return false;
            return bot_ai::doCast(victim, spellId, triggered);
        }

        bool MassGroupHeal(Player* player, uint32 diff)
        {
            if (!PRAYER_OF_HEALING && !DIVINE_HYMN) return false;
            if (!player->GetGroup()) return false;
            if (Rand() > 30) return false;
            if (IsCasting()) return false;

            if (DIVINE_HYMN && Divine_Hymn_Timer <= diff)
            {
                Group* gr = player->GetGroup();
                uint8 LHPcount = 0;
                for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer || !tPlayer->IsInWorld() || me->GetMap() != tPlayer->FindMap() ||
                        tPlayer->IsBeingTeleported() || tPlayer->IsPossessed() || tPlayer->IsCharmed()) continue;
                    if (tPlayer->IsAlive())
                    {
                        if (me->GetExactDist(tPlayer) > 35) continue;
                        uint8 pct = 50 + tPlayer->getAttackers().size()*10;
                        pct = pct < 80 ? pct : 80;
                        if (GetHealthPCT(tPlayer) < pct && GetLostHP(tPlayer) > 4000)
                            ++LHPcount;
                    }
                    if (LHPcount > 1)
                        break;
                    if (!tPlayer->HaveBot()) continue;
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (bot && GetHealthPCT(bot) < 40 && me->GetExactDist(bot) < 30)
                            ++LHPcount;
                        if (LHPcount > 1)
                            break;
                    }
                }
                if (LHPcount > 1 && doCast(me, DIVINE_HYMN))
                {
                    Divine_Hymn_Timer = 180000; //3 min
                    return true;
                }
            }
            if (PRAYER_OF_HEALING)
            {
                Group* gr = player->GetGroup();
                Unit* castTarget = NULL;
                uint8 LHPcount = 0;
                for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    uint8 lowestPCT = 100;
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer || !tPlayer->IsInWorld() || me->GetMap() != tPlayer->GetMap() ||
                        tPlayer->IsBeingTeleported() || tPlayer->IsPossessed() || tPlayer->IsCharmed()) continue;
                    if (tPlayer->IsAlive())
                    {
                        if (me->GetExactDist(tPlayer) > 25) continue;
                        if (GetHealthPCT(tPlayer) < 85)
                        {
                            ++LHPcount;
                            if (GetHealthPCT(tPlayer) < lowestPCT)
                            lowestPCT = GetHealthPCT(tPlayer);
                            castTarget = tPlayer;
                        }
                    }
                    if (LHPcount > 2)
                        break;
                    if (!tPlayer->HaveBot()) continue;
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (bot && GetHealthPCT(bot) < 70 && me->GetExactDist(bot) < 15)
                        {
                            ++LHPcount;
                            if (GetHealthPCT(bot) < lowestPCT)
                            lowestPCT = GetHealthPCT(bot);
                            castTarget = bot;
                        }
                        if (LHPcount > 2)
                            break;
                    }
                }
                if (LHPcount > 2 && castTarget && doCast(castTarget, PRAYER_OF_HEALING))
                    return true;
            }
            return false;
        }//end MassGroupHeal

        bool ShieldTarget(Unit* target, uint32 diff)
        {
            if (!PW_SHIELD || PWS_Timer > diff || Rand() > 50 || IsCasting())
                return false;
            if (target->getAttackers().empty() &&
                GetHealthPCT(target) > 33 &&
                !target->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return false;
            if (target->HasAura(WEAKENED_SOUL_DEBUFF) || HasAuraName(target, PW_SHIELD))
                return false;
            //if (me->GetExactDist(target) > 40) return false;//checked already in HealTarget()

            if (doCast(target, PW_SHIELD))
            {
                if (me->getLevel() >= 30 ||
                    (target->ToCreature() && target->ToCreature()->GetBotAI()))
                    PWS_Timer = 1000;
                else
                    PWS_Timer = 3000;
                GC_Timer = 800;
                return true;
            }
            return false;
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            GetInPosition(force, true);
            SetBotCommandState(COMMAND_ATTACK);
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            if (!me->GetVictim())
                Evade();
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            Disperse(diff);
            BreakCC(diff);
            if (CCed(me)) return;
            DoDevCheck(diff);

            if (GetManaPCT(me) < 33 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }
            //check possible fear
            doDefend(diff);
            //buff and heal master's group
            MassGroupHeal(master, diff);
            BuffAndHealGroup(master, diff);
            CureGroup(master, DISPELMAGIC, diff);
            CureGroup(master, CURE_DISEASE, diff);
            //ShieldGroup(master);
            if (master->IsInCombat() || me->IsInCombat())
            {
                CheckDispel(diff);
                CheckSilence(diff);
            }

            if (me->IsInCombat())
                CheckShackles(diff);
            else
                DoNonCombatActions(diff);

            if (!CheckAttackTarget(CLASS_PRIEST))
                return;

            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();

            if (GetHealthPCT(master) > 90 && GetManaPCT(me) > 35 && GetHealthPCT(me) > 90 &&
                (m_attackers.size() < 4 || b_attackers.size() + m_attackers.size() < 3) &&
                !IsCasting())
                //general rule
            {
                opponent = me->GetVictim();
                if (opponent)
                {
                    if (!IsCasting())
                        StartAttack(opponent);
                }
                else
                    return;
                float dist = me->GetExactDist(opponent);
                if (dist < 40)
                {
                    if (SW_DEATH && SW_Death_Timer <= diff && Rand() < 50 && opponent->GetHealthPct() < 25 &&
                        doCast(opponent, SW_DEATH))
                    {
                        SW_Death_Timer = 8000;
                        return;
                    }
                    if (SW_PAIN && GC_Timer <= diff && Rand() < 25 &&
                        opponent->GetHealth() > me->GetMaxHealth()/4 &&
                        !opponent->HasAura(SW_PAIN, me->GetGUID()) &&
                        doCast(opponent, SW_PAIN))
                        return;
                    if (VAMPIRIC_TOUCH && GC_Timer <= diff && Rand() < 50 &&
                        opponent->GetHealth() > me->GetMaxHealth()/4 &&
                        !opponent->HasAura(VAMPIRIC_TOUCH, me->GetGUID()) &&
                        doCast(opponent, VAMPIRIC_TOUCH))
                        return;
                    if (DEVOURING_PLAGUE && GC_Timer <= diff && !Devcheck && Rand() < 30 &&
                        opponent->GetHealth() > me->GetMaxHealth()/3 &&
                        !opponent->HasAura(DEVOURING_PLAGUE, me->GetGUID()) &&
                        doCast(opponent, DEVOURING_PLAGUE))
                        return;
                    if (MIND_BLAST && Mind_Blast_Timer <= diff && GC_Timer <= 300 && Rand() < 35 &&
                        (!VAMPIRIC_TOUCH || HasAuraName(opponent, VAMPIRIC_TOUCH)) &&
                        doCast(opponent, MIND_BLAST))
                    {
                        Mind_Blast_Timer = 6000;
                        return;
                    }
                    if (MIND_FLAY && Mind_Flay_Timer <= diff && !me->isMoving() && Rand() < 20 &&
                        (opponent->isMoving() || opponent->GetHealth() < me->GetMaxHealth()/5 ||
                        (opponent->HasAura(SW_PAIN, me->GetGUID()) && opponent->HasAura(DEVOURING_PLAGUE, me->GetGUID()))) &&
                        doCast(opponent, MIND_FLAY))
                    {
                        Mind_Flay_Timer = 2500;
                        return;
                    }
                    if (MIND_SEAR && GC_Timer <= diff && !me->isMoving() && !opponent->isMoving() &&
                        dist < 35 && Rand() < 50 && opponent->HasAura(SW_PAIN, me->GetGUID()) &&
                        opponent->HasAura(DEVOURING_PLAGUE, me->GetGUID()))
                    {
                        if (Unit* u = FindSplashTarget(30, opponent))
                            if (doCast(u, MIND_SEAR))
                                return;
                    }
                }//endif opponent
            }//endif damage
            //check horror after dots/damage
            if (PSYCHIC_HORROR && Psychic_Horror_Timer <= diff &&
                opponent->GetCreatureType() != CREATURE_TYPE_UNDEAD &&
                opponent->GetHealth() > me->GetMaxHealth()/5 && Rand() < 30 &&
                me->GetExactDist(opponent) < 30 && !HasAuraName(opponent, PSYCHIC_HORROR) &&
                !CCed(opponent))
            {
                if (doCast(opponent, PSYCHIC_HORROR))
                {
                    Psychic_Horror_Timer = 60000;
                    return;
                }
            }
        }//end UpdateAI

        bool HealTarget(Unit* target, uint8 hp, uint32 diff)
        {
            if (hp > 98)
                return false;
            if (!target || !target->IsAlive() || me->GetExactDist(target) > 40)
                return false;
            if (Rand() > 50 + 20*target->IsInCombat() + 50*master->GetMap()->IsRaid())
                return false;

            //GUARDIAN SPIRIT
            if (GUARDIAN_SPIRIT && Guardian_Spirit_Timer <= diff && target->IsInCombat() &&
                !target->getAttackers().empty() && hp < (5 + std::min(20, uint8(target->getAttackers().size())*5)) &&
                ((master->GetGroup() && master->GetGroup()->IsMember(target->GetGUID())) || target == master) &&
                Rand() < 80 &&
                !target->HasAura(GUARDIAN_SPIRIT))
            {
                temptimer = GC_Timer;
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                if (doCast(target, GUARDIAN_SPIRIT))
                {
                    GC_Timer = temptimer;
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        //if (target->HasAura(GUARDIAN_SPIRIT, me->GetGUID()))
                            me->MonsterWhisper("Guardin Spirit on you!", target->ToPlayer());
                        Guardian_Spirit_Timer = 90000; //1.5 min
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "Guardin Spirit on " << (target == me ? "myself" : target->GetName()) << '!';
                        me->MonsterWhisper(msg.str().c_str(), master);
                        Guardian_Spirit_Timer = 30000; //30 sec for creatures
                    }

                    return true;
                }
            }

            if (IsCasting()) return false;

            //PAIN SUPPRESSION
            if (hp < 35 && PAIN_SUPPRESSION && Pain_Suppression_Timer <= diff &&
                (target->IsInCombat() || !target->getAttackers().empty()) && Rand() < 50 &&
                !target->HasAura(PAIN_SUPPRESSION))
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                temptimer = GC_Timer;
                if (doCast(target, PAIN_SUPPRESSION))
                {
                    GC_Timer = temptimer;
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (target->HasAura(PAIN_SUPPRESSION, me->GetGUID()))
                            me->MonsterWhisper("Pain Suppression on you!", target->ToPlayer());
                        Pain_Suppression_Timer = 60000; //60 sec
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "Guardin Spirit on " << (target == me ? "myself" : target->GetName()) << '!';
                        me->MonsterWhisper(msg.str().c_str(), master);
                        Pain_Suppression_Timer = 15000; //15 sec for creatures
                    }

                    return true;
                }
            }

            //Now Heals Requires GCD
            if (PWS_Timer <= diff && (hp < 80 || !target->getAttackers().empty()) &&
                ShieldTarget(target, diff))
                return true;

            //PENANCE/Greater Heal
            if (hp < 75 || GetLostHP(target) > 4000)
            {
                if (PENANCE && Penance_Timer <= diff && !me->isMoving() && Rand() < 80 &&
                    (target->GetTypeId() != TYPEID_PLAYER ||
                    !(target->ToPlayer()->IsCharmed() || target->ToPlayer()->IsPossessed())) &&
                    doCast(target, PENANCE))
                {
                    Penance_Timer = 8000;
                    return true;
                }
                else if (HEAL && Heal_Timer <= diff && GC_Timer <= diff && hp > 50 && Rand() < 70 &&
                    doCast(target, HEAL))
                {
                    Heal_Timer = 2500;
                    return true;
                }
            }
            //Flash Heal
            if (FLASH_HEAL && GC_Timer <= diff &&
                ((hp > 75 && hp < 90) || hp < 50 || GetLostHP(target) > 1500) &&
                doCast(target, FLASH_HEAL))
                return true;
            //maintain HoTs
            Unit* u = target->GetVictim();
            Creature* boss = u && u->ToCreature() && u->ToCreature()->isWorldBoss() ? u->ToCreature() : NULL;
            bool tanking = tank == target && boss;
            //Renew
            if (RENEW && GC_Timer <= diff &&
                ((hp < 98 && hp > 70) || GetLostHP(target) > 500 || tanking) &&
                !target->HasAura(RENEW, me->GetGUID()) &&
                doCast(target, RENEW))
            {
                GC_Timer = 800;
                return true;
            }

            return false;
        }

        bool BuffTarget(Unit* target, uint32 diff)
        {
            if (GC_Timer > diff || Rand() > 20)
                return false;
            if (!target || !target->IsInWorld() || target->IsDead() || me->GetExactDist(target) > 30)
                return false;

            if (FEAR_WARD && Fear_Ward_Timer <= diff && !target->HasAura(FEAR_WARD) &&
                doCast(target, FEAR_WARD))
            {
                Fear_Ward_Timer = target->GetTypeId() == TYPEID_PLAYER ? 60000 : 30000; //30sec for bots
                GC_Timer = 800;
                return true;
            }

            if (target == me)
            {
                if (INNER_FIRE && !me->HasAura(INNER_FIRE) &&
                    doCast(me, INNER_FIRE))
                {
                    GC_Timer = 800;
                    return true;
                }
                if (VAMPIRIC_EMBRACE && !me->HasAura(VAMPIRIC_EMBRACE) &&
                    doCast(me, VAMPIRIC_EMBRACE))
                {
                    GC_Timer = 800;
                    return true;
                }
            }

            if (me->IsInCombat() && !master->GetMap()->IsRaid()) return false;

            if (PW_FORTITUDE && !HasAuraName(target, PW_FORTITUDE) &&
                doCast(target, PW_FORTITUDE))
            {
                /*GC_Timer = 800;*/
                return true;
            }
            if (SHADOW_PROTECTION && !HasAuraName(target, SHADOW_PROTECTION) &&
                doCast(target, SHADOW_PROTECTION))
            {
                /*GC_Timer = 800;*/
                return true;
            }

            return false;
        }

        void DoNonCombatActions(uint32 diff)
        {
            if (Rand() > 50 || GC_Timer > diff || me->IsMounted())
                return;

            RezGroup(RESURRECTION, master);

            if (Feasting())
                return;

            //if (BuffTarget(master, diff))
            //    return;
            //if (BuffTarget(me, diff))
            //    return;
        }

        void CheckDispel(uint32 diff)
        {
            if (!DISPELMAGIC || CheckDispelTimer > diff || Rand() > 25 || IsCasting())
                return;

            Unit* target = FindHostileDispelTarget();
            if (target && doCast(target, DISPELMAGIC))
            {
                CheckDispelTimer = 3000;
                GC_Timer = 500;
            }
            CheckDispelTimer = 1000;
        }

        void CheckShackles(uint32 diff)
        {
            if (!SHACKLE_UNDEAD || ShackleTimer > diff || GC_Timer > diff || Rand() > 50 || IsCasting())
                return;
            if (FindAffectedTarget(SHACKLE_UNDEAD, me->GetGUID()))
            {
                ShackleTimer = 1500;
                return;
            }
            Unit* target = FindUndeadCCTarget(30, SHACKLE_UNDEAD);
            if (target && doCast(target, SHACKLE_UNDEAD))
            {
                ShackleTimer = 3000;
                GC_Timer = 800;
            }
        }

        void CheckSilence(uint32 diff)
        {
            if (IsCasting()) return;
            temptimer = GC_Timer;
            if (SILENCE && Silence_Timer <= diff)
            {
                if (Unit* target = FindCastingTarget(30))
                    if (doCast(target, SILENCE))
                        Silence_Timer = 30000;
            }
            else if (PSYCHIC_HORROR && Psychic_Horror_Timer <= 20000)
            {
                if (Unit* target = FindCastingTarget(30))
                    if (doCast(target, PSYCHIC_HORROR))
                        Psychic_Horror_Timer = 60000;
            }
            GC_Timer = temptimer;
        }

        void doDefend(uint32 diff)
        {
            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();
            //fear master's attackers
            if (PSYCHIC_SCREAM && Fear_Timer <= diff && !m_attackers.empty() &&
                (master != tank || GetHealthPCT(master) < 75))
            {
                uint8 tCount = 0;
                for (AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
                {
                    if (!(*iter)) continue;
                    if ((*iter)->ToCreature() && (*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                    if (me->GetExactDist((*iter)) > 7) continue;
                    if (CCed(*iter) && me->GetExactDist((*iter)) > 5) continue;
                    if (me->IsValidAttackTarget(*iter))
                        ++tCount;
                }
                if (tCount > 1 && doCast(me, PSYCHIC_SCREAM))
                {
                    Fear_Timer = 22000;
                    return;
                }
            }

            // Defend myself (psychic horror)
            if (!b_attackers.empty() && PSYCHIC_SCREAM && Fear_Timer <= diff)
            {
                uint8 tCount = 0;
                for (AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                {
                    if (!(*iter)) continue;
                    if ((*iter)->ToCreature() && (*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                    if (me->GetExactDist((*iter)) > 7) continue;
                    if (CCed(*iter) && me->GetExactDist((*iter)) > 5) continue;
                    if (me->IsValidAttackTarget(*iter))
                        ++tCount;
                }
                if (tCount > 0 && doCast(me, PSYCHIC_SCREAM))
                {
                    Fear_Timer = 22000;
                    return;
                }
            }
            // Heal myself
            if (GetHealthPCT(me) < 98 && !b_attackers.empty())
            {
                if (ShieldTarget(me, diff)) return;

                if (FADE && Fade_Timer <= diff && me->IsInCombat())
                {
                    if (b_attackers.empty()) return;
                    uint8 Tattackers = 0;
                    for (AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->IsDead()) continue;
                        if (!(*iter)->ToCreature()) continue;
                        if (!(*iter)->CanHaveThreatList()) continue;
                        if (me->GetExactDist((*iter)) < 15)
                            Tattackers++;
                    }
                    if (Tattackers > 0)
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, FADE))
                        {
                            for (AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                                if ((*iter)->getThreatManager().getThreat(me) > 0.f)
                                    (*iter)->getThreatManager().modifyThreatPercent(me, -50);
                            Fade_Timer = 10000;
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
                if (GetHealthPCT(me) < 90 && HealTarget(me, GetHealthPCT(me), diff))
                    return;
            }
        }

        void DoDevCheck(uint32 diff)
        {
            if (!DEVOURING_PLAGUE)
                return;

            if (DevcheckTimer <= diff)
            {
                Devcheck = FindAffectedTarget(DEVOURING_PLAGUE, me->GetGUID());
                DevcheckTimer = 5000;
            }
        }

        void Disperse(uint32 diff)
        {
            if (!DISPERSION || Dispersion_Timer > diff || GC_Timer > diff || IsCasting())
                return;
            if ((me->getAttackers().size() > 3 && Fade_Timer > diff && GetHealthPCT(me) < 90) ||
                (GetHealthPCT(me) < 20 && me->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE)) ||
                (GetManaPCT(me) < 30) ||
                (me->getAttackers().size() > 1 && me->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_ROOT))))
            {
                temptimer = GC_Timer;
                if (doCast(me, DISPERSION))
                    Dispersion_Timer = 60000;
                GC_Timer = temptimer;
                return;
            }

            Dispersion_Timer = 2000;//fail
        }

        void ApplyClassDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;
                //434 new
                //Improved Fire Blast (part 1): 8% additional crit chance for Fire Blast
                //if (lvl >= 11 && spellId == FLAMESTRIKE)
                //    aftercrit += 8.f;

                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                ////!!!spell damage is not yet critical and will be multiplied by 1.5
                ////so we should put here bonus damage mult /1.5
                ////Ice Shards: 50% additional crit damage bonus for Frost spells
                //else if (lvl >= 15 && (SPELL_SCHOOL_MASK_FROST & spellInfo->GetSchoolMask()))
                //    pctbonus += 0.333f;
            }
            //Twin Disciplines (damage part): 6% bonus damage for shadow and holy spells
            if (lvl >= 13)
                if ((SPELL_SCHOOL_MASK_HOLY & spellInfo->GetSchoolMask()) ||
                    (SPELL_SCHOOL_MASK_SHADOW & spellInfo->GetSchoolMask()))
                    pctbonus += 0.06f;
            //Twisted Faith (part 1): 2% bonus damage for shadow spells
            if (lvl >= 21 && (SPELL_SCHOOL_MASK_SHADOW & spellInfo->GetSchoolMask()))
                pctbonus += 0.02f;
            //Mind Melt (part 1): 30% bonus damage for Shadow Word: Death
            if (lvl >= 41 && spellId == SW_DEATH)
                pctbonus += 0.3f;

            //Glyph of Mind Flay: 10% damage bonus for Mind Flay
            if (lvl >= 25 && spellId == MIND_FLAY)
                pctbonus += 0.1f;

            //other
            if (spellId == SW_DEATH_BACKLASH)
            {
                //T13 Shadow 2P Bonus (Shadow Word: Death), part 2
                if (lvl >= 60) //buffed
                    pctbonus -= 0.95f;
                //Pain and Suffering (part 2): 40% reduced backlash damage
                if (lvl >= 50)
                    pctbonus -= 0.4f;

                pctbonus = std::min<float>(pctbonus, 1.0f);
            }

            //Spellpower bonus damage (temp)
            if (m_spellpower > 0)
            {
                if (spellId == SW_DEATH)
                {
                    float flat_mod = m_spellpower * 1.876f;
                    //if (victim->GetHealthPct() < 25) //always true
                        flat_mod *= 2.f; // *= 3.f
                    fdamage += flat_mod;
                }
                else if (spellId == MIND_BLAST)
                    fdamage += m_spellpower * 1.909f;
                else if (spellId == MIND_SEAR_DAMAGE)
                    fdamage += m_spellpower * 0.333f;
                else if (spellId == IMPROVED_DEVOURING_PLAGUE_DAMAGE)
                    fdamage += m_spellpower * 0.786f;
                else if (spellId == DEVOURING_PLAGUE)
                    fdamage += m_spellpower * 0.786f; //0.13f
            }

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void ApplyClassDamageMultiplierEffect(SpellInfo const* spellInfo, uint8 effect_index, float& value) const
        {
            uint32 spellId = spellInfo->Id;

            //float pct_mod = 1.f;

            //Spellpower bonus damage (temp)
            if (spellInfo->Effects[effect_index].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE)
            {
                if (spellId == SW_PAIN)
                    value += m_spellpower * 1.76f / float(spellInfo->GetMaxDuration() / spellInfo->Effects[effect_index].Amplitude);
                else if (spellId == VAMPIRIC_TOUCH)
                    value += m_spellpower * 1.73f / float(spellInfo->GetMaxDuration() / spellInfo->Effects[effect_index].Amplitude);
                else if (spellId == MIND_FLAY)
                    value += m_spellpower * 1.51f / float(spellInfo->GetMaxDuration() / spellInfo->Effects[effect_index].Amplitude);
            }

            //value *= pct_mod;
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            //Strength of Soul: direct heals reduce Weakened Soul duration on target by 4 sec
            if (spellId == HEAL || spellId == FLASH_HEAL)
            {
                if (me->getLevel() >= 51)
                {
                    if (Aura* soul = target->GetAura(WEAKENED_SOUL_DEBUFF))
                    {
                        if (soul->GetDuration() > 4000)
                            soul->SetDuration(soul->GetDuration() - 4000);
                        else
                            target->RemoveAura(soul, AURA_REMOVE_BY_EXPIRE);
                    }
                }
            }

            //Pain and Suffering (part 1, 335 version): 100% to refresh Shadow Word: Pain on target hit by Mind Flay
            if (spellId == MIND_FLAY)
                if (me->getLevel() >= 51)
                    if (Aura* pain = target->GetAura(SW_PAIN, me->GetGUID()))
                        pain->RefreshDuration();

            if (spellId == FEAR_WARD)
            {
                //2 minutes bonus duration for Fear Ward
                if (Aura* ward = target->GetAura(FEAR_WARD, me->GetGUID()))
                {
                    uint32 dur = ward->GetDuration() + 120000;
                    ward->SetDuration(dur);
                    ward->SetMaxDuration(dur);
                }
            }

            if (spellId == INNER_FIRE || spellId == VAMPIRIC_EMBRACE || spellId == PW_FORTITUDE ||
                spellId == SHADOW_PROTECTION)
            {
                //1 hour duration for all buffs
                if (Aura* buff = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = HOUR * IN_MILLISECONDS;
                    buff->SetDuration(dur);
                    buff->SetMaxDuration(dur);
                }
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
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
            Heal_Timer = 0;
            Divine_Hymn_Timer = 0;
            Pain_Suppression_Timer = 0;
            Guardian_Spirit_Timer = 0;
            PWS_Timer = 0;
            Fade_Timer = 0;
            Fear_Timer = 0;
            Mind_Blast_Timer = 0;
            SW_Death_Timer = 0;
            Fear_Ward_Timer = 0;
            Psychic_Horror_Timer = 0;
            Silence_Timer = 0;
            Dispersion_Timer = 0;
            Mind_Flay_Timer = 0;
            Penance_Timer = 0;
            CheckDispelTimer = 0;
            ShackleTimer = 0;
            DevcheckTimer = 20;
            Devcheck = false;

            if (master)
            {
                setStats(CLASS_PRIEST, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_PRIEST);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (Heal_Timer > diff)                 Heal_Timer -= diff;
            if (Fade_Timer > diff)                 Fade_Timer -= diff;
            if (Divine_Hymn_Timer > diff)          Divine_Hymn_Timer -= diff;
            if (Pain_Suppression_Timer > diff)     Pain_Suppression_Timer -= diff;
            if (Guardian_Spirit_Timer > diff)      Guardian_Spirit_Timer -= diff;
            if (PWS_Timer > diff)                  PWS_Timer -= diff;
            if (Fear_Timer > diff)                 Fear_Timer -= diff;
            if (Mind_Blast_Timer > diff)           Mind_Blast_Timer -= diff;
            if (SW_Death_Timer > diff)             SW_Death_Timer -= diff;
            if (Fear_Ward_Timer > diff)            Fear_Ward_Timer -= diff;
            if (Psychic_Horror_Timer > diff)       Psychic_Horror_Timer -= diff;
            if (Silence_Timer > diff)              Silence_Timer -= diff;
            if (Dispersion_Timer > diff)           Dispersion_Timer -= diff;
            if (Mind_Flay_Timer > diff)            Mind_Flay_Timer -= diff;
            if (Penance_Timer > diff)              Penance_Timer -= diff;
            if (CheckDispelTimer > diff)           CheckDispelTimer -= diff;
            if (ShackleTimer > diff)               ShackleTimer -= diff;
            if (DevcheckTimer > diff)              DevcheckTimer -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            DISPELMAGIC                 = lvl >= 72 ? MASS_DISPEL_1 : InitSpell(me, DISPEL_MAGIC_1);
            CURE_DISEASE                            = InitSpell(me, CURE_DISEASE_1);
            FEAR_WARD                               = InitSpell(me, FEAR_WARD_1);
  /*Talent*/PAIN_SUPPRESSION            = lvl >= 49 ? PAIN_SUPPRESSION_1 : 0;
            PSYCHIC_SCREAM                          = InitSpell(me, PSYCHIC_SCREAM_1);
            FADE                                    = InitSpell(me, FADE_1);
  /*Talent*/PSYCHIC_HORROR              = lvl >= 59 ? PSYCHIC_HORROR_1 : 0;
  /*Talent*/SILENCE                     = lvl >= 39 ? SILENCE_1 : 0;
            PENANCE                     = lvl >= 11 ? PENANCE_1 : 0;
  /*Talent*/VAMPIRIC_EMBRACE            = lvl >= 40 ? VAMPIRIC_EMBRACE_1 : 0;
  /*Talent*/DISPERSION                  = lvl >= 67 ? DISPERSION_1 : 0;
            MIND_SEAR                               = InitSpell(me, MIND_SEAR_1);
  /*Talent*/GUARDIAN_SPIRIT             = lvl >= 68 ? GUARDIAN_SPIRIT_1 : 0;
            SHACKLE_UNDEAD                          = InitSpell(me, SHACKLE_UNDEAD_1);
            HEAL                        = lvl >= 38 ? GREATER_HEAL_1 : InitSpell(me, LESSER_HEAL_1);
            RENEW                                   = InitSpell(me, RENEW_1);
            FLASH_HEAL                              = InitSpell(me, FLASH_HEAL_1);
            PRAYER_OF_HEALING                       = InitSpell(me, PRAYER_OF_HEALING_1);
            DIVINE_HYMN                             = InitSpell(me, DIVINE_HYMN_1);
            RESURRECTION                            = InitSpell(me, RESURRECTION_1);
            PW_SHIELD                               = InitSpell(me, PW_SHIELD_1);
            INNER_FIRE                              = InitSpell(me, INNER_FIRE_1);
            PW_FORTITUDE                            = InitSpell(me, PW_FORTITUDE_1);
            SHADOW_PROTECTION                       = InitSpell(me, SHADOW_PROTECTION_1);
            SW_PAIN                                 = InitSpell(me, SW_PAIN_1);
            MIND_BLAST                              = InitSpell(me, MIND_BLAST_1);
            SW_DEATH                                = InitSpell(me, SW_DEATH_1);
            DEVOURING_PLAGUE                        = InitSpell(me, DEVOURING_PLAGUE_1);
            MIND_FLAY                   = lvl >= 10 ? MIND_FLAY_1 : 0;
  /*Talent*/VAMPIRIC_TOUCH              = lvl >= 49 ? VAMPIRIC_TOUCH_1 : 0;
        }
        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 43)
                RefreshAura(BORROWED_TIME); //14% haste
            if (level >= 55)
                RefreshAura(DIVINE_AEGIS); //30% absorb
            if (level >= 31)
                RefreshAura(DIVINE_TOUCH2); //10%
            else if (level >= 29)
                RefreshAura(DIVINE_TOUCH1); //5%
            if (level >= 45)
                RefreshAura(BODY_AND_SOUL); //30%
            if (level >= 60)
                RefreshAura(GRACE); //8% x3
            if (level >= 21)
                RefreshAura(IMPROVED_DEVOURING_PLAGUE); //30%
            if (level >= 21)
                RefreshAura(INSPIRATION2); //10%
            else if (level >= 19)
                RefreshAura(INSPIRATION1); //5%
            //434 new
            if (level >= 61)
                RefreshAura(BLESSED_RESILIENCE);
            if (level >= 31)
                RefreshAura(PHANTASM);
            if (level >= 41)
                RefreshAura(MASOCHISM);
            if (level >= 51)
                RefreshAura(PARALYSIS);
            if (level >= 61)
                RefreshAura(SIN_AND_PUNISHMENT);
            //Glyphs
            if (level >= 25)
                RefreshAura(GLYPH_PW_SHIELD); //20% heal
            //434
            if (level >= 25)
                RefreshAura(GLYPH_PRAYER_OF_HEALING); //HoT 20% heal over 6 sec
            //Special
            if (level >= 29)
                RefreshAura(MIND_QUICKENING);
            if (level >= 70)
                RefreshAura(PRIEST_T10_2P_BONUS);
        }

    private:
        uint32
   /*Buffs*/INNER_FIRE, PW_FORTITUDE, SHADOW_PROTECTION,
    /*Disc*/FEAR_WARD, PAIN_SUPPRESSION, SHACKLE_UNDEAD, PW_SHIELD, DISPELMAGIC, CURE_DISEASE, PENANCE,
    /*Holy*/HEAL, FLASH_HEAL, RENEW, PRAYER_OF_HEALING, DIVINE_HYMN, GUARDIAN_SPIRIT, RESURRECTION,
  /*Shadow*/SW_PAIN, MIND_BLAST, SW_DEATH, DEVOURING_PLAGUE, MIND_FLAY, VAMPIRIC_TOUCH, MIND_SEAR,
  /*Shadow*/PSYCHIC_SCREAM, FADE, PSYCHIC_HORROR, VAMPIRIC_EMBRACE, DISPERSION, SILENCE;
        //Timers/other
/*Disc*/uint32 Penance_Timer, PWS_Timer, Pain_Suppression_Timer, Fear_Ward_Timer;
/*Holy*/uint32 Heal_Timer, Divine_Hymn_Timer, Guardian_Spirit_Timer;
/*Shdw*/uint32 Fade_Timer, Fear_Timer, Mind_Blast_Timer, SW_Death_Timer, Mind_Flay_Timer,
/*Shdw*/    Psychic_Horror_Timer, Silence_Timer, Dispersion_Timer;
/*Misc*/uint16 CheckDispelTimer, ShackleTimer, DevcheckTimer;
/*Misc*/bool Devcheck;

        enum PriestBaseSpells
        {
            DISPEL_MAGIC_1                      = 527,
            MASS_DISPEL_1                       = 32375,
            CURE_DISEASE_1                      = 528,
            FEAR_WARD_1                         = 6346,
  /*Talent*/PAIN_SUPPRESSION_1                  = 33206,
            PSYCHIC_SCREAM_1                    = 8122,
            FADE_1                              = 586,
  /*Talent*/PSYCHIC_HORROR_1                    = 64044,
  /*Talent*/SILENCE_1                           = 15487,
            PENANCE_1                           = 47540,
  /*Talent*/VAMPIRIC_EMBRACE_1                  = 15286,
  /*Talent*/DISPERSION_1                        = 47585,
            MIND_SEAR_1                         = 48045,
  /*Talent*/GUARDIAN_SPIRIT_1                   = 47788,
            SHACKLE_UNDEAD_1                    = 9484,
            LESSER_HEAL_1                       = 2050,
            GREATER_HEAL_1                      = 2060,
            RENEW_1                             = 139,
            FLASH_HEAL_1                        = 2061,
            PRAYER_OF_HEALING_1                 = 596,
            DIVINE_HYMN_1                       = 64843,
            RESURRECTION_1                      = 2006,
            PW_SHIELD_1                         = 17,
            INNER_FIRE_1                        = 588,
            PW_FORTITUDE_1                      = 21562,
            SHADOW_PROTECTION_1                 = 27683,
            SW_PAIN_1                           = 589,
            MIND_BLAST_1                        = 8092,
            SW_DEATH_1                          = 32379,
            DEVOURING_PLAGUE_1                  = 2944,
            MIND_FLAY_1                         = 15407,
  /*Talent*/VAMPIRIC_TOUCH_1                    = 34914
        };
        enum PriestPassives
        {
        //Talents
            IMPROVED_DEVOURING_PLAGUE       = 63626,//rank 2
            DIVINE_AEGIS                    = 47515,//rank 3
            BORROWED_TIME                   = 52797,//rank 2
            GRACE                           = 47517,//rank 2
            DIVINE_TOUCH1                   = 63534,
            DIVINE_TOUCH2                   = 63542,
            INSPIRATION1                    = 14892,
            INSPIRATION2                    = 15362,
            BODY_AND_SOUL                   = 64127,//rank 1
            //434 new
            BLESSED_RESILIENCE              = 33145,//rank 2
            PHANTASM                        = 47570,//rank 2
            MASOCHISM                       = 88995,//rank 2
            PARALYSIS                       = 87195,//rank 2
            SIN_AND_PUNISHMENT              = 87100,//rank 2
        //Glyphs
            GLYPH_PW_SHIELD                 = 55672,
            //434
            GLYPH_PRAYER_OF_HEALING         = 55680,
        //Special
            MIND_QUICKENING                 = 49868,//shadowform part 2
        //other
            PRIEST_T10_2P_BONUS             = 70770,//33% renew
        };
        enum PriestSpecial
        {
            IMPROVED_DEVOURING_PLAGUE_DAMAGE= 63675,
            MIND_SEAR_DAMAGE                = 49821,
            SW_DEATH_BACKLASH               = 32409,
            WEAKENED_SOUL_DEBUFF            = 6788
        };
    };
};

void AddSC_priest_bot()
{
    new priest_bot();
}
