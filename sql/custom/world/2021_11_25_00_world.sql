-- ----------------------------------
--    Pandaren Start Zone Fixes
-- ----------------------------------
-- Quest 29523: item 72109 (Wind Stone) did not summon "The Living Air"
UPDATE `world`.`conditions` SET `ConditionTypeOrReference` = '31' , `ConditionValue1` = '3' WHERE `SourceTypeOrReferenceId` = '13' AND `SourceGroup` = '1' AND `SourceEntry` = '106299' AND `SourceId` = '0' AND `ElseGroup` = '0' AND `ConditionTypeOrReference` = '51' AND `ConditionTarget` = '0' AND `ConditionValue1` = '5' AND `ConditionValue2` = '41200' AND `ConditionValue3` = '0';
-- ----------------------------------
--    Draenei Start Zone Fixes
-- ----------------------------------
-- Quest 9294: item 22955 (Neutralizing Agent) did not see "Irradiated Power Crystal"
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (181433);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(181433, 1, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 33, 88791, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Irradiated Power Crystal - On Gossip Hello - Give Credit ("Bunny - Irradiated Crystal")'),
(181433, 1, 1, 0, 70, 0, 100, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 20239, 0, 0, 0, 0, 0, 0, 'Irradiated Power Crystal - On State Changed - Say Line 1 (Neutralizing Emote Placeholder)');
DELETE FROM `item_script_names` WHERE `Id`='24318';
INSERT INTO `item_script_names` (`Id`, `ScriptName`) VALUES (24318, 'item_water_sample_flask_24318');
DELETE FROM `spell_script_names` WHERE `spell_id`='31549';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (31549, 'spell_bloodmyst_water_sample');
-- Remove old unused spell scripts
DELETE FROM `spell_script_names` WHERE `ScriptName` IN 
('spell_pal_aura_mastery',
'spell_pal_aura_mastery_immune',
'spell_pal_avenging_wrath',
'spell_pal_exorcism_and_holy_wrath_damage',
'spell_pal_eye_for_an_eye',
'spell_pal_righteous_defense',
'spell_pal_sacred_shield',
'spell_pal_shield_of_the_righteous',
'spell_pal_seal_of_righteousness');
-- Add new ones
INSERT IGNORE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(35395, 'spell_pal_crusader_strike'),
(19750, 'spell_pal_flash_of_light'),
(20271, 'spell_pal_judgment'),
(184662, 'spell_pal_shield_of_vengeance'),
(53385, 'spell_pal_divine_storm'),
(20473,'spell_pal_holy_shock'),
(156910,'spell_pal_beacon_of_faith'),
(53563,'spell_pal_beacon_of_light'),
(53651,'spell_pal_beacon_of_light_proc'),
(177173,'spell_pal_beacon_of_light_proc'),
(200025,'spell_pal_beacon_of_light_aura'),
(200025,'spell_pal_beacon_of_virtue'),
(85222,'spell_pal_light_of_dawn'),
(185984,'spell_pal_light_of_dawn_trigger'),
(53576,'spell_pal_infusion_of_light'),
(633,'spell_pal_activate_forbearance'),
(1022,'spell_pal_activate_forbearance'),
(204018,'spell_pal_activate_forbearance');
