--write a SQL query that returns the average energy of all the songs
SELECT SUM(energy)/COUNT(name) as AVERAGE_ENERGY FROM songs;