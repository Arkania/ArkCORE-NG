#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "WorldSession.h"
/*
Paladin NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Around 45-50%
TODO: Tanking, Shield Abilities, Auras
*/
class paladin_bot : public CreatureScript
{
public:
    paladin_bot() : CreatureScript("paladin_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new paladin_botAI(creature);
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

    struct paladin_botAI : public bot_minion_ai
    {
        paladin_botAI(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_PALADIN) != SPELL_CAST_OK)
                return false;
            return bot_ai::doCast(victim, spellId, triggered);
        }

        void HOFGroup(Player* pTarget, uint32 diff)
        {
            if (!HOF || HOF_Timer > diff || GC_Timer > diff || Rand() > 60) return;
            if (IsCasting()) return; //I'm busy

            if (Group* pGroup = pTarget->GetGroup())
            {
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer) continue;
                    if (HOFTarget(tPlayer, diff))
                        return;
                }
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* tPlayer = itr->GetSource();
                    if (!tPlayer || !tPlayer->HaveBot()) continue;
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* cre = tPlayer->GetBotMap(i)->_Cre();
                        if (!cre || !cre->IsInWorld()) continue;
                        if (HOFTarget(cre, diff))
                            return;
                    }
                }
            }
        }

        bool HOFTarget(Unit* target, uint32 diff)
        {
            if (!HOF || HOF_Timer > diff || GC_Timer > diff) return false;
            if (!target || target->IsDead()) return false;
            if (target->ToCreature() && Rand() > 25) return false;
            if (me->GetExactDist(target) > 30) return false;//too far away
            if (HasAuraName(target, HOF)) return false;     //Alredy has HOF

            Unit::AuraMap const &auras = target->GetOwnedAuras();
            for (Unit::AuraMap::const_iterator i = auras.begin(); i != auras.end(); ++i)
            {
                Aura* aura = i->second;
                if (aura->IsPassive()) continue;//most
                if (aura->GetDuration() < 2000) continue;
                if (AuraApplication* app = aura->GetApplicationOfTarget(target->GetGUID()))
                    if (app->IsPositive()) continue;
                SpellInfo const* spellInfo = aura->GetSpellInfo();
                if (spellInfo->AttributesEx & SPELL_ATTR0_HIDDEN_CLIENTSIDE) continue;

                if ((spellInfo->GetAllEffectsMechanicMask() & (1<<MECHANIC_SNARE)) ||
                    (spellInfo->GetAllEffectsMechanicMask() & (1<<MECHANIC_ROOT)))
                {
                    uint32 spell = CLEANSE &&
                        (spellInfo->Dispel == DISPEL_MAGIC ||
                        spellInfo->Dispel == DISPEL_DISEASE ||
                        spellInfo->Dispel == DISPEL_POISON) ? CLEANSE : HOF;

                    if (doCast(target, spell))
                    {
                        if (spell == HOF)
                        {
                            if (target->ToCreature())
                                HOF_Timer = 5000;//5 sec for bots
                            else
                                HOF_Timer = 15000;//improved
                            if (me->getLevel() >= 40)
                                HOFGuid = target->GetGUID();
                        }
                        return true;
                    }
                }
            }
            return false;
        }

        void HOSGroup(Player* hTarget, uint32 diff)
        {
            if (!HOS || HOS_Timer > diff || GC_Timer > diff || Rand() > 30) return;
            if (IsCasting()) return;
            if (Group* pGroup = hTarget->GetGroup())
            {
                bool bots = false;
                float threat;
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* HOSPlayer = itr->GetSource();
                    if (!HOSPlayer) continue;
                    if (HOSPlayer->HaveBot())
                        bots = true;
                    if (HOSPlayer->IsDead()) continue;
                    if (tank && HOSPlayer == tank) continue;//tanks do not need it
                    if (!HOSPlayer->IsInWorld() || master->GetMap() != HOSPlayer->FindMap() || me->GetExactDist(HOSPlayer) > 30) continue;
                    if (HasAuraName(HOSPlayer, HOS)) continue;
                    AttackerSet h_attackers = HOSPlayer->getAttackers();
                    if (h_attackers.empty()) continue;
                    for (AttackerSet::iterator iter = h_attackers.begin(); iter != h_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->IsDead()) continue;
                        if (!(*iter)->CanHaveThreatList()) continue;
                        threat = (*iter)->getThreatManager().getThreat(HOSPlayer);
                        if (threat < 25.f) continue;//too small threat
                        if ((*iter)->getThreatManager().getThreat(tank) < threat * 0.33f) continue;//would be useless
                        if (HOSPlayer->GetDistance((*iter)) > 10) continue;
                        if (HOSTarget(HOSPlayer, diff))
                            return;
                    }//end for
                }//end for
                if (!bots) return;
                for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player* pl = itr->GetSource();
                    if (!pl) continue;
                    if (!pl->HaveBot()) continue;
                    if (master->GetMap() != pl->FindMap()) continue;
                    if (!pl->IsInWorld() || pl->IsBeingTeleported()) continue;
                    for (uint8 i = 0; i != pl->GetMaxNpcBots(); ++i)
                    {
                        Creature* cre = pl->GetBotMap(i)->_Cre();
                        if (!cre || cre->IsDead()) continue;
                        if (cre == tank) continue;
                        if (me->GetExactDist(cre) > 30) continue;
                        if (HasAuraName(cre, HOS)) continue; //Alredy has HOS
                        AttackerSet h_attackers = cre->getAttackers();
                        if (h_attackers.empty()) continue;
                        for (AttackerSet::iterator iter = h_attackers.begin(); iter != h_attackers.end(); ++iter)
                        {
                            if (!(*iter)) continue;
                            if ((*iter)->IsDead()) continue;
                            if (!(*iter)->CanHaveThreatList()) continue;
                            threat = (*iter)->getThreatManager().getThreat(cre);
                            if (threat < 25.f) continue;//too small threat
                            if ((*iter)->getThreatManager().getThreat(tank) < threat * 0.33f) continue;//would be useless
                            if (cre->GetDistance((*iter)) > 10) continue;
                            if (HOSTarget(cre, diff))
                                return;
                        }//end for
                    }//end for
                }//end for
            }//end if
        }

        bool HOSTarget(Unit* target, uint32 diff)
        {
            if (!target || target->IsDead()) return false;
            if (!HOS || HOS_Timer > diff || GC_Timer > diff || Rand() > 50) return false;
            if (target == tank) return false; //tanks do not need it
            if (IsCasting()) return false; //I'm busy casting
            if (me->GetExactDist(target) > 30) return false; //too far away
            if (HasAuraName(target, HOS)) return false; //Alredy has HOS

            AttackerSet h_attackers = target->getAttackers();
            if (h_attackers.empty()) return false; //no aggro
            float threat;
            uint8 Tattackers = 0;
            for (AttackerSet::iterator iter = h_attackers.begin(); iter != h_attackers.end(); ++iter)
            {
                if (!(*iter)) continue;
                if ((*iter)->IsDead()) continue;
                if (!(*iter)->CanHaveThreatList()) continue;
                threat = (*iter)->getThreatManager().getThreat(target);
                if (threat < 25.f) continue; //too small threat
                if ((*iter)->getThreatManager().getThreat(tank) < threat * 0.33f) continue;//would be useless
                if (target->GetDistance((*iter)) <= 10)
                    Tattackers++;
            }
            if (Tattackers > 0 && doCast(target, HOS))
            {
                for (AttackerSet::iterator iter = h_attackers.begin(); iter != h_attackers.end(); ++iter)
                    if ((*iter)->getThreatManager().getThreat(target) > 0.f)
                        (*iter)->getThreatManager().modifyThreatPercent(target, -(30 + 50*(target->HasAura(586)))); //Fade
                HOS_Timer = 25000 - 20000*IS_CREATURE_GUID(target->GetGUID());
                return true;
            }
            return false;
        }
        //Holy_Shock setup (Modify HERE)
        bool HS(Unit* target, uint32 diff)
        {
            if (!target || target->IsDead()) return false;
            if (!HOLY_SHOCK || HS_Timer > diff || GC_Timer > diff) return false;
            if (IsCasting()) return false;
            if (target->GetTypeId() == TYPEID_PLAYER && (target->IsCharmed() || target->IsPossessed()))
                return false; //do not damage friends under control
            if (me->GetExactDist(target) > 40) return false;

            if (doCast(target, HOLY_SHOCK))
            {
                if (urand(1,100) > 20) //Daybreak: 20% to not trigger HS CD, only GCD
                    HS_Timer = target->ToCreature() ? 3500 : 5000;
                return true;
            }
            return false;
        }

        bool HealTarget(Unit* target, uint8 hp, uint32 diff)
        {
            if (!target || target->IsDead()) return false;
            if (hp > 97) return false;
            //sLog->outBasic("HealTarget() by %s on %s", me->GetName().c_str(), target->GetName().c_str());
            if (Rand() > 40 + 20*target->IsInCombat() + 50*master->GetMap()->IsRaid()) return false;
            if (me->GetExactDist(target) > 35) return false;
            if (IsCasting()) return false;
            if (HAND_OF_PROTECTION && BOP_Timer <= diff && IS_PLAYER_GUID(target->GetGUID()) &&
                (master->GetGroup() && master->GetGroup()->IsMember(target->GetGUID()) || target == master) &&
                ((hp < 30 && !target->getAttackers().empty()) || (hp < 50 && target->getAttackers().size() > 3)) &&
                me->GetExactDist(target) < 30 &&
                !HasAuraName(target, HAND_OF_PROTECTION) &&
                !HasAuraName(target, "Forbearance"))
            {
                if (doCast(target, HAND_OF_PROTECTION))
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        me->MonsterWhisper("BOP on you!", target->ToPlayer());
                    BOP_Timer = 60000; //1 min
                    if (!HasAuraName(target, "Forbearance"))
                        me->AddAura(25771, target); //Forbearance
                    if (HasAuraName(target, "Forbearance") && !target->HasAura(HAND_OF_PROTECTION))
                        me->AddAura(HAND_OF_PROTECTION, target);
                }
                return true;
            }
            else if (hp < 20 && !HasAuraName(target, HAND_OF_PROTECTION))
            {
                // 20% to cast loh, else just do a Shock
                switch (rand()%3)
                {
                    case 1:
                        if (LAY_ON_HANDS && LOH_Timer <= diff && hp < 20 &&
                            target->GetTypeId() == TYPEID_PLAYER &&
                            (target->IsInCombat() || !target->getAttackers().empty()) &&
                            !HasAuraName(target, "Forbearance"))
                        {
                            if (doCast(target, LAY_ON_HANDS))
                            {
                                me->MonsterWhisper("Lay of Hands on you!", target->ToPlayer());
                                LOH_Timer = 150000; //2.5 min
                                return true;
                            }
                        }
                    case 2:
                        if (GC_Timer > diff) return false;
                        if (FLASH_OF_LIGHT && doCast(target, FLASH_OF_LIGHT))
                            return true;
                    case 3:
                        if (GC_Timer > diff) return false;
                        if (HOLY_SHOCK && HS_Timer <= diff && HS(target, diff))
                            return true;
                }
            }
            if (GC_Timer > diff) return false;
            if (HOLY_SHOCK && (hp < 85 || GetLostHP(target) > 6000) && HS_Timer <= diff)
                if (HS(target, diff))
                    return true;
            if ((hp > 35 && (hp < 75 || GetLostHP(target) > 8000)) || (!FLASH_OF_LIGHT && hp < 85))
                if (doCast(target, HOLY_LIGHT))
                    return true;
            if (FLASH_OF_LIGHT && (hp < 90 || GetLostHP(target) > 1500))
                if (doCast(target, FLASH_OF_LIGHT))
                    return true;
            return false;
        }//end HealTarget

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
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (HOFGuid != 0)
            {
                if (Unit* ally = sObjectAccessor->FindUnit(HOFGuid))
                    if (Aura* hof = ally->GetAura(HOF, me->GetGUID()))
                        hof->SetDuration(hof->GetDuration() + 4000); //Guardian's Favor part 2 (handled separately)
                HOFGuid = 0;
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
            //HOFTarget(me, diff);//self stun cure goes FIRST
            if (CCed(me)) return;

            if (GetManaPCT(me) < 30 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }
            if (GetManaPCT(me) < 40 && DIVINE_PLEA && Divine_Plea_Timer <= diff)
                if (doCast(me, DIVINE_PLEA))
                    Divine_Plea_Timer = 45000;

            CureTarget(me, CLEANSE, diff); //maybe unnecessary but this goes FIRST
            HOFTarget(master, diff); //maybe unnecessary
            CureTarget(master, CLEANSE, diff); //maybe unnecessary
            BuffAndHealGroup(master, diff);
            HOSTarget(master, diff);
            CureGroup(master, CLEANSE, diff);
            HOFGroup(master, diff);
            HOSGroup(master, diff);

            if (GetHealthPCT(me) < 50 && Potion_cd <= diff)
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
            //buff
            if (SEAL_OF_TRUTH && Rand() < 20 && GC_Timer <= diff && !me->HasAura(SEAL_OF_TRUTH) &&
                doCast(me, SEAL_OF_TRUTH))
                GC_Timer = 500;

            // Heal myself
            if (GetHealthPCT(me) < 80)
                HealTarget(me, GetHealthPCT(me), diff);

            if (!CheckAttackTarget(CLASS_PALADIN))
                return;

            Repentance(diff);
            //Counter(diff);
            DoNormalAttack(diff);
        }

        void DoNonCombatActions(uint32 diff)
        {
            if (GC_Timer > diff || me->IsMounted()) return;

            RezGroup(REDEMPTION, master);

            if (Feasting()) return;

            //aura
            if (master->IsAlive() && me->GetExactDist(master) < 20)
            {
                uint8 myAura;
                if (me->HasAura(DEVOTION_AURA, me->GetGUID()))
                    myAura = DEVOTIONAURA;
                else if (me->HasAura(CONCENTRATION_AURA, me->GetGUID()))
                    myAura = CONCENTRATIONAURA;
                else myAura = NOAURA;

                if (myAura != NOAURA)
                    return; //do not bother

                Aura* concAura = master->GetAura(CONCENTRATION_AURA);
                Aura* devAura = master->GetAura(DEVOTION_AURA);
                if (devAura && concAura) return;
                if (devAura && devAura->GetCasterGUID() == me->GetGUID()) return;
                if (concAura && concAura->GetCasterGUID() == me->GetGUID()) return;

                if ((master->getClass() == CLASS_MAGE ||
                    master->getClass() == CLASS_PRIEST ||
                    master->getClass() == CLASS_WARLOCK ||
                    master->getClass() == CLASS_DRUID || devAura) &&
                    !concAura &&
                    doCast(me, CONCENTRATION_AURA))
                {
                    /*GC_Timer = 800;*/
                    return;
                }
                if (!devAura && doCast(me, DEVOTION_AURA))
                {
                    /*GC_Timer = 800;*/
                    return;
                }
            }
        }

        bool BuffTarget(Unit* target, uint32 diff)
        {
            if (!target || target->IsDead() || GC_Timer > diff || Rand() > 20) return false;
            if (me->IsInCombat() && !master->GetMap()->IsRaid()) return false;
            if (me->GetExactDist(target) > 30) return false;

            bool kings = !BLESSING_OF_KINGS || HasAuraName(target, BLESSING_OF_KINGS);
            bool might = !BLESSING_OF_MIGHT || HasAuraName(target, BLESSING_OF_MIGHT);
            if (kings && might)
                return false;

            if (!kings && doCast(target, BLESSING_OF_KINGS))
                return true;

            if (!might && doCast(target, BLESSING_OF_MIGHT))
                return true;

            return false;
        }

        void Repentance(uint32 diff, Unit* target = NULL)
        {
            if (target && Repentance_Timer < 25000 && doCast(target, REPENTANCE))
            {
                temptimer = GC_Timer;
                Repentance_Timer = 45000;
                GC_Timer = temptimer;
                return;
            }
            if (REPENTANCE && Repentance_Timer <= diff)
            {
                Unit* u = FindStunTarget(30);
                if (u && u->GetVictim() != me && doCast(u, REPENTANCE))
                    Repentance_Timer = 45000;
            }
        }

        void Counter(uint32 diff)
        {
            if (IsCasting())
                return;

            if (REBUKE && Rand() < 90 && Rebuke_Timer <= diff && me->GetDistance(opponent) < 5 &&
                opponent->IsNonMeleeSpellCast(false))
            {
                temptimer = GC_Timer;
                if (doCast(opponent, REBUKE))
                {
                    Rebuke_Timer = 8000;
                    GC_Timer = temptimer;
                    return;
                }
            }

            if (Rand() > 60)
                return;

            Unit* target = Repentance_Timer < 25000 ? FindCastingTarget(30, false, REPENTANCE) : NULL;
            if (target)
                Repentance(diff, target); //first check repentance
            else if (TURN_EVIL && Turn_Evil_Timer < 1500)
            {
                target = FindCastingTarget(20, 0, false, TURN_EVIL);
                temptimer = GC_Timer;
                if (target && doCast(target, TURN_EVIL, true))
                    Turn_Evil_Timer = 3000;
                GC_Timer = temptimer;
            }
            else if (HOLY_WRATH && Holy_Wrath_Timer < 8000)
            {
                target = FindCastingTarget(8, 0, false, TURN_EVIL); //here we check target as with turn evil cuz of same requirements
                temptimer = GC_Timer;
                if (target && doCast(me, HOLY_WRATH))
                    Holy_Wrath_Timer = 23500 - me->getLevel() * 100; //23.5 - 0...8.5 sec (15 sec on 85)
                GC_Timer = temptimer;
            }
            else if (HAMMER_OF_JUSTICE && HOJ_Timer <= 7000/* && GC_Timer <= diff*/)
            {
                target = FindCastingTarget(10);
                if (target && doCast(opponent, HAMMER_OF_JUSTICE))
                    HOJ_Timer = 69000 - master->getLevel()*500; //25 sec on 85
            }
        }

        void TurnEvil(uint32 diff)
        {
            if (!TURN_EVIL || Turn_Evil_Timer > diff || GC_Timer > diff || Rand() > 50 || IsCasting() ||
                FindAffectedTarget(TURN_EVIL, me->GetGUID(), 50))
                return;
            Unit* target = FindUndeadCCTarget(20, TURN_EVIL);
            if (target &&
                (target != me->GetVictim() || GetHealthPCT(me) < 70 || target->GetVictim() == master) &&
                doCast(target, TURN_EVIL, true))
            {
                Turn_Evil_Timer = 3000;
                return;
            }
            else
            if ((opponent->GetCreatureType() == CREATURE_TYPE_UNDEAD || opponent->GetCreatureType() == CREATURE_TYPE_DEMON) &&
                !CCed(opponent) &&
                opponent->GetVictim() && tank && opponent->GetVictim() != tank && opponent->GetVictim() != me &&
                GetHealthPCT(me) < 90 &&
                doCast(opponent, TURN_EVIL, true))
                Turn_Evil_Timer = 3000;
        }

        void Wrath(uint32 diff)
        {
            if (!HOLY_WRATH || Holy_Wrath_Timer > diff || GC_Timer > diff || Rand() > 50)
                return;
            if ((opponent->GetCreatureType() == CREATURE_TYPE_UNDEAD || opponent->GetCreatureType() == CREATURE_TYPE_DEMON) &&
                me->GetExactDist(opponent) <= 8 && doCast(me, HOLY_WRATH))
                Holy_Wrath_Timer = 23500 - me->getLevel() * 100; //23.5 - 0...8.5 sec (15 sec on 85)
            else
            {
                Unit* target = FindUndeadCCTarget(8, HOLY_WRATH);
                if (target && doCast(me, HOLY_WRATH))
                    Holy_Wrath_Timer = 23500 - me->getLevel() * 100; //23.5 - 0...8.5 sec (15 sec on 85)
            }
        }

        void DoNormalAttack(uint32 diff)
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
            TurnEvil(diff);

            if (MoveBehind(*opponent))
                wait = 5;

            if (HOW && HOW_Timer <= diff && Rand() < 30 && GetHealthPCT(opponent) < 19 && GC_Timer <= 300 &&// custom GCD check
                me->GetExactDist(opponent) < 30)
            {
                temptimer = GC_Timer;
                if (doCast(opponent, HOW))
                {
                    HOW_Timer = 6000; //6 sec
                    GC_Timer = temptimer;
                    return;
                }
            }

            Unit* u = opponent->GetVictim();
            if (Rand() < 50 && HANDOFRECKONING && Hand_Of_Reckoning_Timer <= diff && me->GetExactDist(opponent) < 30 &&
                u && u != me && u != tank && (IsInBotParty(u) || tank == me)) //No GCD
            {
                Creature* cre = opponent->ToCreature();
                temptimer = GC_Timer;
                if (((cre && cre->isWorldBoss() && !isMeleeClass(u->getClass())) ||
                    GetHealthPCT(u) < GetHealthPCT(me) - 5 || tank == me) &&
                    doCast(opponent, HANDOFRECKONING))
                {
                    Hand_Of_Reckoning_Timer = (me == tank) ? 4000 : 8000;
                    GC_Timer = temptimer;
                    return;
                }
            }

            if (Rand() < 20 && HAMMER_OF_JUSTICE && HOJ_Timer <= diff && GC_Timer <= diff &&
                !CCed(opponent) && me->GetExactDist(opponent) < 10)
            {
                if (doCast(opponent, HAMMER_OF_JUSTICE))
                {
                    HOJ_Timer = 69000 - master->getLevel()*500; //25 sec on 85
                    return;
                }
            }

            if (JUDGEMENT && Judge_Timer <= diff && GC_Timer <= diff && Rand() < 50 &&
                me->GetExactDist(opponent) < 10 && me->HasAura(SEAL_OF_TRUTH))
                if (doCast(opponent, JUDGEMENT))
                    Judge_Timer = 7000;

            if (Rand() < 50 && CONSECRATION && Consecration_cd <= diff && GC_Timer <= diff &&
                me->GetDistance(opponent) < 7 && !opponent->isMoving())
            {
                if (doCast(me, CONSECRATION))
                {
                    Consecration_cd = 20000;
                    return;
                }
            }

            if (Rand() < 25 && AVENGING_WRATH && AW_Timer <= diff &&
                (opponent->GetHealth() > master->GetMaxHealth()*2/3))
            {
                temptimer = GC_Timer;
                if (doCast(me, AVENGING_WRATH))
                {
                    AW_Timer = 60000; //1 min
                    GC_Timer = temptimer;
                    return;
                }
            }

            if (CRUSADER_STRIKE && Crusader_cd <= diff && GC_Timer <= diff && me->GetDistance(opponent) < 5)
            {
                if (doCast(opponent, CRUSADER_STRIKE))
                {
                    Crusader_cd = 4530 - me->getLevel() * 18; //3 sec on 85
                    return;
                }
            }

            if (EXORCISM && Exorcism_Timer <= diff && GC_Timer <= diff && me->GetExactDist(opponent) < 30 &&
                (tank != me || opponent->GetVictim() == me || opponent->IsVehicle() || opponent->ToPlayer()))
            {
                if (doCast(opponent, EXORCISM, me->HasAura(THE_ART_OF_WAR_BUFF)))
                {
                    Exorcism_Timer = 7000;
                    return;
                }
            }

            Wrath(diff);

            if (DIVINE_STORM && DS_Timer <= diff && GC_Timer <= diff && me->GetExactDist(opponent) < 7)
            {
                if (doCast(opponent, DIVINE_STORM))
                {
                    DS_Timer = 10000 - me->getLevel()/4 * 100; //10 - 2 sec
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
                //Rule of Law: 15% additional crit chance for Crusader Strike etc.
                if (lvl >= 30 && spellId == CRUSADER_STRIKE)
                    aftercrit += 15.f;
                //Arbiter of the Light: 12% additional crit chance for Judgements etc.
                if (lvl >= 10 && (spellInfo->GetCategory() == SPELLCATEGORY_JUDGEMENT || spellInfo->GetSpellSpecific() == SPELL_SPECIFIC_JUDGEMENT))
                    aftercrit += 12.f;

                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            //if (crit)
            //{
            //}
            //Wrath of the Lightbringer (part 1): 100% bonus damage for Crusader Strike and Judgements
            if (lvl >= 30 &&
                (spellId == CRUSADER_STRIKE ||
                spellInfo->GetCategory() == SPELLCATEGORY_JUDGEMENT ||
                spellInfo->GetSpellSpecific() == SPELL_SPECIFIC_JUDGEMENT))
                pctbonus += 1.f;
            //Hallowed Ground: 40% bonus damage for Consecration
            if (lvl >= 30 && spellId == CONSECRATION)
                pctbonus += 0.4f;
            //Crusade (part 1): 30% bonus damage for Crusader Strike etc.
            if (lvl >= 10 && spellId == CRUSADER_STRIKE)
                pctbonus += 0.3f;

            damage = int32(fdamage * (1.0f + pctbonus));
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
                //Wrath of the Lightbringer (part 2): 30% additional crit chance for Holy Wrath and Hammer of Wrath
                if (lvl >= 30 && (spellId == HOLY_WRATH || spellId == HOW))
                    aftercrit += 30.f;
                //Sanctified Wrath: 6% additional critical chance for Hammer of Wrath
                if (lvl >= 40 && spellId == HOW)
                    aftercrit += 6.f;

                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            //if (crit)
            //{
            //}

            //Blazing Light: 20% bonus damage for Exorcism and Holy Shock
            if (lvl >= 20 && (spellId == EXORCISM || spellId == HOLY_SHOCK))
                pctbonus += 0.2f;

            //SPECIAL
            //The Art of War (buff): 100% bonus damage for Exorcism
            if (lvl >= 33 && spellId == EXORCISM && me->HasAura(THE_ART_OF_WAR_BUFF))
            {
                me->RemoveAura(THE_ART_OF_WAR_BUFF);
                pctbonus += 1.f;
            }

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            if (spellId == BLESSING_OF_KINGS || spellId == BLESSING_OF_MIGHT)
            {
                //Blessings duration 1h
                if (Aura* shout = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = HOUR * IN_MILLISECONDS;
                    shout->SetDuration(dur);
                    shout->SetMaxDuration(dur);
                }
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            OnSpellHit(caster, spell);
        }

        void DamageTaken(Unit* u, uint32& /*damage*/)
        {
            OnOwnerDamagedBy(u);
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            //Custom OnHit() handlers

            if (damageType == DIRECT_DAMAGE)
            {
                //The Art of War: 20% on autoattack
                if (me->getLevel() >= 33)
                    if (urand(1,100) <= 20)
                        me->CastSpell(me, THE_ART_OF_WAR_BUFF, true);
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

        void OwnerAttackedBy(Unit* u)
        {
            OnOwnerDamagedBy(u);
        }

        void Reset()
        {
            Crusader_cd = 0;
            Consecration_cd = 0;
            LOH_Timer = 0;
            HOJ_Timer = 0;
            HOF_Timer = 0;
            Judge_Timer = 0;
            HS_Timer = 0;
            BOP_Timer = 0;
            HOW_Timer = 0;
            DS_Timer = 0;
            AW_Timer = 10000;
            HOS_Timer = 0;
            Hand_Of_Reckoning_Timer = 0;
            Divine_Plea_Timer = 0;
            Repentance_Timer = 0;
            Exorcism_Timer = 0;
            Holy_Wrath_Timer = 0;
            Turn_Evil_Timer = 0;
            Rebuke_Timer = 0;

            HOFGuid = 0;

            if (master)
            {
                setStats(CLASS_PALADIN, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_PALADIN);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (HOW_Timer > diff)                   HOW_Timer -= diff;
            if (DS_Timer > diff)                    DS_Timer -= diff;
            if (AW_Timer > diff)                    AW_Timer -= diff;
            if (HOS_Timer > diff)                   HOS_Timer -= diff;
            if (HS_Timer > diff)                    HS_Timer -= diff;
            if (BOP_Timer > diff)                   BOP_Timer -= diff;
            if (Consecration_cd > diff)             Consecration_cd -= diff;
            if (Crusader_cd > diff)                 Crusader_cd -= diff;
            if (LOH_Timer > diff)                   LOH_Timer -= diff;
            if (HOJ_Timer > diff)                   HOJ_Timer -= diff;
            if (HOF_Timer > diff)                   HOF_Timer -= diff;
            if (Judge_Timer > diff)                 Judge_Timer -= diff;
            if (Hand_Of_Reckoning_Timer > diff)     Hand_Of_Reckoning_Timer -= diff;
            if (Divine_Plea_Timer > diff)           Divine_Plea_Timer -= diff;
            if (Repentance_Timer > diff)            Repentance_Timer -= diff;
            if (Exorcism_Timer > diff)              Exorcism_Timer -= diff;
            if (Holy_Wrath_Timer > diff)            Holy_Wrath_Timer -= diff;
            if (Turn_Evil_Timer > diff)             Turn_Evil_Timer -= diff;
            if (Rebuke_Timer > diff)                Rebuke_Timer -= diff;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            FLASH_OF_LIGHT                          = InitSpell(me, FLASH_OF_LIGHT_1);
            HOLY_LIGHT                  = lvl <= 61 ? InitSpell(me, HOLY_LIGHT_1) : InitSpell(me, DIVINE_LIGHT_1); //exception
            LAY_ON_HANDS                            = InitSpell(me, LAY_ON_HANDS_1);
            HOLY_SHOCK                  = lvl >= 10 ? HOLY_SHOCK_1 : 0;
            CLEANSE                     = lvl >= 34 ? CLEANSE_1 : 0;
            REDEMPTION                              = InitSpell(me, REDEMPTION_1);
            HAMMER_OF_JUSTICE                       = InitSpell(me, HAMMER_OF_JUSTICE_1);
            REPENTANCE                  = lvl >= 47 ? REPENTANCE_1 : 0;
            TURN_EVIL                               = InitSpell(me, TURN_EVIL_1);
            HOLY_WRATH                              = InitSpell(me, HOLY_WRATH_1);
            EXORCISM                                = InitSpell(me, EXORCISM_1);
            SEAL_OF_TRUTH               = lvl >= 10 ? SEAL_OF_TRUTH_1 : 0;
            CRUSADER_STRIKE                         = CRUSADER_STRIKE_1; //exception
            JUDGEMENT                               = InitSpell(me, JUDGEMENT_1);
            CONSECRATION                            = InitSpell(me, CONSECRATION_1);
            DIVINE_STORM                = lvl >= 29 ? DIVINE_STORM_1 : 0;
            HOW /*Hammer of Wrath*/                 = InitSpell(me, HOW_1);
            AVENGING_WRATH                          = InitSpell(me, AVENGING_WRATH_1);
            BLESSING_OF_MIGHT                       = InitSpell(me, BLESSING_OF_MIGHT_1);
            BLESSING_OF_KINGS                       = InitSpell(me, BLESSING_OF_KINGS_1);
            DEVOTION_AURA                           = InitSpell(me, DEVOTION_AURA_1);
            CONCENTRATION_AURA                      = InitSpell(me, CONCENTRATION_AURA_1);
            DIVINE_PLEA                             = InitSpell(me, DIVINE_PLEA_1);
            HAND_OF_PROTECTION                      = InitSpell(me, HAND_OF_PROTECTION_1);
            HOF  /* Hand of Freedom */              = InitSpell(me, HOF_1);
            HOS /*Hand of salvation*/               = InitSpell(me, HOS_1);
            HANDOFRECKONING                         = InitSpell(me, HANDOFRECKONING_1);
            REBUKE                                  = InitSpell(me, REBUKE_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            //1 - crit 3%
            if (level >= 78)
                RefreshAura(SPELLDMG,5); //+15%
            else if (level >= 75)
                RefreshAura(SPELLDMG,4); //+12%
            else if (level >= 55)
                RefreshAura(SPELLDMG,3); //+9%
            else if (level >= 35)
                RefreshAura(SPELLDMG,2); //+6%
            else if (level >= 15)
                RefreshAura(SPELLDMG); //+3%
            //2 - SPD 2%
            if (level >= 55)
                RefreshAura(SPELLDMG2,5); //+10%
            else if (level >= 45)
                RefreshAura(SPELLDMG2,4); //+8%
            else if (level >= 35)
                RefreshAura(SPELLDMG2,3); //+6%
            else if (level >= 25)
                RefreshAura(SPELLDMG2,2); //+4%
            else if (level >= 15)
                RefreshAura(SPELLDMG2); //+2%
            //Talents
            if (level >= 10)
                RefreshAura(PURE);
            if (level >= 11)
                RefreshAura(WISE);
            if (level >= 43)
                RefreshAura(CONVICTION3);
            else if (level >= 41)
                RefreshAura(CONVICTION2);
            else if (level >= 39)
                RefreshAura(CONVICTION1);
            if (level >= 45)
                RefreshAura(SHEATH_OF_LIGHT);
            if (level >= 37)
                RefreshAura(DIVINE_PURPOSE);
            if (level >= 35)
                RefreshAura(VINDICATION);
            //434 new
            if (level >= 51)
                RefreshAura(HEAL_DONETAKEN,5); //+30%
            else if (level >= 41)
                RefreshAura(HEAL_DONETAKEN,4); //+24%
            else if (level >= 31)
                RefreshAura(HEAL_DONETAKEN,3); //+18%
            else if (level >= 21)
                RefreshAura(HEAL_DONETAKEN,2); //+12%
            else if (level >= 11)
                RefreshAura(HEAL_DONETAKEN); //+6%

            if (level >= 13)
                RefreshAura(POTI3);
            else if (level >= 11)
                RefreshAura(POTI2);
            else if (level >= 10)
                RefreshAura(POTI1);

            if (level >= 31)
                RefreshAura(DENOUNCE);

            if (level >= 43)
                RefreshAura(SPEED_OF_LIGHT);

            if (level >= 21)
                RefreshAura(JUST);

            if (level >= 29)
                RefreshAura(COMMUNION);

            if (level >= 39)
                RefreshAura(SACRED_SHIELD);
        }

    private:
        uint32
   /*Heals*/FLASH_OF_LIGHT, HOLY_LIGHT, HOLY_SHOCK, LAY_ON_HANDS,
      /*CC*/HAMMER_OF_JUSTICE, REPENTANCE, TURN_EVIL, REBUKE,
  /*Damage*/SEAL_OF_TRUTH, HOLY_WRATH, EXORCISM, CRUSADER_STRIKE, JUDGEMENT,
  /*Damage*/CONSECRATION, DIVINE_STORM, AVENGING_WRATH, HOW, //hammer of wrath
/*Blessing*/BLESSING_OF_MIGHT, BLESSING_OF_KINGS,
   /*Auras*/DEVOTION_AURA, CONCENTRATION_AURA,
   /*Hands*/HAND_OF_PROTECTION, HOF, HOS, HANDOFRECKONING,
    /*Misc*/CLEANSE, REDEMPTION, DIVINE_PLEA;
        //Timers
        uint32 Crusader_cd, Consecration_cd, Exorcism_Timer, Holy_Wrath_Timer, Judge_Timer, HOF_Timer,
            HS_Timer, HOW_Timer, DS_Timer, HOS_Timer, Hand_Of_Reckoning_Timer, Turn_Evil_Timer,
            LOH_Timer, HOJ_Timer, BOP_Timer, AW_Timer, Divine_Plea_Timer, Repentance_Timer,
            Rebuke_Timer;
        uint64 HOFGuid;

        enum PaladinBaseSpells// all orignals
        {
            REBUKE_1                            = 96231,
            DIVINE_LIGHT_1                      = 82326,
            FLASH_OF_LIGHT_1                    = 19750,
            HOLY_LIGHT_1                        = 635,
            LAY_ON_HANDS_1                      = 633,
            REDEMPTION_1                        = 7328,
            HOF_1  /*Hand of Freedom*/          = 1044,
            HOLY_SHOCK_1                        = 20473,
            CLEANSE_1                           = 66116,//4987 original spell
            HAND_OF_PROTECTION_1                = 1022,
            HOS_1 /*Hand of salvation*/         = 1038,
            SEAL_OF_TRUTH_1                     = 31801,
            HANDOFRECKONING_1                   = 62124,
            DIVINE_PLEA_1                       = 54428,
            REPENTANCE_1                        = 20066,
            TURN_EVIL_1                         = 10326,
            CRUSADER_STRIKE_1                   = 35395,
            JUDGEMENT_1                         = 20271,
            CONSECRATION_1                      = 26573,
            HAMMER_OF_JUSTICE_1                 = 853,
            DIVINE_STORM_1                      = 53385,
            HOW_1   /*Hammer of Wrath*/         = 24275,
            EXORCISM_1                          = 879,
            HOLY_WRATH_1                        = 2812,
            AVENGING_WRATH_1                    = 31884,
            BLESSING_OF_MIGHT_1                 = 19740,
            BLESSING_OF_KINGS_1                 = 20217,
            DEVOTION_AURA_1                     = 465,
            CONCENTRATION_AURA_1                = 19746
        };
        enum PaladinPassives
        {
        //Talents
            DIVINE_PURPOSE                      = 86172,
            PURE/*Judgements of the Pure*/      = 54151,
            JUST/*Judgements of the Just*/      = 53696,//rank 2
            VINDICATION                         = 26016,
            CONVICTION1                         = 20049,
            CONVICTION2                         = 20056,
            CONVICTION3                         = 20057,
            POTI1 /*Protector of the Innocent*/ = 20138,
            POTI2                               = 20139,
            POTI3                               = 20140,
            DENOUNCE                            = 85510,//rank 2
            SPEED_OF_LIGHT                      = 85499,//rank 3
            COMMUNION                           = 31876,
            SACRED_SHIELD                       = 85285,
        //Special
            SHEATH_OF_LIGHT                     = 53503,//not a talent
            WISE/*Judgements of the Wise*/      = 31878,//not a talent
        //other
            SPELLDMG/*Piercing Ice - mage*/     = 15060,//3% crit
            SPELLDMG2/*Earth and Moon - druid*/ = 48511 //2% dam
        };

        enum PaladinSpecial
        {
            NOAURA,
            DEVOTIONAURA,
            CONCENTRATIONAURA,

            THE_ART_OF_WAR_BUFF                 = 59578
        };
    };
};

void AddSC_paladin_bot()
{
    new paladin_bot();
}
