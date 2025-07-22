SELECT AVG(ratings.rating) AS average_rating FROM ratings
JOIN movies on ratings.movie_id = movies.id
WHERE movies.year = 2012
;
