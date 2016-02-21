
-- all member of carawan is mounted and quest invisible 5
delete from creature_addon where guid in (103421, 103563, 104029);
insert into creature_addon values
(104029, 0, 37212, 65536, 1, 0, 80797),
(103563, 0, 37492, 65536, 1, 0, 80797),
(103421, 0, 37496, 65536, 1, 0, 80797);

-- cleanup scripts in zone tanaris.. 
update creature_template set AIName="", ScriptName="npc_aquementas_9453" where entry=9453;
update creature_template set AIName="", ScriptName="npc_custodian_of_time_19950" where entry=19950;
update creature_template set AIName="", ScriptName="npc_steward_of_time_20142" where entry=20142;
update creature_template set AIName="", ScriptName="npc_OOX17_7784" where entry=7784;
update creature_template set AIName="", ScriptName="npc_tooga_5955" where entry=5955;
update creature_template set AIName="", ScriptName="npc_uldum_caravan_harness_46516" where entry=46516;
update creature_template set AIName="", ScriptName="npc_adarrah_44833" where entry=44833;
update creature_template set AIName="", ScriptName="" where entry=46517;

delete from vehicle_template_accessory where entry=46516;
insert into vehicle_template_accessory values
(46516, 46525, 0, 0, "Turgore", 8, 0),
(46516, 46528, 5, 0, "Tanzar", 8, 0),
(46516, 46529, 2, 0, "Kurzel", 8, 0),
(46516, 46514, 3, 0, "Domesticated Kodo", 8, 0),
(46516, 46530, 4, 0, "Harkor", 8, 0);

delete from npc_spellclick_spells where npc_entry in (46514, 46525, 46528, 46529, 46530);
insert into npc_spellclick_spells values
(46514, 46598, 0, 0),
(46516, 46598, 0, 0),
(46525, 46598, 0, 0),
(46528, 46598, 0, 0),
(46529, 46598, 0, 0),
(46530, 46598, 0, 0);

-- spawned by script
delete from creature where guid in (103801, 104508, 104732, 104745, 104952, 105171);
delete from creature_addon where guid in (103801, 104508, 104732, 104745, 104952, 105171);

UPDATE locales_quest SET OfferRewardText_loc3="Jenseits dieses Tals warten Wunder nur darauf entdeckt zu werden! Sie werden uns gehören!" WHERE Id=28558;

UPDATE locales_quest SET CompletedText_loc3="Sprecht mit Adarrah in der verlorenen Stadt der Tol'vir" WHERE Id=27003;

UPDATE quest_template SET Flags=786432, RequiredNpcOrGo1=44833, RequiredNpcOrGoCount1=1 WHERE Id=27003;

UPDATE creature_template SET npcflag=0 WHERE entry=46517;
delete from npc_spellclick_spells where npc_entry=46517 and spell_id=86942;

delete from creature_text where entry=46533 and groupid in (0, 1);

delete from creature_text where entry=46520 and groupid in (0);

delete from creature_text where entry=47326 and groupid in (0, 1, 2);
insert into creature_text values
(47326, 0, 0, "Attack!", 12, 0, 100, 0, 0, 0, "", 46761),
(47326, 1, 0, "How many coconuts we can get for the ugly one?", 12, 0, 100, 0, 0, 0, "", 46774),
(47326, 2, 0, "TREEE? he woulda paid five, easy... dummy!", 12, 0, 100, 0, 0, 0, "", 46839);

delete from creature_text where entry=48030 and groupid in (0, 1, 2);
insert into creature_text values
(48030, 0, 0, "Please don't break... please don't break....", 12, 0, 100, 0, 0, 0, "", 48271),
(48030, 1, 0, "Crap!  That was my last lock pick!", 12, 0, 100, 0, 0, 0, "", 48272),
(48030, 2, 0, "Here comes the guard, $N!  Take him out!", 12, 0, 100, 0, 0, 0, "", 48273);

delete from creature_text where entry=48078 and groupid in (0, 1);
insert into creature_text values
(48078, 0, 0, "You're the last of your tribe with any sense left.  As a reward for giving us Prince Nadun, I grant you the gift that is your birthright and more!", 12, 0, 100, 0, 0, 0, "", 47610),
(48078, 1, 0, "Your makers failed you... your flawed race succumbed to the curse of flesh!  Lord Deathwing's gift makes you perfect again!", 12, 0, 100, 0, 0, 0, "", 47611);

delete from creature_text where entry=47567 and groupid in (0);
insert into creature_text values
(47567, 0, 0, "How did you get here?  I will destroy you!", 12, 0, 100, 0, 0, 0, "", 47829);

delete from creature_text where entry=48267 and groupid in (0, 1, 2, 3, 4);
insert into creature_text values
(48267, 0, 0, "You won't make it far!", 12, 0, 100, 0, 0, 0, "", 48102),
(48267, 1, 0, "I will spill your blood in Deathwing's name!", 12, 0, 100, 0, 0, 0, "", 48103),
(48267, 2, 0, "If slavery does not suit you, maybe death will!", 12, 0, 100, 0, 0, 0, "", 48104),
(48267, 3, 0, "I will show you the weakness of flesh!", 12, 0, 100, 0, 0, 0, "", 48105),
(48267, 4, 0, "You're going to wish you'd never set foot in Uldum!", 12, 0, 100, 0, 0, 0, "", 48106);

delete from creature_text where entry=47306 and groupid in (0, 1, 2, 3, 4);
insert into creature_text values
(47306, 0, 0, "You won't make it far!", 12, 0, 100, 0, 0, 0, "", 48102),
(47306, 1, 0, "I will spill your blood in Deathwing's name!", 12, 0, 100, 0, 0, 0, "", 48103),
(47306, 2, 0, "If slavery does not suit you, maybe death will!", 12, 0, 100, 0, 0, 0, "", 48104),
(47306, 3, 0, "I will show you the weakness of flesh!", 12, 0, 100, 0, 0, 0, "", 48105),
(47306, 4, 0, "You're going to wish you'd never set foot in Uldum!", 12, 0, 100, 0, 0, 0, "", 48106);




