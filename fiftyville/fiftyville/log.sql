-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 1.) Crime Scene Report:
SELECT description FROM crime_scene_reports
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND street = "Humphrey Street";
--      a.) Humphrey Street Bakery at 10:15am.
--      b.) Three witnesses.
-- 2.) Now check witness reports:
SELECT name, transcript FROM interviews
    WHERE year = 2021
        AND month = 7
        AND day = 28;
--      a.) Ruth - saw Thief leave between 10:15 and 10:25 by car from the bakery parking lot.
--      b.) Eugene - saw Thief withdrawing money from ATM on Leggett Street before 10:15am
--      c.) Raymond - saw Thief on phone as he was leaving (10 - 1015);
--          heard them on the phone for less than a minute;
--          overheard them say they were leaving on the first flight out of Fiftyville the next morning;
--          asked other end to purchase flight ticket.
--  3.) Check earliest flights out of Fiftyville (airport id: 8). First flight is to New York (flight #36) at 820am:

SELECT full_name, flights.id, hour, minute FROM flights
    JOIN airports ON flights.origin_airport_id AND flights.destination_airport_id = airports.id
        WHERE year = 2021
        AND month = 7
        AND day = 29
        AND origin_airport_id = (SELECT id FROM airports
            WHERE city = "Fiftyville");
--  4.) Now cross-check license plates with with atm records. Then intersect with passenger list from flight #36; then with phone calls

    SELECT name FROM people WHERE id IN
        (SELECT person_id FROM bank_accounts
            WHERE account_number IN
                (SELECT atm_transactions.account_number FROM atm_transactions
                    WHERE atm_location = "Leggett Street"
                    AND year = 2021
                    AND month = 7
                    AND day = 28))
    INTERSECT

    SELECT name FROM people WHERE license_plate IN
        (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute BETWEEN 15 AND 26)

    INTERSECT

     SELECT name FROM people
        JOIN passengers ON people.passport_number = passengers.passport_number
        WHERE flight_id = 36

    INTERSECT

    SELECT name FROM people WHERE phone_number IN
        (SELECT caller FROM phone_calls
            WHERE year = 2021
            AND month = 7
            AND day = 28);

-- 5.) Bruce. Now who's the accomplice? Are they on the flight with Bruce?

SELECT name FROM people WHERE phone_number IN
    (SELECT receiver FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28)

INTERSECT

SELECT name FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers
        WHERE flight_id = 36);

SELECT name FROM people WHERE passport_number IN
    (SELECT passport_number
    FROM passengers WHERE seat = "4C"
    AND flight_id = 36);

SELECT seat FROM passengers
    WHERE flight_id = 36
    AND passport_number IN
    (SELECT passport_number
    From people WHERE name = "Bruce");

SELECT name, seat FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = 36;

--6.) No. So let's just look at who Bruce called on the 28th

SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE
    year = 2021
    AND month = 7
    AND day = 28
    AND caller =
(SELECT phone_number FROM people WHERE name = "Bruce"));

--7.) Batman and Robin, cheeky.