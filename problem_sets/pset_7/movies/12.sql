--write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
SELECT DISTINCT title FROM movies JOIN stars, people ON
stars.person_id = people.id and
stars.movie_id = movies.id
WHERE title IN (
    SELECT title FROM movies JOIN stars, people ON
    stars.person_id = people.id and
    stars.movie_id = movies.id
    WHERE people.name = 'Johnny Depp'
) and title IN (
    SELECT title FROM movies JOIN stars, people ON
    stars.person_id = people.id and
    stars.movie_id = movies.id
    WHERE people.name = 'Helena Bonham Carter'
);
