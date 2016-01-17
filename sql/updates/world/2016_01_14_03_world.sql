

UPDATE quest_template SET Flags=524288, SpecialFlags=4 WHERE Id=25924;

-- Ozumat is spawnet by script
delete from creature where guid in (12533, 51709, 51706, 51708, 51707, 12933, 12929, 12931, 12935, 12934, 12932);

-- Pirate Ship is spawnet by script
delete from gameobject where guid in (164589, 183996);

