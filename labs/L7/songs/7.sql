--write a SQL query that returns the average energy of songs that are by Drake
SELECT SUM(energy)/COUNT(energy) FROM songs JOIN artists on songs.artist_id = artists.id and artists.name = 'Drake';