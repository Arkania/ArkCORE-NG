
-- fix arkcore issue #14

-- http://www.wowhead.com/quest=25617/into-the-maw
delete from creature_queststarter where id=40834 and quest=25617;

-- both ghost are spawned from spell
delete from creature where id in (39622, 39627);
-- both ghost are freandly to both
update creature_template set faction=35 where entry in (39622, 39627);
-- remove questtaker as queststarter
delete from creature_queststarter where id=39432 and quest in (25279, 25612);
delete from creature_questender where id=39432 and quest=25272;
insert into creature_questender values
(39432, 25272);
delete from creature_questender where id=39433 and quest=25273;
insert into creature_questender values
(39433, 25273);

UPDATE quest_template SET PrevQuestId=25353, NextQuestId=25575, ExclusiveGroup=-25618 WHERE Id=25618;
UPDATE quest_template SET PrevQuestId=25353, NextQuestId=25575, ExclusiveGroup=-25618 WHERE Id=25623;
UPDATE quest_template SET PrevQuestId=25353, NextQuestId=25575, ExclusiveGroup=-25617 WHERE Id=25617;
UPDATE quest_template SET PrevQuestId=25355, NextQuestId=25575, ExclusiveGroup=-25617 WHERE Id=25624;

UPDATE quest_template SET PrevQuestId=25278 WHERE Id=25353;
UPDATE quest_template SET PrevQuestId=25277 WHERE Id=25355;

update gameobject_loot_template set ChanceOrQuestChance=100 where entry=202731;

UPDATE quest_template SET Flags=0, SpecialFlags=0, RequiredSourceItemId1=52853, RequiredSourceItemCount1=1, RequiredItemId1=52834, RequiredItemCount1=1 WHERE Id=25353;
UPDATE quest_template SET Flags=0, SpecialFlags=0, RequiredSourceItemId1=52854, RequiredSourceItemCount1=1, RequiredItemId1=52834, RequiredItemCount1=1 WHERE Id=25355;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Benutzt das Totem von Goldrinn, um den Geist von Goldrinn zu beschwören und mit ihm zu sprechen." WHERE Id=25353;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Benutzt das Totem von Lo'Gosh, um den Geist von Lo'Gosh zu beschwören und mit ihm zu sprechen." WHERE Id=25355;

UPDATE quest_template SET PrevQuestId=25233 WHERE Id=25269;
UPDATE quest_template SET PrevQuestId=25269 WHERE Id=25270;
UPDATE quest_template SET PrevQuestId=25270 WHERE Id=25272;
UPDATE quest_template SET PrevQuestId=25272, NextQuestId=25297  WHERE Id=25279;

UPDATE quest_template SET PrevQuestId=25233 WHERE Id=25268;
UPDATE quest_template SET PrevQuestId=25268 WHERE Id=25271;
UPDATE quest_template SET PrevQuestId=25271 WHERE Id=25273;
UPDATE quest_template SET PrevQuestId=25273, NextQuestId=25297 WHERE Id=25279;

UPDATE quest_template SET PrevQuestId=25297 WHERE Id=25298;
























