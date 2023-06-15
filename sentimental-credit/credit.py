from cs50 import get_string
import math

# input card number
cardNumber = get_string("Number: ")

cardNumberlength = len(cardNumber)

# use slicing to store first two digits in variable, start/end/step
firstDigit = cardNumber[0:2]

# this slicing syntax starts -2 from 0, and steps -2 (every other) through the list
multDig = cardNumber[-2::-2]
addDig = cardNumber[-1::-2]

multSum = 0

# the mathfloor method rounds down
for i in range(len(multDig)):
    multSum += math.floor((int(multDig[i]) * 2 / 10)) + math.floor((int(multDig[i]) * 2 % 10))

addSum = 0

for i in range(len(addDig)):
    addSum += int(addDig[i])

checkSum = addSum + multSum
print(firstDigit)

if (cardNumberlength < 13) or (cardNumberlength > 16):
    print("INVALID")
elif (checkSum % 10 == 0) and (firstDigit == "34" or firstDigit == "37"):
    print("AMEX")
elif (checkSum % 10 == 0) and (firstDigit[0] == "4"):
    print("VISA")
elif (checkSum % 10 == 0) and (firstDigit == "51" or firstDigit == "52" or firstDigit == "53" or firstDigit == "54" or firstDigit == "55"):
    print("MASTERCARD")
else:
    print("INVALID")