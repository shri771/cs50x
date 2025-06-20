from cs50 import get_string

# Global Function's
grade = 0


# Function to compute the value's in Coleman-Liau indxes
def Coleman_index(no_letters, no_words, no_sentences):
    global grade
    l = (no_letters / no_words) * 100
    s = (no_sentences / no_words) * 100
    index = 0.0588 * l - 0.296 * s - 15.8
    grade = round(index)


# Function to print grade
def print_grade(grade):
    if grade < 1:
        print('Before Grade 1')
    elif grade > 16:
        print('Grade 16+')
    else:
        print(f'Grade {grade}')


# Main
def main():
    # Promot user for text
    text = get_string('Text: ')

    # Count number of letters and words
    no_letters, no_words, no_sentences = 0, 0, 0
    for text in text:
        if text.isalpha():
            no_letters += 1
        if text.isspace():
            no_words += 1
        if text in '.!?':
            no_sentences += 1

    no_words += 1

    # Call-Funcitons
    Coleman_index(no_letters, no_words, no_sentences)
    print_grade(grade)


main()
