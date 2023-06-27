-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Searches for crime reports on day and street
SELECT description
  FROM crime_scene_reports
 WHERE street = "Humphrey Street"
   AND year = 2021
   AND month = 7
   AND day = 28;

-- Result: "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."

-- Searches for interviews with 'bakery' in transcript
SELECT transcript
  FROM interviews
 WHERE transcript
  LIKE "%bakery%"
   AND year = 2021
   AND month = 7
   AND day = 28;

-- Result: "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- Result: "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
-- Result: "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."

-- Search bakery security logs for license plates
-- Use license plates to find person id
SELECT id
  FROM people
 WHERE license_plate IN (
SELECT license_plate
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25
   AND activity = "exit");
-- Result: 221103, 243696, 396669, 398010, 467400, 514354, 560886, 686048

-- Search ATM transactions for account number
-- Use account number to find person id
SELECT person_id
  FROM bank_accounts
 WHERE account_number IN (
SELECT account_number
  FROM atm_transactions
 WHERE atm_location = "Leggett Street"
   AND transaction_type = "withdraw"
   AND year = 2021
   AND month = 7
   AND day = 28);
-- Result: 686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727

-- Search phone calls for phone number
-- Use phone number to find person id
SELECT id
  FROM people
 WHERE phone_number IN (
SELECT caller
  FROM phone_calls
 WHERE duration < 60
   AND year = 2021
   AND month = 7
   AND day = 28);
-- Result: 395717, 398010, 438727, 449774, 514354, 560886, 686048, 907148

-- Search for earliest flight the day after
SELECT id, distination
  FROM flights
 WHERE year = 2021
   AND month = 7
   AND day = 29
 ORDER BY hour, minute
 LIMIT 1;
-- Result: flight id = 36, destination id = 4

-- Use destination id to find destination city
SELECT city
  FROM airports
 WHERE id = 4;
-- Result: New York City

-- Use flight id to find passenger passport numbers
-- Use passport number to find person id
SELECT id
  FROM people
 WHERE passport_number IN (
SELECT passport_number
  FROM passengers
 WHERE flight_id = 36);
-- Result: 395717, 398010, 449774, 467400, 560886, 651714, 686048, 953679

-- Find name and person id of thief using four id sets
SELECT name
  FROM people
 WHERE id IN (221103, 243696, 396669, 398010, 467400, 514354, 560886, 686048)
   AND id IN (686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727)
   AND id IN (395717, 398010, 438727, 449774, 514354, 560886, 686048, 907148)
   AND id IN (395717, 398010, 449774, 467400, 560886, 651714, 686048, 953679);
-- Result: Bruce

-- Use name to find phone calls
-- Use phone call to find accomplice name
SELECT name
  FROM people
 WHERE phone_number IN (
SELECT receiver
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60
   AND caller = (
SELECT phone_number
  FROM people
 WHERE name = "Bruce"));
-- Result: Robin