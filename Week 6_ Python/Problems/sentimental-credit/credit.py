from cs50 import get_int

credit = get_int("Credit Card Number: ")
length = len(str(credit))

# Calculate sum of digits
sum = 0

# For every digit
for i in range(length):
    digit = credit // 10**i % 10
    if i % 2 == 0:
        sum += digit
    else:
        other = digit * 2
        other1s = other % 10
        other10s = other // 10
        sum += other1s + other10s

# Check if sum has last digit 0
if sum % 10 == 0:
    # Find first two digits
    d1 = credit // 10**(length - 1)
    d2 = credit // 10**(length - 2) % 10

    # VISA
    if (length == 13 or length == 16) and d1 == 4:
        print("VISA")
    # American Express
    elif length == 15 and d1 == 3 and (d2 == 4 or d2 == 7):
        print("AMEX")
    # Mastercard
    elif length == 16 and d1 == 5 and d2 >= 1 and d2 <= 5:
        print("MASTERCARD")
    # Invalid (Doesn't match requirements)
    else:
        print("INVALID")
# Invalid (Doesn't end with 0)
else:
    print("INVALID")