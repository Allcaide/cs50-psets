from cs50 import get_string
import string

text = get_string("Text: ")

count_letters = 0
count_words = 0
count_setences = 0


def count_letters(text):
    sum_letters = sum(1 for char in text if char.isalpha())
    return sum_letters


def count_setences(text):
    sum_setences = sum(1 for char in text if char in ".?!")
    return sum_setences


def count_words(text):
    sum_words = len(text.split())
    return sum_words


letters = count_letters(text)
words = count_words(text)
setences = count_setences(text)

L = 100 * letters/words
S = 100 * setences/words
index = 0.0588 * L - 0.296 * S - 15.8
# print(L)

if index < 1:
    print("Before Grade 1")

elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
