
UPDATE quest_template SET Title="Learning the Word",Objectives="Reach level 3 to learn Shadow Word: Pain. Use it 2 times on a bloodfang worgen. ",Details="You have much to learn, $N.  And I've much to teach you.$B$BThese are perilous times, however, and I fear that we might have to accelerate certain lessons.$B$BHave no fear, $g brother:sister;.  The Light will guide us through this. Go, get more experience, and learn a new skill. Use it against the bloodfang worgen nearby.",RequiredSpell=589,ObjectiveText1="Practice Shadow Word: Pain" WHERE Id=14279;

UPDATE quest_template SET PrevQuestId=14099 WHERE Id in (14265,14269,14273,14275,14277,14278,14280);
UPDATE quest_template SET PrevQuestId=0 WHERE Id=14157;
UPDATE quest_template SET PrevQuestId=0 WHERE Id=24930;

delete from creature_queststarter where id=35118 and quest=24930;


