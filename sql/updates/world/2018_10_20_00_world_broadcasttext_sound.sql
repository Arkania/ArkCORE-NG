
-- it seems some data from 548 client or newer are stored into BroadcastText
-- when the core is find such entries, its ignore the complete text.. better is we delete wrong sound and language entries.

-- in client 434 the SoundEntry.db2 has id's upto 26682 
update broadcast_text set SoundId=0 where SoundId > 26682;

update broadcast_text set EmoteId0=0 where EmoteId0 = 547;

update broadcast_text set Language=0 where Language = 42;

update broadcast_text set Language=0 where Language = 168;
