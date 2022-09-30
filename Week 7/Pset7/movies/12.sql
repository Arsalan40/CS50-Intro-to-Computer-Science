SELECT m.title
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE p.name ="Johnny Depp"
AND m.title IN(
             SELECT m.title
             FROM people p
             JOIN stars s ON p.id = s.person_id
             JOIN movies m ON s.movie_id = m.id
             WHERE p.name ="Helena Bonham Carter");
