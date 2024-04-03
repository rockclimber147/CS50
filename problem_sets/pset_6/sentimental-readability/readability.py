import cs50

text = cs50.get_string('enter text: ')

# Make containers for data
sentence_count = 0
word_count = 1
letter_count = 0

# Loop through characters in text and add to variables
for character in text:
    if character == '.' or character == '!' or character == '?':
        sentence_count += 1
    elif character == ' ':
        word_count += 1
    elif character.isalpha():
        letter_count += 1

# Calculate equation variables
letters_per_100_words = 100 * letter_count / word_count
sentences_per_100_words = 100 * sentence_count / word_count

grade_level = round(0.0588 * letters_per_100_words - 0.296 * sentences_per_100_words - 15.8)

# Print depending on grade level
if grade_level < 1:
    print('Before Grade 1')
elif grade_level >= 16:
    print('Grade 16+')
else:
    print(f"Grade {grade_level}")