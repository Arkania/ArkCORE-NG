#include "bot_ai.h"
#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "Totem.h"
/*
Shaman NpcBot (reworked by Graff onlysuffering@gmail.com)
Complete - around 30%
TODO:
*/
enum TotemSlot
{
    T_FIRE  = 0,//m_SummonSlot[1]
    T_EARTH = 1,//m_SummonSlot[2]
    T_WATER = 2,//m_SummonSlot[3]
    T_AIR   = 3,//m_SummonSlot[4]
    MAX_TOTEMS
};
struct TotemParam
{
    TotemParam() : effradius(0.f) {}
    Position pos;
    float effradius;
};
typedef std::pair<uint64 /*guid*/, TotemParam /*param*/> BotTotem;
class shaman_bot : public CreatureScript
{
public:
    shaman_bot() : CreatureScript("shaman_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new shaman_botAI(creature);
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

    struct shaman_botAI : public bot_minion_ai
    {
        shaman_botAI(Creature* creature) : bot_minion_ai(creature)
        {
            Reset();
        }

        bool doCast(Unit* victim, uint32 spellId, bool triggered = false)
        {
            if (checkBotCast(victim, spellId, CLASS_SHAMAN) != SPELL_CAST_OK)
                return false;

            bool maelstrom = false;
            if (!triggered)
                maelstrom = (MaelstromCount >= 5 &&
                (spellId == LIGHTNING_BOLT || spellId == CHAIN_LIGHTNING ||
                spellId == HEALING_WAVE || spellId == LESSER_HEALING_WAVE ||
                spellId == CHAIN_HEAL || spellId == HEX));

            triggered |= maelstrom;

            bool result = bot_ai::doCast(victim, spellId, triggered, me->GetGUID());

            if (result && maelstrom)
            {
                MaelstromCount = 0;
                me->RemoveAurasDueToSpell(MAELSTROM_WEAPON_BUFF, 0, 0, AURA_REMOVE_BY_EXPIRE);
            }

            return result;
        }

        void StartAttack(Unit* u, bool force = false)
        {
            if (GetBotCommandState() == COMMAND_ATTACK && !force) return;
            Aggro(u);
            GetInPosition(force, !isTwoHander());
            SetBotCommandState(COMMAND_ATTACK);
        }

        void EnterCombat(Unit*) { }
        void Aggro(Unit*) { }
        void AttackStart(Unit*) { }
        void KilledUnit(Unit*) { }
        void EnterEvadeMode() { }
        void MoveInLineOfSight(Unit*) { }
        void JustDied(Unit*) { master->SetNpcBotDied(me->GetGUID()); }

        bool Shielded(Unit* target) const
        {
            return
                (HasAuraName(target, WATER_SHIELD_1) ||
                HasAuraName(target, EARTH_SHIELD_1) ||
                HasAuraName(target, LIGHTNING_SHIELD_1));
        }

        void CheckBloodlust(uint32 diff)
        {
            if (!BLOODLUST || Bloodlust_Timer > diff || me->GetDistance(master) > 18 || IsCasting() || Rand() > 15)
                return;
            if (!me->IsInCombat() || !master->IsInCombat())
                return;
            if (HasAuraName(master, BLOODLUST))
            {
                Bloodlust_Timer += 3000;
                return;
            }

            if (Unit* u = me->GetVictim())
            {
                Creature* cre = u->ToCreature();
                if (u->GetMaxHealth() > me->GetHealth() * 2 ||
                    (cre && (cre->IsDungeonBoss() || cre->isWorldBoss())) ||
                    me->getAttackers().size() + master->getAttackers().size() > 5)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, BLOODLUST))
                    {
                        GC_Timer = temptimer;
                        Bloodlust_Timer = 180000; //3 min
                        return;
                    }
                }
            }

            Bloodlust_Timer = 2000; //fail
        }

        void CheckTotems(uint32 diff)
        {
            //update rate
            if (Rand() > 25)
                return;
            //Unsummon
            for (uint8 i = 0; i != MAX_TOTEMS; ++i)
            {
                if (_totems[i].first != 0)
                {
                    if (master->GetDistance2d(_totems[i].second.pos.m_positionX, _totems[i].second.pos.m_positionY) > _totems[i].second.effradius &&
                        me->GetDistance2d(_totems[i].second.pos.m_positionX, _totems[i].second.pos.m_positionY) > _totems[i].second.effradius)
                    {
                        Unit* to = sObjectAccessor->FindUnit(_totems[i].first);
                        if (!to)
                        {
                            _totems[i].first = 0;
                            //TC_LOG_ERROR("entities.player", "%s has lost totem in slot %u! Despawned normally?", me->GetName().c_str(), i);
                            continue;
                        }

                        to->ToTotem()->UnSummon();
                    }
                }
            }
            if (GC_Timer > diff || IsCasting() || me->GetDistance(master) > 15 || Feasting())
                return;
            //Summon
            //TODO: role-based totems (attack/heal)
            if (me->IsInCombat())
            {
                if (WINDFURY_TOTEM && !_totems[T_AIR].first && !master->m_SummonSlot[T_AIR+1])
                {
                    temptimer = GC_Timer;
                    if (doCast(me, WINDFURY_TOTEM))
                    {
                        if (me->getLevel() >= 57)
                            GC_Timer = temptimer;
                        return;
                    }
                }

                if (!_totems[T_EARTH].first && !master->m_SummonSlot[T_EARTH+1])
                {
                    if (STRENGTH_OF_EARTH_TOTEM)
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, STRENGTH_OF_EARTH_TOTEM))
                        {
                            if (me->getLevel() >= 57)
                                GC_Timer = temptimer;
                            return;
                        }
                    }
                    else if (STONESKIN_TOTEM)
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, STONESKIN_TOTEM))
                        {
                            if (me->getLevel() >= 57)
                                GC_Timer = temptimer;
                            return;
                        }
                    }
                }

                if (!_totems[T_FIRE].first && !master->m_SummonSlot[T_FIRE+1])
                {
                    if (TOTEM_OF_WRATH && Totem_of_Wrath_Timer <= diff)
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, TOTEM_OF_WRATH))
                        {
                            //bot's poor AI cannot use totems wisely so just reduce CD on this
                            Totem_of_Wrath_Timer = 30000; //30 sec, old 5 min
                            if (me->getLevel() >= 57)
                                GC_Timer = temptimer;
                            return;
                        }
                    }
                    else if (SEARING_TOTEM && Searing_Totem_Timer <= diff)
                    {
                        if (Unit* u = me->GetVictim())
                        {
                            if (me->GetExactDist(u) < (u->isMoving() ? 10 : 25))
                            {
                                temptimer = GC_Timer;
                                if (doCast(me, SEARING_TOTEM))
                                {
                                    Searing_Totem_Timer = 20000;
                                    if (me->getLevel() >= 57)
                                        GC_Timer = temptimer;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            if (!me->isMoving() && !master->isMoving())
            {
                if (!_totems[T_WATER].first && !master->m_SummonSlot[T_WATER+1])
                {
                    uint8 manapct = GetManaPCT(master);
                    uint8 hppct = GetHealthPCT(master);
                    if (HEALINGSTREAM_TOTEM && hppct < 98 && master->getPowerType() != POWER_MANA &&
                        (hppct < 25 || manapct > hppct))
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, HEALINGSTREAM_TOTEM))
                        {
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                    else if (MANASPRING_TOTEM && (manapct < 97 || GetManaPCT(me) < 90))
                    {
                        temptimer = GC_Timer;
                        if (doCast(me, MANASPRING_TOTEM))
                        {
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
            }
        }

        void CheckThunderStorm(uint32 diff)
        {
            if (!THUNDERSTORM || Thunderstorm_Timer > diff || IsCasting() || Rand() > 25)
                return;

            //case 1: low mana
            if (GetManaPCT(me) < 15)
            {
                temptimer = GC_Timer;
                if (doCast(me, THUNDERSTORM))
                {
                    GC_Timer = temptimer;
                    Thunderstorm_Timer = 25000; //45 - 20 = 25 sec for mana restore
                }
                return;
            }

            //case 2: knock attackers
            if (tank == me) //pretty stupid idea I think
                return;

            //AttackerSet m_attackers = master->getAttackers();
            AttackerSet b_attackers = me->getAttackers();
            if (b_attackers.empty())
                return;

            uint8 tCount = 0;
            for (AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
            {
                if (!(*iter)) continue;
                if (me->GetExactDist((*iter)) > 9) continue;
                if (CCed(*iter)) continue;
                if (me->IsValidAttackTarget(*iter))
                {
                    ++tCount;
                    break;
                }
            }

            if (tCount > 0)
            {
                temptimer = GC_Timer;
                if (doCast(me, THUNDERSTORM))
                {
                    GC_Timer = temptimer;
                    Thunderstorm_Timer = 40000; //45 - 5 = 40 sec for knock
                }
                return;
            }
        }

        void CheckManaTide(uint32 diff)
        {
            if (!MANA_TIDE_TOTEM || Mana_Tide_Totem_Timer > diff || IsCasting() || Rand() > 20)
                return;

            Group* group = master->GetGroup();
            if (!group)
                return;

            uint8 LMPcount = 0;
            uint8 members = group->GetMembersCount();
            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* tPlayer = itr->GetSource();
                if (!tPlayer || !tPlayer->IsInWorld() || tPlayer->GetMapId() != me->GetMapId() ||
                    (!tPlayer->IsAlive() && !tPlayer->HaveBot())) continue;
                if (me->GetExactDist(tPlayer) > 20) continue;
                if (tPlayer->getPowerType() != POWER_MANA) continue;
                if (GetManaPCT(tPlayer) < 35)
                {
                    ++LMPcount;
                    if (LMPcount > 3 || LMPcount > members / 3) break;
                }
                if (tPlayer->HaveBot())
                {
                    for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
                    {
                        Creature* bot = tPlayer->GetBotMap(i)->_Cre();
                        if (bot && bot->IsInWorld() && bot->getPowerType() == POWER_MANA &&
                            bot->GetExactDist(me) < 20 && GetManaPCT(bot) < 35)
                        {
                            ++LMPcount;
                            if (LMPcount > 3 || LMPcount > members / 3) break;
                        }
                    }
                }
            }

            if (LMPcount > 3 || LMPcount > members / 3)
            {
                if (_totems[T_WATER].first != 0)
                {
                    Unit* to = sObjectAccessor->FindUnit(_totems[T_WATER].first);
                    if (!to)
                        _totems[T_WATER].first = 0;
                    else
                        to->ToTotem()->UnSummon();
                }
                if (doCast(me, MANA_TIDE_TOTEM))
                {
                    Mana_Tide_Totem_Timer = 60000; //1 min
                    return;
                }
            }

            Mana_Tide_Totem_Timer = 3000; //fail
        }

        void UpdateAI(uint32 diff)
        {
            ReduceCD(diff);
            if (IAmDead()) return;
            if (me->GetVictim())
            {
                if (isTwoHander())
                    DoMeleeAttackIfReady();
            }
            else
                Evade();
            CheckAuras();
            if (wait == 0)
                wait = GetWait();
            else
                return;
            CheckThunderStorm(diff);
            BreakCC(diff);
            if (CCed(me)) return;

            CheckHexy(diff);
            CheckEarthy(diff);

            if (GetManaPCT(me) < 30 && Potion_cd <= diff)
            {
                temptimer = GC_Timer;
                if (doCast(me, MANAPOTION))
                {
                    Potion_cd = POTION_CD;
                    GC_Timer = temptimer;
                }
            }

            CheckBloodlust(diff);
            BuffAndHealGroup(master, diff);
            CureGroup(master, CURE_TOXINS, diff);
            CheckManaTide(diff);
            CheckTotems(diff);

            if (master->IsInCombat() || me->IsInCombat())
                CheckDispel(diff);

            if (!me->IsInCombat())
                DoNonCombatActions(diff);
            //buff myself
            if (LIGHTNING_SHIELD && tank != me && !Shielded(me))
            {
                temptimer = GC_Timer;
                if (doCast(me, LIGHTNING_SHIELD))
                    GC_Timer = temptimer;
            }
            //heal myself
            if (GetHealthPCT(me) < 80)
                HealTarget(me, GetHealthPCT(me), diff);

            if (!CheckAttackTarget(CLASS_SHAMAN))
                return;

            CheckHexy2(diff);

            //Counter(diff);
            DoNormalAttack(diff);
        }

        void Counter(uint32 diff)
        {
            if (!WIND_SHEAR || Wind_Shear_Timer > diff || Rand() > 60)
                return;

            Unit* u = me->GetVictim();
            if (u && u->IsNonMeleeSpellCast(false))
            {
                temptimer = GC_Timer;
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                if (doCast(u, WIND_SHEAR))
                {
                    Wind_Shear_Timer = 5000; //improved
                    GC_Timer = temptimer;
                }
            }
            else if (Unit* target = FindCastingTarget(25))
            {
                temptimer = GC_Timer;
                if (me->IsNonMeleeSpellCast(false))
                    me->InterruptNonMeleeSpells(false);
                if (doCast(target, WIND_SHEAR))
                {
                    Wind_Shear_Timer = 5000;
                    GC_Timer = temptimer;
                }
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

            //AttackerSet m_attackers = master->getAttackers();
            //AttackerSet b_attackers = me->getAttackers();
            float dist = me->GetExactDist(opponent);
            float meleedist = me->GetDistance(opponent);

            if (MoveBehind(*opponent))
                wait = 5;

            if (IsCasting()) return;

            //STORMSTRIKE
            if (STORMSTRIKE && isTwoHander() && Stormstrike_Timer <= diff && GC_Timer <= diff &&
                meleedist <= 5 && Rand() < 70)
            {
                if (doCast(opponent, STORMSTRIKE))
                {
                    Stormstrike_Timer = 6000; //improved
                    return;
                }
            }
            //SHOCKS
            if ((FLAME_SHOCK || EARTH_SHOCK || FROST_SHOCK) && Shock_Timer <= diff && GC_Timer <= diff &&
                dist < 25 && Rand() < 30)
            {
                temptimer = GC_Timer;

                bool canFlameShock = (FLAME_SHOCK != 0);
                if (canFlameShock)
                {
                    if (Aura* fsh = opponent->GetAura(FLAME_SHOCK, me->GetGUID()))
                        if (fsh->GetDuration() > 3000)
                            canFlameShock = false;
                }

                if (canFlameShock)
                {
                    if (doCast(opponent, FLAME_SHOCK))
                    {
                        Shock_Timer = 3000; //improved twice
                        GC_Timer = temptimer;
                        return;
                    }
                }
                else if (EARTH_SHOCK || FROST_SHOCK)
                {
                    uint32 SHOCK = !FROST_SHOCK ? EARTH_SHOCK : RAND(EARTH_SHOCK, FROST_SHOCK);
                    if (SHOCK && !opponent->HasAuraWithMechanic((1<<MECHANIC_SNARE)|(1<<MECHANIC_ROOT)) &&
                        !opponent->HasAura(SHOCK))
                    {
                        if (doCast(opponent, SHOCK))
                        {
                            Shock_Timer = 3000; //improved twice
                            GC_Timer = temptimer;
                            return;
                        }
                    }
                }
            }
            //LAVA BURST
            if (LAVA_BURST && Lava_Burst_Timer <= diff && GC_Timer <= diff && dist < 30 && Rand() < 50)
            {
                if (doCast(opponent, LAVA_BURST))
                {
                    Lava_Burst_Timer = 8000;
                    return;
                }
            }

            if (GetManaPCT(me) < 15 || (isTwoHander() && MaelstromCount < 5))
                return;

            //CHAIN LIGHTNING
            if (CHAIN_LIGHTNING && Chain_Lightning_Timer <= diff && GC_Timer <= diff && dist < 30 && Rand() < 80)
            {
                if (doCast(opponent, CHAIN_LIGHTNING))
                {
                    Chain_Lightning_Timer = 3500; //improved
                    return;
                }
            }
            //LIGHTNING BOLT
            if (LIGHTNING_BOLT && Lightning_Bolt_Timer <= diff && GC_Timer <= diff && dist < 20)
            {
                if (doCast(opponent, LIGHTNING_BOLT))
                {
                    Lightning_Bolt_Timer = uint32(float(sSpellMgr->GetSpellInfo(LIGHTNING_BOLT)->CalcCastTime()/100) * me->GetFloatValue(UNIT_MOD_CAST_SPEED) + 200);
                    return;
                }
            }
        }

        void CheckHexy(uint32 diff)
        {
            if (HexyCheckTimer <= diff && HEX)
            {
                Hexy = FindAffectedTarget(HEX, me->GetGUID());
                HexyCheckTimer = 2000;
            }
        }

        void CheckHexy2(uint32 diff)
        {
            if (HEX && Hexy == false && Hex_Timer < diff && me->GetVictim())
            {
                if (Unit* target = FindPolyTarget(20, me->GetVictim()))
                {
                    if (doCast(target, HEX))
                    {
                        Hexy = true;
                        Hex_Timer = 30000; //45 - 15 = 30 sec for bots
                        HexyCheckTimer += 2000;
                    }
                }
            }
        }

        void CheckEarthy(uint32 diff)
        {
            if (EarthyCheckTimer <= diff && EARTH_SHIELD)
            {
                Unit* u = FindAffectedTarget(EARTH_SHIELD, me->GetGUID(), 90.f, 2);
                Earthy = (u && (u == tank || u == master));
                EarthyCheckTimer = 1000;
            }
        }

        void DoNonCombatActions(uint32 diff)
        {
            if (GC_Timer > diff || Rand() > 50 || me->IsMounted()) return;

            RezGroup(ANCESTRAL_SPIRIT, master);

            if (Feasting()) return;

            if (Shielded(me) && Rand() < 25)
            {
                Aura* shield = NULL;
                uint32 SHIELD = LIGHTNING_SHIELD;
                if (SHIELD)
                    shield = me->GetAura(SHIELD);
                if (!shield && EARTH_SHIELD && tank == me)
                {
                    SHIELD = EARTH_SHIELD;
                    shield = me->GetAura(SHIELD);
                }
                if (!shield && WATER_SHIELD)
                {
                    SHIELD = WATER_SHIELD;
                    shield = me->GetAura(SHIELD);
                }
                if (shield && shield->GetCharges() < 5)
                {
                    temptimer = GC_Timer;
                    if (doCast(me, SHIELD))
                    {
                        GC_Timer = temptimer;
                        return;
                    }
                }
            }
        }

        bool BuffTarget(Unit* target, uint32 diff)
        {
            if (!WATER_WALKING && !WATER_BREATHING && !EARTH_SHIELD)
                return false;

            if (GC_Timer > diff || !target || !target->IsAlive() || Rand() > 40) return false;
            
            if (EARTH_SHIELD && Earthy == false && ((!tank && target == master) || target == tank) &&
                (target->IsInCombat() || !target->isMoving()) &&
                me->GetExactDist(target) < 40 && Rand() < 75)
            {
                bool cast = !Shielded(target);
                if (!cast)
                    if (Aura* eShield = target->GetAura(EARTH_SHIELD))
                        if (eShield->GetCharges() < 5)
                            cast = true;
                if (cast && doCast(target, EARTH_SHIELD))
                {
                    Earthy = true;
                    //GC_Timer = 800;
                    return true;
                }
            }

            if (me->GetExactDist(target) > 30) return false;
            if (me->IsInCombat() && !master->GetMap()->IsRaid()) return false;

            if (target->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
            {
                //bots don't need water breathing
                if (WATER_BREATHING && target->GetTypeId() == TYPEID_PLAYER &&
                    !target->HasAuraType(SPELL_AURA_WATER_BREATHING) &&
                    doCast(target, WATER_BREATHING))
                {
                    //GC_Timer = 800;
                    return true;
                }
                //water walking breaks on any damage
                if (WATER_WALKING && target->getAttackers().empty() &&
                    !target->HasAuraType(SPELL_AURA_WATER_WALK) &&
                    doCast(target, WATER_WALKING))
                {
                    //GC_Timer = 800;
                    return true;
                }
            }
            return false;
        }

        void CheckDispel(uint32 diff)
        {
            if (!PURGE || CheckDispelTimer > diff || Rand() > 35 || IsCasting())
                return;
            Unit* target = FindHostileDispelTarget();
            if (target && doCast(target, PURGE))
            {
                CheckDispelTimer = 3000;
                GC_Timer = 500;
            }
            CheckDispelTimer = 1000;
        }

        bool HealTarget(Unit* target, uint8 hp, uint32 diff)
        {
            if (hp > 97)
                return false;
            if (!target || !target->IsAlive() || me->GetExactDist(target) > 40)
                return false;
            if (Rand() > 50 + 20*target->IsInCombat() + 50*master->GetMap()->IsRaid())
                return false;

            //PLACEHOLDER: Instant spell req. interrupt current spell

            if (IsCasting()) return false;

            if (LESSER_HEALING_WAVE && ((hp > 70 && hp < 85) || hp < 50 || GetLostHP(target) > 1800) && GC_Timer <= diff &&
                Rand() < 75)
            {
                if (doCast(target, LESSER_HEALING_WAVE))
                    return true;
            }
            if (HEALING_WAVE && hp > 40 && (hp < 75 || GetLostHP(target) > 4000) && GC_Timer <= diff &&
                Rand() < 65)
            {
                if (doCast(target, HEALING_WAVE))
                    return true;
            }
            if (CHAIN_HEAL && ((hp > 40 && hp < 90) || GetLostHP(target) > 1300) && GC_Timer <= diff &&
                Rand() < 120)
            {
                if (RIPTIDE && Riptide_Timer <= diff && (hp < 85 || GetLostHP(target) > 2500) &&
                    !target->HasAura(RIPTIDE))
                {
                    temptimer = GC_Timer;
                    if (doCast(target, RIPTIDE, true))
                    {
                        Riptide_Timer = 5000;
                        if (doCast(target, CHAIN_HEAL))
                        {
                            GC_Timer = temptimer;
                            return true;
                        }
                    }
                }
                else if (doCast(target, CHAIN_HEAL))
                    return true;
            }
            
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
                ////Incite: 15% additional critical chance for Cleave, Heroic Strike and Thunder Clap
                //if (lvl >= 15 && spellId == CLEAVE /*|| spellId == HEROICSTRIKE || spellId == THUNDERCLAP*/)
                //    aftercrit += 15.f;

                //second roll (may be illogical)
                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!Melee spell damage is not yet critical, all reduced by half
                //Elemental Fury (part 2): 50% additional crit damage bonus for Nature, Fire and Frost (all) spells
                if (lvl >= 21)
                    pctbonus += 0.25f;
            }

            //SHAMAN_T8_ENCHANCEMENT_2P_BONUS: 20% bonus damage for Lava Lash and Stormstrike
            if (lvl >= 60 &&
                (spellId == STORMSTRIKE_DAMAGE || spellId == STORMSTRIKE_DAMAGE_OFFHAND/* || spellId == LAVA_LASH*/))
                pctbonus += 0.2f;

            //custom bonus to make stormstrike useful
            if (spellId == STORMSTRIKE_DAMAGE || spellId == STORMSTRIKE_DAMAGE_OFFHAND)
                pctbonus += 1.0f;

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
                //Call of Thunder: 5% additional critical chance for Lightning Bolt, Chain Lightning and Thunderstorm,
                if (lvl >= 30 &&
                    (spellId == LIGHTNING_BOLT ||
                    spellId == CHAIN_LIGHTNING ||
                    spellId == THUNDERSTORM))
                    aftercrit += 5.f;
                //Tidal Mastery (part 2): 5% additional critical chance for lightning spells
                if (lvl >= 25 && (SPELL_SCHOOL_MASK_NATURE & spellInfo->GetSchoolMask()))
                    aftercrit += 5.f;

                if (aftercrit > 0.f)
                    crit = roll_chance_f(aftercrit);
            }

            //2) apply bonus damage mods
            float pctbonus = 0.0f;
            if (crit)
            {
                //!!!spell damage is not yet critical and will be multiplied by 1.5
                //so we should put here bonus damage mult /1.5
                //Elemental Fury (part 2): 50% additional crit damage bonus for Nature, Fire and Frost (all) spells
                if (lvl >= 21)
                    pctbonus += 0.333f;
                //Lava Flows (part 1): 24% additional crit damage bonus for Lava Burst
                if (lvl >= 50 && spellId == LAVA_BURST)
                    pctbonus += 0.16f;
            }
            //Concussion: 5% bonus damage for Lightning Bolt, Chain Lightning, Thunderstorm, Lava Burst and Shocks
            if (lvl >= 10 &&
                (spellId == LIGHTNING_BOLT ||
                spellId == CHAIN_LIGHTNING ||
                spellId == THUNDERSTORM ||
                spellId == LAVA_BURST ||
                spellId == EARTH_SHOCK ||
                spellId == FROST_SHOCK ||
                spellId == FLAME_SHOCK))
                pctbonus += 0.05f;
            //Call of Flame (part 2): 6% bonus damage for Lava burst
            if (lvl >= 15 && spellId == LAVA_BURST)
                pctbonus += 0.06f;
            //Storm, Earth and fire (part 3): 60% bonus damage for Flame Shock (periodic damage in fact but who cares?)
            if (lvl >= 40 && spellId == FLAME_SHOCK)
                pctbonus += 0.6f;
            //Booming Echoes (part 2): 20% bonus damage for Flame Shock and Frost Shock (direct damage)
            if (lvl >= 45 &&
                (spellId == FLAME_SHOCK ||
                spellId == FROST_SHOCK))
                pctbonus += 0.2f;

            //flat damage mods (temp)
            ////Shamanism: 25% bonus damage from bonus damage effects for Lightning Bolt, Chain Lightning and Lava Burst
            //if (lvl >= 55 &&
            //    (spellId == LIGHTNING_BOLT ||
            //    spellId == CHAIN_LIGHTNING ||
            //    spellId == LAVA_BURST))
            //    fdamage += float(m_spellpower / 4);

            damage = int32(fdamage * (1.0f + pctbonus));
        }

        void OnBotDespawn(Creature* summon)
        {
            if (!summon)
            {
                UnsummonAll();
                return;
            }

            TempSummon* totem = summon->ToTempSummon();
            if (!totem || !totem->ToTotem())
            {
                TC_LOG_ERROR("entities.player", "SummonedCreatureDespawn(): Shaman bot %s has despawned summon %s which is not a temp summon or not a totem...", me->GetName().c_str(), summon->GetName().c_str());
                return;
            }

            int8 slot = -1;
            switch (totem->m_Properties->Id)
            {
                case SUMMON_TYPE_TOTEM_FIRE:
                    slot = T_FIRE;
                    break;
                case SUMMON_TYPE_TOTEM_EARTH:
                    slot = T_EARTH;
                    break;
                case SUMMON_TYPE_TOTEM_WATER:
                    slot = T_WATER;
                    break;
                case SUMMON_TYPE_TOTEM_AIR:
                    slot = T_AIR;
                    break;
                default:
                    TC_LOG_ERROR("entities.player", "SummonedCreatureDespawn(): Shaman bot %s has despawned totem %s with unknown type %u", me->GetName().c_str(), summon->GetName().c_str(), totem->m_Properties->Id);
                    return;
            }

            _totems[slot].first = 0;
        }

        void OnBotSummon(Creature* summon)
        {
            TempSummon* totem = summon->ToTempSummon();
            if (!totem || !totem->ToTotem())
            {
                TC_LOG_ERROR("entities.player", "OnBotSummon(): Shaman bot %s has summoned creature %s which is not a temp summon or not a totem...", me->GetName().c_str(), summon->GetName().c_str());
                return;
            }

            totem->SetCreatorGUID(me->GetGUID());

            int8 slot = -1;
            switch (totem->m_Properties->Id)
            {
                case SUMMON_TYPE_TOTEM_FIRE:
                    slot = T_FIRE;
                    break;
                case SUMMON_TYPE_TOTEM_EARTH:
                    slot = T_EARTH;
                    break;
                case SUMMON_TYPE_TOTEM_WATER:
                    slot = T_WATER;
                    break;
                case SUMMON_TYPE_TOTEM_AIR:
                    slot = T_AIR;
                    break;
                default:
                    TC_LOG_ERROR("entities.player", "OnBotSummon(): Shaman bot %s has summoned totem %s with unknown type %u", me->GetName().c_str(), summon->GetName().c_str(), totem->m_Properties->Id);
                    return;
            }

            float radius = 0.f;
            if (SpellInfo const* info = sSpellMgr->GetSpellInfo(summon->m_spells[0]))
                if (SpellRadiusEntry const* entry = info->Effects[0].RadiusEntry)
                    radius = entry->RadiusMax;

            _totems[slot].first = summon->GetGUID();
            _totems[slot].second.pos.Relocate(*summon);
            _totems[slot].second.effradius = std::max<float>(radius, 20.f) + 5.f;

            //TC_LOG_ERROR("entities.player", "shaman bot: summoned %s (type %u) at x='%f', y='%f', z='%f'",
            //    summon->GetName().c_str(), slot, _totems[slot].second.GetPositionX(), _totems[slot].second.GetPositionY(), _totems[slot].second.GetPositionZ());

            summon->SetDisplayId(me->GetModelForTotem(PlayerTotemType(totem->m_Properties->Id)));
            master->m_SummonSlot[++slot] = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;

            //Maelstrom Weapon improved: 10% to gain full stack and 30% to add an extra stack
            if (spellId == MAELSTROM_WEAPON_BUFF)
            {
                if (Aura* mwb = me->GetAura(MAELSTROM_WEAPON_BUFF))
                {
                    uint32 stacks = mwb->GetStackAmount();
                    if (stacks < 5)
                    {
                        if (urand(1,100) <= 10)
                            mwb->ModStackAmount(5);
                        if (urand(1,100) <= 30)
                            mwb->ModStackAmount(1);
                    }

                    MaelstromCount = mwb->GetStackAmount();
                }

                MaelstromTimer = 30000; //30 sec duration then reset
            }

            OnSpellHit(caster, spell);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            uint32 spellId = spell->Id;
            //Shields improvement, replaces Static Shock (part 2) and Improved Earth Shield (part 1)
            if (spellId == LIGHTNING_SHIELD || spellId == EARTH_SHIELD/* || spellId == WATER_SHIELD*/)
            {
                if (Aura* shield = target->GetAura(spellId, me->GetGUID()))
                {
                    shield->SetCharges(shield->GetCharges() + 12);
                }
            }
            //Lightning Overload: 20% cast SAME spell with no mana! make sure this does not proc on itself!
   /*else */if (me->getLevel() >= 40 && (spellId == LIGHTNING_BOLT || spellId == CHAIN_LIGHTNING))
            {
                bool cast = (urand(1,100) <= 20);
                if (spellId == LIGHTNING_BOLT)
                {
                    if (LOvBolt == false)
                    {
                        if (cast)
                        {
                            LOvBolt = true;
                            me->CastSpell(target, LIGHTNING_BOLT, true);
                        }
                    }
                    else
                        LOvBolt = false;
                }
                if (spellId == CHAIN_LIGHTNING)
                {
                    if (LOvChain == false)
                    {
                        if (cast)
                        {
                            LOvChain = true;
                            me->CastSpell(target, CHAIN_LIGHTNING, true);
                        }
                    }
                    else
                        LOvChain = false;
                }
            }
   /*else */if (spellId == STORMSTRIKE)
            {
                //Windfury: 10% chance
                if (WindfuryTimer == 0 && me->getLevel() >= 30)
                {
                    if (urand(0,100) < 10)
                        WindfuryTimer = 1000;

                    if (WindfuryTimer > 0)
                        me->CastSpell(target, WINDFURY_PROC, true);
                }
            }
        }

        void DamageDealt(Unit* victim, uint32& /*damage*/, DamageEffectType damageType)
        {
            if (victim == me)
                return;

            if (damageType == DIRECT_DAMAGE)
            {
                //Windfury: 10% chance
                if (WindfuryTimer == 0 && me->getLevel() >= 30)
                {
                    if (urand(0,100) < 10)
                        WindfuryTimer = 1000;

                    if (WindfuryTimer > 0)
                        me->CastSpell(victim, WINDFURY_PROC, true);
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

        void UnsummonAll()
        {
            for (uint8 i = 0; i != MAX_TOTEMS; ++i)
            {
                if (_totems[i].first != 0)
                {
                    Unit* to = sObjectAccessor->FindUnit(_totems[i].first);
                    if (!to)
                    {
                        //TC_LOG_ERROR("entities.player", "%s has no totem in slot %u during remove!", me->GetName().c_str(), i);
                        continue;
                    }
                    to->ToTotem()->UnSummon();
                }
            }
        }

        void Reset()
        {
            Riptide_Timer = 0;
            Shock_Timer = 0;
            Lightning_Bolt_Timer = 0;
            Searing_Totem_Timer = 0;
            Totem_of_Wrath_Timer = 0;
            CheckDispelTimer = 0;
            Wind_Shear_Timer = 0;
            Chain_Lightning_Timer = 0;
            Lava_Burst_Timer = 0;
            Thunderstorm_Timer = 0;
            Hex_Timer = 0;
            Bloodlust_Timer = 10000;
            Stormstrike_Timer = 0;
            Mana_Tide_Totem_Timer = 10000;

            HexyCheckTimer = 3000;
            EarthyCheckTimer = 2000;
            MaelstromTimer = 0;
            WindfuryTimer = 0;

            MaelstromCount = 0;

            Hexy = false;
            Earthy = false;
            LOvBolt = false;
            LOvChain = false;

            if (master)
            {
                setStats(CLASS_SHAMAN, me->getRace(), master->getLevel(), true);
                ApplyClassPassives();
                ApplyPassives(CLASS_SHAMAN);
            }
        }

        void ReduceCD(uint32 diff)
        {
            CommonTimers(diff);
            if (Riptide_Timer > diff)           Riptide_Timer -= diff;
            if (Shock_Timer > diff)             Shock_Timer -= diff;
            if (Lightning_Bolt_Timer > diff)    Lightning_Bolt_Timer -= diff;
            if (Searing_Totem_Timer > diff)     Searing_Totem_Timer -= diff;
            if (Totem_of_Wrath_Timer > diff)    Totem_of_Wrath_Timer -= diff;
            if (CheckDispelTimer > diff)        CheckDispelTimer -= diff;
            if (Wind_Shear_Timer > diff)        Wind_Shear_Timer -= diff;
            if (Chain_Lightning_Timer > diff)   Chain_Lightning_Timer -= diff;
            if (Lava_Burst_Timer > diff)        Lava_Burst_Timer -= diff;
            if (Thunderstorm_Timer > diff)      Thunderstorm_Timer -= diff;
            if (Hex_Timer > diff)               Hex_Timer -= diff;
            if (Bloodlust_Timer > diff)         Bloodlust_Timer -= diff;
            if (Stormstrike_Timer > diff)       Stormstrike_Timer -= diff;
            if (Mana_Tide_Totem_Timer > diff)   Mana_Tide_Totem_Timer -= diff;

            if (HexyCheckTimer > diff)          HexyCheckTimer -= diff;
            if (EarthyCheckTimer > diff)        EarthyCheckTimer -= diff;

            if (MaelstromTimer > diff)          MaelstromTimer -= diff;
            else if (MaelstromCount > 0)        MaelstromCount = 0;

            if (WindfuryTimer > diff)           WindfuryTimer -= diff;
            else                                WindfuryTimer = 0;
        }

        bool CanRespawn()
        {return false;}

        void InitSpells()
        {
            uint8 lvl = me->getLevel();
            HEALING_WAVE                            = InitSpell(me, HEALING_WAVE_1);
            CHAIN_HEAL                              = InitSpell(me, CHAIN_HEAL_1);
            LESSER_HEALING_WAVE                     = InitSpell(me, LESSER_HEALING_WAVE_1);
  /*Talent*/RIPTIDE                     = lvl >= 60 ? InitSpell(me, RIPTIDE_1) : 0;
            ANCESTRAL_SPIRIT                        = InitSpell(me, ANCESTRAL_SPIRIT_1);
            CURE_TOXINS                 = lvl <= 38 ? InitSpell(me, CURE_TOXINS_1) : CLEANSE_SPIRIT_1;
            FLAME_SHOCK                             = InitSpell(me, FLAME_SHOCK_1);
            EARTH_SHOCK                             = InitSpell(me, EARTH_SHOCK_1);
            FROST_SHOCK                             = InitSpell(me, FROST_SHOCK_1);
            STORMSTRIKE                 = lvl >= 40 ? STORMSTRIKE_1 : 0;
            LIGHTNING_BOLT                          = InitSpell(me, LIGHTNING_BOLT_1);
            CHAIN_LIGHTNING                         = InitSpell(me, CHAIN_LIGHTNING_1);
            LAVA_BURST                              = InitSpell(me, LAVA_BURST_1);
  /*Talent*/THUNDERSTORM                = lvl >= 60 ? InitSpell(me, THUNDERSTORM_1) : 0;
            LIGHTNING_SHIELD                        = InitSpell(me, LIGHTNING_SHIELD_1);
  /*Talent*/EARTH_SHIELD                = lvl >= 50 ? InitSpell(me, EARTH_SHIELD_1) : 0;
     /*NYI*/WATER_SHIELD                            = InitSpell(me, WATER_SHIELD_1);
            WATER_BREATHING                         = InitSpell(me, WATER_BREATHING_1);
            WATER_WALKING                           = InitSpell(me, WATER_WALKING_1);
  /*CUSTOM*/BLOODLUST                   = lvl >= 60 ? BLOODLUST_1 : 0;
            PURGE                                   = InitSpell(me, PURGE_1);
            WIND_SHEAR                              = InitSpell(me, WIND_SHEAR_1);
            HEX                                     = InitSpell(me, HEX_1);
   /*Quest*/STONESKIN_TOTEM             = lvl >= 10 ? InitSpell(me, STONESKIN_TOTEM_1) : 0;
            HEALINGSTREAM_TOTEM                     = InitSpell(me, HEALINGSTREAM_TOTEM_1);
            MANASPRING_TOTEM                        = InitSpell(me, MANASPRING_TOTEM_1);
   /*Quest*/SEARING_TOTEM               = lvl >= 10 ? InitSpell(me, SEARING_TOTEM_1) : 0;
            WINDFURY_TOTEM                          = InitSpell(me, WINDFURY_TOTEM_1);
            STRENGTH_OF_EARTH_TOTEM                 = InitSpell(me, STRENGTH_OF_EARTH_TOTEM_1);
  /*Talent*/TOTEM_OF_WRATH              = lvl >= 50 ? InitSpell(me, TOTEM_OF_WRATH_1) : 0;
  /*Talent*/MANA_TIDE_TOTEM             = lvl >= 40 ? MANA_TIDE_TOTEM_1 : 0;
        }

        void ApplyClassPassives()
        {
            uint8 level = master->getLevel();
            if (level >= 58)
                RefreshAura(ELEMENTAL_WARDING,2); //12%
            else if (level >= 15)
                RefreshAura(ELEMENTAL_WARDING); //6%
            if (level >= 18)
                RefreshAura(ELEMENTAL_DEVASTATION3); //9%
            else if (level >= 15)
                RefreshAura(ELEMENTAL_DEVASTATION2); //6%
            else if (level >= 12)
                RefreshAura(ELEMENTAL_DEVASTATION1); //3%
            if (level >= 30)
                RefreshAura(ANCESTRAL_KNOWLEDGE,3); //30%
            else if (level >= 20)
                RefreshAura(ANCESTRAL_KNOWLEDGE,2); //20%
            else if (level >= 10)
                RefreshAura(ANCESTRAL_KNOWLEDGE); //10%
            if (level >= 25)
                RefreshAura(TOUGHNESS); //10%, 30%
            if (level >= 29)
                RefreshAura(FLURRY5); //30%
            else if (level >= 28)
                RefreshAura(FLURRY4); //24%
            else if (level >= 27)
                RefreshAura(FLURRY3); //18%
            else if (level >= 26)
                RefreshAura(FLURRY2); //12%
            else if (level >= 25)
                RefreshAura(FLURRY1); //6%
            if (level >= 50)
                RefreshAura(WEAPON_MASTERY,3); //30%
            else if (level >= 40)
                RefreshAura(WEAPON_MASTERY,2); //20%
            else if (level >= 30)
                RefreshAura(WEAPON_MASTERY); //10%
            if (level >= 45)
                RefreshAura(STATIC_SHOCK,2); //12%
            else if (level >= 41)
                RefreshAura(STATIC_SHOCK); //6%
            if (level >= 20)
                RefreshAura(ANCESTRAL_HEALING); //10%
            if (level >= 50)
                RefreshAura(ANCESTRAL_AWAKENING); //30%

            if (level >= 70)
                RefreshAura(SHAMAN_T10_RESTO_4P); //25%


            //spec-based (race-based)
            if (level >= 40)
            {
                if (isTwoHander())
                {
                    if (level >= 70)
                        RefreshAura(MAELSTROM_WEAPON5,2);
                    else if (level >= 60)
                        RefreshAura(MAELSTROM_WEAPON5);
                    else if (level >= 55)
                        RefreshAura(MAELSTROM_WEAPON4);
                    else if (level >= 50)
                        RefreshAura(MAELSTROM_WEAPON3);
                    else if (level >= 45)
                        RefreshAura(MAELSTROM_WEAPON2);
                    else// if (level >= 40)
                        RefreshAura(MAELSTROM_WEAPON1);

                    RefreshAura(UNLEASHED_RAGE);
                    RefreshAura(IMPROVED_STORMSTRIKE); //20%
                }
                else
                    RefreshAura(ELEMENTAL_OATH);
            }

            EARTHLIVING_WEAPON =
                level >= 70 ? EARTHLIVING_WEAPON_PASSIVE_6 :
                level >= 50 ? EARTHLIVING_WEAPON_PASSIVE_5 :
                level >= 30 ? EARTHLIVING_WEAPON_PASSIVE_4 : 0;
            if (EARTHLIVING_WEAPON)
            {
                me->RemoveAurasDueToSpell(EARTHLIVING_WEAPON_PASSIVE_4);
                me->RemoveAurasDueToSpell(EARTHLIVING_WEAPON_PASSIVE_5);
                me->RemoveAurasDueToSpell(EARTHLIVING_WEAPON_PASSIVE_6);
                RefreshAura(EARTHLIVING_WEAPON, 3);
            }
        }

    private:
        BotTotem _totems[MAX_TOTEMS];
        uint32
            HEALING_WAVE, CHAIN_HEAL, LESSER_HEALING_WAVE, RIPTIDE, ANCESTRAL_SPIRIT, CURE_TOXINS,
            FLAME_SHOCK, EARTH_SHOCK, FROST_SHOCK, STORMSTRIKE, LIGHTNING_BOLT, CHAIN_LIGHTNING, LAVA_BURST, THUNDERSTORM,
            LIGHTNING_SHIELD, EARTH_SHIELD, WATER_SHIELD, WATER_BREATHING, WATER_WALKING, BLOODLUST,
            PURGE, WIND_SHEAR, HEX,
            STONESKIN_TOTEM, HEALINGSTREAM_TOTEM, MANASPRING_TOTEM, WINDFURY_TOTEM, STRENGTH_OF_EARTH_TOTEM,
            SEARING_TOTEM, TOTEM_OF_WRATH, MANA_TIDE_TOTEM;
        uint32
            EARTHLIVING_WEAPON;
        //Timers
        uint32 Riptide_Timer, Shock_Timer, Lightning_Bolt_Timer, Searing_Totem_Timer, Totem_of_Wrath_Timer,
            CheckDispelTimer, Wind_Shear_Timer, Chain_Lightning_Timer, Lava_Burst_Timer, Thunderstorm_Timer,
            Hex_Timer, Bloodlust_Timer, Stormstrike_Timer, Mana_Tide_Totem_Timer;
        uint32 HexyCheckTimer, EarthyCheckTimer, MaelstromTimer, WindfuryTimer;
        uint8 MaelstromCount;
        bool Hexy, Earthy, LOvChain, LOvBolt;

        enum ShamanBaseSpells
        {
            HEALING_WAVE_1                      = 331,
            CHAIN_HEAL_1                        = 1064,
            LESSER_HEALING_WAVE_1               = 8004,
            RIPTIDE_1                           = 61295,
            ANCESTRAL_SPIRIT_1                  = 2008,
            CURE_TOXINS_1                       = 526,
            CLEANSE_SPIRIT_1                    = 51886,
            FLAME_SHOCK_1                       = 8050,
            EARTH_SHOCK_1                       = 8042,
            FROST_SHOCK_1                       = 8056,
            STORMSTRIKE_1                       = 17364,
            LIGHTNING_BOLT_1                    = 403,
            CHAIN_LIGHTNING_1                   = 421,
            LAVA_BURST_1                        = 51505,
            THUNDERSTORM_1                      = 51490,
            LIGHTNING_SHIELD_1                  = 324,
            EARTH_SHIELD_1                      = 974,
            WATER_SHIELD_1                      = 52127,
            WATER_BREATHING_1                   = 131,
            WATER_WALKING_1                     = 546,
            //BLOODLUST_1                         = 54516,//custom, moved to specials
            PURGE_1                             = 370,
            WIND_SHEAR_1                        = 57994,
            HEX_1                               = 51514,
            STONESKIN_TOTEM_1                   = 8071,
            HEALINGSTREAM_TOTEM_1               = 5394,
            MANASPRING_TOTEM_1                  = 5675,
            SEARING_TOTEM_1                     = 3599,
            WINDFURY_TOTEM_1                    = 8512,
            STRENGTH_OF_EARTH_TOTEM_1           = 8075,
            TOTEM_OF_WRATH_1                    = 30706,
            MANA_TIDE_TOTEM_1                   = 16190
        };

        enum ShamanPassives
        {
            //Elemental
            ELEMENTAL_DEVASTATION1              = 30160,
            ELEMENTAL_DEVASTATION2              = 29179,
            ELEMENTAL_DEVASTATION3              = 29180,
            ELEMENTAL_WARDING                   = 28998,//rank 3
            ELEMENTAL_OATH                      = 51470,//rank 2
            //Enchancement
            ANCESTRAL_KNOWLEDGE                 = 17489,//rank 5
            TOUGHNESS                           = 16309,//rank 5
            FLURRY1                             = 16256,
            FLURRY2                             = 16281,
            FLURRY3                             = 16282,
            FLURRY4                             = 16283,
            FLURRY5                             = 16284,
            WEAPON_MASTERY                      = 29086,//rank 3
            UNLEASHED_RAGE                      = 30809,//rank 3
            STATIC_SHOCK                        = 51527,//rank 3
            IMPROVED_STORMSTRIKE                = 51522,//rank 2
            MAELSTROM_WEAPON1                   = 51528,
            MAELSTROM_WEAPON2                   = 51529,
            MAELSTROM_WEAPON3                   = 51530,
            MAELSTROM_WEAPON4                   = 51531,
            MAELSTROM_WEAPON5                   = 51532,
            //Restoration
            ANCESTRAL_HEALING                   = 16240,//rank 3
            ANCESTRAL_AWAKENING                 = 51558,//rank 3
            //Special
            SHAMAN_T10_RESTO_4P                 = 70808 //Chain Heal HoT
        };

        enum ShamanSpecial
        {
            //2 extra white attacks
            //100 yd
            //"Increases attack power for 1.50 sec"
            //Warning! can proc even from itself!
            WINDFURY_PROC                       = 32910,
            //"Increases melee,ranged and spell casting speed by 35%
            //for all party members. Lasts 20 sec."
            //250 mana, 20 yd
            //affects raid
            //no penalty
            BLOODLUST_1                         = 54516,
            //20% chance to put HoT on healed target over 12 sec
            EARTHLIVING_WEAPON_PASSIVE_4        = 52005,//348 base hp
            EARTHLIVING_WEAPON_PASSIVE_5        = 52007,//456 base hp
            EARTHLIVING_WEAPON_PASSIVE_6        = 52008,//652 base hp

            MAELSTROM_WEAPON_BUFF               = 53817,
            STORMSTRIKE_DAMAGE                  = 32175,
            STORMSTRIKE_DAMAGE_OFFHAND          = 32176
        };
    };
};


void AddSC_shaman_bot()
{
    new shaman_bot();
}
