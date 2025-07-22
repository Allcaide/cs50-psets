-- Keep a log of any SQL queries you execute as you solve the mystery.

.output resultado.txt

--See the first clue
SELECT * FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street";
--Bakery and interview made today, 3 Whitnesses

.output resultado.txt
SELECT * FROM interviews
WHERE transcript LIKE '%bakery%'
--Ruth bakery footage
--Eugene - ATM legget
--Raymond - Short phone call  ....  flight ticket


.output resultado.txt
SELECT * FROM bakery_security_logs WHERE year = 2023 and MONTH = 7 AND day = 28 AND hour = 10 and minute between 15 and 25;
-- check licence plates

.output resultado.txt
SELECT p.name, bsl.activity, bsl.license_plate, bsl.year, bsl.month, bsl.day, bsl.hour, bsl.minute
FROM bakery_security_logs bsl
JOIN people p ON p.license_plate = bsl.license_plate
WHERE bsl.year = 2023 AND bsl.month = 7 and bsl.day = 28 and bsl.hour = 10 and bsl.minute BETWEEN 15 and 25;

--check Eugene regard ATM
.output resultado.txt
SELECT * FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND year = 2023 AND month = 7 and day = 28;
--add name of withraws of wquery before

.output resultado.txt
SELECT a.*, p.name
FROM atm_transactions a
JOIN bank_accounts b ON a.account_number = b.account_number
JOIN people p ON b.person_id = p.id
WHERE a.atm_location = 'Leggett Street' AND a.year = 2023 and a.month = 7 and a.day = 28 and a.transaction_type = 'withdraw';
--Witness 3 phone call investigation

.output resultado.txt
SELECT *
FROM phone_calls
WHERE year = 2023 and month = 7 and day = 28 and duration <60;
--Muito vago, has to have a name on it to track

.output resultado.txt
SELECT p.name, pc.caller, pc.receiver, pc.year, pc.month, pc.day, pc.duration
FROM phone_calls pc
JOIN people p ON pc.caller = p.phone_number
WHERE pc.year = 2023 and pc.month = 7 and pc.day = 28 and pc.duration <60;

--WHEREs the airport id on fiftyville
SELECT * FROM airports
WHERE airports.city Like "%Fifty%";
--Number id = 8 CSF hows on departures

--FIND the earliest flight on the next day said RAYMOND
.output resultado.txt
SELECT f.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
FROM flights f
JOIN airports origin ON f.origin_airport_id = origin.id
JOIN airports destination ON f.destination_airport_id = destination.id
WHERE origin.id = 8 AND f.year = 2023 and f.month = 7 and f.day = 28
ORDER by f.hour, f.minute;

--Combine the info from the 3 witnesses
SELECT p.name
FROM bakery_security_logs as bsl
JOIN people p ON p.license_plate = bsl.license_plate
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
JOIN phone_calls pc on pc.caller = p.phone_number
WHERE bsl.year = 2023 AND bsl.month = 7 and bsl.day = 28 and bsl.hour = 10 and bsl.minute BETWEEN 15 and 25
AND at.atm_location ='Leggett Street' and at.year = 2023 and at.month = 7 and at.day = 28 and at.transaction_type = 'withdraw'
AND pc.year = 2023 and pc.month = 7 and pc.day = 28 and pc.duration < 60;
--Bruce or Diana, whos on dflight
.output resultado.txt
SELECT p.name
FROM people p
JOIN passengers ps ON p.passport_number = ps.passport_number
WHERE ps.flight_id = 36
AND p.name IN ('Bruce', 'Diana');
--Only bruce was on flight, bruce is most likely to be guilty

--Who did bruce called on that 60 sec
.output resultado.txt
SELECT p2.name AS receiver
FROM phone_calls pc
JOIN people p1 ON pc.caller = p1.phone_number
JOIN people p2 ON pc.receiver = p2.phone_number
WHERE p1.name = 'Bruce' and pc.year =2023 and pc.month = 7 and pc.day = 28 and pc.duration <60;
--Robin is most likely the coop
