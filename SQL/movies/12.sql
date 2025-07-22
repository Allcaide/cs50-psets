SELECT movies.title FROM movies
JOIN ratings on movies.id = ratings.movie_id
JOIN stars AS stars1 on movies.id = stars1.movie_id
JOIN stars AS stars2 on movies.id = stars2.movie_id
WHERE stars1.person_id =(
    SELECT id FROM people WHERE name = 'Bradley Cooper'
)
AND stars2.person_id=(
    SELECT id FROM people WHERE name = 'Jennifer Lawrence'
);
