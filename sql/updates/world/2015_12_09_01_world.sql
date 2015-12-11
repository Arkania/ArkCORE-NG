
UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Lasst mich Eure Hände sehen... aha! Ihr seid beim Pflücken dieser Frucht auch nicht besser als ich!", RequestItemsText_loc3="Konntet Ihr genug Früchte finden?", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26227;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Uff, gerne gekocht habe ich diese schleimigen Dinger nie. Danke für Eure Hilfe, $N.", RequestItemsText_loc3="Konntet Ihr ein paar Flusskrebse fangen?", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26226;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gute Arbeit, $N. Das wird köstlicher Speck.", RequestItemsText_loc3="Habt Ihr die Schweine schon geschlachtet?", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26220;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gute Arbeit, $N! Ich werde dafür sorgen, dass die Rationen umgehend wieder zu unseren Truppen kommen.", RequestItemsText_loc3="Konntet Ihr die Rationen finden?", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26235;

UPDATE quest_template SET RequiredSkillPoints=225 WHERE Id=6611;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Hah! Dieser Cromula ist wirklich zu komisch..$B$BOh, stimmt ja, Schlingendorntal. Ihr wollt wirklich dorthin?", CompletedText_loc3="Meldet Euch bei Bort in Orgrimmar." WHERE Id=26416;

UPDATE locales_quest SET OfferRewardText_loc3="Seid Ihr bereit, mit diesen Berichten nach Orgrimmar zurückzukehren? Ich kann sofort einen Flug für Euch arrangieren." WHERE Id=26806;

delete from quest_poi where questId in (8611, 8612, 8580, 8581, 8549, 8550, 8825, 8818, 8583, 8582, 8533, 8532, 8545, 8546);
delete from quest_poi where questId in (8792, 8851, 8852, 8853, 8854, 8855, 8792, 8793, 8794, 8588, 8589, 8600, 8601, 8590, 8591);
delete from quest_poi where questId in (8604, 8605, 8606, 8607, 8608, 8815, 8823, 10500, 1508, 8368, 8389, 8530,8531,8542,8543);
delete from quest_poi where questId in (8566, 8568, 8570, 8609, 8610, 8613, 8614, 8615, 8616, 8816, 8817, 8824, 8826);

delete from quest_poi_points where questId in (8611, 8612, 8580, 8581, 8549, 8550, 8825, 8818, 8583, 8582, 8533, 8532, 8545, 8546);
delete from quest_poi_points where questId in (8792, 8851, 8852, 8853, 8854, 8855, 8792, 8793, 8794, 8588, 8589, 8600, 8601, 8590, 8591);
delete from quest_poi_points where questId in (8604, 8605, 8606, 8607, 8608, 8815, 8823, 10500, 1508, 8368, 8389, 8530,8531,8542,8543);
delete from quest_poi_points where questId in (8566, 8568, 8570, 8609, 8610, 8613, 8614, 8615, 8616, 8816, 8817, 8824, 8826);

