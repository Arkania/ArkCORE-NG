
-- A Vision of the Past

UPDATE `quest_template` SET 
 `MinLevel`=12, 
 `Level`=15, 
 `NextQuestIdChain`=26322, 
 `ZoneOrSort`=40, 
 `SoundAccept`=890, 
 `SoundTurnIn`=878, 
 `SourceItemID`=58147, 
 `SourceItemCount`=1, 
 `RequiredSourceItemID1`=58147, 
 `RequiredSourceItemCount1`=1, 
 `RewardMoneyMaxLevel`=6300, 
 `RewardOrRequiredMoney`=700, 
 `RewardXPId`=5,  -- 1050
 `RewardFactionValueIdOverride1`=5, 
 `OfferRewardEmote1`=5, 
 `OfferRewardEmoteDelay1`=0, 
 `OfferRewardEmote2`=1, 
 `OfferRewardEmoteDelay2`=0, 
 `RewardFactionID1`=72, 
 `RewardFactionValueID1`=0, 
 `RewardFactionValueIDOverride1`=5, 

 `RequiredNpcOrGO1`=42371,
 `RequiredNpcOrGOCount1`=1,
 `ObjectiveText1`="Explore the Deadmines.",
 `ObjectiveText2`="See into the past.",
 
 `WDBVerified`=18414 WHERE `Id`=26320; 
