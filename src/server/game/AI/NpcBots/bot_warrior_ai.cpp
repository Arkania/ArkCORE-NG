#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "WorldSession.h"
/*
Warrior NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - Around 40-45%
TODO: Thunder Clap, Piercing Howl, Challenging Shout, other tanking stuff
*/
class warrior_bot : public CreatureScript
{
public:
    warrior_bot() : CreatureScript("warrior_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new warrior_botAI(creature);
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

    struct warrior_botAI : public bot_minion_ai
    {
        warrior_botAI(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_WARRIOR) != SPELL_CAST_OK)
                return false;
            return bot_ai::doCast(victim, spellId, triggered);
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            if (me->GetVictim())
                DoMeleeAttackIfReady();
            else
                Evade();

            if (ragetimer <= diff)
            {
                if (!me->IsInCombat())
                {
                    if (getrage() > uint32(10.f*rageLossMult))
                        me->SetPower(POWER_RAGE, rage - uint32(10.f*rageLossMult));//-1 rage per 1.5 sec
                    else
                        me->SetPower(POWER_RAGE, 0);//min
                }
                ragetimer = 1500;
            }

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
            CheckIntervene(diff);
            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            if (Rand() < 30 && batcomShout_cd <= diff && GC_Timer <= diff && me->GetDistance(master) < 30 &&
                !master->HasAura(BATTLESHOUT) &&
                master->IsWithinLOSInMap(me) &&
                doCast(me, BATTLESHOUT))
                batcomShout_cd = SHOUT_CD;

            if (!CheckAttackTarget(CLASS_WARRIOR))
            {
                if (tank != me && !me->IsInCombat() && battleStance != true && master->getAttackers().empty() && stancetimer <= diff)
                    stanceChange(diff, 1);
                return;
            }

            if (Rand() < 20 && BLOODRAGE && bloodrage_cd <= diff && me->IsInCombat() && getrage() < 600)
            {
                temptimer = GC_Timer;
                if (doCast(me, BLOODRAGE))
                {
                    bloodrage_cd = BLOODRAGE_CD;
                    GC_Timer = temptimer;
                }
            }

            Attack(diff);
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
        void KilledUnit(Unit* u)
        {
            //victorious state emulation
            if (me->getLevel() >= 5 && u->getLevel() + 9 >= me->getLevel())
            {
                temptimer = GC_Timer;
                if (doCast(me, VICTORIOUS_SPELL, true))
                {
                    GC_Timer = temptimer;
                    return;
                }
            }
        }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }
        void DoNonCombatActions(uint32 /*diff*/) {}

        void modrage(int32 mod, bool set = false)
        {
            if (set && mod < 0)
                return;
            if (mod < 0 && rage < uint32(abs(mod)))
            {
                //debug set rage to 0
                mod = 0;
                set = true;
                return;
            }

            if (set)
                rage = mod ? mod*10 : 0;
            else
                rage += mod*10;

            me->SetPower(POWER_RAGE, rage);
        }

        uint32 getrage()
        {
            rage = me->GetPower(POWER_RAGE);
            return rage;
        }

        void BreakCC(uint32 diff)
        {
            if (me->HasAuraWithMechanic((1<<MECHANIC_FEAR)|(1<<MECHANIC_SAPPED)|(1<<MECHANIC_DISORIENTED)))
            {
                if (BERSERKERRAGE && berserkerRage_cd <= diff && GC_Timer <= diff &&
                    doCast(me, BERSERKERRAGE))
                {
                    berserkerRage_cd = BERSERKERRAGE_CD;
                    if (me->getLevel() >= 40)
                        doCast(me, 58096, true); //Berserker Rage Effect (434 unused)
                    return;
                }
            }
            bot_minion_ai::BreakCC(diff);
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
            //Keep defensive stance if tank
            if (tank == me && defensiveStance != true && stancetimer <= diff)
                stanceChange(diff, 2);
            //SelfHeal
            if (ENRAGED_REGENERATION)
            {
                if (Rand() < 40 && GetHealthPCT(me) < 40 && getrage() > 150 && regen_cd <= diff && GC_Timer <= diff &&
                    me->HasAuraWithMechanic(uint32(1<<MECHANIC_ENRAGED)))
                {
                    temptimer = 0;
                    if (doCast(me, ENRAGED_REGENERATION))
                    {
                        regen_cd = ENRAGED_REGENERATION_CD;
                        GC_Timer = temptimer;
                        return;
                    }
                }
            }

            AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();
            float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);
            //charge + warbringer
            if (CHARGE && charge_cd <= diff && dist > 11 && dist < 25 && me->HasInArc(M_PI, opponent) &&
                (me->getLevel() >= 50 ||
                (!me->IsInCombat() && (battleStance || stanceChange(diff, 1)))))
            {
                temptimer = GC_Timer;
                if (me->getLevel() >= 29)
                    me->RemoveMovementImpairingAuras();
                if (doCast(opponent, CHARGE, me->IsInCombat()))
                {
                    charge_cd = CHARGE_CD;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //intercept
            if (INTERCEPT && intercept_cd <= diff && tank != me &&
                getrage() > 100 && dist > 11 && dist < 25 && me->HasInArc(M_PI, opponent) &&
                !CCed(opponent) && (berserkerStance || stanceChange(diff, 3)))
            {
                if (doCast(opponent, INTERCEPT))
                {
                    intercept_cd = INTERCEPT_CD;
                    return;
                }
            }
            //SelfHeal 2
            if (VICTORY_RUSH && VICTORIOUS && meleedist <= 5 && GC_Timer <= diff &&
                (b_attackers.size() <= 1 || (GetHealthPCT(me) < std::max<int32>(100 - b_attackers.size() * 10, 75))))
            {
                if (doCast(opponent, VICTORY_RUSH))
                {
                    me->RemoveAura(VICTORIOUS_SPELL);
                    return;
                }
            }
            //FEAR
            if (INTIMIDATING_SHOUT && intimidatingShout_cd <= diff && GC_Timer <= diff && Rand() < 70 && getrage() > 250)
            {
                if (opponent->IsNonMeleeSpellCast(false, false, true) && dist <= 8 &&
                    !(opponent->ToCreature() && opponent->ToCreature()->GetCreatureType() == CREATURE_TYPE_UNDEAD))
                {
                    if (doCast(opponent, INTIMIDATING_SHOUT))
                    {
                        intimidatingShout_cd = INTIMIDATINGSHOUT_CD;
                        return;
                    }
                }
                Unit* fearTarget = NULL;
                bool triggered = false;
                uint8 tCount = 0;
                //fear master's attackers
                if (!m_attackers.empty() &&
                    ((master->getClass() != CLASS_DEATH_KNIGHT &&
                    master->getClass() != CLASS_WARRIOR &&
                    master->getClass() != CLASS_PALADIN) ||
                    GetHealthPCT(master) < 70))
                {
                    for(AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                        if (me->GetExactDist((*iter)) <= 8 && (*iter)->isTargetableForAttack())
                        {
                            ++tCount;
                            fearTarget = (*iter);
                            if (tCount > 1) break;
                        }
                    }
                    if (tCount > 0 && !fearTarget)
                    {
                        fearTarget = opponent;
                        triggered = true;
                    }
                    if (tCount > 1 && doCast(fearTarget, INTIMIDATING_SHOUT, triggered))
                    {
                        intimidatingShout_cd = INTIMIDATINGSHOUT_CD;
                        return;
                    }
                }
                //Defend myself
                if (b_attackers.size() > 1)
                {
                    tCount = 0;
                    fearTarget = NULL;
                    triggered = false;
                    for(AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                    {
                        if (!(*iter)) continue;
                        if ((*iter)->GetCreatureType() == CREATURE_TYPE_UNDEAD) continue;
                        if (me->GetExactDist((*iter)) <= 8 && (*iter)->isTargetableForAttack())
                        {
                            ++tCount;
                            fearTarget = (*iter);
                            if (tCount > 0) break;
                        }
                    }
                    if (tCount > 0 && !fearTarget)
                    {
                        fearTarget = opponent;
                        triggered = true;
                    }
                    if (tCount > 0 && doCast(fearTarget, INTIMIDATING_SHOUT, triggered))
                    {
                        intimidatingShout_cd = INTIMIDATINGSHOUT_CD;
                        return;
                    }
                }
            }//end FEAR
            //OVERPOWER
            if (OVERPOWER && Rand() < 50 && getrage() > 50 && meleedist <= 5 && GC_Timer <= diff &&
                (battleStance || stancetimer <= diff))
            {
                if (me->HasAura(TASTE_FOR_BLOOD_BUFF))
                {
                    if (battleStance || stanceChange(diff, 1))
                    {
                        if (doCast(opponent, OVERPOWER))
                        {
                            me->RemoveAura(TASTE_FOR_BLOOD_BUFF);
                            return;
                        }
                    }
                }
            }

            if (MoveBehind(*opponent))
                wait = 5;
            //HAMSTRING
            if (HAMSTRING && Rand() < 50 && getrage() > 100 && GC_Timer <= diff && meleedist <= 5 && opponent->isMoving() &&
                (battleStance || berserkerStance || stancetimer <= diff) &&
                !opponent->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_ROOT)))
            {
                if (battleStance || berserkerStance || stanceChange(diff, 5))
                    if (doCast(opponent, HAMSTRING))
                        return;
            }
            //UBERS
            //Dont use RETA unless capable circumstances
            if (Rand() < 20 && uber_cd <= diff && GC_Timer <= diff)
            {
                if (RETALIATION && b_attackers.size() > 4)
                {
                    if (doCast(me, RETALIATION))
                    {
                        uber_cd = UBER_CD;
                        return;
                    }
                }
                //Dont use RECKL unless capable circumstances
                if (RECKLESSNESS && tank != me &&
                    (m_attackers.size() > 3 || opponent->GetHealth() > me->GetHealth() * 10))
                {
                    if (doCast(me, RECKLESSNESS))
                    {
                        uber_cd = UBER_CD;
                        return;
                    }
                }
            }
            //DEATHWISH
            if (DEATHWISH && deathwish_cd <= diff && GC_Timer <= diff && getrage() > 100 &&
                Rand() < 20 && opponent->GetHealth() > me->GetHealth()/2)
            {
                if (doCast(me, DEATHWISH))
                {
                    deathwish_cd = DEATHWISH_CD;
                    return;
                }
            }
            //TAUNT
            Unit* u = opponent->GetVictim();
            if (TAUNT && taunt_cd <= diff && u && u != me && u != tank && dist <= 30 &&
                !CCed(opponent) && !isTankingClass(u->getClass()) && (IsInBotParty(u) || tank == me) &&
                (defensiveStance || (stancetimer <= diff && stanceChange(diff, 2))))//No GCD
            {
                temptimer = GC_Timer;
                if (doCast(opponent, TAUNT, true))
                {
                    taunt_cd = TAUNT_CD;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //EXECUTE
            if (EXECUTE && tank != me && Rand() < 70 && GC_Timer <= diff && getrage() > 100 &&
                meleedist <= 5 && GetHealthPCT(opponent) < 20 &&
                (battleStance || berserkerStance || (stancetimer <= diff && stanceChange(diff, 5))))
            {
                if (doCast(opponent, EXECUTE))
                {
                    //sudden death
                    if (me->getLevel() >= 50 && getrage() <= 200)
                        modrage(10, true);
                    return;
                }
            }
            //SUNDER
            if (SUNDER && Rand() < 35 && meleedist <= 5 && tank == me &&
                opponent->GetHealth() > me->GetMaxHealth() &&
                GC_Timer <= diff && getrage() > 150 && (sunder_cd <= diff || getrage() > 500))
            {
                Aura* sunder = opponent->GetAura(SUNDER, me->GetGUID());
                if ((!sunder || sunder->GetStackAmount() < 5 || sunder->GetDuration() < 15000) &&
                    doCast(opponent, SUNDER))
                {
                    sunder_cd = SUNDER_CD;
                    GC_Timer = 800;
                    return;
                }
            }
            //SS
            if (SWEEPING_STRIKES && sweeping_strikes_cd <= diff && tank != me && Rand() < 25 &&
                (battleStance || berserkerStance || stancetimer <= diff) &&
                (b_attackers.size() > 1 || FindSplashTarget(7, opponent)))
            {
                temptimer = GC_Timer;
                if ((battleStance || berserkerStance || stanceChange(diff, 5)) &&
                    doCast(me, SWEEPING_STRIKES, true))//no rage use as with glyph
                {
                    sweeping_strikes_cd = SWEEPING_STRIKES_CD;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //WHIRLWIND
            if (WHIRLWIND && Rand() < 50 && whirlwind_cd <= diff && GC_Timer <= diff && getrage() >= 200 && tank != me &&
               (FindSplashTarget(7, opponent) || (getrage() > 800 && dist <= 7)) &&
               (berserkerStance || stancetimer <= diff))
            {
                if ((berserkerStance || stanceChange(diff, 3)) &&
                    doCast(me, WHIRLWIND))
                {
                    whirlwind_cd = WHIRLWIND_CD;
                    return;
                }
            }
            //BLADESTORM
            if (BLADESTORM && bladestorm_cd <= diff && GC_Timer <= diff &&
               getrage() >= 250 && (Rand() < 20 || me->HasAura(RECKLESSNESS)) &&
               (b_attackers.size() > 1 || opponent->GetHealth() > me->GetMaxHealth()))
            {
                if (doCast(me, BLADESTORM))
                {
                    bladestorm_cd = BLADESTORM_CD;
                    return;
                }
            }
            //Mortal Strike
            if (MORTALSTRIKE && getrage() > 200 && meleedist <= 5 && mortalStrike_cd <= diff && GC_Timer <= diff)
            {
                if (doCast(opponent, MORTALSTRIKE))
                {
                    mortalStrike_cd = MORTALSTRIKE_CD;
                    slam_cd = 0;//reset here
                }
            }
            //Slam
            bool triggered = (mortalStrike_cd == MORTALSTRIKE_CD);
            if (SLAM && Rand() < (30 + triggered * 30) && slam_cd <= diff && getrage() > 150 && meleedist <= 5)
            {
                if (doCast(opponent, SLAM, true))
                {
                    slam_cd = 3000; //must be > MORTALSTRIKE_CD/2
                    modrage(-15);
                    return;
                }
            }
            //PUMMEL
            if (PUMMEL && Rand() < 80 && pummel_cd <= diff && getrage() > 100 && meleedist <= 5 &&
                opponent->IsNonMeleeSpellCast(false))
            {
                temptimer = GC_Timer;
                if (doCast(opponent, PUMMEL))
                {
                    pummel_cd = PUMMEL_CD;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //REND
            if (REND && Rand() < 50 && getrage() > 100 && GC_Timer <= diff && meleedist <= 5 &&
                opponent->GetHealth() > me->GetHealth()/2 &&
                !opponent->HasAura(REND, me->GetGUID()) &&
                (battleStance || defensiveStance || (stancetimer <= diff && stanceChange(diff, 4))))
            {
                if (doCast(opponent, REND))
                    return;
            }
            //Cleave
            if (Rand() < 30 && CLEAVE && cleave_cd <= diff && me->getLevel() >= 20 && getrage() > 250 && meleedist <= 5)
            {
                temptimer = GC_Timer;
                u = FindSplashTarget(5);
                if (u && doCast(opponent, CLEAVE))
                {
                    cleave_cd = me->getAttackTimer(BASE_ATTACK); //once per swing, prevents rage loss
                    GC_Timer = temptimer;
                    return;
                }
            }
            else {}//HEROIC STRIKE placeholder
            //DISARM DEPRECATED
            /*if (disarm_cd <= diff && meleedist < 5 &&
                (opponent->GetVictim()->GetGUID() == master->GetGUID() ||
                opponent->GetVictim()->GetGUID() == m_creature->GetGUID()) &&
                getrage() > 15 &&
                !HasAuraName(opponent, GetSpellName(DISARM)) &&
                GC_Timer <= diff)
            {
                if (opponent->getClass() == CLASS_ROGUE  ||
                    opponent->getClass() == CLASS_WARRIOR   ||
                    opponent->getClass() == CLASS_SHAMAN    ||
                    opponent->getClass() == CLASS_PALADIN)
                {
                    if (defensiveStance == true)
                    {
                        doCast(opponent, DISARM, true);
                        //rage -= 100;
                        disarm_cd = DISARM_CD;
                    }
                    else stanceChange(diff, 2);
                }
            }*/
        }//end Attack

        void CheckIntervene(uint32 diff)
        {
            if (INTERVENE && intervene_cd <= diff && getrage() > 100 && Rand() < ((tank == me) ? 80 : 30) &&
                (defensiveStance || stancetimer <= diff))
            {
                if (!master->IsInCombat() && master->getAttackers().empty() && master->isMoving())
                {
                    float mydist = me->GetExactDist(master);
                    if (mydist < 24 && mydist > 19 && (defensiveStance || stanceChange(diff, 2)))
                    {
                        temptimer = GC_Timer;
                        if (doCast(master, INTERVENE))
                        {
                            intervene_cd = INTERVENE_CD;
                            GC_Timer = temptimer;
                            Follow(true);
                            return;
                        }
                    }
                }
                Group* gr = master->GetGroup();
                if (!gr)
                {
                    if (GetHealthPCT(master) < 95 && !master->getAttackers().empty() &&
                        me->getAttackers().size() <= master->getAttackers().size())
                    {
                        float dist = me->GetExactDist(master);
                        if (dist > 25 || dist < 10) return;
                        if (!(defensiveStance || stanceChange(diff, 2))) return;
                        temptimer = GC_Timer;
                        if (doCast(master, INTERVENE))
                        {
                            intervene_cd = INTERVENE_CD;
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
                else
                {
                    bool Bots = false;
                    float dist;
                    for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        Player* tPlayer = itr->GetSource();
                        if (!tPlayer) continue;
                        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
                        if (tPlayer->FindMap() != me->GetMap()) continue;
                        if (tPlayer->HaveBot())
                            Bots = true;
                        if (tPlayer->IsDead() || GetHealthPCT(tPlayer) > 90 || tank == tPlayer) continue;
                        if (tPlayer->getAttackers().size() < me->getAttackers().size()) continue;
                        dist = me->GetExactDist(tPlayer);
                        if (dist > 24 || dist < 10) continue;
                        if (defensiveStance || stanceChange(diff, 2))
                        {
                            temptimer = GC_Timer;
                            if (doCast(tPlayer, INTERVENE))
                            {
                                intervene_cd = INTERVENE_CD;
                                GC_Timer = temptimer;
                                return;
                            }
                        }
                    }
                    if (!Bots) return;
                    for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        Player* tPlayer = itr->GetSource();
                        if (!tPlayer || !tPlayer->HaveBot()) continue;
                        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
                        if (tPlayer->FindMap() != me->GetMap()) continue;
                        for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                        {
                            Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                            if (!bot || !bot->IsInWorld() || bot == me || bot->IsDead()) continue;
                            if (GetHealthPCT(bot) > 90 || tank == bot) continue;
                            dist = me->GetExactDist(bot);
                            if (dist > 25 || dist < 10) continue;
                            if (bot->getAttackers().size() <= me->getAttackers().size()) continue;
                            if (defensiveStance || stanceChange(diff, 2))
                            {
                                temptimer = GC_Timer;
                                if (doCast(bot, INTERVENE))
                                {
                                    intervene_cd = INTERVENE_CD/2;
                                    GC_Timer = temptimer;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            if (spellId == OVERPOWER)
            {
                //Unrelenting Assault
                if (UNRELENTING_ASSAULT && target->HasUnitState(UNIT_STATE_CASTING))
                    target->CastSpell(target, UNRELENTING_ASSAULT_SPELL, true);
            }
            if (spellId == BATTLESHOUT/* || spellId == COMMANDINGSHOUT*/)
            {
                //Glyph of Battle/Command + 2 min duration (8 for bots)
                if (Aura* shout = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = shout->GetDuration() + 480000;
                    shout->SetDuration(dur);
                    shout->SetMaxDuration(dur);
                }
            }
            if (spellId == MORTALSTRIKE || spellId == CLEAVE || spellId == SLAM ||
                spellId == EXECUTE || spellId == WHIRLWIND || spellId == PUMMEL ||
                spellId == SUNDER || spellId == VICTORY_RUSH || spellId == OVERPOWER ||
                spellId == 50622 || //whirlwind (bladestorm)
                spellId == 44949) //whirlwind off-hand
            {
                //Warrior T13 Arms and Fury 4P Bonus (Colossus Smash)
                if (me->getLevel() >= 50 && urand(1, 100) <= 18)
                    me->CastSpell(target, COLOSSUS_SMASH_EFFECT, true);
            }
        }

        bool stanceChange(uint32 diff, uint8 stance)
        {
            if (!(stancetimer <= diff) || !stance)
                return false;

            if (stance == 5)
            {
                switch (urand(0,1))
                {
                    case 0:
                        stance = 1;
                        break;
                    case 1:
                        stance = me->getLevel() < 30 ? 1 : (urand(1,100) > 75 ? 3 : 1);
                        break;
                }
            }
            else if (stance == 4)
            {
                switch (urand(0,1))
                {
                    case 0:
                        stance = 1;
                        break;
                    case 1:
                        stance = me == tank ? 2 : 1;
                        break;
                }
            }

            if (stance == 2 && me->getLevel() < 10)
                return false;
            if (stance == 3 && me->getLevel() < 30)
                return false;

            temptimer = GC_Timer;
            //stance mastery impl
            uint32 temprage = 0;
            uint32 myrage = me->GetPower(POWER_RAGE);
            if (me->getLevel() >= 20)
                temprage = myrage > 500 ? 500 : myrage;
            else if (me->getLevel() >= 15)
                temprage = myrage > 250 ? 250 : myrage;
            switch (stance)
            {
                case 1:
                    if (doCast(me, BATTLESTANCE))
                    {
                        if (me->HasAura(BATTLESTANCE))
                        {
                            battleStance = true;
                            defensiveStance = false;
                            berserkerStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 1520 - me->getLevel() * 12;//500 on 85
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                case 2:
                    if (doCast(me, DEFENSIVESTANCE))
                    {
                        if (me->HasAura(DEFENSIVESTANCE))
                        {
                            defensiveStance = true;
                            battleStance = false;
                            berserkerStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 1520 - me->getLevel() * 12;//500 on 85
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                case 3:
                    if (doCast(me, BERSERKERSTANCE))
                    {
                        if (me->HasAura(BERSERKERSTANCE))
                        {
                            berserkerStance = true;
                            battleStance = false;
                            defensiveStance = false;
                            me->SetPower(POWER_RAGE, temprage);
                            stancetimer = 1520 - me->getLevel() * 12;//500 on 85
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                    break;
                default:
                    break;
            }
            GC_Timer = temptimer;
            return false;
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
                //Taste For Blood part 1: 60% additional critical chance for Overpower
                if (lvl >= 30 && spellId == OVERPOWER)
                    aftercrit += 60.f;
                //Cruelty: 10% additional crit chance for Bloodthirst, Mortal Strike and Shield Slam
                if (lvl >= 10 && (spellId == MORTALSTRIKE/* || || */))
                    aftercrit += 10.f;
                //Incite: 15% additional crit chance for Heroic Strike (lvl 10) TODO

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half
                //Impale: 20% crit damage bonus for all abilities
                if (lvl >= 20)
                    pctbonus += 0.10f;
            }

            //Lambs to the Slaughter: 10% bonus damage for Execute, Overpower, Slam and MS per stack
            if (lvl >= 50 && spellId == EXECUTE || spellId == OVERPOWER || spellId == SLAM || spellId == MORTALSTRIKE)
            {
                if (Aura* sl = me->GetAura(LAMBS_TO_THE_SLAUGHTER_BUFF))
                    pctbonus += 0.1f * sl->GetStackAmount();
            }
            //Meat Cleaver: 30% bonus damage for Whirlwind and Cleave (3 stacks) - placeholder
            if (lvl >= 50 && spellId == WHIRLWIND || spellId == CLEAVE)
                pctbonus += 0.3f;
            //Improved Slam: 20% bonus damage for Slam
            if (lvl >= 40 && spellId == SLAM)
                pctbonus += 0.2f;
            //War Academy: 15% bonus damage for MS, Raging Blow, Devastate, Victory Rush and Slam
            if (lvl >= 10 && (spellId == MORTALSTRIKE || spellId == SLAM/* || || || */))
                pctbonus += 0.15f;

            //execute 250% - fix too low damage
            if (spellId == EXECUTE)
                pctbonus += 1.5f;

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            switch (spell->Id)
            {
                case VICTORIOUS_SPELL:
                    VICTORIOUS = true;
                    break;
                default:
                    break;
            }
            OnSpellHit(caster, spell);
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (victim == me)
                return;

            if (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE)
            {
                //zzzOLD Sword Specialization: 1 - 15% chance
                if (swordspectimer == 0 && me->getLevel() >= 15)
                {
                    if (urand(0,100) < std::min<uint8>(15, me->getLevel() - 14))
                        swordspectimer = 1000;

                    if (swordspectimer > 0)
                    {
                        //Spell* spell = new Spell(me, sSpellMgr->GetSpellInfo(SWORD_SPECIALIZATION_TRIGGERED), TRIGGERED_FULL_MASK);
                        //spell->ExecuteLogEffectExtraAttacks(EFFECT_0, victim, 1);
                        //spell->SendLogExecute();
                        //delete spell;
                        //me->m_extraAttacks += 1;
                        me->CastSpell(victim, SWORD_SPECIALIZATION_TRIGGERED, true);
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
            slam_cd = 0;
            regen_cd = 20000;
            sweeping_strikes_cd = 0;
            charge_cd = 0;
            deathwish_cd = 7000;
            mortalStrike_cd = 0;
            uber_cd = 10000;
            berserkerRage_cd = 0;
            batcomShout_cd = 0;
            intercept_cd = 0;
            intimidatingShout_cd = 0;
            pummel_cd = 0;
            whirlwind_cd = 5000;
            cleave_cd = 0;
            bladestorm_cd = 10000;
            bloodrage_cd = 0;
            intervene_cd = 0;
            taunt_cd = 5000;
            sunder_cd = 0;
            stancetimer = 0;
            ragetimer = 1500;
            swordspectimer = 0;

            battleStance = true;
            defensiveStance = false;
            berserkerStance = false;

            rageIncomeMult = sWorld->getRate(RATE_POWER_RAGE_INCOME);
            rageLossMult = sWorld->getRate(RATE_POWER_RAGE_LOSS);
            me->setPowerType(POWER_RAGE);
            rage = 0;

            if (master)
            {
                setStats(CLASS_WARRIOR, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_WARRIOR);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (regen_cd > diff)                    regen_cd -= diff;
            if (slam_cd > diff)                     slam_cd -= diff;
            if (batcomShout_cd > diff)              batcomShout_cd -= diff;
            if (sweeping_strikes_cd > diff)         sweeping_strikes_cd -= diff;
            if (deathwish_cd > diff)                deathwish_cd -= diff;
            if (mortalStrike_cd > diff)             mortalStrike_cd -= diff;
            if (uber_cd > diff)                     uber_cd -= diff;
            if (berserkerRage_cd > diff)            berserkerRage_cd -= diff;
            if (charge_cd > diff)                   charge_cd -= diff;
            if (intercept_cd > diff)                intercept_cd -= diff;
            if (intimidatingShout_cd > diff)        intimidatingShout_cd -= diff;
            if (pummel_cd > diff)                   pummel_cd -= diff;
            if (whirlwind_cd > diff)                whirlwind_cd -= diff;
            if (bladestorm_cd > diff)               bladestorm_cd -= diff;
            if (cleave_cd > diff)                   cleave_cd -= diff;
            if (bloodrage_cd > diff)                bloodrage_cd -= diff;
            if (intervene_cd > diff)                intervene_cd -= diff;
            if (taunt_cd > diff)                    taunt_cd -= diff;
            if (sunder_cd > diff)                   sunder_cd -= diff;

            if (stancetimer > diff)                 stancetimer -= diff;
            if (ragetimer > diff)                   ragetimer -= diff;

            if (swordspectimer > diff)              swordspectimer -= diff;
            else                                    swordspectimer = 0;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            //CHALLENGING_SHOUT                       = InitSpell(me, CHALLENGING_SHOUT_1);
            INTIMIDATING_SHOUT                      = InitSpell(me, INTIMIDATING_SHOUT_1);
            ENRAGED_REGENERATION                    = InitSpell(me, ENRAGED_REGENERATION_1);
            CHARGE                                  = InitSpell(me, CHARGE_1);
            OVERPOWER                               = InitSpell(me, OVERPOWER_1);
   /*Quest*/TAUNT                       = lvl >= 10 ? TAUNT_1 : 0;
            //DISARM                                  = InitSpell(DISARM_1);
            BLOODRAGE                               = InitSpell(me, BLOODRAGE_1);
            BERSERKERRAGE                           = InitSpell(me, BERSERKERRAGE_1);
            INTERCEPT                               = InitSpell(me, INTERCEPT_1);
            CLEAVE                                  = InitSpell(me, CLEAVE_1);
            HAMSTRING                               = InitSpell(me, HAMSTRING_1);
            INTERVENE                               = InitSpell(me, INTERVENE_1);
            WHIRLWIND                               = InitSpell(me, WHIRLWIND_1);
  /*Talent*/BLADESTORM                  = lvl >= 60 ? BLADESTORM_1 : 0;
            BATTLESHOUT                             = InitSpell(me, BATTLESHOUT_1);
            REND                                    = InitSpell(me, REND_1);
            EXECUTE                                 = InitSpell(me, EXECUTE_1);
            PUMMEL                                  = InitSpell(me, PUMMEL_1);
  /*Talent*/MORTALSTRIKE                = lvl >= 10 ? InitSpell(me, MORTALSTRIKE_1) : 0;
            SLAM                                    = InitSpell(me, SLAM_1);
   /*Quest*/SUNDER                      = lvl >= 10 ? InitSpell(me, SUNDER_1) : 0;
  /*Talent*/SWEEPING_STRIKES            = lvl >= 30 ? SWEEPING_STRIKES_1 : 0;
            BATTLESTANCE                            = BATTLESTANCE_1;
   /*Quest*/DEFENSIVESTANCE             = lvl >= 10 ? DEFENSIVESTANCE_1 : 0;
   /*Quest*/BERSERKERSTANCE             = lvl >= 30 ? BERSERKERSTANCE_1 : 0;
            RECKLESSNESS                            = InitSpell(me, RECKLESSNESS_1);
            RETALIATION                             = InitSpell(me, RETALIATION_1);
  /*Talent*/DEATHWISH                   = lvl >= 30 ? DEATHWISH_1 : 0;
            VICTORY_RUSH                            = InitSpell(me, VICTORY_RUSH_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 61)
                RefreshAura(WC2); //10%
            else if (level >= 59)
                RefreshAura(WC1); //5%
            if (level >= 53)
                RefreshAura(LAMBS_TO_THE_SLAUGHTER); //10% x3
            if (level >= 37)
                RefreshAura(FLURRY3); //30%
            else if (level >= 35)
                RefreshAura(FLURRY2); //20%
            else if (level >= 33)
                RefreshAura(FLURRY1); //10%
            if (level >= 60)
                RefreshAura(RAMPAGE);
            if (level >= 45)
                RefreshAura(BLOOD_FRENZY);
            if (level >= 40)
                RefreshAura(SECOND_WIND);
            if (level >= 40)
                RefreshAura(TOUGHNESS,2); //-60%
            else if (level >= 15)
                RefreshAura(TOUGHNESS); //-30%
            if (level >= 35)
                RefreshAura(IMP_HAMSTRING);
            if (level >= 35)
                UNRELENTING_ASSAULT = true;
            if (level >= 30)
                RefreshAura(TASTE_FOR_BLOOD3); //100%
            else if (level >= 28)
                RefreshAura(TASTE_FOR_BLOOD2); //66%
            else if (level >= 25)
                RefreshAura(TASTE_FOR_BLOOD1); //33%
            if (level >= 13)
                RefreshAura(BLOOD_CRAZE3);
            else if (level >= 11)
                RefreshAura(BLOOD_CRAZE2);
            else if (level >= 10)
                RefreshAura(BLOOD_CRAZE1);
            //BloodRage Absorb
            if (level >= 60)
                RefreshAura(WARRIOR_T10_4P);
        }

    private:
        uint32
  /*Shouts*/INTIMIDATING_SHOUT, BATTLESHOUT, CHALLENGING_SHOUT,
 /*Charges*/CHARGE, INTERCEPT, INTERVENE,
  /*Damage*/OVERPOWER, CLEAVE, REND, EXECUTE, WHIRLWIND, BLADESTORM, MORTALSTRIKE, SLAM,
 /*Stances*/BATTLESTANCE, DEFENSIVESTANCE, BERSERKERSTANCE,
   /*Ubers*/RECKLESSNESS, RETALIATION, DEATHWISH,
  /*Others*/TAUNT, DISARM, BLOODRAGE, ENRAGED_REGENERATION, VICTORY_RUSH,
        BERSERKERRAGE, HAMSTRING, PUMMEL, SUNDER, SWEEPING_STRIKES;

        //CDs/Timers/misc
/*shts*/uint32 batcomShout_cd, intimidatingShout_cd;
/*chrg*/uint32 charge_cd, intercept_cd, intervene_cd;
 /*Dmg*/uint32 mortalStrike_cd, slam_cd, whirlwind_cd, cleave_cd, bladestorm_cd;
/*else*/uint32 regen_cd, sweeping_strikes_cd, deathwish_cd, uber_cd, berserkerRage_cd, pummel_cd,
            bloodrage_cd, taunt_cd, sunder_cd;
/*tmrs*/uint32 stancetimer, ragetimer, swordspectimer;
/*misc*/uint32 rage;
/*misc*/float rageIncomeMult, rageLossMult;
/*Chck*/bool battleStance, defensiveStance, berserkerStance, UNRELENTING_ASSAULT, VICTORIOUS;

        enum WarriorBaseSpells
        {
            //CHALLENGING_SHOUT_1                     = 1161,
            INTIMIDATING_SHOUT_1                    = 5246,
            ENRAGED_REGENERATION_1                  = 55694,
            CHARGE_1                                = 100,//11578,
            OVERPOWER_1                             = 7384,
            TAUNT_1                                 = 355,
            //DISARM_1                                = 676,
            BLOODRAGE_1                             = 29131,//2687,
            BERSERKERRAGE_1                         = 18499,
            INTERCEPT_1                             = 20252,
            CLEAVE_1                                = 90981,//'90981 - (150% damage 3 targets)'//845,
            HAMSTRING_1                             = 1715,
            INTERVENE_1                             = 3411,
            WHIRLWIND_1                             = 1680,
            BLADESTORM_1                            = 46924,
            BATTLESHOUT_1                           = 6673,
            REND_1                                  = 772,
            EXECUTE_1                               = 5308,
            PUMMEL_1                                = 6552,
            MORTALSTRIKE_1                          = 12294,
            SLAM_1                                  = 1464,
            SUNDER_1                                = 7386,
            SWEEPING_STRIKES_1                      = 12328,
            BATTLESTANCE_1                          = 2457,
            DEFENSIVESTANCE_1                       = 71,
            BERSERKERSTANCE_1                       = 2458,
            RECKLESSNESS_1                          = 13847,//1719, original warrior spell
            RETALIATION_1                           = 20230,
            DEATHWISH_1                             = 12292,
            VICTORY_RUSH_1                          = 34428
        };
        enum WarriorPassives
        {
        //Talents
            WC1  /*WRECKING CREW1*/                 = 46867,
            WC2  /*WRECKING CREW2*/                 = 56611,
            FLURRY1                                 = 16256,
            FLURRY2                                 = 16281,
            FLURRY3                                 = 16282,
            BLOOD_CRAZE1                            = 16487,
            BLOOD_CRAZE2                            = 16489,
            BLOOD_CRAZE3                            = 16492,
            TASTE_FOR_BLOOD1                        = 56636,
            TASTE_FOR_BLOOD2                        = 56637,
            TASTE_FOR_BLOOD3                        = 56638,
            BLOOD_FRENZY                            = 29859,
            RAMPAGE                                 = 29801,
            SECOND_WIND                             = 29838,//rank 2
            TOUGHNESS                               = 12762,//rank 3
            IMP_HAMSTRING                           = 12668,//rank 2
            LAMBS_TO_THE_SLAUGHTER                  = 84588,//rank 3
        //other
            WARRIOR_T10_4P                          = 70844
        };
        enum WarriorSpecial
        {
            TASTE_FOR_BLOOD_BUFF                    = 60503,
            LAMBS_TO_THE_SLAUGHTER_BUFF             = 84586,
            UNRELENTING_ASSAULT_SPELL               = 65925,//64849
            VICTORIOUS_SPELL                        = 32216,
            COLOSSUS_SMASH_EFFECT                   = 108126,
            SWORD_SPECIALIZATION_TRIGGERED          = 16459
        };
        enum WarriorCooldowns
        {
            ENRAGED_REGENERATION_CD = 90000,  //1.5 min
            SWEEPING_STRIKES_CD     = 20000,
            CHARGE_CD               = 12000,
            DEATHWISH_CD            = 144000, //3 min improved -20%
            MORTALSTRIKE_CD         = 4500,
            UBER_CD                 = 150000, //RETALIATION_RECKLESSNESS_SHIELDWALL 2.5 min NEED SEPARATE
            BERSERKERRAGE_CD        = 25000,
            INTERCEPT_CD            = 20000,  //30 sec improved -10
            INTIMIDATINGSHOUT_CD    = 45000,
            PUMMEL_CD               = 9000,
            WHIRLWIND_CD            = 6500,
            BLADESTORM_CD           = 60000,
            BLOODRAGE_CD            = 20000,
            //DISARM_CD               = 40000,
            INTERVENE_CD            = 20000,  //-10 sec for bots
            SHOUT_CD                = 60000,
            //SPELLREFLECTION_CD      = 8000,
            TAUNT_CD                = 8000,
            SUNDER_CD               = 7000
        };
    };
};

void AddSC_warrior_bot()
{
    new warrior_bot();
}
