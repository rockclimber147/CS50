--write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
SELECT name FROM people JOIN directors, movies, ratings ON
directors.movie_id = movies.id and
directors.person_id = people.id and
ratings.movie_id = movies.id
WHERE rating >= 9.0;