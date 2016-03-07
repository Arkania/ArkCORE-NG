
-- fix part of issue #99
update smart_scripts set link=0 where id=8 and entryorguid=14390;
update smart_scripts set event_param2=5 where id in(8,9) and entryorguid=14390;
