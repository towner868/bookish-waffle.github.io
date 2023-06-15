SELECT title FROM movies
    INNER JOIN stars ON movies.id = stars.movie_id
    INNER JOIN people ON stars.person_id = people.id
    WHERE name = 'Johnny Depp' AND name = 'Helena Bonham Carter'
    GROUP BY movies.id;
