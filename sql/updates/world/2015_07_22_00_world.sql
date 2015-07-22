
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Meldet Euch bei Unteroffizier Grau im Baradinbasislager, wenn Ihr fertig seid." WHERE Id=27987;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Joren Eisenquell im Eisklammtal zurück." WHERE Id=24469;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Joren Eisenquell im Eisklammtal zurück." WHERE Id=24470;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Sten Starkarm im Eisklammtal zurück." WHERE Id=24471;

delete from spell_script_names where spell_id=69855;
insert into spell_script_names values (69855, "spell_heal_wounded_mountaineer");

update creature_text set BroadcastTextID=36983 where entry=37080 and groupid=0 and id=0;
update creature_text set BroadcastTextID=36982 where entry=37080 and groupid=0 and id=1;
update creature_text set BroadcastTextID=36983 where entry=37080 and groupid=0 and id=2;


