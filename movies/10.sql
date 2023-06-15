SELECT DISTINCT name FROM people
    INNER JOIN directors ON people.id = directors.person_id
    INNER JOIN ratings ON directors.movie_id = ratings.movie_id
    INNER JOIN movies ON ratings.movie_id = movies.id
    WHERE rating >= 9.0;