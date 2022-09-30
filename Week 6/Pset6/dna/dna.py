import csv
from sys import argv, exit


def main():
    # TODO: Check for command-line usage
    if len(argv) < 3:
        print("pattern: python dna.py file.csv file.txt")
        exit(1)

        # TODO: Read database file into a variable
    file_csv = argv[1]
    file_txt = argv[2]
    csv_file = []
    with open(file_csv) as database_file:
        csvFile = csv.DictReader(database_file)                # csv.reader \n next(csv_file)
        for row in csvFile:
            csv_file.append(row)
        # print("csv opened")

        # TODO: Read DNA sequence file into a variable
    with open(file_txt) as sequence_file:
        txt_file = sequence_file.read()
        # print("txt opened")

        # TODO: Find longest match of each STR in DNA sequence
    sub_seq = list(csv_file[0].keys())[1:]
    match = {}
    for dna_seq in sub_seq:
        match[dna_seq] = longest_match(txt_file, dna_seq)

        # TODO: Check database for matching profiles
    for name in csv_file:
        match_count = 0
        for dna_seq in sub_seq:
            if int(name[dna_seq]) == match[dna_seq]:
                match_count += 1
        if match_count == len(sub_seq):
            print(name["name"])
            return
    print("no match")
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
