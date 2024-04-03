-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Note date of crime being July 28th 2021 on Humphrey Street
.schema --Check everything to see what might relate

--Search crime reports from the date of the crime
SELECT description FROM crime_scene_reports
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';

--Note the exact time of the crime was 10:15am, three witnesses mention the bakery
--Check bakery security logs
SELECT * FROM bakery_security_logs
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10;

--There are a few license plates linked to activity from around 10:15 but none at exactly at that time
--Check interviews
SELECT transcript, name FROM interviews
WHERE year = 2021
    AND month = 7
    AND day = 28;

--Notable interviews:

--Eugene:
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

--Ruth
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking
--lot in that time frame.

--Lily
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

--Per Ruth, get license plates from 10:35 to 10:45 on the day of the crime from the bakery
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 and 25;

-- There are a few which are useful, get a list of names:
-- Get info from people table for license plate owners
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE license_plate IN (
    --Gets the license plates
    SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 and 25);

/* Resulting table:
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/
-- Per Eugene, check ATM withdrawals on Legett Street the morning of the crime
SELECT account_number, amount FROM atm_transactions
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

--There are a few entries here so get names from the account numbers and compare with names from license plates spotted on the
--morning of the crime

SELECT name, license_plate, phone_number, passport_number from people JOIN bank_accounts, atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
    AND people.id = bank_accounts.person_id
    WHERE month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
    AND name IN(
        SELECT name FROM people
            WHERE license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                    WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute BETWEEN 15 and 25));

/*
There are now four suspects:
+-------+---------------+----------------+-----------------+
| name  | license_plate |  phone_number  | passport_number |
+-------+---------------+----------------+-----------------+
| Bruce | 94KL13X       | (367) 555-5533 | 5773159633      |
| Diana | 322W7JE       | (770) 555-1861 | 3592750733      |
| Iman  | L93JTIZ       | (829) 555-5269 | 7049073643      |
| Luca  | 4328GD8       | (389) 555-5198 | 8496433585      |
+-------+---------------+----------------+-----------------+
*/

--Recall what Lily said:

--Lily
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- We can narrow things down further by checking the phone call logs, knowing the date andlength of the call (<1 minute),

SELECT name FROM people JOIN phone_calls
    ON phone_calls.caller = people.phone_number
    WHERE duration < 60
    AND year = 2021
    AND month = 7
    AND day = 28
    AND name IN ('Bruce', 'Diana', 'Imam', 'Luca');

-- There are now two suspects, Diana and Bruce.

--The criminal took the earliest flight the next day (the 29th), so check the flights leaving fiftyville that day

SELECT flights.id, hour, minute FROM flights
    JOIN airports
    ON flights.origin_airport_id = airports.id
    WHERE airports.city = 'Fiftyville'
    AND year = 2021
    AND month = 7
    AND day = 29
    ORDER BY flights.hour ASC, flights.minute ASC
    LIMIT 5;

-- The earliest that day has an id of 36
-- Check whether Bruce or Diana were on that flight

SELECT name FROM people
    JOIN passengers
    ON passengers.passport_number = people.passport_number
    WHERE flight_id = 36
    AND passengers.passport_number IN ('5773159633', '3592750733');

--Bruce was the one on the flight so he must be the criminal.
--Check his destination:
SELECT city FROM airports
    JOIN flights
    ON flights.destination_airport_id = airports.id
    WHERE flights.id = 36;
--He fled to New York City

--But who did he call?
SELECT name FROM people
    JOIN phone_calls
    ON phone_calls.receiver = people.phone_number
    WHERE year = 2021
    AND month = 07
    AND day = 28
    AND caller = '(367) 555-5533'
    AND duration < 60;

--Batman called Robin. Nice.