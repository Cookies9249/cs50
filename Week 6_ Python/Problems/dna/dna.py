import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    data = []
    strList = []

    # Open and read .csv file into data
    with open(sys.argv[1]) as dataFile:
        dataReader = csv.DictReader(dataFile)
        for name in dataReader:
            data.append(name)

    # Identify STRs from .csv file header into strList
    with open(sys.argv[1]) as headerFile:
        strReader = csv.reader(headerFile)
        strList = next(strReader)

    # TODO: Read DNA sequence file into a variable

    # Open and read .txt file into sequence
    with open(sys.argv[2]) as sequenceFile:
        sequence = sequenceFile.read()

    # TODO: Find longest match of each STR in DNA sequence
    profile = {}
    strCount = len(data[0]) - 1
    dataCount = len(data)

    # Find longest match for every STR
    for i in range(strCount):
        str = strList[i + 1]
        longest = longest_match(sequence, str)

        # Add new set to dict
        profile[str] = longest

    # TODO: Check database for matching profiles

    # Search every person in data set
    for i in range(dataCount):

        # For each STR, compare two data sets
        for j in range(strCount):
            str = strList[j + 1]

            # If a difference is found, stop search
            if int(profile[str]) != int(data[i][str]):
                break

            # If no difference is found, print match and exit main
            if j == strCount - 1:
                match = data[i]["name"]
                print(match)
                return

    # If no person is found to match, print and exit main
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
