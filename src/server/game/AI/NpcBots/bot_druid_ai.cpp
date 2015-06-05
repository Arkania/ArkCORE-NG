#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "WorldSession.h"
/*
Druid NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Maybe 30%
TODO: Feral Spells (from scratch), More Forms, Balance Spells + treants...
*/
class druid_bot : public CreatureScript
{
public:
    druid_bot() : CreatureScript("druid_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new bot_druid_ai(creature);
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

    struct bot_druid_ai : public bot_minion_ai
    {
        bot_druid_ai(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_DRUID) != SPELL_CAST_OK)
                return false;

            info = sSpellMgr->GetSpellInfo(spellId);
            if (me->GetShapeshiftForm() == FORM_NONE && swiftness && info->CalcCastTime() > 0)
            {
                DoCast(victim, spellId, true);
                me->RemoveAurasDueToSpell(NATURES_SWIFTNESS, me->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
                me->RemoveAurasDueToSpell(CRIT_50, me->GetGUID(), 0, AURA_REMOVE_BY_EXPIRE);
                swiftness = false;
                return true;
            }
            if (spellId == BEAR_FORM || spellId == CAT_FORM)
            {
                if (tempMana)
                {
                    //remove form if any to make sure we have mana
                    removeFeralForm(true);
                }
                else
                {
                    me->ModifyPower(POWER_MANA, -(info->CalcPowerCost(me, info->GetSchoolMask())));
                    tempMana = me->GetPower(POWER_MANA);
                }

                if (Unit* u = me->GetVictim())
                    GetInPosition(true, false, u);
            }

            bool result = bot_ai::doCast(victim, spellId, triggered);

            if (result &&
                //spellId != BEAR_FORM && spellId != CAT_FORM &&
                spellId != MANAPOTION && spellId != WARSTOMP &&
                me->HasAura(OMEN_OF_CLARITY_BUFF))
            {
                cost = info->CalcPowerCost(me, info->GetSchoolMask());
                clearcast = true;
                power = me->getPowerType();
            }
            return result;
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { removeFeralForm(false); master->SetNpcBotDied(me->GetGUID()); }

        uint8 GetBotStance() const
        {
            switch (me->GetShapeshiftForm())
            {
                case FORM_BEAR:
                case FORM_DIREBEAR:
                    return DRUID_BEAR_FORM;
                case FORM_CAT:
                    return DRUID_CAT_FORM;
            }

            return CLASS_DRUID;
        }

        void warstomp(uint32 diff)
        {
            if (me->getRace() != RACE_TAUREN) return;
            if (Warstomp_Timer > diff) return;

            AttackerSet b_attackers = me->getAttackers();

            if (b_attackers.empty())
            {
                Unit* u = me->SelectNearestTarget(6);
                if (u && u->IsInCombat() && u->isTargetableForAttack())
                {
                    if (doCast(me, WARSTOMP))
                    {
                        Warstomp_Timer = 30000; //30sec
                        return;
                    }
                }
            }
            for(AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
            {
                if (!(*iter) || (*iter)->IsDead()) continue;
                if (!(*iter)->isTargetableForAttack()) continue;
                if (me->GetDistance((*iter)) <= 6)
                {
                    if (doCast(me, WARSTOMP))
                        Warstomp_Timer = 30000; //30sec
                }
            }
        }

        bool DamagePossible()
        {
            return true;
            //return (GetManaPCT(me) < 30 || GetHealthPCT(master) < 50);
            /*if (GetHealthPCT(master) < 75 || GetHealthPCT(me) < 75) return false;

            if (Group* pGroup = master->GetGroup())
            {
                uint8 LHPcount = 0;
                uint8 DIScount = 0;
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer || tPlayer->IsDead()) continue;
                    if (me->GetExactDist(tPlayer) > 30) continue;
                    if (tPlayer->GetHealth()*100 / tPlayer->GetMaxHealth() < 75)
                        ++LHPcount;
                    Unit::AuraApplicationMap const& auras = tPlayer->GetAppliedAuras();
                    for (Unit::AuraApplicationMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                        if (itr->second->GetBase()->GetSpellInfo()->Dispel == DISPEL_POISON)
                            ++DIScount;
                }
                uint8 members = master->GetGroup()->GetMembersCount();

                if (members > 10)
                {
                    if (LHPcount > 1 || DIScount > 2) return false;
                }
                if (members > 4)
                {
                    if (LHPcount > 0 || DIScount > 1) return false;
                }
                if (members < 5)
                {
                    if (LHPcount > 0 || DIScount > 0) return false;
                }
            }//endif unitlist

            Unit* u = master->GetVictim();
            if (master->getAttackers().size() > 4 ||
              (!master->getAttackers().empty() &&
                u != NULL && u->GetHealth() > me->GetMaxHealth()*17))
                return false;

            return true;*/
        }

        void removeFeralForm(bool recast)
        {
            ShapeshiftForm form = me->GetShapeshiftForm();
            if (form != FORM_NONE)
            {
                switch (form)
                {
                case FORM_BEAR:
                    me->RemoveAurasDueToSpell(BEAR_FORM);
                    break;
                case FORM_CAT:
                    me->RemoveAurasDueToSpell(CAT_FORM);
                    me->RemoveAurasDueToSpell(ENERGIZE);
                    break;
                default:
                    break;
                }
                SetStats(CLASS_DRUID, recast);
                //prevent using mana restore while jumping between forms (434)
                Potion_cd = std::max<uint32>(Potion_cd, 1500);
                Innervate_Timer = std::max<uint32>(Innervate_Timer, 1500);
            }
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force, me->GetShapeshiftForm() == FORM_NONE);
        }

        void doBearActions(uint32 diff)
        {
            if (me->getPowerType() != POWER_RAGE) return;

            if (GetHealthPCT(me) < 75)
                if (HealTarget(me, GetHealthPCT(me), diff))
                    return;
            opponent = me->GetVictim();
            if (opponent)
                StartAttack(opponent, true);
            else
                return;

            //range check (melee) to prevent fake casts
            if (me->GetDistance(opponent) > 5) return;

            if (MANGLE_BEAR && MangleB_Timer <= diff && GC_Timer <= diff && rage >= 150 && Rand() < 35 &&
                doCast(opponent, MANGLE_BEAR))
            {
                MangleB_Timer = 6000;
                return;
            }

            if (SWIPE && GC_Timer <= diff && rage >= 150 && Rand() < 75 &&
                doCast(opponent, SWIPE))
                return;

        }//end doBearActions

        void doCatActions(uint32 diff)
        {
            if (me->getPowerType() != POWER_ENERGY) return;

            if (GetHealthPCT(me) < 75)
                if (HealTarget(me, GetHealthPCT(me), diff))
                    return;
            opponent = me->GetVictim();
            if (opponent)
                StartAttack(opponent, true);
            else
                return;
            uint32 energy = me->GetPower(POWER_ENERGY);

            if (MoveBehind(*opponent))
                wait = 5;

            //range check (melee) to prevent fake casts
            if (me->GetDistance(opponent) > 5) return;

            if (MANGLE_CAT && Mangle_Cat_Timer <= diff && GC_Timer <= diff && energy > 45 && Rand() < 35 &&
                doCast(opponent, MANGLE_CAT))
            {
                Mangle_Cat_Timer = 6000;
                return;
            }
            if (RAKE && Rake_Timer <= diff && GC_Timer <= diff && energy > 40 && Rand() < 30 &&
                doCast(opponent, RAKE))
            {
                Rake_Timer = 10000;
                return;
            }
            if (SHRED && Shred_Timer <= diff && GC_Timer <= diff && energy > 60 && !opponent->HasInArc(M_PI, me) && Rand() < 50 &&
                doCast(opponent, SHRED))
            {
                Shred_Timer = 12000;
                return;
            }
            if (RIP && Rip_Timer <= diff && GC_Timer <= diff && energy > 30 && Rand() < 30 &&
                doCast(opponent, RIP))
            {
                Rip_Timer = 15000;
                return;
            }
            if (CLAW && GC_Timer <= diff && energy > 45 && Rand() < 80 &&
                doCast(opponent, CLAW))
                return;
        }//end doCatActions

        void doBalanceActions(uint32 diff)
        {
            removeFeralForm(false);
            opponent = me->GetVictim();
            if (opponent)
            {
                if (!IsCasting())
                    StartAttack(opponent);
            }
            else
                return;
            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();

            //range check to prevent fake casts
            if (me->GetExactDist(opponent) > 30 || !DamagePossible()) return;

            if (HURRICANE && Hurricane_Timer <= diff && GC_Timer <= diff && !me->isMoving() && Rand() < 35)
            {
                Unit* target = FindAOETarget(30, true);
                if (target && doCast(target, HURRICANE))
                {
                    Hurricane_Timer = 5000;
                    return;
                }
                Hurricane_Timer = 2000; //fail
            }
            if (FAERIE_FIRE && GC_Timer <= diff &&
                opponent->getAttackers().size() > 1 && //check if faerie fire is not useless 50/50
                Rand() < 20)
            {
                Aura* ff = opponent->GetAura(FAERIE_FIRE/*, me->GetGUID()*/);
                if (!ff || ff->GetStackAmount() < 3)
                    if (doCast(opponent, FAERIE_FIRE))
                        return;
            }
            if (MOONFIRE && Moonfire_Timer <= diff && GC_Timer <= diff && Rand() < 20 &&
                !opponent->HasAura(MOONFIRE, me->GetGUID()))
            {
                if (doCast(opponent, MOONFIRE))
                {
                    Moonfire_Timer = 5000;
                    return;
                }
            }
            if (STARFIRE && Starfire_Timer <= diff && GC_Timer <= diff && Rand() < 50)
            {
                if (doCast(opponent, STARFIRE))
                {
                    Starfire_Timer = 11000;
                    return;
                }
            }
            if (WRATH && Wrath_Timer <= diff && GC_Timer <= diff && Rand() < 40)
            {
                if (doCast(opponent, WRATH))
                {
                    Wrath_Timer = uint32(sSpellMgr->GetSpellInfo(WRATH)->CalcCastTime()/100 * me->GetFloatValue(UNIT_MOD_CAST_SPEED) + 1);
                    return;
                }
            }
        }

        bool MassGroupHeal(Player* gPlayer, uint32 diff)
        {
            if (!gPlayer || GC_Timer > diff) return false;
            if (!TRANQUILITY && !WILD_GROWTH) return false;
            if (Tranquility_Timer > diff && Wild_Growth_Timer > diff) return false;
            if (Rand() > 30) return false;
            if (IsCasting()) return false; // if I'm already casting
            Group* pGroup = gPlayer->GetGroup();
            if (!pGroup) return false;
            uint8 LHPcount = 0;
            uint8 pct = 100;
            Unit* healTarget = NULL;
            for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* tPlayer = itr->GetSource();
                if (!tPlayer || !tPlayer->IsInWorld() || tPlayer->GetMapId() != me->GetMapId() ||
                    (tPlayer->IsDead() && !tPlayer->HaveBot())) continue;
                if (me->GetExactDist(tPlayer) > 39) continue;
                if (GetHealthPCT(tPlayer) < 80)
                {
                    if (GetHealthPCT(tPlayer) < pct)
                    {
                        pct = GetHealthPCT(tPlayer);
                        healTarget = tPlayer;
                    }
                    ++LHPcount;
                    if (LHPcount > 2) break;
                }
                if (tPlayer->HaveBot())
                {
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (bot && bot->IsInWorld() && bot->GetExactDist(me) < 40 && GetHealthPCT(bot) < 80)
                        {
                            if (GetHealthPCT(bot) < pct)
                            {
                                pct = GetHealthPCT(bot);
                                healTarget = bot;
                            }
                            ++LHPcount;
                            if (LHPcount > 2) break;
                        }
                    }
                }
            }
            if (LHPcount > 2 && TRANQUILITY && Tranquility_Timer <= diff &&
                doCast(me, TRANQUILITY))
                { Tranquility_Timer = 60000; return true; }
            if (LHPcount > 0 && WILD_GROWTH && Wild_Growth_Timer <= diff &&
                doCast(healTarget, WILD_GROWTH))
                { Wild_Growth_Timer = 6000; return true; }
            return false;
        }//end MassGroupHeal

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (me->GetShapeshiftForm() == FORM_BEAR && me->getPowerType() != POWER_RAGE)
                me->setPowerType(POWER_RAGE);
            if (me->GetShapeshiftForm() == FORM_CAT && me->getPowerType() != POWER_ENERGY)
                me->setPowerType(POWER_ENERGY);
            if (me->GetShapeshiftForm() == FORM_NONE && me->getPowerType() != POWER_MANA)
                me->setPowerType(POWER_MANA);
            if (IAmDead()) return;
            if (!me->GetVictim())
                Evade();
            else if (me->GetShapeshiftForm() == FORM_BEAR || me->GetShapeshiftForm() == FORM_CAT)
                DoMeleeAttackIfReady();

            if (me->GetShapeshiftForm() == FORM_BEAR)
            {
                rage = me->GetPower(POWER_RAGE);
                if (ragetimer <= diff)
                {
                    if (!me->IsInCombat())
                    {
                        if (rage > 10.f*rageLossMult)
                            me->SetPower(POWER_RAGE, rage - uint32(10.f*rageLossMult)); //-1 rage per 1.5 sec
                        else
                            me->SetPower(POWER_RAGE, 0);
                    }
                    ragetimer = 1500;
                    if (rage > 1000) me->SetPower(POWER_RAGE, 1000);
                    if (rage < 10) me->SetPower(POWER_RAGE, 0);
                }
            }
            if (clearcast && me->HasAura(OMEN_OF_CLARITY_BUFF) && !me->IsNonMeleeSpellCast(false))
            {
                me->ModifyPower(power, cost);
                me->RemoveAurasDueToSpell(OMEN_OF_CLARITY_BUFF,me->GetGUID(),0,AURA_REMOVE_BY_EXPIRE);
                clearcast = false;
            }
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            BreakCC(diff);
            if (CCed(me)) return;
            warstomp(diff);

            if (Potion_cd <= diff && me->getPowerType() == POWER_MANA && GetManaPCT(me) < 20)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }

            //Heal master
            if (GetHealthPCT(master) < 85)
                HealTarget(master, GetHealthPCT(master), diff);
            //Innervate
            doInnervate(diff);

            MassGroupHeal(master, diff);
            if (!me->IsInCombat())
                DoNonCombatActions(diff);
            else
                CheckBattleRez(diff);
            BuffAndHealGroup(master, diff);
            CureTarget(master, REMOVE_CORRUPTION, diff);
            CureGroup(master, REMOVE_CORRUPTION, diff);

            if (!CheckAttackTarget(CLASS_DRUID))
                return;

            //debug
            opponent = me->GetVictim();

            if (GetHealthPCT(me) < 75)
            {
                HealTarget(me, GetHealthPCT(me), diff);
                return;
            }

            if (IsCasting()) return; //Casting heal or something
            CheckRoots(diff);

            if (DamagePossible() && opponent != NULL)
            {
                Unit* u = opponent->GetVictim();
                //if the target is attacking us, we want to go bear
                if (BEAR_FORM && !CCed(opponent) &&
                    (u == me || (tank == me && IsInBotParty(u))) ||
                    (!me->getAttackers().empty() && (*me->getAttackers().begin()) == opponent && opponent->GetMaxHealth() > me->GetMaxHealth()*2))
                {
                    //if we don't have bear yet
                    if (me->GetShapeshiftForm() != FORM_BEAR && formtimer <= diff &&
                        doCast(me, BEAR_FORM))
                    {
                        SetStats(DRUID_BEAR_FORM);
                        formtimer = 1500;
                    }
                    if (me->GetShapeshiftForm() == FORM_BEAR)
                        doBearActions(diff);
                }
                else
                if (CAT_FORM && master->GetVictim() != opponent && tank && u == tank && u != me &&
                    opponent->GetMaxHealth() < tank->GetMaxHealth()*3)
                {
                    //if we don't have cat yet
                    if (me->GetShapeshiftForm() != FORM_CAT && formtimer <= diff)
                    {
                        if (doCast(me, CAT_FORM))
                        {
                            SetStats(DRUID_CAT_FORM);
                            formtimer = 1500;
                        }
                    }
                    if (me->GetShapeshiftForm() == FORM_CAT)
                        doCatActions(diff);
                }
                else if (tank != me)
                    doBalanceActions(diff);
            }
            else if (tank != me)
                doBalanceActions(diff);
        }

        bool HealTarget(Unit* target, uint8 hp, uint32 diff)
        {
            if (hp > 95) return false;
            if (!target || target->IsDead()) return false;
            if (tank == me && hp > 35) return false;
            if (hp > 50 && me->GetShapeshiftForm() != FORM_NONE) return false;//do not waste heal if in feral or so
            if (Rand() > 50 + 20*target->IsInCombat() + 50*master->GetMap()->IsRaid() - 50*me->GetShapeshiftForm()) return false;
            if (me->GetExactDist(target) > 40) return false;

            //TODO: Narture swiftness 434
            if ((hp < 15 || (hp < 35 && target->getAttackers().size() > 2)) &&
                Nature_Swiftness_Timer <= diff && (target->IsInCombat() || !target->getAttackers().empty()))
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                if (NATURES_SWIFTNESS && doCast(me, NATURES_SWIFTNESS) && RefreshAura(CRIT_50, 2))
                {
                    swiftness = true;
                    if (doCast(target, HEALING_TOUCH, true))
                    {
                        Nature_Swiftness_Timer = 120000; //2 min
                        Heal_Timer = 3000;
                        return true;
                    }
                }
            }
            if (SWIFTMEND && (hp < 25 || GetLostHP(target) > 5000) && Swiftmend_Timer <= 3000 &&
                (HasAuraName(target, REGROWTH) || HasAuraName(target, REJUVENATION)))
            {
                if (doCast(target, SWIFTMEND))
                {
                    Swiftmend_Timer = 10000;
                    if (GetHealthPCT(target) > 75)
                        return true;
                    else if (!target->getAttackers().empty())
                    {
                        if (doCast(target, REGROWTH))
                        {
                            GC_Timer = 300;
                            return true;
                        }
                    }
                }
            }
            if (hp > 35 && (hp < 75 || GetLostHP(target) > 3000) && Heal_Timer <= diff && NOURISH)
            {
                switch (urand(1,3))
                {
                    case 1:
                    case 2:
                        if (doCast(target, NOURISH))
                        {
                            Heal_Timer = 3000;
                            return true;
                        }
                        break;
                    case 3:
                        if (doCast(target, HEALING_TOUCH))
                        {
                            Heal_Timer = 3000;
                            return true;
                        }
                        break;
                }
            }
            //maintain HoTs
            Unit* u = target->GetVictim();
            Creature* boss = u && u->ToCreature() && u->ToCreature()->isWorldBoss() ? u->ToCreature() : NULL;
            bool tanking = tank == target && boss;
            if (( (hp < 80 || GetLostHP(target) > 3500 || tanking) &&
                Regrowth_Timer <= diff && GC_Timer <= diff && !target->HasAura(REGROWTH, me->GetGUID()) )
                ||
                (target->HasAura(REGROWTH, me->GetGUID()) && target->HasAura(REJUVENATION, me->GetGUID()) &&
                (hp < 70 || GetLostHP(target) > 3000) && Regrowth_Timer <= diff && GC_Timer <= diff))
            {
                if (doCast(target, REGROWTH))
                { Regrowth_Timer = 2000; return true; }
            }
            if (hp > 25 && (hp < 90 || GetLostHP(target) > 2000 || tanking) && GC_Timer <= diff &&
                !HasAuraName(target, REJUVENATION, me->GetGUID()))
            {
                if (doCast(target, REJUVENATION))
                {
                    if (!target->getAttackers().empty() && (hp < 75 || GetLostHP(target) > 4000))
                        if (SWIFTMEND && Swiftmend_Timer <= diff && doCast(target, SWIFTMEND))
                            Swiftmend_Timer = 10000;
                    GC_Timer = 500;
                    return true;
                }
            }
            if (LIFEBLOOM != 0 && GC_Timer <= diff &&
                ((hp < 85 && hp > 40) || (hp > 70 && tanking) ||
                (hp < 70 && hp > 25 && HasAuraName(target, REGROWTH) && HasAuraName(target, REJUVENATION)) ||
                (GetLostHP(target) > 1500 && hp > 35)))
            {
                Aura* bloom = target->GetAura(LIFEBLOOM, me->GetGUID());
                if ((!bloom || bloom->GetStackAmount() < 3) && doCast(target, LIFEBLOOM))
                    return true;
            }
            if (hp > 30 && (hp < 70 || GetLostHP(target) > 3000) && Heal_Timer <= diff &&
                doCast(target, HEALING_TOUCH))
            {
                Heal_Timer = 3000;
                return true;
            }
            return false;
        }

        bool BuffTarget(Unit* target, uint32 diff)
        {
            if (GC_Timer > diff || Rand() > 20) return false;

            if (target && target->IsAlive() && me->GetExactDist(target) < 30)
            {
                if (Thorns_Timer <= diff && me->GetShapeshiftForm() == FORM_NONE &&
                    !target->getAttackers().empty() && !HasAuraName(target, THORNS))
                {
                    if (doCast(target, THORNS))
                    {
                        Thorns_Timer = target->ToCreature() ? 10000 : 45000;
                        return true;
                    }
                    //fail
                    Thorns_Timer = 2500;
                }
                if (!me->IsInCombat() || master->GetMap()->IsRaid())
                    if (!HasAuraName(target, MARK_OF_THE_WILD))
                        if (doCast(target, MARK_OF_THE_WILD))
                            return true;
            }
            return false;
        }

        void DoNonCombatActions(uint32 diff)
        {
            if (GC_Timer > diff || me->IsMounted()) return;

            RezGroup(REVIVE, master);

            //if eating or drinking don't do anything but rez
            if (Feasting()) return;

            if (BuffTarget(master, diff))
            {
                /*GC_Timer = 800;*/
                return;
            }
            if (BuffTarget(me, diff))
            {
                /*GC_Timer = 800;*/
                return;
            }
        }

        void doInnervate(uint32 diff, uint8 minmanaval = 50)
        {
            if (!INNERVATE || Innervate_Timer > diff || GC_Timer > diff || Rand() > 15) return;
            if (me->GetShapeshiftForm() != FORM_NONE && (tank == me || me->getAttackers().size() > 3)) return;

            Unit* iTarget = NULL;

            if (master->IsInCombat() && master->getPowerType() == POWER_MANA &&
                GetManaPCT(master) < 20 && !master->HasAura(INNERVATE))
                iTarget = master;
            else if (me->IsInCombat() && me->getPowerType() == POWER_MANA &&
                GetManaPCT(me) < 20 && !me->HasAura(INNERVATE))
                iTarget = me;

            Group* group = master->GetGroup();
            if (!iTarget && !group) //first check master's bots
            {
                for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
                {
                    Creature* bot = master->GetBotMap(i)->_Cre();
                    if (!bot || !bot->IsInCombat() || bot->IsDead()) continue;
                    if (me->GetExactDist(bot) > 30) continue;
                    if (bot->getPowerType() != POWER_MANA) continue;
                    if (GetManaPCT(bot) < minmanaval && !bot->HasAura(INNERVATE))
                    {
                        iTarget = bot;
                        break;
                    }
                }
            }
            if (!iTarget && group) //cycle through player members...
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (tPlayer == NULL || !tPlayer->IsInWorld() || !tPlayer->IsInCombat() || tPlayer->IsDead()) continue;
                    if (me->GetExactDist(tPlayer) > 30) continue;
                    if (tPlayer->getPowerType() != POWER_MANA) continue;
                    if (GetManaPCT(tPlayer) < minmanaval && !tPlayer->HasAura(INNERVATE))
                    {
                        iTarget = tPlayer;
                        break;
                    }
                    if (iTarget)
                        break;
                }
            }
            if (!iTarget && group) //... and their bots.
            {
                for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (tPlayer == NULL || !tPlayer->HaveBot()) continue;
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (!bot || bot->IsDead()) continue;
                        if (me->GetExactDist(bot) > 30) continue;
                        if (bot->getPowerType() != POWER_MANA) continue;
                        if (GetManaPCT(bot) < minmanaval && !bot->HasAura(INNERVATE))
                        {
                            iTarget = bot;
                            break;
                        }
                    }
                    if (iTarget)
                        break;
                }
            }

            //fail
            if (!iTarget)
            {
                Innervate_Timer = 3000;
                return;
            }

            if (doCast(iTarget, INNERVATE))
            {
                if (iTarget->GetTypeId() == TYPEID_PLAYER)
                    me->MonsterWhisper("Innervate on You!", iTarget->ToPlayer());
                else
                {
                    std::ostringstream msg;
                    msg << "Innervate on " << (iTarget == me ? "myself" : iTarget->GetName()) << '!';
                    me->MonsterWhisper(msg.str().c_str(), master);
                }

                Innervate_Timer = iTarget->GetTypeId() == TYPEID_PLAYER ? 60000 : 20000; //1 min if player and 20 sec if bot
            }
        }

        void CheckRoots(uint32 diff)
        {
            if (!ENTANGLING_ROOTS || GC_Timer > diff || Rand() > 35) return;
            if (me->GetShapeshiftForm() != FORM_NONE) return;
            if (FindAffectedTarget(ENTANGLING_ROOTS, me->GetGUID(), 60)) return;
            if (Unit* target = FindRootTarget(33, ENTANGLING_ROOTS))
                if (doCast(target, ENTANGLING_ROOTS))
                    return;
        }

        void CheckBattleRez(uint32 diff)
        {
            if (!REBIRTH || Rebirth_Timer > diff || Rand() > 10 || IsCasting() || me->IsMounted()) return;
            Group* gr = master->GetGroup();
            if (!gr)
            {
                Unit* target = master;
                if (master->IsAlive()) return;
                if (master->IsRessurectRequested()) return; //ressurected
                if (master->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                    target = (Unit*)master->GetCorpse();
                if (!target || !target->IsInWorld())
                    return;
                if (me->GetExactDist(target) > 40)
                {
                    me->GetMotionMaster()->MovePoint(master->GetMapId(), *target);
                    Rebirth_Timer = 1500;
                    return;
                }
                else if (!target->IsWithinLOSInMap(me))
                    me->Relocate(*target);

                if (doCast(target, REBIRTH)) //rezzing
                {
                    me->MonsterWhisper("Rezzing You", master);
                    Rebirth_Timer = me->getLevel() >= 60 ? 300000 : 600000; //5-10 min (improved possible)
                }
                return;
            }
            for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* tPlayer = itr->GetSource();
                Unit* target = tPlayer;
                if (!tPlayer || tPlayer->IsAlive()) continue;
                if (tPlayer->IsRessurectRequested()) continue; //ressurected
                if (tPlayer->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                    target = (Unit*)tPlayer->GetCorpse();
                if (!target || !target->IsInWorld()) continue;
                if (master->GetMap() != target->FindMap()) continue;
                if (me->GetExactDist(target) > 30)
                {
                    me->GetMotionMaster()->MovePoint(target->GetMapId(), *target);
                    Rebirth_Timer = 1500;
                    return;
                }
                else if (!target->IsWithinLOSInMap(me))
                    me->Relocate(*target);

                if (doCast(target, REBIRTH)) //rezzing
                {
                    me->MonsterWhisper("Rezzing You", tPlayer);
                    Rebirth_Timer = me->getLevel() >= 60 ? 300000 : 600000; //5-10 min (improved possible)
                    return;
                }
            }
        }

        void SetStats(uint8 form, bool reshapeshift = false)
        {
            switch (form)
            {
                case DRUID_BEAR_FORM:
                    me->SetBotClass(DRUID_BEAR_FORM);
                    me->setPowerType(POWER_RAGE);
                    me->SetMaxPower(POWER_RAGE, 1000);
                    //me->SetPower(POWER_RAGE, me->getLevel() >= 11 ? 200 : 0);
                    if (me->getLevel() >= 40 && !me->HasAura(LEADER_OF_THE_PACK_BUFF))
                        RefreshAura(LEADER_OF_THE_PACK_BUFF);
                    setStats(DRUID_BEAR_FORM, me->getRace(), master->getLevel());
                    break;
                case DRUID_CAT_FORM:
                    me->SetBotClass(DRUID_CAT_FORM);
                    me->setPowerType(POWER_ENERGY);
                    me->SetMaxPower(POWER_ENERGY, 100);
                    //me->SetPower(POWER_ENERGY, me->getLevel() >= 11 ? 100 : 0);
                    if (me->getLevel() >= 40 && !me->HasAura(LEADER_OF_THE_PACK_BUFF))
                        RefreshAura(LEADER_OF_THE_PACK_BUFF);
                    RefreshAura(ENERGIZE, me->getLevel()/41 + 1);
                    setStats(DRUID_CAT_FORM, me->getRace(), master->getLevel());
                    break;
                case CLASS_DRUID:
                    me->SetBotClass(CLASS_DRUID);
                    me->setPowerType(POWER_MANA);
                    setStats(CLASS_DRUID, me->getRace(), master->getLevel(), false, reshapeshift);
                    //me->SetPower(POWER_MANA, init ? mana : 0);
                    //tempMana = 0;
                    break;
            }
        }

        void ApplyClassDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            //uint8 lvl = me->getLevel();
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
            ////Twin Disciplines (damage part): 6% bonus damage for shadow and holy spells
            //if (lvl >= 13)
            //    if ((SPELL_SCHOOL_MASK_HOLY & spellInfo->GetSchoolMask()) ||
            //        (SPELL_SCHOOL_MASK_SHADOW & spellInfo->GetSchoolMask()))
            //        pctbonus += 0.06f;

            //Spellpower bonus damage (temp)
            if (m_spellpower > 0)
            {
                if (spellId == MOONFIRE)
                    fdamage += m_spellpower * 0.256f;
                else if (spellId == STARFIRE)
                    fdamage += m_spellpower * 1.969f;
                else if (spellId == HURRICANE_DAMAGE)
                    fdamage += m_spellpower * 0.316f;
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
                if (spellId == MOONFIRE)
                    value += m_spellpower * 1.68f / float(spellInfo->GetMaxDuration() / spellInfo->Effects[effect_index].Amplitude);
            }

            //value *= pct_mod;
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
            Regrowth_Timer = 0;
            Swiftmend_Timer = 0;
            Wild_Growth_Timer = 0;
            Tranquility_Timer = 10000;
            Nature_Swiftness_Timer = 15000;
            Rebirth_Timer = 10000;
            Warstomp_Timer = 0;
            MangleB_Timer = 0;
            Claw_Timer = 0;
            Rake_Timer = 0;
            Shred_Timer = 0;
            Rip_Timer = 0;
            Mangle_Cat_Timer = 0;
            Moonfire_Timer = 0;
            Starfire_Timer = 0;
            Wrath_Timer = 0;
            Hurricane_Timer = 0;
            Innervate_Timer = 0;
            Thorns_Timer = 0;
            formtimer = 0;
            clearcast = false;
            swiftness = false;
            power = POWER_MANA;
            //mana = 0;
            rage = 0;
            rageIncomeMult = sWorld->getRate(RATE_POWER_RAGE_INCOME);
            rageLossMult = sWorld->getRate(RATE_POWER_RAGE_LOSS);
            ragetimer = 0;

            if (master)
            {
                setStats(CLASS_DRUID, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_DRUID);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (MangleB_Timer > diff)               MangleB_Timer -= diff;
            if (Claw_Timer > diff)                  Claw_Timer -= diff;
            if (Rake_Timer > diff)                  Rake_Timer -= diff;
            if (Shred_Timer > diff)                 Shred_Timer -= diff;
            if (Mangle_Cat_Timer > diff)            Mangle_Cat_Timer -= diff;
            if (Moonfire_Timer > diff)              Moonfire_Timer -= diff;
            if (Starfire_Timer > diff)              Starfire_Timer -= diff;
            if (Wrath_Timer > diff)                 Wrath_Timer -= diff;
            if (Hurricane_Timer > diff)             Hurricane_Timer -= diff;
            if (Innervate_Timer > diff)             Innervate_Timer -= diff;
            if (Rip_Timer > diff)                   Rip_Timer -= diff;
            if (Regrowth_Timer > diff)              Regrowth_Timer -= diff;
            if (Heal_Timer > diff)                  Heal_Timer -= diff;
            if (Swiftmend_Timer > diff)             Swiftmend_Timer -= diff;
            if (Wild_Growth_Timer > diff)           Wild_Growth_Timer -= diff;
            if (Nature_Swiftness_Timer > diff)      Nature_Swiftness_Timer -= diff;
            if (Tranquility_Timer > diff)           Tranquility_Timer -= diff;
            if (Rebirth_Timer > diff)               Rebirth_Timer -= diff;
            if (Thorns_Timer > diff)                Thorns_Timer -= diff;
            if (Warstomp_Timer > diff)              Warstomp_Timer -= diff;
            if (formtimer > diff)                   formtimer -= diff;
            if (ragetimer > diff)                   ragetimer -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            MARK_OF_THE_WILD                        = InitSpell(me, MARK_OF_THE_WILD_1);
            THORNS                                  = InitSpell(me, THORNS_1);
            HEALING_TOUCH                           = InitSpell(me, HEALING_TOUCH_1);
            REGROWTH                                = InitSpell(me, REGROWTH_1);
            REJUVENATION                            = InitSpell(me, REJUVENATION_1);
            LIFEBLOOM                               = InitSpell(me, LIFEBLOOM_1);
            NOURISH                                 = InitSpell(me, NOURISH_1);
     /*tal*/WILD_GROWTH                 = lvl >= 49 ? InitSpell(me, WILD_GROWTH_1) : 0;
            SWIFTMEND                   = lvl >= 11 ? InitSpell(me, SWIFTMEND_1) : 0;
            TRANQUILITY                             = InitSpell(me, TRANQUILITY_1);
            REVIVE                                  = InitSpell(me, REVIVE_1);
            REBIRTH                                 = InitSpell(me, REBIRTH_1);
            BEAR_FORM                               = InitSpell(me, BEAR_FORM_1);
            SWIPE                                   = InitSpell(me, SWIPE_1);
            MANGLE_BEAR                 = lvl >= 10 ? InitSpell(me, MANGLE_BEAR_1) : 0;
            //BASH                                    = InitSpell(me, BASH_1);
            CAT_FORM                                = InitSpell(me, CAT_FORM_1);
            CLAW                                    = InitSpell(me, CLAW_1);
            RAKE                                    = InitSpell(me, RAKE_1);
            SHRED                                   = InitSpell(me, SHRED_1);
            RIP                                     = InitSpell(me, RIP_1);
            MANGLE_CAT                  = lvl >= 10 ? InitSpell(me, MANGLE_CAT_1) : 0;
            MOONFIRE                                = InitSpell(me, MOONFIRE_1);
            STARFIRE                                = InitSpell(me, STARFIRE_1);
            WRATH                                   = InitSpell(me, WRATH_1);
            HURRICANE                               = InitSpell(me, HURRICANE_1);
            FAERIE_FIRE                             = InitSpell(me, FAERIE_FIRE_1);
            REMOVE_CORRUPTION                       = InitSpell(me, REMOVE_CORRUPTION_1);
            INNERVATE                               = InitSpell(me, INNERVATE_1);
            ENTANGLING_ROOTS                        = InitSpell(me, ENTANGLING_ROOTS_1);
     /*tal*/NATURES_SWIFTNESS           = lvl >= 29 ? InitSpell(me, NATURES_SWIFTNESS_1) : 0;
            WARSTOMP                                = WARSTOMP_1;
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 82)
                RefreshAura(SPELLDMG2, 5); //+10%
            else if (level >= 75)
                RefreshAura(SPELLDMG2, 4); //+8%
            else if (level >= 67)
                RefreshAura(SPELLDMG2, 3); //+6%
            else if (level >= 58)
                RefreshAura(SPELLDMG2, 2); //+4%
            else if (level >= 49)
                RefreshAura(SPELLDMG2); //+2%
            if (level >= 82)
                RefreshAura(SPELLDMG, 5); //+15%
            else if (level >= 75)
                RefreshAura(SPELLDMG, 4); //+12%
            else if (level >= 67)
                RefreshAura(SPELLDMG, 3); //+9%
            else if (level >= 58)
                RefreshAura(SPELLDMG, 2); //+6%
            else if (level >= 49)
                RefreshAura(SPELLDMG); //+3%
            if (level >= 45)
                RefreshAura(NATURE_WARD2); //50%
            else if (level >= 43)
                RefreshAura(NATURE_WARD1); //100%
            if (level >= 50)
                RefreshAura(LIVING_SEED3); //100%
            else if (level >= 48)
                RefreshAura(LIVING_SEED2); //66%
            else if (level >= 46)
                RefreshAura(LIVING_SEED1); //33%
            if (level >= 53)
                RefreshAura(REVITALIZE2, 2/*3*/); //20% (2%)x3
            else if (level >= 51)
                RefreshAura(REVITALIZE1, 2/*3*/); //20%  (1%)x3
            if (level >= 70)
                RefreshAura(OMEN_OF_CLARITY, 3); //x3
            else if (level >= 40)
                RefreshAura(OMEN_OF_CLARITY, 2); //x2
            else if (level >= 20)
                RefreshAura(OMEN_OF_CLARITY); //x1
            if (level >= 45)
                RefreshAura(GLYPH_SWIFTMEND); //no comsumption
            if (level >= 40)
                RefreshAura(GLYPH_INNERVATE); //no comsumption
            if (level >= 20)
                RefreshAura(NATURESGRACE);
            if (level >= 12)
                RefreshAura(FUROR);
            if (level >= 78)
            {
                RefreshAura(T9_RESTO_P4_BONUS);
                RefreshAura(T8_RESTO_P4_BONUS);
                RefreshAura(T9_BALANCE_P2_BONUS);
                RefreshAura(T10_BALANCE_P2_BONUS);
                RefreshAura(T10_BALANCE_P4_BONUS);
            }
        }

    private:
        uint32
   /*Buffs*/MARK_OF_THE_WILD, THORNS,
/*Heal/Rez*/HEALING_TOUCH, REGROWTH, REJUVENATION, LIFEBLOOM, NOURISH, WILD_GROWTH, SWIFTMEND, TRANQUILITY, REVIVE, REBIRTH,
    /*Bear*/BEAR_FORM, SWIPE, MANGLE_BEAR,// BASH,
     /*Cat*/CAT_FORM, CLAW, RAKE, SHRED, RIP, MANGLE_CAT,
 /*Balance*/MOONFIRE, STARFIRE, WRATH, HURRICANE, FAERIE_FIRE,
    /*Misc*/REMOVE_CORRUPTION, INNERVATE, ENTANGLING_ROOTS, NATURES_SWIFTNESS, WARSTOMP;
        //Timers/other
/*Heal*/uint32 Heal_Timer, Regrowth_Timer, Swiftmend_Timer, Wild_Growth_Timer,
/*Heal*/    Tranquility_Timer, Nature_Swiftness_Timer, Rebirth_Timer, Thorns_Timer;
/*Bear*/uint32 MangleB_Timer;
/*Cat*/ uint32 Claw_Timer, Rake_Timer, Shred_Timer, Rip_Timer, Mangle_Cat_Timer;
/*Bal*/ uint32 Moonfire_Timer, Starfire_Timer, Wrath_Timer, Hurricane_Timer, Innervate_Timer;
/*Misc*/uint32 formtimer, ragetimer, Warstomp_Timer;
/*Chck*/bool clearcast, swiftness;
/*Misc*/Powers power;
/*Misc*/uint32 /*mana, */rage;
/*Misc*/float rageIncomeMult, rageLossMult;

        enum DruidBaseSpells
        {
            MARK_OF_THE_WILD_1                  = 1126,
            THORNS_1                            = 467,
            HEALING_TOUCH_1                     = 5185,
            REGROWTH_1                          = 8936,
            REJUVENATION_1                      = 774,
            LIFEBLOOM_1                         = 33763,
            NOURISH_1                           = 50464,
     /*tal*/WILD_GROWTH_1                       = 48438,
            SWIFTMEND_1                         = 18562,
            TRANQUILITY_1                       = 740,
            REVIVE_1                            = 50769,
            REBIRTH_1                           = 20484,
            BEAR_FORM_1                         = 5487,
            SWIPE_1                             = 779,
            MANGLE_BEAR_1                       = 33878,
            //BASH_1                              = 5211,
            CAT_FORM_1                          = 768,
            CLAW_1                              = 1082,
            RAKE_1                              = 1822,
            SHRED_1                             = 5221,
            RIP_1                               = 1079,
            MANGLE_CAT_1                        = 33876,
            MOONFIRE_1                          = 8921,
            STARFIRE_1                          = 2912,
            WRATH_1                             = 5176,
            HURRICANE_1                         = 16914,
            FAERIE_FIRE_1                       = 770,
            REMOVE_CORRUPTION_1                 = 2782,
            INNERVATE_1                         = 29166,
            ENTANGLING_ROOTS_1                  = 339,
     /*tal*/NATURES_SWIFTNESS_1                 = 17116,
            WARSTOMP_1                          = 20549
        };
        enum DruidPassives
        {
        //Talents
            OMEN_OF_CLARITY                     = 16864,//clearcast
            NATURESGRACE                        = 61346,//haste 20% for 3 sec
            NATURE_WARD1                        = 33881,
            NATURE_WARD2                        = 33882,
            LIVING_SEED1                        = 48496,//rank 1
            LIVING_SEED2                        = 48499,//rank 2
            LIVING_SEED3                        = 48500,//rank 3
            REVITALIZE1                         = 48539,//rank 1
            REVITALIZE2                         = 48544,//rank 2
            FUROR                               = 17059,//rank 3
        //Glyphs
            GLYPH_SWIFTMEND                     = 54824,//no consumption
            GLYPH_INNERVATE                     = 54832,//self regen
        //other
            T9_RESTO_P4_BONUS                   = 67128,//rejuve crits
            T8_RESTO_P4_BONUS                   = 64760,//rejuve init heal
            T9_BALANCE_P2_BONUS                 = 67125,//moonfire crits
            T10_BALANCE_P2_BONUS                = 70718,//omen of doom (15%)
            T10_BALANCE_P4_BONUS                = 70723,//Languish(DOT)
            SPELLDMG/*Piercing Ice - mage*/     = 15060,//3% crit
            SPELLDMG2/*Earth and Moon - druid*/ = 48511,//2% dam
            ENERGIZE                            = 27787,//Rogue Armor Energize (chance: +35 energy on hit)
            CRIT_50                             = 23434 //50% spell crit
        };
        enum DruidSpecial
        {
            HURRICANE_DAMAGE                    = 42231,
  /*Talent*/LEADER_OF_THE_PACK_BUFF             = 24932,
            //NATURESGRACEBUFF                    = 16886,
            OMEN_OF_CLARITY_BUFF                = 16870 //434 deprecated
        };
    };
};

void AddSC_druid_bot()
{
    new druid_bot();
}
