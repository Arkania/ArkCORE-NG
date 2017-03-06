
delete from quest_poi where questId=12733;
insert into quest_poi values
(12733, 1, 0, 609, 502, 0, 0, 3);

delete from creature_queststarter where id=44217 and quest=26866;
delete from creature_queststarter where id=44217 and quest=26865;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ich danke Euch, $C. Die Geister der geschmolzenen Elementare haben endlich ihre Ruhe gefunden.", RequestItemsText_loc3="Habt Ihr die Bindungen?", CompletedText_loc3="Kehrt zu Bovaal Weißhorn im Flammenschlund zurück." WHERE Id=26862;
UPDATE locales_quest SET OfferRewardText_loc3="Ich habe Eure Ankunft erwartet,  $N." WHERE Id=26865;
UPDATE locales_quest SET OfferRewardText_loc3="Ich habe Eure Ankunft erwartet,  $N." WHERE Id=26866;
UPDATE locales_quest SET OfferRewardText_loc3="Ich habe Eure Ankunft erwartet,  $N." WHERE Id=26867;
UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ihr habt es geschafft, $N! Ihr habt die Invasion der Brennenden Klinge verhindert, bevor sie begann! Nehmt dies als Zeichen meiner Dankbarkeit.", CompletedText_loc3="Kehrt zu Steingardist Kurjack im Flammenschlund zurück." WHERE Id=26856;


update creature_template set AINAme="" where entry in (42698, 48832, 29021, 29024, 29022, 29023, 46209, 46210, 46211, 48936);
update creature_template set AINAme="SmartAI" where entry in (23574, 23576, 23577, 23578, 44600);

delete from spell_linked_spell where spell_trigger=62158 and spell_effect=58586; -- (62158, 58586, 0, "Runeforging Credit")

update creature_template set AIName="", ScriptName="boss_oggleflint" where entry=11517;
update creature_template set AIName="", ScriptName="boss_jergosh_the_invoker" where entry=11518;
update creature_template set AIName="", ScriptName="boss_bazzalan" where entry=11519;
update creature_template set AIName="", ScriptName="boss_taragaman_the_hungerer" where entry=11520;

delete from quest_poi where questId=26856;
insert into quest_poi values
(26856, 0, 0, 389, 680, 1, 0, 7),
(26856, 1, 1, 389, 680, 1, 0, 7),
(26856, 2, 2, 389, 680, 1, 0, 7);

delete from quest_poi_points where questId=26856;
insert into quest_poi_points values
(26856, 0, 0, -369, 203),
(26856, 1, 0, -387, 140),
(26856, 2, 0, -277, -61);

UPDATE creature_template SET npcflag=0 WHERE entry=11520;


