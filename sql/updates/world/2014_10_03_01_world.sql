
delete from spell_script_names where spell_id=76606 and ScriptName="spell_disable_beacon_beams"; 
insert into spell_script_names values (76606, "spell_disable_beacon_beams");

delete from spell_script_names where spell_id=76608 and ScriptName="spell_disable_beacon_beams"; 
insert into spell_script_names values (76608, "spell_disable_beacon_beams");

update gameobject_template set faction=35,flags=16,data0=1845,data6=8,data10=76606,AIName="",ScriptName="" where entry=207218;
update gameobject_template set faction=35,flags=16,data0=1845,data6=8,data10=76608,AIName="",ScriptName="" where entry=207219;

update gameobject_template set faction=35,flags=16,data0=0,data6=8,data10=76606,AIName="",ScriptName="" where entry=203133;
update gameobject_template set faction=35,flags=16,data0=0,data6=8,data10=76608,AIName="",ScriptName="" where entry=203136;
