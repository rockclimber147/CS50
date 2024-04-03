--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name FROM people Join stars, movies ON
stars.person_id = people.id and
stars.movie_id = movies.id
WHERE movies.id IN (
    --Get IDs of movies with Kevin Bacon
    SELECT id FROM movies JOIN stars ON
    movie_id = id
    WHERE stars.person_id IN (
        --Get Kevin Bacon's ID
        SELECT id FROM people WHERE name = 'Kevin Bacon' and birth = 1958
    )
) and name != 'Kevin Bacon';