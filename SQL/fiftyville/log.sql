-- description of the Crime
SELECT
    description
FROM
    crime_scene_reports
WHERE
    year = 2024
    AND month = 7
    AND street = 'Humphrey Street'
    AND day = 28
    AND description LIKE '%CS50%';

-- To Check the interviews realated to the theft
SELECT
    transcript
FROM
    interviews
WHERE
    transcript LIKE '%bakery%'
    AND year = 2024
    AND month = 7
    AND day = 28;

-- Find the number plate and the name
SELECT
    name,
    hour,
    minute,
    people.id,
    passport_number,
    activity
FROM
    bakery_security_logs,
    people
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND (hour = 10
        OR hour = 9)
    AND bakery_security_logs.license_plate = people.license_plate;

-- Find the atm trancaitons
SELECT
    person_id
FROM
    atm_transactions,
    bank_accounts
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
    AND atm_transactions.account_number = bank_accounts.account_number;

-- Find the people who where there in bakery and withdrawed money in morning
SELECT
    name,
    people.phone_number,
    people.id,
    passport_number,
    activity
FROM
    bakery_security_logs,
    people
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND (hour = 10
        OR hour = 9)
    AND bakery_security_logs.license_plate = people.license_plate
    AND people.id IN (
        SELECT
            person_id
        FROM
            atm_transactions,
            bank_accounts
        WHERE
            year = 2024
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
            AND atm_transactions.account_number = bank_accounts.account_number);

SELECT
    *
FROM
    phone_calls
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND duration <= 60;

-- Find the theft
SELECT
    name,
    passport_number
FROM
    bakery_security_logs,
    people
WHERE
    year = 2024
    AND month = 7
    AND day = 28
    AND (hour = 10
        OR hour = 9)
    AND bakery_security_logs.license_plate = people.license_plate
    AND people.id IN (
        SELECT
            person_id
        FROM
            atm_transactions,
            bank_accounts
        WHERE
            year = 2024
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
            AND atm_transactions.account_number = bank_accounts.account_number)
    AND (people.phone_number IN (
            SELECT
                caller
            FROM
                phone_calls
            WHERE
                year = 2024
                AND month = 7
                AND day = 28
                AND duration <= 60));

SELECT
    *
FROM
    flights
WHERE
    year = 2024
    AND month = 7
    AND day = 29;

SELECT
    *
FROM
    passengers
WHERE
    flight_id = 36;

