CREATE TABLE IF NOT EXISTS logs(
	ID INTEGER PRIMARY KEY
,	theDate TEXT
,	theTime TEXT
,	name TEXT
,	dose blob
);

CREATE TABLE IF NOT EXISTS drugs(
	ID INTEGER PRIMARY KEY
,	name TEXT
,	doses blob
);
