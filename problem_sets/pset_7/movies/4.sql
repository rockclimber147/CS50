--write a SQL query to determine the number of movies with an IMDb rating of 10.0
SELECT COUNT(title) FROM movies JOIN ratings ON ratings.movie_id = movies.id and ratings.rating = 10.0;