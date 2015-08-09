/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_descent.h"

enum Says
{
    SAY_INTRO_NORMAL = 0,
    SAY_INTRO_HEROIC = 1
};

// 49427 npc_nefarian_helper_heroic
class npc_nefarian_helper_heroic : public CreatureScript
{
public:
    npc_nefarian_helper_heroic() : CreatureScript("npc_nefarian_helper_heroic") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nefarian_helper_heroicAI (creature);
    }

    struct npc_nefarian_helper_heroicAI : public ScriptedAI
    {
        npc_nefarian_helper_heroicAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    };
};

// 49580
class npc_nefarian_yeller : public CreatureScript // 49580
{
public:
    npc_nefarian_yeller() : CreatureScript("npc_nefarian_yeller") { }

    struct npc_nefarian_yellerAI : public ScriptedAI
    {
        npc_nefarian_yellerAI(Creature* creature) : ScriptedAI(creature)
        {
            timer = 1000;
            introSaid = false;
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            creature->SetDisplayId(11686);
        }

        uint32 timer;
        bool introSaid;

        void UpdateAI(uint32 diff) 
        {
            if (timer <= diff)
            {
                if (Player* target = me->FindNearestPlayer(20.0f, true))
                {
                    if (target->GetDistance(me) <= 20.0f && !introSaid)
                    {
                        if(!me->GetMap()->IsHeroic())
                            Talk(SAY_INTRO_NORMAL);
                        else
                            Talk(SAY_INTRO_HEROIC);

                        introSaid = true;

                        me->DespawnOrUnsummon(15000);
                    } else
                        timer = 1000;
                }
                else
                    timer = 1000;

            } else timer -= diff;
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nefarian_yellerAI(creature);
    }
};

void AddSC_blackwing_descent()
{
    new npc_nefarian_helper_heroic();
    new npc_nefarian_yeller();
}
