def main():
    height = get_height()
    for i in range(1, height + 1):
        print(" "*(height - i), end="")
        for k in range(1, i + 1):
            print("#", end="")
            k += 1
        print("  ", end="")
        for l in range(1, i + 1):
            print("#", end="")
            l += 1
        print()
        i += 1


def get_height():
    while True:
        try:
            n = int(input("Please choose a height between number 1 and 8: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Integer, please")
            

main()