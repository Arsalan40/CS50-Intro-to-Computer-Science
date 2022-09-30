
--given hint to use crime scene so i extract description of the crime
--hints: took place at 10:15am
SELECT description FROM crime_scene_reports WHERE month = 7 and day = 28 and year = 2021 and street = "Humphrey Street";
--3 interviews conducted where transcript have bakery for all 3
SELECT name,transcript from interviews WHERE month = 7 and day = 28 and year = 2021 and transcript LIKE "%Bakery%";

-- now we will investigate for all interviewers transcript
--interview 1
--hints:10minutes, exit the bakery parking lot
SELECT license_plate from bakery_security_logs WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit";

--interview 2
--hints: used atm on Leggett Street
SELECT account_number from atm_transactions WHERE month =7 and day =28 and year =2021 and transaction_type ="withdraw" and atm_location="Leggett Street";
select passport_number from passengers WHERE flight_id IN( SELECT id from flights WHERE  month =7 and day=29 and year =2021 order by hour,minute LIMIT 1);

--interview 3
--hints: called for less than a minute, going to book earliest flight that leaves fiftyville
SELECT caller,receiver FROM phone_calls WHERE month =7 and day =28 and year =2021 and duration < 60;

-- SELECT distinct(name) from people JOIN phone_calls ON people.phone_number = phone_calls.caller
-- WHERE license_plate IN(SELECT license_plate from bakery_security_logs WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit"
-- ) and month =7 and day =28 and year =2021 and duration < 60;

SELECT * FROM airports WHERE city ="Fiftyville";
-- SELECT * from flights where month =7 and day=29 and year =2021 order by hour,minute LIMIT 1 ;
SELECT * from flights JOIN airports ON flights.origin_airport_id = airports.id WHERE  month =7 and day=29 and year =2021 order by hour,minute LIMIT 1;
SELECT city from airports where id=4;


-- CREATE TABLE latest_table AS
-- SELECT name,phone_number,passport_number,people.license_plate from people JOIN bakery_security_logs b
-- ON people.license_plate = b.license_plate
-- WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit";

-- SELECT * from latest_table;

-- CREATE TABLE updated_table AS
-- SELECT distinct(name),phone_number,passport_number,license_plate from latest_table l JOIN phone_calls
-- ON l.phone_number = phone_calls.caller
-- WHERE month =7 and day =28 and year =2021 and duration < 60;

SELECT * from updated_table;

-- select * from updated_table where passport_number IN
-- (select passport_number from passengers WHERE flight_id IN( SELECT id from flights WHERE  month =7 and day=29 and year =2021 order by hour,minute LIMIT 1)
-- and license_plate IN (SELECT license_plate from bakery_security_logs WHERE month =7 and day =28 and year =2021 and hour = 10 and minute BETWEEN 15 and 25 and activity ="exit"
-- )
-- and phone_number IN (SELECT caller FROM phone_calls WHERE month =7 and day =28 and year =2021 and duration < 60
-- )
-- );
