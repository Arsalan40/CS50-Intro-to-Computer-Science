SELECT p.name
FROM people p
JOIN stars s ON p.id= s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE p.name !="Kevin Bacon" and m.title IN(
          SELECT m.title
          FROM people p
          JOIN stars s ON p.id = s.person_id
          JOIN movies m ON s.movie_id = m.id
          WHERE p.name = "Kevin Bacon" AND p.birth = 1958);
