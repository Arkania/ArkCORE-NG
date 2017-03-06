
-- fix issue #131
update creature set id=35374 where id=36286 and guid between 116836 and 116844;

delete from creature where id=36396 and guid in (252131, 252132, 252133, 252134);

