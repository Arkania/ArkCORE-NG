/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2018 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "script_helper.h"

// npc 40079
class npc_feralas_wisp_40079 : public CreatureScript
{
public:
    npc_feralas_wisp_40079() : CreatureScript("npc_feralas_wisp_40079") { }

    enum eWisp
    {
        SPELL_WISP_DETONATE = 6237,

    };

    struct npc_feralas_wisp_40079AI : public ScriptedAI
    {
        npc_feralas_wisp_40079AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        bool      _isFollowing;
        uint64    _playerGUID;

        void Initialize()
        {
        }

        void Reset() override
        {
            _isFollowing = false;
            _playerGUID = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (spell->Id == 74738 && !_isFollowing)
                {
                    _isFollowing = true;
                    _playerGUID = player->GetGUID();
                    me->setActive(true); // the npc hold the sector alive.. no player must be near..
                    player->KilledMonsterCredit(40079);

                    me->GetMotionMaster()->MoveFollow(player, frand(8.0f, 12.0f), frand(2.14f, 4.14f) + 3.14f);

                    _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID);
                    if (!player)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (player->GetQuestStatus(25407) == QUEST_STATUS_REWARDED)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (player->GetQuestStatus(25407) == QUEST_STATUS_NONE)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else if (me->GetDistance2d(player) > 100.0f)
                        me->CastSpell(me, SPELL_WISP_DETONATE, true);
                    else
                        _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                }
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_feralas_wisp_40079AI(creature);
    }
};

void AddSC_zone_feralas()
{
    new npc_feralas_wisp_40079();

}
