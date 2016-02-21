

delete from creature_text where entry=46873 and groupid in (0, 1, 2, 3, 4, 5);
insert into creature_text values
(46873, 0, 0, "Please don't break... please don't break....", 12, 0, 100, 0, 0, 0, "", 48271),
(46873, 1, 0, "Crap! That was my last lock pick!", 12, 0, 100, 0, 0, 0, "", 48272),
(46873, 2, 0, "Here comes the guard, $N! Take him out!", 12, 0, 100, 0, 0, 0, "", 48273),
(46873, 3, 0, "Well done! I was about to jump in! But it looked like you had it under control.", 12, 0, 100, 0, 0, 0, "", 48274),
(46873, 4, 0, "That cat-creature chained back there looks like he wants to talk. Maybe he can help us... but be careful.", 12, 0, 100, 0, 0, 0, "", 48275);

update creature set phaseMask=3 where guid=121423 and id=35374;

update gameobject set phaseMask=2 where guid=179452 and id=206953;
update gameobject set phaseMask=3 where guid=179453 and id=206949;
update gameobject set phaseMask=3 where guid=179454 and id=206949;

update creature set phaseMask=4 where guid=126910 and id=47896;
update creature set phaseMask=3 where guid=126995 and id=46872;
update creature set phaseMask=2 where guid=107580 and id=48029;

-- spawned by script
delete from creature where guid=121441 and id=48011;
delete from creature where guid=91783 and id=46782;
delete from creature where guid=99674 and id=46781;
delete from creature where guid=99672 and id=47912;

update creature set phaseMask=2, position_x=-11000.028320, position_y=-1255.607788, position_z=13.243546, orientation=0.387507 where guid=106354;
update creature set phaseMask=2, position_x=-11000.260742, position_y=-1258.076782, position_z=13.243546, orientation=0.737009 where guid=99755;
update creature set phaseMask=2, position_x=-10989.253906, position_y=-1258.206909, position_z=13.243546, orientation=1.930815 where guid=106219;
update creature set phaseMask=2, position_x=-10988.774414, position_y=-1254.988403, position_z=13.243546, orientation=4.412672 where guid=70220;
update creature set phaseMask=2, position_x=-10989.276367, position_y=-1256.671875, position_z=13.243546, orientation=2.670659 where guid=132459;
update creature set phaseMask=2, position_x=-11022.362305, position_y=-1259.901733, position_z=13.581140, orientation=4.622367 where guid=107580;
update creature set phaseMask=2, position_x=-10994.924805, position_y=-1257.853394, position_z=13.243113, orientation=4.583099 where guid=99673;

update creature_template set AIName="", ScriptName="npc_adarrah_46873" where entry=46873;

