import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py .csv .txt")

    # TODO: Read database file into a variable
    with open(sys.argv[1]) as fcsv:
        dnaDbase = list(csv.reader(fcsv))

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as ftxt:
        dnaList = ftxt.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR = {
        "AGATC": longest_match(dnaList, 'AGATC'),
        "TTTTTTCT": longest_match(dnaList, 'TTTTTTCT'),
        "AATG": longest_match(dnaList, 'AATG'),
        "TCTAG": longest_match(dnaList, 'TCTAG'),
        "GATA": longest_match(dnaList, 'GATA'),
        "TATC": longest_match(dnaList, 'TATC'),
        "GAAA": longest_match(dnaList, 'GAAA'),
        "TCTG": longest_match(dnaList, 'TCTG')
    }

    # TODO: Check database for matching profiles
    if len(dnaDbase) < 5:
        for i in range(1, len(dnaDbase)):
            if STR["AGATC"] == int(dnaDbase[i][1]) and STR["AATG"] == int(dnaDbase[i][2]) and STR["TATC"] == int(dnaDbase[i][3]):
                print(dnaDbase[i][0])
                return
        print("No Match")

    else:
        for i in range(1, len(dnaDbase)):
            if STR["AGATC"] == int(dnaDbase[i][1]) and STR["TTTTTTCT"] == int(dnaDbase[i][2]) and STR["AATG"] == int(dnaDbase[i][3]) and STR["TCTAG"] == int(dnaDbase[i][4]) and STR["GATA"] == int(dnaDbase[i][5]) and STR["TATC"] == int(dnaDbase[i][6]) and STR["GAAA"] == int(dnaDbase[i][7]) and STR["TCTG"] == int(dnaDbase[i][8]):
                print(dnaDbase[i][0])
                return
        print("No Match")


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