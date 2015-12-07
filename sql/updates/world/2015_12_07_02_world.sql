
-- console error
delete from smart_scripts where entryorguid=3670;

delete from smart_scripts where entryorguid=4854;

delete from smart_scripts where entryorguid in (1854, 2021, 2091, 2207, 3247, 3434, 3457, 3458, 3672, 3712, 3725, 3799, 4096);

update creature_template set AIName="" where entry in (1854, 2021, 2091, 2207, 3247, 3434, 3457, 3458, 3672, 3712, 3725, 3799, 4096);

delete from smart_scripts where entryorguid in (4116, 4289, 4303, 4352, 4517, 4674, 4675, 4798, 4805, 4809, 4818, 4820, 4831);

update creature_template set AIName="" where entry in (4116, 4289, 4303, 4352, 4517, 4674, 4675, 4798, 4805, 4809, 4818, 4820, 4831);

