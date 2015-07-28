#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
/*
Death Knight NpcBot by Graff onlysuffering@gmail.com
Complete - around 55%
Note: Rune system adapted from TC
TODO: REMEMBER ALREADY DK HAS MINIMUM LEVEL 55!
*/
const RuneType runeSlotTypes[MAX_RUNES] =
{
    RUNE_BLOOD,
    RUNE_BLOOD,
    RUNE_UNHOLY,
    RUNE_UNHOLY,
    RUNE_FROST,
    RUNE_FROST
};
struct BotRuneInfo
{
    uint8 BaseRune;
    uint8 CurrentRune;
    uint32 Cooldown;
    //AuraEffect const* ConvertAura;
};

struct BotRunes
{
    BotRuneInfo runes[MAX_RUNES];
    //uint8 runeState;          //UNUSED
    //uint8 lastUsedRune;       //UNUSED

    //void SetRuneState(uint8 index, bool set = true)
    //{
    //    if (set)
    //        runeState |= (1 << index);    // usable
    //    else
    //        runeState &= ~(1 << index);   // on cooldown
    //}
};
class death_knight_bot : public CreatureScript
{
public:
    death_knight_bot() : CreatureScript("death_knight_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new death_knight_botAI(creature);
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

    struct death_knight_botAI : public bot_minion_ai
    {
        death_knight_botAI(Creature* creature) : bot_minion_ai(creature) { }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_DEATH_KNIGHT) != SPELL_CAST_OK)
                return false;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            int32 runecost[NUM_RUNE_TYPES];
            for (uint8 i = 0; i != NUM_RUNE_TYPES; ++i)
                runecost[i] = 0;

            if (!triggered)
            {
                if (!HaveRunes(spellInfo, runecost))
                    return false;
            }

            bool result = bot_ai::doCast(victim, spellId, triggered);

            if (result)
            {
                //std::ostringstream str;
                //str << "Casting " << spellInfo->SpellName[0] << " on " << victim->GetName();
                //me->MonsterWhisper(str.str().c_str(), master->GetGUID());
                //Set cooldown for runes
                if (!triggered)
                {
                    SpendRunes(runecost);
                    ////debug
                    //for (uint8 i = 0; i != NUM_RUNE_TYPES; ++i)
                    //    if (runecost[i])
                    //        TC_LOG_FATAL("entities.player", "doCast():: DK bot %s has casted spell %u (%s) without %u rune(s) (type %u)!",
                    //            me->GetName().c_str(), spellId, spellInfo->SpellName[0], runecost[i], i);
                }
                //runic power gain: all dk spells are instant but some have no unit target so
                //we gain runic power here instead of SpellHitTarget()
                if (SpellRuneCostEntry const* src = sSpellRuneCostStore.LookupEntry(spellInfo->RuneCostID))
                    if (int32 rp = int32(src->runePowerGain * runicpowerIncomeMult))
                        me->ModifyPower(POWER_RUNIC_POWER, int32(rp));
            }

            return result;
        }

        bool HaveRunes(SpellInfo const* spellInfo, int32 *runecost) const
        {
            if (spellInfo->PowerType != POWER_RUNES || !spellInfo->RuneCostID)
                return true;

            CalcRuneCost(spellInfo, runecost);

            if (runecost[RUNE_DEATH] != 0 && runecost[RUNE_DEATH] > GetDeathRunesCount())
                return false;

            return true;
        }

        void CalcRuneCost(SpellInfo const* spellInfo, int32 *runecost) const
        {
            SpellRuneCostEntry const* src = sSpellRuneCostStore.LookupEntry(spellInfo->RuneCostID);
            if (!src)
                return;

            if (src->NoRuneCost())
                return;

            for (uint8 i = 0; i != RUNE_DEATH; ++i)
                runecost[i] = src->RuneCost[i];

            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                uint8 rune = _runes.runes[i].BaseRune;
                if (_runes.runes[i].CurrentRune == rune && _runes.runes[i].Cooldown == 0 && runecost[rune] > 0)
                    runecost[rune]--;
            }

            for (uint8 i = 0; i != RUNE_DEATH; ++i)
                if (runecost[i] > 0)
                    runecost[RUNE_DEATH] += runecost[i];

            ////restore cost to allow cooldown set
            //for (uint8 i = 0; i != RUNE_DEATH; ++i)
            //    runecost[i] = src->RuneCost[i];
        }

        int32 GetDeathRunesCount() const
        {
            int32 count = 0;
            for (uint8 i = 0; i != MAX_RUNES; ++i)
                if (_runes.runes[i].CurrentRune == RUNE_DEATH && _runes.runes[i].Cooldown == 0)
                    ++count;

            return count;
        }

        uint8 GetCooledRunesCount(uint8 runetype) const
        {
            uint8 count = 0;
            for (uint8 i = 0; i != MAX_RUNES; ++i)
                if (_runes.runes[i].BaseRune == runetype && _runes.runes[i].Cooldown > 0)
                    ++count;

            return count;
        }

        void SpendRunes(int32* runecost)
        {
            for (uint8 i = 0; i != NUM_RUNE_TYPES; ++i)
            {
                if (runecost[i] <= 0)
                    continue;

                for (uint8 j = 0; j != MAX_RUNES && runecost[i] > 0; ++j)
                {
                    if (SpendRune(i))
                        runecost[i]--;
                }
            }

            if (GetCooledRunesCount(RUNE_BLOOD) > 1)
            {
                me->CastSpell(me, BLADE_BARRIER_AURA, true);
            }
        }

        bool SpendRune(uint8 runetype)
        {
            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                if (_runes.runes[i].CurrentRune == runetype && _runes.runes[i].Cooldown == 0)
                {
                    _runes.runes[i].CurrentRune = _runes.runes[i].BaseRune;
                    //_runes.lastUsedRune = _runes.runes[i].CurrentRune;        //UNUSED
                    //_runes.SetRuneState(i, false);                            //UNUSED
                    //DK receives rune regen bonus from mana regen
                    uint32 cooldown = RUNE_BASE_COOLDOWN - std::min<uint32>(uint32(GetManaRegen() * 10), RUNE_BASE_COOLDOWN);
                    _runes.runes[i].Cooldown = cooldown;
                    //std::ostringstream str;
                    //str << "Spent rune " << uint32(i) << " (type: " << uint32(runetype) << ')';
                    //me->MonsterWhisper(str.str().c_str(), master->GetGUID());
                    return true;
                }
            }

            return false;
        }

        bool HaveRune(uint8 runetype) const
        {
            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                if ((_runes.runes[i].CurrentRune == runetype || _runes.runes[i].CurrentRune == RUNE_DEATH) &&
                    _runes.runes[i].Cooldown == 0)
                {
                    return true;
                }
            }

            return false;
        }

        void ConvertRune(uint8 runetype, uint8 count)
        {
            if (runetype == RUNE_DEATH)
                return;

            uint8 failcount = 0;
            for (uint8 i = 0; i != MAX_RUNES && count > 0; ++i)
            {
                if (_runes.runes[i].BaseRune == runetype)
                {
                    if (_runes.runes[i].CurrentRune == RUNE_DEATH)
                    {
                        ++failcount;
                        continue;
                    }

                    if (_runes.runes[i].Cooldown > 3000)
                        _runes.runes[i].Cooldown -= 3000;

                    _runes.runes[i].CurrentRune = RUNE_DEATH;
                    --count;
                }
            }

            if (!count && !failcount)
                return;

            //std::ostringstream str;
            //str << "Failed to convert rune of type: " << uint32(runetype) << ")!";
            //me->MonsterWhisper(str.str().c_str(), master->GetGUID());
        }

        void ActivateAllRunes()
        {
            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                _runes.runes[i].Cooldown = 0;
                //_runes.SetRuneState(i, true);       //UNUSED
            }
        }

        void InitRunes()
        {
            //_runes.runeState = 0;                   //UNUSED
            //_runes.lastUsedRune = RUNE_BLOOD;       //UNUSED

            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                _runes.runes[i].BaseRune = runeSlotTypes[i];
                _runes.runes[i].CurrentRune = _runes.runes[i].BaseRune;
                _runes.runes[i].Cooldown = 0;
                //_runes.runes[i].ConvertAura = NULL; //UNUSED
                //_runes.SetRuneState(i, true);       //UNUSED
            }
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            SetBotCommandState(COMMAND_ATTACK);
            GetInPosition(force, false);
        }

        void RuneTimers(uint32 diff)
        {
            for (uint8 i = 0; i != MAX_RUNES; ++i)
            {
                if (_runes.runes[i].Cooldown <= diff)
                {
                    _runes.runes[i].Cooldown = 0;
                    //_runes.SetRuneState(i, true);     //UNUSED
                }
                else
                    _runes.runes[i].Cooldown -= diff;
            }
        }

        void modpower(int32 mod, bool set = false)
        {
            if (set && mod < 0)
                return;
            if (mod < 0 && runicpower < uint32(abs(mod)))
            {
                //debug set runic power to 0
                mod = 0;
                set = true;
                return;
            }

            if (set)
                runicpower = mod ? mod * 10 : 0;
            else
                runicpower += mod * 10;

            me->SetPower(POWER_RUNIC_POWER, runicpower);
        }

        uint32 getpower()
        {
            runicpower = me->GetPower(POWER_RUNIC_POWER);
            return runicpower;
        }

        uint8 GetBotStance() const { return Presence; }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }
        void KilledUnit(Unit*) { }
        void DoNonCombatActions(uint32 diff)
        {
            if (GC_Timer > diff || IsCasting() || Feasting() || Rand() > 20)
                return;

            //PATH OF FROST
            if (PATH_OF_FROST && HaveRune(RUNE_FROST)/* && !me->IsMounted()*/) //works while mounted
            {
                if ((me->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING) && !me->HasAuraType(SPELL_AURA_WATER_WALK)) ||
                    (master->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING) && !master->HasAuraType(SPELL_AURA_WATER_WALK) && me->GetDistance(master) < 50))
                {
                    if (doCast(me, PATH_OF_FROST))
                        return;
                }
            }
        }

        void CheckHysteria(uint32 diff)
        {
            if (!HYSTERIA || Hysteria_cd > diff || GC_Timer > diff || IsCasting() || Rand() > 15)
                return;

            Unit* target = NULL;

            if (master->IsAlive() && isMeleeClass(master->getClass()) && master->IsInCombat() &&
                GetHealthPCT(master) > 80 && me->GetDistance(master) < 30 &&
                master->getAttackers().empty() && !CCed(master, true))
            {
                if (Unit* u = master->GetVictim())
                    if (u->GetHealth() > me->GetMaxHealth() / 2)
                        target = master;
            }

            if (!target && isMeleeClass(me->GetBotClass()) && GetHealthPCT(me) > 80 &&
                me->getAttackers().empty() && !CCed(me, true))
            {
                if (Unit* u = me->GetVictim())
                    if (u->GetHealth() > me->GetMaxHealth() / 2)
                        target = me;
            }

            if (!target)
            {
                Group* gr = master->GetGroup();
                if (gr)
                {
                    for (GroupReference* itr = gr->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        Player* tPlayer = itr->GetSource();
                        if (tPlayer == master) continue;
                        if (!tPlayer || !tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
                        if (!tPlayer->IsAlive() || me->GetMap() != tPlayer->FindMap()) continue;
                        if (!isMeleeClass(tPlayer->getClass()) || !tPlayer->IsInCombat()) continue;
                        if (GetHealthPCT(tPlayer) < 80 || me->GetDistance(tPlayer) > 30) continue;
                        if (!tPlayer->getAttackers().empty() || CCed(tPlayer, true)) continue;
                        if (Unit* u = tPlayer->GetVictim())
                        {
                            if (u->GetHealth() > (me->GetMaxHealth() * 2) / 3)
                            {
                                target = tPlayer;
                                break;
                            }
                        }
                    }
                }
            }

            if (target && doCast(target, HYSTERIA))
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    me->MonsterWhisper("Hysteria on You!", target->ToPlayer());
                    Hysteria_cd = 90000; //1.5 min for player
                }
                else
                    Hysteria_cd = 30000; //30 sec for bot

                GC_Timer = 800;
                return;
            }

            Hysteria_cd = 2000; //fail
        }

        void CheckAntiMagicShell(uint32 diff)
        {
            if (!ANTI_MAGIC_SHELL || AntiMagicShell_cd > diff || GetHealthPCT(me) > 55 ||
                getpower() < 200 || IsCasting() || Rand() > 50)
                return;

            AttackerSet b_attackers = me->getAttackers();

            if (b_attackers.empty())
                return;

            bool cast = false;
            uint8 count = 0;

            for (AttackerSet::const_iterator itr = b_attackers.begin(); itr != b_attackers.end(); ++itr)
            {
                if (!(*itr) || !(*itr)->IsAlive()) continue;
                if (Spell* spell = (*itr)->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                {
                    if (spell->m_targets.GetUnitTargetGUID() == me->GetGUID())
                    {
                        if ((*itr)->ToCreature() && (*itr)->ToCreature()->isWorldBoss())
                        {
                            cast = true;
                            break;
                        }

                        if (++count >= 3)
                        {
                            cast = true;
                            break;
                        }
                    }
                }
            }

            if (cast)
            {
                temptimer = GC_Timer;
                if (doCast(me, ANTI_MAGIC_SHELL))
                {
                    AntiMagicShell_cd = 30000; //30 sec for bot
                    GC_Timer = temptimer;
                    return;
                }
            }

            AntiMagicShell_cd = 1500; //fail
        }

        void CheckPresence(uint32 diff)
        {
            if (presencetimer > diff || IsCasting() || Rand() > 30) //no GCD
                return;

            uint8 newpresence = master->GetBotTank(me->GetCreatureTemplate()->Entry) == me ? DEATH_KNIGHT_FROST_PRESENCE : DEATH_KNIGHT_BLOOD_PRESENCE;
            if (Presence == newpresence)
            {
                presencetimer = 500;
                return;
            }

            Presence = newpresence;

            if (Presence == DEATH_KNIGHT_FROST_PRESENCE && HaveRune(RUNE_FROST))
            {
                temptimer = GC_Timer;
                if (doCast(me, FROST_PRESENCE))
                {
                    GC_Timer = temptimer;
                    presencetimer = 1000;
                    return;
                }
            }
            else if (Presence == DEATH_KNIGHT_BLOOD_PRESENCE && HaveRune(RUNE_BLOOD))
            {
                temptimer = GC_Timer;
                if (doCast(me, BLOOD_PRESENCE))
                {
                    GC_Timer = temptimer;
                    presencetimer = 1000;
                    return;
                }
            }

            presencetimer = 500; //fail
        }

        void BreakCC(uint32 diff)
        {
            if (LICHBORNE && Lichborne_cd <= diff &&/* Rand() < 75 &&*/
                me->HasAuraWithMechanic((1<<MECHANIC_CHARM)|(1<<MECHANIC_FEAR)|(1<<MECHANIC_SLEEP)))
            {
                temptimer = GC_Timer;
                if (doCast(me, LICHBORNE))
                {
                    Lichborne_cd = 60000;
                    GC_Timer = temptimer;
                    return;
                }
            }

            bot_minion_ai::BreakCC(diff);
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            if (me->GetVictim())
                DoMeleeAttackIfReady();
            else
                Evade();

            if (me->getPowerType() != POWER_RUNIC_POWER)
                InitPowers();

            if (runicpowertimer <= diff)
            {
                if (!me->IsInCombat())
                {
                    if (getpower() > uint32(30 * runicpowerLossMult))
                        me->SetPower(POWER_RUNIC_POWER, runicpower - uint32(30 * runicpowerLossMult)); //-3 runic power every 2 sec
                    else
                        me->SetPower(POWER_RUNIC_POWER, 0);
                }
                runicpowertimer = 2000;
            }
            if (runicpowertimer2 <= diff)
            {
                if (me->IsInCombat())
                {
                    if (int32(getpower()) < me->GetMaxPower(POWER_RUNIC_POWER))
                        me->SetPower(POWER_RUNIC_POWER, runicpower + uint32(20 * runicpowerIncomeMult)); //+2 runic power every 5 sec
                    else
                        me->SetPower(POWER_RUNIC_POWER, me->GetMaxPower(POWER_RUNIC_POWER));
                }
                runicpowertimer2 = 5000;
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
            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            CheckPresence(diff);

            //HORN OF WINTER
            if (HORN_OF_WINTER && HornOfWinter_cd <= (me->IsInCombat() ? 45000 : diff) && Rand() < 30 &&
                (me->IsInCombat() || (me->GetDistance(master) < 28 && master->IsWithinLOSInMap(me))))
            {
                Aura* horn = master->GetAura(HORN_OF_WINTER);
                if (!horn || horn->GetDuration() < 5000)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, HORN_OF_WINTER))
                    {
                        HornOfWinter_cd = 60000;
                        GC_Timer = temptimer;
                        return;
                    }
                }
            }
            //BONE SHIELD
            if (BONE_SHIELD && BoneShield_cd <= diff && GC_Timer <= diff && HaveRune(RUNE_UNHOLY) && Rand() < 25)
            {
                Aura* bone = me->GetAura(BONE_SHIELD);
                if (!bone || bone->GetCharges() < 2 || (!me->IsInCombat() && bone->GetDuration() < 60000))
                {
                    if (doCast(me, BONE_SHIELD))
                    {
                        BoneShield_cd = 30000;
                        GC_Timer = 800;
                        return;
                    }
                }

                BoneShield_cd = 1000; //fail
            }

            if (me->IsInCombat())
            {
                //ICEBOUND FORTITUDE
                if (ICEBOUND_FORTITUDE && IceboundFortitude_cd <= diff && getpower() >= 200 &&
                    GetHealthPCT(me) < std::min<uint32>(85, 45 + uint8(me->getAttackers().size()) * 7) &&
                    Rand() < 40 + (me == tank) * 50)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, ICEBOUND_FORTITUDE))
                    {
                        GC_Timer = temptimer;
                        IceboundFortitude_cd = 90000;
                    }
                }

                CheckAntiMagicShell(diff);
                CheckHysteria(diff);
            }

            if (!CheckAttackTarget(CLASS_DEATH_KNIGHT))
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

            //SELFHEAL

            //RUNE TAP
            if (RUNE_TAP && RuneTap_cd <= diff && GC_Timer <= 600 && GetHealthPCT(me) < 40 && Rand() < 50)
            {
                if (!HaveRune(RUNE_BLOOD) && EMPOWER_RUNE_WEAPON && EmpowerRuneWeapon_cd <= diff)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, EMPOWER_RUNE_WEAPON))
                    {
                        ActivateAllRunes();
                        EmpowerRuneWeapon_cd = 60000;
                        GC_Timer = temptimer;
                    }
                }
                temptimer = GC_Timer;
                if (doCast(me, RUNE_TAP))
                {
                    RuneTap_cd = 20000;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //VAMPIRIC BLOOD
            if (VAMPIRIC_BLOOD && VampiricBlood_cd <= diff && GetHealthPCT(me) < 26/* && Rand() < 75*/)
            {
                if (!HaveRune(RUNE_BLOOD) && EMPOWER_RUNE_WEAPON && EmpowerRuneWeapon_cd <= 40000)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, EMPOWER_RUNE_WEAPON))
                    {
                        ActivateAllRunes();
                        EmpowerRuneWeapon_cd = 60000;
                        GC_Timer = temptimer;
                    }
                }
                temptimer = GC_Timer;
                if (doCast(me, VAMPIRIC_BLOOD))
                {
                    VampiricBlood_cd = 40000;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //END SELFHEAL

            //MARK OF BLOOD
            Unit* u = opponent->GetVictim();
            if (MARK_OF_BLOOD && MarkOfBlood_cd <= diff && GC_Timer <= diff && HaveRune(RUNE_BLOOD) &&
                u && GetHealthPCT(u) < 85 && opponent->GetHealth() > u->GetMaxHealth() / 3 &&
                (u == tank || u->GetTypeId() == TYPEID_PLAYER) &&
                Rand() < 35 && !opponent->HasAura(MARK_OF_BLOOD) && IsInBotParty(u))
            {
                if (doCast(opponent, MARK_OF_BLOOD))
                {
                    MarkOfBlood_cd = 90000; //1.5 min for bots
                    GC_Timer = 800;
                    return;
                }
            }

            //AttackerSet m_attackers = master->getAttackers();
            //AttackerSet b_attackers = me->getAttackers();
            float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);

            //NON-DISEASE SECTION

            //PLACEHOLDER: ARMY OF THE DEAD

            //RANGED SECTION

            //STRANGULATE
            if (STRANGULATE && Strangulate_cd <= diff && GC_Timer <= diff && meleedist <= 30 && HaveRune(RUNE_BLOOD) &&
                opponent->IsNonMeleeSpellCast(false) && Rand() < 40)
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);

                if (doCast(opponent, STRANGULATE))
                {
                    Strangulate_cd = 40000; //-67% for bots
                    return;
                }

                Strangulate_cd = 500; //fail
            }
            //DARK COMMAND
            if (DARK_COMMAND && DarkCommand_cd <= diff && dist < 30 && tank == me && opponent->GetVictim() != me &&
                Rand() < 70)
            {
                temptimer = GC_Timer;
                if (doCast(opponent, DARK_COMMAND))
                {
                    DarkCommand_cd = 6000;
                    GC_Timer = temptimer;
                    return;
                }
            }
            ////DEATH GRIP - DISABLED
            //if (DEATH_GRIP && DeathGrip_cd <= diff && dist < 30 &&
            //    (tank == me && opponent->GetVictim() != me) ||
            //    (opponent->GetVictim() == me && opponent->ToPlayer() && opponent->IsNonMeleeSpellCast(false)) &&
            //    Rand() < 75)
            //{
            //    temptimer = GC_Timer;
            //    if (doCast(opponent, DEATH_GRIP))
            //    {
            //        DeathGrip_cd = 25000;
            //        GC_Timer = temptimer;
            //        return;
            //    }

            //    DeathGrip_cd = 1000; //fail
            //}
            //CHAINS OF ICE
            if (CHAINS_OF_ICE && GC_Timer <= diff && dist < 20 && HaveRune(RUNE_FROST) && opponent->isMoving() &&
                !CCed(opponent) && opponent->GetVictim() != tank && IsInBotParty(opponent->GetVictim()) && Rand() < 25)
            {
                Aura* chains = opponent->GetAura(CHAINS_OF_ICE);
                if (!chains || chains->GetDuration() < chains->GetMaxDuration() / 4)
                {
                    if (doCast(opponent, CHAINS_OF_ICE))
                    {
                        //Improved Chains of Ice: convert frost rune into death rune
                        ConvertRune(RUNE_FROST, 1);
                        return;
                    }
                }
            }

            //AOE SECTION

            //HOWLING BLAST
            if (HOWLING_BLAST && HowlingBlast_cd <= diff && GC_Timer <= diff &&
                tank == me && meleedist < 8 && me->getAttackers().size() > 2 &&
                Rand() < 50 && HaveRune(RUNE_UNHOLY) && HaveRune(RUNE_FROST))
            {
                if (doCast(me, HOWLING_BLAST))
                {
                    HowlingBlast_cd = 7000;
                    GC_Timer = 800;
                    return;
                }

                HowlingBlast_cd = 500; //fail
            }
            //BLOOD BOIL
            if (BLOOD_BOIL && GC_Timer <= diff && Rand() < (10 + 40 * (tank == me)) && HaveRune(RUNE_BLOOD))
            {
                std::list<Unit*> targets;
                GetNearbyTargetsList(targets, 9.5f);
                if (targets.size() >= 5)
                    if (doCast(me, BLOOD_BOIL))
                        return;
            }
            //DEATH AND DECAY
            if (DEATH_AND_DECAY && DeathAndDecay_cd <= diff && GC_Timer <= diff && Rand() < (30 + 30 * (tank == me)) &&
                HaveRune(RUNE_BLOOD) && HaveRune(RUNE_UNHOLY) && HaveRune(RUNE_FROST))
            {
                if (Unit* target = FindAOETarget(30, true))
                {
                    if (doCast(target, DEATH_AND_DECAY))
                    {
                        DeathAndDecay_cd = 15000; //improved by Morbidity
                        return;
                    }
                }

                DeathAndDecay_cd = 500; //fail
            }

            //END AOE SECTION

            //ICY TOUCH
            if (ICY_TOUCH && GC_Timer <= diff && dist < 20 && HaveRune(RUNE_FROST) && Rand() < 25 &&
                !opponent->HasAura(FROST_FEVER_AURA, me->GetGUID()))
            {
                if (doCast(opponent, ICY_TOUCH))
                    return;
            }
            //DEATH COIL
            if (DEATH_COIL && GC_Timer <= 600 && dist < 20 &&
                int32(getpower()) >= (400 + 200 * (RUNE_STRIKE != 0 || MIND_FREEZE != 0 || ANTI_MAGIC_SHELL != 0) + 400 * (HUNGERING_COLD != 0)) &&
                Rand() < 60)
            {
                if (doCast(opponent, DEATH_COIL))
                    return;
            }

            //MELEE SECTION

            //MIND FREEZE
            if (MIND_FREEZE && MindFreeze_cd <= diff && meleedist <= 5 && getpower() >= 200 &&
                opponent->IsNonMeleeSpellCast(false) && Rand() < 60)
            {
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);

                temptimer = GC_Timer;
                if (doCast(opponent, MIND_FREEZE))
                {
                    MindFreeze_cd = 8000;
                    GC_Timer = temptimer;
                    return;
                }
            }
            //HUNGERING COLD
            if (HUNGERING_COLD && HungeringCold_cd <= diff && GC_Timer <= diff && getpower() >= 400 && Rand() < 20)
            {
                std::list<Unit*> targets;
                GetNearbyTargetsList(targets, 9.f, 0, true);
                if (targets.size() >= 3)
                {
                    if (doCast(me, HUNGERING_COLD))
                    {
                        HungeringCold_cd = 45000;
                        return;
                    }
                }

                HungeringCold_cd = 500; //fail
            }

            if (MoveBehind(*opponent))
                wait = 5;

            //RUNE STRIKE
            if (RUNE_STRIKE && RuneStrike_cd <= diff && runestriketimer > me->getAttackTimer(BASE_ATTACK) &&
                meleedist <= 5 && getpower() >= 200/* && Rand() < 75*/)
            {
                temptimer = GC_Timer;
                if (doCast(opponent, RUNE_STRIKE))
                {
                    RuneStrike_cd = me->getAttackTimer(BASE_ATTACK); //only one per swing
                    runestriketimer = 0; //do not remove aura, just disable ability
                    GC_Timer = temptimer;
                }
            }
            //PLAGUE STRIKE
            if (PLAGUE_STRIKE && GC_Timer <= diff && meleedist <= 5 && HaveRune(RUNE_UNHOLY) && Rand() < 35 &&
                !opponent->HasAura(BLOOD_PLAGUE_AURA, me->GetGUID()))
            {
                if (doCast(opponent, PLAGUE_STRIKE))
                    return;
            }

            //DISEASE SECTION
            uint32 diseases = opponent->GetDiseasesByCaster(me->GetGUID());

            //PESTILENCE
            if (PESTILENCE && pestilencetimer == 0 && GC_Timer <= 600 && diseases > 1 && meleedist <= 5 &&
                HaveRune(RUNE_BLOOD) && Rand() < 15)
            {
                std::list<Unit*> targets;
                GetNearbyTargetsList(targets, 9.f);
                if (targets.size() > 2)
                {
                    if (doCast(opponent, PESTILENCE))
                    {
                        pestilencetimer = 10000;
                        return;
                    }
                }

                pestilencetimer = 1000; //fail
            }
            //DEATH STRIKE
            if (DEATH_STRIKE && GC_Timer <= diff && diseases > 0 && meleedist <= 5 &&
                HaveRune(RUNE_UNHOLY) && HaveRune(RUNE_FROST) &&
                GetHealthPCT(me) < (91 - 10 * diseases) && Rand() < 70)
            {
                if (doCast(opponent, DEATH_STRIKE))
                    return;
            }
            //OBLITERATE
            if (OBLITERATE && GC_Timer <= diff && diseases > 2 && meleedist <= 5 &&
                HaveRune(RUNE_UNHOLY) && HaveRune(RUNE_FROST) && Rand() < 20)
            {
                if (doCast(opponent, OBLITERATE))
                    return;
            }
            //BLOOD STRIKE
            if (BLOOD_STRIKE && GC_Timer <= diff && diseases > 1 && meleedist <= 5 &&
                HaveRune(RUNE_BLOOD) && Rand() < 25)
            {
                if (doCast(opponent, BLOOD_STRIKE))
                    return;
            }
        }

        void ApplyClassDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;

                //Increased Plague Strike Crit (id 60130): 10% additional critical chance for Plague Strike
                if (spellId == PLAGUE_STRIKE)
                    aftercrit += 0.1f;
                //Glyph of Rune Strike: 10% additional critical chance for Rune Strike
                if (spellId == RUNE_STRIKE)
                    aftercrit += 0.1f;
                //Subversion: 9% additional critical chance for Blood Strike, Scourge Strike, Heart Strike and Obliterate
                if (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE ||
                    /*spellId == SCOURGE_STRIKE || */spellId == OBLITERATE)
                    aftercrit += 0.09f;
                //Improved Death Strike (part 2): 6% additional critical chance for Death Strike
                if (spellId == DEATH_STRIKE)
                    aftercrit += 0.06f;
                //Rime (part 1 melee): 15% additional critical chance for Obliterate
                if (lvl >= 68 && spellId == OBLITERATE)
                    aftercrit += 15.f;
                //Vicious Strikes (part 1): 6% additional critical chance for Plague Strike and Scourge Strike
                if (lvl >= 57 && (spellId == PLAGUE_STRIKE/* || spellId == SCOURGE_STRIKE*/))
                    aftercrit += 6.f;

                //Annihilation: 3% additional critical chance for melee special abilities
                if (lvl >= 57)
                    aftercrit += 0.03f;

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half

                //Might of Mograine: 45% crit damage bonus for Blood Boil, Blood Strike, Death Strike and Heart Strike
                if (lvl >= 68 &&
                    (spellId == BLOOD_BOIL || spellId == BLOOD_STRIKE ||
                    spellId == DEATH_STRIKE || spellId == HEART_STRIKE))
                    pctbonus += 0.45f / 2.f;
                //Guile of Gorefiend (part 1 melee): 45% crit damage bonus for Blood Strike, Frost Strike and Obliterate
                if (lvl >= 69 &&
                    (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE ||
                    spellId == OBLITERATE/* || spellId == FROST_STRIKE*/))
                    pctbonus += 0.45f / 2.f;
                //Vicious Strikes (part 2): 30% crit damage bonus for Plague Strike and Scourge Strike
                if (lvl >= 57 && (spellId == PLAGUE_STRIKE/* || spellId == SCOURGE_STRIKE*/))
                    pctbonus += 0.3f / 2.f;
            }

            //Glypg of Plague Strike: 20% bonus damage for Plague Strike
            if (spellId == PLAGUE_STRIKE)
                pctbonus += 0.2f;
            //Glyph of Blood Strike: 20% bonus damage for Blood Strike on snared targets (Heart Strike too for bots)
            //warning unsafe
            if (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE)
                if (damageinfo.target->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_SLOW_ATTACK)))
                    pctbonus += 0.2f;
            //Increased Blood Strike Damage: 90 bonus damage for Blood Strike and Heart Strike
            if (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE)
                fdamage += 90.f;
            //Glyph of Death Strike: 1% bonus damage for every runic power point (max 25) for Death Strike
            if (spellId == DEATH_STRIKE && me->GetPower(POWER_RUNIC_POWER) >= 10)
            {
                //10 to 250 * 0.001 = 10 to 250 / 1000 = 0.01 to 0.25
                pctbonus += float(std::min<uint32>(me->GetPower(POWER_RUNIC_POWER), 250)) * 0.001f;
            }
            //Glyph of Obliterate: 25% bonus damage for Obliterate
            if (spellId == OBLITERATE)
                pctbonus += 0.25f;
            //Bloody Strikes: 15% bonus damage for Blood Strike, 45% for Heart Strike and 30% for Blood Boil
            if (lvl >= 60)
            {
                if (spellId == BLOOD_STRIKE)
                    pctbonus += 0.15f;
                else if (spellId == HEART_STRIKE)
                    pctbonus += 0.45f;
                else if (spellId == BLOOD_BOIL)
                    pctbonus += 0.3f;
            }
            //Improved Death Strike (part 1): 30% bonus damage for Death Strike
            if (spellId == DEATH_STRIKE)
                pctbonus += 0.3f;
            //Merciless Combat (melee): 12% bonus damage for Obliterate on targets with less than 35% hp
            //warning unsafe
            if (lvl >= 67 && spellId == OBLITERATE && damageinfo.target->GetHealthPct() < 35)
                pctbonus += 0.12f;
            //Blood of the North (part 1): 10% bonus damage for Blood Strike and Frost Strike (make Heart strike too)
            if (lvl >= 69 && (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE/* || spellId == FROST_STRIKE*/))
                pctbonus += 0.1f;
            //Tundra Stalker (melee): 40% damage bonus on targets affected with Frost Fever (20% for bot, regardless of caster)
            //warning unsafe
            if (lvl >= 70 && damageinfo.target->HasAura(FROST_FEVER_AURA))
                pctbonus += 0.2f;
            //Outbreak: 30% bonus damage for Plague Strike and 20% for Scourge Strike
            if (lvl >= 59)
            {
                if (spellId == PLAGUE_STRIKE)
                    pctbonus += 0.3f;
                //else if (spellId == SCOURGE_STRIKE)
                //    pctbonus += 0.2f;
            }

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void ApplyClassDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool& crit) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float fdamage = float(damage);
            //1) apply additional crit chance. This additional chance roll will replace original (balance safe)
            if (!crit)
            {
                float aftercrit = 0.f;
                //Rime (part 1 spell): 15% additional critical chance for Icy Touch
                if (lvl >= 68 && spellId == ICY_TOUCH)
                    aftercrit += 15.f;

                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!spell damage is not yet critical and will be multiplied by 1.5
                //so we should put here bonus damage mult /1.5

                //Guile of Gorefiend (part 1 spell): 45% crit damage bonus for Howling Blast
                if (lvl >= 69 && spellId == HOWLING_BLAST)
                    pctbonus += 0.45f / 1.5f;

                //Runic Focus: 50% crit damage bonus for all spells
                pctbonus += 0.5f / 1.5f;
            }

            //Improved Icy Touch: 15% bonus damage for Icy Touch
            if (spellId == ICY_TOUCH)
                pctbonus += 0.15f;
            //Increased Icy Touch Damage (id 54800): 111 bonus damage for Icy Touch
            if (spellId == ICY_TOUCH)
                fdamage += 111.f;
            //Increased Death Coil Damage (id 54807): 80 bonus damage for Death Coil
            if (spellId == DEATH_COIL)
                fdamage += 80.f;
            //Black Ice: 10% bonus damage for all Shadow and Frost spells
            if (lvl >= 58 &&
                ((SPELL_SCHOOL_MASK_FROST & spellInfo->GetSchoolMask()) ||
                (SPELL_SCHOOL_MASK_SHADOW & spellInfo->GetSchoolMask())))
                pctbonus += 0.1f;
            //Glacier Rot: 20% bonus damage for Icy Touch, Howling Blast and Frost Strike
            //warning unsafe
            if (lvl >= 63 && (spellId == ICY_TOUCH || spellId == HOWLING_BLAST/* || spellId == FROST_STRIKE*/) &&
                damageinfo.target->GetDiseasesByCaster(me->GetGUID()) > 0)
                pctbonus += 0.2f;
            //Merciless Combat (spell): 12% bonus damage for Icy Touch, Howling Blast and Frost Strike on targets with less than 35% hp
            //warning unsafe
            if (lvl >= 67 &&
                (spellId == ICY_TOUCH || spellId == HOWLING_BLAST/* || spellId == FROST_STRIKE*/) &&
                damageinfo.target->GetHealthPct() < 35)
                pctbonus += 0.12f;
            //Tundra Stalker (spell): 40% damage bonus on targets affected with Frost Fever (20% for bot, regardless of caster)
            //warning unsafe
            if (lvl >= 70 && damageinfo.target->HasAura(FROST_FEVER_AURA))
                pctbonus += 0.2f;
            //Morbidity: 15% damage bonus for Death Coil
            if (lvl >= 58 && spellId == DEATH_COIL)
                pctbonus += 0.15f;

            //temp
            if (spellId == RUNE_TAP)
                pctbonus += 1.f;

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void ApplyClassDamageMultiplierEffect(SpellInfo const* spellInfo, uint8 effect_index, float& value) const
        {
            uint32 spellId = spellInfo->Id;
            uint8 lvl = me->getLevel();
            float pct_mod = 1.f;

            //Periodic damage bonuses
            if (spellInfo->Effects[effect_index].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE)
            {
                //float ticksnum = float(spellInfo->GetMaxDuration() / spellInfo->Effects[effect_index].Amplitude);

                //Increased Plague Strike DoT Damage (id 54802): increased DoT damage by 100
                if (spellId == BLOOD_PLAGUE_AURA)
                    value += 100.f;
                //Glyph of Icy Touch: 20% bonus damage for Frost Fever
                if (spellId == FROST_FEVER_AURA)
                    pct_mod += 0.2f;
                //Black Ice: 10% bonus damage for all Shadow and Frost spells
                if (lvl >= 58 &&
                    ((SPELL_SCHOOL_MASK_FROST & spellInfo->GetSchoolMask()) ||
                    (SPELL_SCHOOL_MASK_SHADOW & spellInfo->GetSchoolMask())))
                    pct_mod += 0.1f;
                //Glyph of Unholy Blight: 40% damage bonus for Unholy Blight (100% for bot)
                if (spellId == UNHOLY_BLIGHT_AURA)
                    pct_mod += 1.f;
            }
            //Heal bonuses
            if (spellInfo->Effects[effect_index].Effect == SPELL_EFFECT_HEAL)
            {
                //Improved Rune Tap: 100% bonus healing from Rune Tap
                if (spellId == RUNE_TAP)
                    pct_mod += 1.f;
            }

            value *= pct_mod;
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            //Glyph of Horn of Winter: 1 minute bonus duration (3 for bot)
            if (spellId == HORN_OF_WINTER)
            {
                if (Aura* horn = target->GetAura(HORN_OF_WINTER, me->GetGUID()))
                {
                    uint32 dur = horn->GetDuration() + 180000;
                    horn->SetDuration(dur);
                    horn->SetMaxDuration(dur);
                }
            }

            if (target == me)
                return;

            //Epidemic: 10 sec bonus duration for all diseases
            if (spellId == FROST_FEVER_AURA || spellId == BLOOD_PLAGUE_AURA ||
                spellId == CRYPT_FEVER_AURA || spellId == EBON_PLAGUE_AURA)
            {
                if (Aura* fever = target->GetAura(spellId, me->GetGUID()))
                {
                    uint32 dur = fever->GetDuration() + 10000;
                    fever->SetDuration(dur);
                    fever->SetMaxDuration(dur);
                }
            }
            //Sudden Doom: 15% ctc Death Coil on Blood Strike or Heart Strike (up to 30% for bot)
            if (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE)
            {
                if (DEATH_COIL && me->getLevel() >= 65 && irand(1,100) <= (me->getLevel() - 50))
                {
                    //debug: dk bot cannot cast without runic power even triggered spells
                    modpower(40);
                    me->CastSpell(target, DEATH_COIL, true);
                }
            }
            //Rime (part 2): Obliterate has 15% chance to reset Howling Blast cooldown (25% for bot, screw runes part)
            if (spellId == OBLITERATE)
            {
                if (me->getLevel() >= 67 && urand(1,100) <= 25)
                    HowlingBlast_cd = 0;
            }
            //Chillblains Improved: increase duration by 10 sec (disable on players)
            if (spellId == ICY_CLUTCH)
            {
                if (target->GetTypeId() != TYPEID_PLAYER)
                {
                    if (Aura* chill = target->GetAura(ICY_CLUTCH, me->GetGUID()))
                    {
                        uint32 dur = chill->GetDuration() + 10000;
                        chill->SetDuration(dur);
                        chill->SetMaxDuration(dur);
                    }
                }
            }
            //Blood of the North (part 2): Blood Strike and Pestilence convert Blood Rune to Dark Rune (make Heart Strike too)
            if (spellId == BLOOD_STRIKE || spellId == HEART_STRIKE || spellId == PESTILENCE)
            {
                if (me->getLevel() >= 69)
                    ConvertRune(RUNE_BLOOD, 1);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            if (spellId == RUNE_STRIKE_ACIVATION_AURA)
            {
                //Rune Strike activation and timer set
                runestriketimer = 10000;
            }
            if (spellId == ANTI_MAGIC_SHELL)
            {
                //Glyph of Anti-Magic Shell: 2 sec increased duration (5 for bot)
                if (Aura* shell = me->GetAura(ANTI_MAGIC_SHELL))
                {
                    uint32 dur = shell->GetDuration() + 5000;
                    shell->SetDuration(dur);
                    shell->SetMaxDuration(dur);
                }
            }
            if (spellId == VAMPIRIC_BLOOD)
            {
                //Glyph of Vampiric Blood: 5 sec increased duration
                if (Aura* blood = me->GetAura(VAMPIRIC_BLOOD))
                {
                    uint32 dur = blood->GetDuration() + 5000;
                    blood->SetDuration(dur);
                    blood->SetMaxDuration(dur);
                }
            }
            if (spellId == BONE_SHIELD)
            {
                //Glyph of Bone Shield: 1 bonus charge (2 for bot, 7 for tank)
                if (Aura* bone = me->GetAura(BONE_SHIELD))
                {
                    bone->SetCharges(bone->GetCharges() + (master->GetBotTank(me->GetCreatureTemplate()->Entry) == me ? 3 : 1));
                }
            }
            if (spellId == ICY_TALONS_AURA1 || spellId == ICY_TALONS_AURA2 ||
                spellId == ICY_TALONS_AURA3 || spellId == ICY_TALONS_AURA4 || spellId == ICY_TALONS_AURA5)
            {
                //Icy Talons: Synchronize with Epidemic, add 10 sec duration
                if (Aura* talons = me->GetAura(spellId))
                {
                    uint32 dur = talons->GetDuration() + 10000;
                    talons->SetDuration(dur);
                    talons->SetMaxDuration(dur);
                }
            }
            if (spellId == DEATH_STRIKE || spellId == OBLITERATE)
            {
                //Death Rune Mastery: convert Unholy and Frost Runes into Death Runes
                ConvertRune(RUNE_UNHOLY, 1);
                ConvertRune(RUNE_FROST, 1);
            }
            if (spellId == ICEBOUND_FORTITUDE)
            {
                //Guile of Gorefiend (part 2): Icebound Fortitude 6 sec increased duration (18 for bot)
                if (Aura* fort = me->GetAura(ICEBOUND_FORTITUDE))
                {
                    uint32 dur = fort->GetDuration() + 18000;
                    fort->SetDuration(dur);
                    fort->SetMaxDuration(dur);
                }
            }

            OnSpellHit(caster, spell);
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType)
        {
            if (victim == me)
                return;

            if (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE)
            {
                //Blood Presence Heal
                if (me->HasAura(IMPROVED_BLOOD_PRESENCE_AURA))
                {
                    int32 bp0 = int32(damage / 25); //4%
                    me->CastCustomSpell(me, BLOOD_PRESENCE_HEAL_EFFECT, &bp0, NULL, NULL, true);
                }

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
            DeathGrip_cd = 0;
            MindFreeze_cd = 0;
            Strangulate_cd = 0;
            DeathAndDecay_cd = 0;
            IceboundFortitude_cd = 0;
            DarkCommand_cd = 0;
            HornOfWinter_cd = 0;
            RuneStrike_cd = 0;
            AntiMagicShell_cd = 0;
            ArmyOfTheDead_cd = 0;
            RuneTap_cd = 5000;
            BoneShield_cd = 5000;
            EmpowerRuneWeapon_cd = 10000;
            MarkOfBlood_cd = 10000;
            VampiricBlood_cd = 10000;
            Lichborne_cd = 10000;
            HungeringCold_cd = 10000;
            HowlingBlast_cd = 3000;
            Hysteria_cd = 10000;

            presencetimer = 0;
            runicpowertimer = 2000;
            runicpowertimer2 = 5000;
            runestriketimer = 0;
            pestilencetimer = 0;

            //rendTarget = 0;

            Presence = BOT_STANCE_NONE;

            runicpowerIncomeMult = sWorld->getRate(RATE_POWER_RUNICPOWER_INCOME);
            runicpowerLossMult = sWorld->getRate(RATE_POWER_RUNICPOWER_LOSS);
            me->setPowerType(POWER_RUNIC_POWER);
            me->SetMaxPower(POWER_RUNIC_POWER, me->GetCreatePowers(POWER_RUNIC_POWER));

            if (master)
            {
                setStats(CLASS_DEATH_KNIGHT, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_DEATH_KNIGHT);
                InitPowers();
                InitRunes();
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            RuneTimers(diff);
            if (DeathGrip_cd > diff)                DeathGrip_cd -= diff;
            if (MindFreeze_cd > diff)               MindFreeze_cd -= diff;
            if (Strangulate_cd > diff)              Strangulate_cd -= diff;
            if (DeathAndDecay_cd > diff)            DeathAndDecay_cd -= diff;
            if (IceboundFortitude_cd > diff)        IceboundFortitude_cd -= diff;
            if (DarkCommand_cd > diff)              DarkCommand_cd -= diff;
            if (HornOfWinter_cd > diff)             HornOfWinter_cd -= diff;
            if (RuneStrike_cd > diff)               RuneStrike_cd -= diff;
            if (AntiMagicShell_cd > diff)           AntiMagicShell_cd -= diff;
            if (ArmyOfTheDead_cd > diff)            ArmyOfTheDead_cd -= diff;
            if (RuneTap_cd > diff)                  RuneTap_cd -= diff;
            if (BoneShield_cd > diff)               BoneShield_cd -= diff;
            if (EmpowerRuneWeapon_cd > diff)        EmpowerRuneWeapon_cd -= diff;
            if (MarkOfBlood_cd > diff)              MarkOfBlood_cd -= diff;
            if (VampiricBlood_cd > diff)            VampiricBlood_cd -= diff;
            if (Lichborne_cd > diff)                Lichborne_cd -= diff;
            if (HungeringCold_cd > diff)            HungeringCold_cd -= diff;
            if (HowlingBlast_cd > diff)             HowlingBlast_cd -= diff;
            if (Hysteria_cd > diff)                 Hysteria_cd -= diff;

            if (presencetimer > diff)               presencetimer -= diff;
            if (runicpowertimer > diff)             runicpowertimer -= diff;
            if (runicpowertimer2 > diff)            runicpowertimer2 -= diff;

            if (runestriketimer > diff)             runestriketimer -= diff;
            else                                    runestriketimer = 0;
            if (pestilencetimer > diff)             pestilencetimer -= diff;
            else                                    pestilencetimer = 0;
        }

        bool CanRespawn()
        {return false;}

        void InitPowers()
        {
            if (master->getLevel() >= 70)
                RefreshAura(RUNIC_POWER_MASTERY,5);
            else if (master->getLevel() >= 58)
                RefreshAura(RUNIC_POWER_MASTERY,4);
            else
                me->SetMaxPower(POWER_RUNIC_POWER, me->GetCreatePowers(POWER_RUNIC_POWER));

            if (runicpower)
                me->SetPower(POWER_RUNIC_POWER, runicpower);
        }

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            //BLOOD_STRIKE                            = InitSpell(me, BLOOD_STRIKE_1);
            ICY_TOUCH                               = InitSpell(me, ICY_TOUCH_1);
            PLAGUE_STRIKE                           = InitSpell(me, PLAGUE_STRIKE_1);
            DEATH_STRIKE                            = InitSpell(me, DEATH_STRIKE_1);
            OBLITERATE                              = InitSpell(me, OBLITERATE_1);
            RUNE_STRIKE                             = InitSpell(me, RUNE_STRIKE_1);
  /*Talent*/HEART_STRIKE                            = InitSpell(me, HEART_STRIKE_1);

            BLOOD_BOIL                              = InitSpell(me, BLOOD_BOIL_1);
            DEATH_AND_DECAY                         = InitSpell(me, DEATH_AND_DECAY_1);
  /*Talent*/HOWLING_BLAST               = lvl >= 63 ? InitSpell(me, HOWLING_BLAST_1) : 0;

            DEATH_COIL                              = InitSpell(me, DEATH_COIL_1);
            DEATH_GRIP                              = DEATH_GRIP_1;
            PESTILENCE                              = InitSpell(me, PESTILENCE_1);
            MIND_FREEZE                             = InitSpell(me, MIND_FREEZE_1);
            STRANGULATE                             = InitSpell(me, STRANGULATE_1);
            CHAINS_OF_ICE                           = InitSpell(me, CHAINS_OF_ICE_1);
            ICEBOUND_FORTITUDE                      = InitSpell(me, ICEBOUND_FORTITUDE_1);
            DARK_COMMAND                            = InitSpell(me, DARK_COMMAND_1);
            ANTI_MAGIC_SHELL                        = InitSpell(me, ANTI_MAGIC_SHELL_1);
            ARMY_OF_THE_DEAD                        = InitSpell(me, ARMY_OF_THE_DEAD_1);
  /*Talent*/LICHBORNE                               = LICHBORNE_1;
  /*Talent*/HUNGERING_COLD              = lvl >= 60 ? HUNGERING_COLD_1 : 0;

            PATH_OF_FROST                           = InitSpell(me, PATH_OF_FROST_1);
            HORN_OF_WINTER                          = InitSpell(me, HORN_OF_WINTER_1);
  /*Talent*/RUNE_TAP                                = RUNE_TAP_1;
  /*Talent*/BONE_SHIELD                 = lvl >= 58 ? BONE_SHIELD_1 : 0;
            EMPOWER_RUNE_WEAPON                     = InitSpell(me, EMPOWER_RUNE_WEAPON_1);
  /*Talent*/MARK_OF_BLOOD                           = MARK_OF_BLOOD_1;
  /*Talent*/VAMPIRIC_BLOOD                          = VAMPIRIC_BLOOD_1;
  /*Talent*/HYSTERIA                    = lvl >= 59 ? HYSTERIA_1 : 0;

            BLOOD_PRESENCE                          = BLOOD_PRESENCE_1;
            FROST_PRESENCE                          = FROST_PRESENCE_1;
            //UNHOLY_PRESENCE                         = UNHOLY_PRESENCE_1;

            BLOOD_STRIKE                = lvl >= 65 ? HEART_STRIKE : InitSpell(me, BLOOD_STRIKE_1);
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();

            if (level >= 58)
                RefreshAura(GLYPH_OF_CHAINS_OF_ICE);
            if (level >= 80)
                RefreshAura(CHAINS_OF_ICE_FROST_RUNE_REFRESH,4);
            else if (level >= 77)
                RefreshAura(CHAINS_OF_ICE_FROST_RUNE_REFRESH,3);
            else if (level >= 68)
                RefreshAura(CHAINS_OF_ICE_FROST_RUNE_REFRESH,2);
            else if (level >= 58)
                RefreshAura(CHAINS_OF_ICE_FROST_RUNE_REFRESH);
            if (level >= 65)
                RefreshAura(GLYPH_OF_HEART_STRIKE);
            if (level >= 68)
                RefreshAura(GLYPH_OF_RUNE_TAP,2);
            else if (level >= 60)
                RefreshAura(GLYPH_OF_RUNE_TAP);
            if (level >= 63)
                RefreshAura(GLYPH_OF_HOWLING_BLAST);
            if (level >= 57)
                RefreshAura(BUTCHERY);
            if (level >= 58)
                RefreshAura(SCENT_OF_BLOOD);
            if (level >= 59)
                RefreshAura(VENDETTA);
            if (level >= 65)
                RefreshAura(BLOODY_VENGEANCE3);
            else if (level >= 60)
                RefreshAura(BLOODY_VENGEANCE2);
            else if (level >= 57)
                RefreshAura(BLOODY_VENGEANCE1);
            if (level >= 60)
                RefreshAura(ABOMINATIONS_MIGHT);
            if (level >= 67)
                RefreshAura(IMPROVED_BLOOD_PRESENCE);
            if (level >= 65)
                RefreshAura(BLOODWORMS,2);
            //if (level >= 66)
            //    RefreshAura(IMPROVED_DEATH_STRIKE);
            if (level >= 57)
                RefreshAura(TOUGHNESS);
            if (level >= 57)
                RefreshAura(ANNIHILATION);
            if (level >= 60)
                RefreshAura(ICY_TALONS);
            if (level >= 68)
                RefreshAura(CHILL_OF_THE_GRAVE,2);
            else if (level >= 58)
                RefreshAura(CHILL_OF_THE_GRAVE);
            if (level >= 64)
                RefreshAura(IMPROVED_ICY_TALONS);
            if (level >= 68)
                RefreshAura(CHILBLAINS);
            if (level >= 69)
                RefreshAura(ACCLIMATION);
            if (level >= 63)
                RefreshAura(NECROSIS5);
            else if (level >= 62)
                RefreshAura(NECROSIS4);
            else if (level >= 61)
                RefreshAura(NECROSIS3);
            else if (level >= 60)
                RefreshAura(NECROSIS2);
            else if (level >= 59)
                RefreshAura(NECROSIS1);
            if (level >= 65)
                RefreshAura(BLOOD_CAKED_BLADE3);
            else if (level >= 62)
                RefreshAura(BLOOD_CAKED_BLADE2);
            else if (level >= 60)
                RefreshAura(BLOOD_CAKED_BLADE1);
            if (level >= 67)
                RefreshAura(DIRGE,2);
            else if (level >= 61)
                RefreshAura(DIRGE);
            if (level >= 61)
                RefreshAura(UNHOLY_BLIGHT);
            if (level >= 62)
                RefreshAura(DESECRATION);
            if (level >= 64)
                RefreshAura(CRYPT_FEVER);
            if (level >= 68)
                RefreshAura(EBON_PLAGUEBRINGER);
            if (level >= 67)
                RefreshAura(WANDERING_PLAGUE);

            RefreshAura(FROST_FEVER);
            RefreshAura(BLOOD_PLAGUE);
        }

    private:
        uint32
            BLOOD_STRIKE, ICY_TOUCH, PLAGUE_STRIKE, DEATH_STRIKE, OBLITERATE, RUNE_STRIKE, HEART_STRIKE,
            BLOOD_BOIL, DEATH_AND_DECAY, HOWLING_BLAST,
            DEATH_COIL, DEATH_GRIP, PESTILENCE, MIND_FREEZE, STRANGULATE, CHAINS_OF_ICE,
            ICEBOUND_FORTITUDE, DARK_COMMAND, ANTI_MAGIC_SHELL, ARMY_OF_THE_DEAD, LICHBORNE, HUNGERING_COLD,
            PATH_OF_FROST, HORN_OF_WINTER, BONE_SHIELD, RUNE_TAP, EMPOWER_RUNE_WEAPON, MARK_OF_BLOOD, VAMPIRIC_BLOOD, HYSTERIA,
            BLOOD_PRESENCE, FROST_PRESENCE/*, UNHOLY_PRESENCE*/;

        uint32
            DeathGrip_cd, MindFreeze_cd, Strangulate_cd, DeathAndDecay_cd, IceboundFortitude_cd,
            DarkCommand_cd, HornOfWinter_cd, RuneStrike_cd, AntiMagicShell_cd, ArmyOfTheDead_cd,
            RuneTap_cd, BoneShield_cd, EmpowerRuneWeapon_cd, MarkOfBlood_cd, VampiricBlood_cd,
            Lichborne_cd, HungeringCold_cd, HowlingBlast_cd, Hysteria_cd;

/*tmrs*/uint32 presencetimer, runicpowertimer, runicpowertimer2, runestriketimer, pestilencetimer;
///*misc*/uint64 rendTarget;
/*misc*/uint32 runicpower;
/*misc*/float runicpowerIncomeMult, runicpowerLossMult;
/*Chck*/uint8 Presence;

        BotRunes _runes;

        enum DeathKnightBaseSpells
        {
            BLOOD_STRIKE_1                      = 45902,
            ICY_TOUCH_1                         = 45477,
            PLAGUE_STRIKE_1                     = 45462,
            DEATH_STRIKE_1                      = 49998,
            OBLITERATE_1                        = 49020,
            RUNE_STRIKE_1                       = 56815,
            HEART_STRIKE_1                      = 55050,

            BLOOD_BOIL_1                        = 48721,
            DEATH_AND_DECAY_1                   = 43265,
            HOWLING_BLAST_1                     = 49184,

            DEATH_COIL_1                        = 47541,
            DEATH_GRIP_1                        = 49576,
            PESTILENCE_1                        = 50842,
            MIND_FREEZE_1                       = 47528,
            STRANGULATE_1                       = 47476,
            CHAINS_OF_ICE_1                     = 45524,
            ICEBOUND_FORTITUDE_1                = 48792,
            DARK_COMMAND_1                      = 56222,
            ANTI_MAGIC_SHELL_1                  = 48707,
            ARMY_OF_THE_DEAD_1                  = 42650,
            LICHBORNE_1                         = 49039,
            HUNGERING_COLD_1                    = 49203,

            PATH_OF_FROST_1                     = 3714,
            HORN_OF_WINTER_1                    = 57330,
            BONE_SHIELD_1                       = 49222,
            RUNE_TAP_1                          = 48982,
            EMPOWER_RUNE_WEAPON_1               = 47568,
            MARK_OF_BLOOD_1                     = 49005,
            VAMPIRIC_BLOOD_1                    = 55233,
            HYSTERIA_1                          = 49016,

            BLOOD_PRESENCE_1                    = 48266,
            FROST_PRESENCE_1                    = 48263
            //UNHOLY_PRESENCE_1                   = 48265
        };
        enum DeathKnightPassives
        {
        //Talents
            BUTCHERY                            = 49483,//rank 2
            SCENT_OF_BLOOD                      = 49509,//rank 3
            VENDETTA                            = 55136,//rank 3
            BLOODY_VENGEANCE1                   = 48988,
            BLOODY_VENGEANCE2                   = 49503,
            BLOODY_VENGEANCE3                   = 49504,
            ABOMINATIONS_MIGHT                  = 53138,//rank 2
            IMPROVED_BLOOD_PRESENCE             = 50371,//rank 2
            BLOODWORMS                          = 49543,//rank 3
            IMPROVED_DEATH_STRIKE               = 62908,//rank 2
            TOUGHNESS                           = 49789,//rank 5
            ANNIHILATION                        = 51473,//rank 3
            ICY_TALONS                          = 50887,//rank 5
            CHILL_OF_THE_GRAVE                  = 50115,//rank 2
            IMPROVED_ICY_TALONS                 = 55610,
            CHILBLAINS                          = 50043,//rank 3
            ACCLIMATION                         = 50152,//rank 3
            NECROSIS1                           = 51459,
            NECROSIS2                           = 51462,
            NECROSIS3                           = 51463,
            NECROSIS4                           = 51464,
            NECROSIS5                           = 51465,
            BLOOD_CAKED_BLADE1                  = 49219,
            BLOOD_CAKED_BLADE2                  = 49227,
            BLOOD_CAKED_BLADE3                  = 49228,
            DIRGE                               = 51206,//rank 2
            UNHOLY_BLIGHT                       = 49194,
            DESECRATION                         = 55667,//rank 2
            CRYPT_FEVER                         = 49632,//rank 3
            EBON_PLAGUEBRINGER                  = 51161,//rank 3
            WANDERING_PLAGUE                    = 49655,//rank 3
        //Special
  /*Talent*/RUNIC_POWER_MASTERY                 = 50147,//rank 2
            FROST_FEVER                         = 59921,
            BLOOD_PLAGUE                        = 59879,
        //Other
            GLYPH_OF_CHAINS_OF_ICE              = 58620,//damage proc
            CHAINS_OF_ICE_FROST_RUNE_REFRESH    = 62459,//5 runic power gain
            GLYPH_OF_HEART_STRIKE               = 58616,//snare 50% for 10 sec
            GLYPH_OF_RUNE_TAP                   = 59327,//10% heal for party
            GLYPH_OF_HOWLING_BLAST              = 63335 //frost fever on targets
        };
        enum DeathKnightSpecial
        {
            FROST_FEVER_AURA                    = 55095,
            BLOOD_PLAGUE_AURA                   = 55078,
            CRYPT_FEVER_AURA                    = 50510,//rank 3
            EBON_PLAGUE_AURA                    = 51735,//rank 3

            RUNE_STRIKE_ACIVATION_AURA          = 56817,

            IMPROVED_BLOOD_PRESENCE_AURA        = 63611,
            BLOOD_PRESENCE_HEAL_EFFECT          = 50475,
            BLADE_BARRIER_AURA                  = 64859,//rank 5
            UNHOLY_BLIGHT_AURA                  = 50536,

            ICY_TALONS_AURA1                    = 50882,//rank 1
            ICY_TALONS_AURA2                    = 58575,//rank 2
            ICY_TALONS_AURA3                    = 58576,//rank 3
            ICY_TALONS_AURA4                    = 58577,//rank 4
            ICY_TALONS_AURA5                    = 58578,//rank 5

            DEATH_COIL_ENEMY                    = 47632,
            ICY_CLUTCH                          = 50436 //rank 3 Chilblains proc
        };
        //enum RunePlacing
        //{
        //    RUNE_BLOOD_FIRST,
        //    RUNE_BLOOD_SECOND,
        //    RUNE_UNHOLY_FIRST,
        //    RUNE_UNHOLY_SECOND,
        //    RUNE_FROST_FIRST,
        //    RUNE_FROST_SECOND,
        //    NO_RUNE
        //};
    };
};

void AddSC_death_knight_bot()
{
    new death_knight_bot();
}
