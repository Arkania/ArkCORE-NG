
update creature_template set minlevel=19, maxlevel=19 where entry in (47294, 47143, 47145, 47232, 47134, 47140, 47231, 47135, 47131);

update creature_template set minlevel=20, maxlevel=20 where entry in (50869, 50561, 47146, 47137, 47138);
update creature_template set minlevel=20, maxlevel=20 where entry in (50857, 47141, 47136, 47132, 50851);

-- delete from creature where id in (47030, 47031, 47865, 47294); 
delete from creature where id in (47006, 47027, 47862, 3864, 3865);
delete from creature where id in (47293, 3849, 6486, 11153, 11154);


