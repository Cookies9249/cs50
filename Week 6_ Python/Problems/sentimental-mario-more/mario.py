# Get height input
while True:
    try:
        height = int(input("Height: "))
        if height >= 1 and height <= 8:
            break
    except ValueError:
        print(end='')

# For each row
for i in range(height):
    # Spaces
    print(" " * (height - i - 1), end="")

    # Left stair
    print('#' * (i + 1), end="  ")

    # Right stair
    print("#" * (i + 1))