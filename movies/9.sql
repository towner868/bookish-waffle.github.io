    SELECT name FROM people
    GROUP BY name
    HAVING COUNT(DISTINCT people.id) = 1;
    INNER JOIN stars ON people.id = stars.person_id
    INNER JOIN movies ON stars.movie_id = movies.id
    WHERE year = 2004
    ORDER BY birth;

