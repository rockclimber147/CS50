--write a SQL query to list the names of all people who starred in Toy Story.
SELECT name FROM people JOIN stars, movies ON
stars.movie_id = movies.id and
people.id = stars.person_id
WHERE movies.title = 'Toy Story';