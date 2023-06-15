from cs50 import get_string

text = get_string("Text: ")

letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1

for i in range(len(text)):
    if text[i] == " ":
        words += 1

for i in range(len(text)):
    if text[i] == "." or text[i] == "?" or text[i] == "!":
        sentences += 1
        
L = float(letters / words * 100)
S = float(sentences / words * 100)

rough = .0588 * L - .296 * S - 15.8

index = round(rough)

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
