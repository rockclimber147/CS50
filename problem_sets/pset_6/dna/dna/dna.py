import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py data.csv sequence.txt')

    # TODO: Read database file into a variable

    # Make a list of dictionaries
    people_str_counts = []
    with open(sys.argv[1], "r") as database_file:
        reader = csv.DictReader(database_file)
        for person in reader:
            people_str_counts.append(person)

    # TODO: Read DNA sequence file into a variable

    # Put file string in variable
    with open(sys.argv[2], "r") as dna_file:
        dna_sequence = dna_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Make a sequence list of the str and the count
    sequences_list = []
    # Get key values from people list as str strings
    for str_sequence in people_str_counts[0]:
        # skip name
        if str_sequence != 'name':
            # Make a tuple in the form str, count and append to list
            tuple_pair = str_sequence, longest_match(dna_sequence, str_sequence)
            sequences_list.append(tuple_pair)
    # Turn the list into a dictionary
    sequences_dict = dict(sequences_list)

    # TODO: Check database for matching profiles
    for people in people_str_counts:
        # Keep track of matches
        matches = 0
        for str in sequences_dict:
            # check if person str counts match the sample OH GOD OH FUCK MAKE IT AN INT YOU STUPID BITCH
            if int(people[str]) == sequences_dict[str]:
                matches += 1
        # Break out of script when a person matches everything
        if matches == len(sequences_list):
            print(people['name'])
            return
    print('No match')
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
