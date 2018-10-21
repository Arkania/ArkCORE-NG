
-- SpellScript: Priest

DELETE FROM `spell_script_names` WHERE `spell_id`=528 AND `ScriptName`='spell_pri_cure_disease';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(528, 'spell_pri_cure_disease');

DELETE FROM `spell_script_names` WHERE `spell_id`=48045 AND `ScriptName`='spell_pri_mind_sear_spell';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(48045, 'spell_pri_mind_sear_spell');

DELETE FROM `spell_script_names` WHERE `spell_id`=8092 AND `ScriptName`='spell_pri_mind_blast';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(8092, 'spell_pri_mind_blast');

DELETE FROM `spell_script_names` WHERE `spell_id`=73510 AND `ScriptName`='spell_pri_mind_spike';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(73510, 'spell_pri_mind_spike');

DELETE FROM `spell_script_names` WHERE `spell_id`=586 AND `ScriptName`='spell_pri_fade';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(586, 'spell_pri_fade');

DELETE FROM `spell_script_names` WHERE `spell_id`=588 AND `ScriptName`='spell_pri_inner_fire';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(588, 'spell_pri_inner_fire');

DELETE FROM `spell_script_names` WHERE `spell_id`=77487 AND `ScriptName`='spell_pri_shadow_orbs';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(77487, 'spell_pri_shadow_orbs');

DELETE FROM `spell_script_names` WHERE `spell_id`=89485 AND `ScriptName`='spell_pri_inner_focus';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(89485, 'spell_pri_inner_focus');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (81751, 94472) AND `ScriptName`='spell_pri_atonement_heal';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(81751, 'spell_pri_atonement_heal'),
(94472, 'spell_pri_atonement_heal');

DELETE FROM `spell_script_names` WHERE `spell_id`=81781 AND `ScriptName`='spell_pri_power_word_barrier';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(81781, 'spell_pri_power_word_barrier');

DELETE FROM `spell_script_names` WHERE `spell_id`=88686 AND `ScriptName`='spell_pri_holyword_sanctuary_heal';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(88686, 'spell_pri_holyword_sanctuary_heal');

DELETE FROM `spell_script_names` WHERE `spell_id`=8122 AND `ScriptName`='spell_pri_fear';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(8122, 'spell_pri_fear');

DELETE FROM `spell_script_names` WHERE `spell_id`=97690 AND `ScriptName`='spell_pri_friendly_dispel';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(97690, 'spell_pri_friendly_dispel');

DELETE FROM `spell_script_names` WHERE `spell_id`=27827 AND `ScriptName`='spell_pri_spirit_of_redemption_form';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(27827, 'spell_pri_spirit_of_redemption_form');

DELETE FROM `spell_script_names` WHERE `spell_id`=20711 AND `ScriptName`='spell_pri_spirit_of_redemption';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(20711, 'spell_pri_spirit_of_redemption');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (81208, 81206) AND `ScriptName`='spell_pri_chakra_swap_supressor';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(81206, 'spell_pri_chakra_swap_supressor'),
(81208, 'spell_pri_chakra_swap_supressor');

DELETE FROM `spell_script_names` WHERE `spell_id`=81585 AND `ScriptName`='spell_pri_chakra_serenity_proc';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(81585, 'spell_pri_chakra_serenity_proc');

DELETE FROM `spell_script_names` WHERE `spell_id`=88685 AND `ScriptName`='spell_pri_chakra_sanctuary_heal';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(88685, 'spell_pri_chakra_sanctuary_heal');
