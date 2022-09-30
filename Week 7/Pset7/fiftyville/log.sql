--given information about the crime scene
--Extracted description from crime report table
SELECT description FROM crime_scene_reports WHERE month = 7 and day = 28 and year = 2021 and street = "Humphrey Street";
--hints: took place at 10:15 am
--      all 3 interviewers said about bakery in transcript

--used like operator with wildcard % to get only transcript with word bakery
SELECT name,transcript from interviews WHERE month = 7 and day = 28 and year = 2021 and transcript LIKE "%Bakery%";
--hints: first interviewer= wihtin 10 mins, thief exited from bakery parking
--       second interviewer= thief used atm machine to withdraw on Leggett Street
--       third interviewer= thief called accomplice to book the earliest ticket out of fiftyville tomorrow.

                  -- SELECT license_plate from bakery_security_logs WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit";

                -- SELECT account_number from atm_transactions WHERE month =7 and day =28 and year =2021 and transaction_type ="withdraw" and atm_location="Leggett Street";
                -- select passport_number from passengers WHERE flight_id IN( SELECT id from flights WHERE  month =7 and day=29 and year =2021 order by hour,minute LIMIT 1);

                -- SELECT caller,receiver FROM phone_calls WHERE month =7 and day =28 and year =2021 and duration < 60;

                -- SELECT * FROM airports WHERE city ="Fiftyville";

                -- CREATE TABLE updated_table AS
                -- SELECT distinct(name),phone_number,passport_number,license_plate from latest_table l JOIN phone_calls
                -- ON l.phone_number = phone_calls.caller
                -- WHERE month =7 and day =28 and year =2021 and duration < 60;

--so now I'm extracting data using the hints from interviewers
--First Interviewer
-- getting the name from people table. getting license_plate from bakery_logs table for the given date and as said within 10 mins of time so i used between to filter result when car is exiting
SELECT name from people where license_plate IN (SELECT license_plate from bakery_security_logs WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit");

-- INTERSECT       --using intersect to get the common names everytime, so thief is the last one

--getting names from the account_number who withdrawn on that day on given street.
SELECT name from people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE month =7 and day =28 and year =2021 and transaction_type ="withdraw" and atm_location="Leggett Street";
-- INTERSECT
--getting names that are passengers on the flight where id is extracted for that day and getting id of the origin_airport for the city fiftyville
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id IN (
SELECT id from flights WHERE  month =7 and day=29 and year =2021
AND origin_airport_id IN (
    SELECT id FROM airports WHERE city ="Fiftyville")
    order by hour,minute LIMIT 1
);
-- INTERSECT
-- getting names for those who called on that day with duration less than 60
SELECT distinct(name) FROM people
JOIN  phone_calls p ON people.phone_number =p.caller
WHERE month =7 and day =28 and year =2021 and duration < 60;

--getting all data of flights and airport for the given day which is leaving very first
SELECT * from flights JOIN airports ON flights.origin_airport_id = airports.id WHERE  month =7 and day=29 and year =2021 order by hour,minute LIMIT 1;
--as we knew that destination flight id 4 is leaving first so our tief will be in it.
SELECT city from airports where id=4; --extracting city for that destination id

-- now we got our thief we have to find accomplice. he must be the receiver
-- used nested query here. first we r getting number of receiver from phone_calls where caller name is Bruce and duration is less than 60.
--then outer query is getting name from people table where phone_numbers are equal.
SELECT name from people where phone_number IN (
    SELECT receiver from phone_calls
    WHERE caller IN (SELECT phone_number from people WHERE name ="Bruce") and month =7 and day=28 and year =2021 and duration <60
);