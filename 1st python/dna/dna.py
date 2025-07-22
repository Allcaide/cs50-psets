import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error 3 args - python dna.py data.csv sequence.txt")
        sys.exit(1)

    database_file = sys.argv[1]
    dna_sequence_file = sys.argv[2]

    # TODO: Read database file into a variable
    rows = []

    with open(database_file) as file:
        reader = csv.DictReader(file)

        # Colocar uma lista tipo hash com os nomes à esquerda
        # print(reader.fieldnames)
        dna_codes = reader.fieldnames[1:]

        for row in reader:
            rows.append(row)

    # print("Database")
    # print(rows)

    # TODO: Read DNA sequence file into a variable
    with open(dna_sequence_file) as file:
        sequence = file.read().strip()

    # print("DNA sequence:")
    # print(sequence)

    # print("##########")
    # print("dna_codes abaixo")
    # print(f"{dna_codes}")

    # TODO: Find longest match of each STR in DNA sequence

    dna_counts = {}
    for dna_code in dna_codes:
        dna_counts[dna_code] = longest_match(sequence, dna_code)

    # print("##########")
    # print("Ver se acrescentou aos códigos")
    # print(f"{dna_counts}")

    # TODO: Check database for matching profiles

    for person in rows:
        # print(f"{person[dna_codes[0]]}")

        match = all(
            int(person[dna_codes]) == dna_counts[dna_codes]
            for dna_codes in dna_counts

        )
        if match:
            print(f"{person['name']}")
            break
    if match == False:
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
