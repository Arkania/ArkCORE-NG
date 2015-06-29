
update waypoint_data set delay=70000 where id=237642 and point in (8,12);
update waypoint_data set delay=20000 where id=237642 and point in (1,4);

-- razuvious 28357
update creature_template set AIName="", ScriptName="npc_instructor_razuvious" where entry=28357;

update creature set position_x=2511.08, position_y=-5591.19, position_z=420.644, orientation=0.2752 where guid=237725;

-- Acherus Ghoul 28405 spawned by script
delete from creature where guid in (237815, 237816, 237817);
update creature_template set AIName="", ScriptName="npc_acherus_ghoul" where entry=28405;

-- Death Knight Initiate 
delete from creature_text where entry in (28390, 52458, 52459, 52462, 52463, 52464, 52465, 52466, 52468, 52469, 52470, 52471, 52472, 52473, 52474, 52475, 52479, 52480, 52481, 52482, 52483, 52484, 52485, 52486, 52487);
SET @ID=28390;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52458;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52459;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52462;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52463;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52464;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52465;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52466;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52468;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52469;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52470;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52471;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52472;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52473;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52474;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52475;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52479;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52480;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52481;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52482;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52483;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52484;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52485;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52486;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

SET @ID=52487;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(@ID,0,0,"Where am I? What is this place?",12,27856),
(@ID,0,1,"I... I have awoken to a nightmare?",12,27857),
(@ID,0,2,"Who... who are you? Who... what am I?",12,27858),
(@ID,0,3,"I hurt... suffering unbearable... end my pain... I beg of you!",12,27859),
(@ID,1,0,"Dark energy courses through me... Such power! I hunger for more!",12,27877),
(@ID,1,1,"Reborn, I shall become an instrument of doom...",12,27878),
(@ID,1,2,"The voice... such splendor... Arthas... My king....",12,27879),
(@ID,1,3,"I return from the grave to do my master's bidding.",12,27880),
(@ID,2,0,"I live only to serve the Lich King!",12,27886),
(@ID,2,1,"Victory to the Scourge!",12,27887),
(@ID,2,2,"Death to all that oppose us!",12,27888);

-- razuvious 28357
delete from creature_text where entry=28357;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(28357,0,0,"Another failure...",12,27861),
(28357,0,1,"Useless...",12,27862),
(28357,0,2,"I smell its fear...",12,27863),
(28357,0,3,"Pathetic...",12,27865),
(28357,1,0,"This one has awoken too soon. It retains emotion and memory...",12,27864),
(28357,1,1,"You have been measured and found wanting...",12,27866),
(28357,2,0,"Dispose of it...",12,27867),
(28357,3,0,"Marvel at its tenacity and vigor! A champion has been found!",12,27868),
(28357,3,1,"The Lich King will be pleased with this initiate.",12,27869),
(28357,3,2,"Amidst the wretch, a champion has been found.",12,27870),
(28357,3,3,"CHAOS! DOOM! DESTRUCTION! This one will claim them all!",12,27871),
(28357,3,4,"A harbinger of death is reborn...",12,27872),
(28357,4,0,"Place upon it the trappings befitting a herald of Arthas.",12,27873),
(28357,5,0,"This one...",12,27876),
(28357,6,0,"Listen, death knight... Listen for the voice of your master. He calls to you now.",12,27884),
(28357,7,0,"Stand and be measured! Rise, for your master awaits your arrival. Go now!",12,27883);

-- Acherus Necromancer 28383
update creature_template set AIName="", ScriptName="npc_acherus_necromancer" where entry=28383;
delete from creature_text where entry=28383;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values
(28383,0,0,"Yes, instructor.",12,27874),
(28383,1,0,"Rise, minions. Rise and feast upon the weak!",12,27875),
(28383,2,0,"Right away, instructor.",12,27881),
(28383,3,0,"As you command, instructor!",12,27885);

delete from waypoint_data where id=5247300;
insert into waypoint_data values
(5247300, 1,2504.293701, -5599.702637, 420.643433, 4.940517, 0, 1, 0, 100, 0),
(5247300, 2,2496.158203, -5620.272461, 420.643433, 4.335763, 0, 1, 0, 100, 0),
(5247300, 3,2486.224365, -5630.530762, 420.643433, 3.943065, 0, 1, 0, 100, 0),
(5247300, 4,2470.358887, -5637.403320, 420.643433, 3.550366, 0, 1, 0, 100, 0),
(5247300, 5,2452.144775, -5637.410156, 420.643433, 3.141958, 0, 1, 0, 100, 0),
(5247300, 6,2417.267334, -5624.152832, 420.645264, 2.772821, 0, 1, 0, 100, 0),
(5247300, 7,2399.461426, -5627.919922, 420.661560, 3.350089, 0, 1, 0, 100, 0),
(5247300, 8,2381.503662, -5635.283691, 420.836182, 3.530731, 0, 1, 0, 100, 0),
(5247300, 9,2371.681152, -5645.917480, 426.128540, 3.966627, 0, 1, 0, 100, 0),
(5247300, 10,2347.123535, -5675.513184, 426.028717, 4.084436, 0, 1, 0, 100, 0);


-- spell ID - 51516 Totenerweckung  visuell spell bis zum erscheinen des npc
-- spell ID - 51519 Initiand der Todesritter

-- spell gibt dem target npc ein neues outfit
-- http://www.wowhead.com/npc=28395/dk-human-male    		spell 51520 
-- http://www.wowhead.com/npc=28420/dk-human-female			spell 51534 
-- http://www.wowhead.com/npc=28427/dk-night-elf-male		spell 51535 
-- http://www.wowhead.com/npc=28423/dk-night-elf-female		spell 51536 
-- http://www.wowhead.com/npc=28421/dk-dwarf-female			spell 51537 
-- http://www.wowhead.com/npc=28425/dk-dwarf-male			spell 51538 
-- http://www.wowhead.com/npc=28426/dk-gnome-male			spell 51539 
-- http://www.wowhead.com/npc=28422/dk-gnome-female			spell 51540 
-- http://www.wowhead.com/npc=28428/dk-draenei-male			spell 51541 
-- http://www.wowhead.com/npc=28424/dk-draenei-female		spell 51542 
-- http://www.wowhead.com/npc=28430/dk-orc-male				spell 51543 
-- http://www.wowhead.com/npc=28436/dk-orc-female			spell 51544 
-- http://www.wowhead.com/npc=28435/dk-troll-female			spell 51545 
-- http://www.wowhead.com/npc=28432/dk-troll-male			spell 51546 
-- http://www.wowhead.com/npc=28433/dk-tauren-male			spell 51547 
-- http://www.wowhead.com/npc=28438/dk-tauren-female		spell 51548 
-- http://www.wowhead.com/npc=28431/dk-forsaken-male		spell 51549 
-- http://www.wowhead.com/npc=28437/dk-forsaken-female		spell 51550 
-- http://www.wowhead.com/npc=28429/dk-blood-elf-male		spell 51551 
-- http://www.wowhead.com/npc=28434/dk-blood-elf-female		spell 51552 

-- 52458	Gnome Female
-- 52459	Gnome Male
-- 52462	Worgen Male
-- 52463	Worgen Female
-- 52464	Goblin Male
-- 52465	Goblin Female
-- 52466	Draenei Female
-- 52468	Draenei Male
-- 52469	Troll Male
-- 52470	Troll Female
-- 52471	Undead Male
-- 52472	Undead Female
-- 52473	Human Male
-- 52474	Human Female
-- 52475	Dwarf Male
-- 52479	Dwarf Female
-- 52480	Night Elf Female
-- 52481	Night Elf Male
-- 52482	Tauren Female
-- 52483	Tauren Male
-- 52484	Orc Male
-- 52485	Orc Female
-- 52486	Blood Elf Female
-- 52487	Blood Elf Male


