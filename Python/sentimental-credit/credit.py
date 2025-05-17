from cs50 import get_int


#  First to add alternative number and add then remaing number (1)multiply by 2 (2)add the digits
def alternative_digit_sum(credit_card):
    sum = 0
    alternative = False

    while credit_card > 0:
        if alternative == True:
            last_digit = credit_card % 10
            produt = multiply_sum(last_digit)
            sum = sum + produt
        else:
            last_digit = credit_card % 10
            sum = sum + last_digit
        alternative = not alternative
        credit_card = credit_card // 10
    return sum

# // To multiply alternative number by 2 and adding the single digit("not the PRODUCT")


def multiply_sum(last_digit):
    multiply = last_digit * 2
    sum = 0
    while multiply > 0:
        last_digit_multiply = multiply % 10
        sum = sum + last_digit_multiply
        multiply = multiply // 10
    return sum

# // Sum of first two digit


def first_two(credit_card, n):
    first_two_digit = credit_card // (10 ** (n - 2))
    return first_two_digit

# // To count digit


def num_digit(credit_card):
    count = 0
    while credit_card > 0:
        count += 1
        credit_card //= 10
    return count


def main():
    credit_card = get_int("credit num: ")
    Luhns_Algorithm = alternative_digit_sum(credit_card)
    last_digit = Luhns_Algorithm % 10
    n = num_digit(credit_card)
    f = first_two(credit_card, n)

    if last_digit == 0:
        if f == 37 or (f == 35 and n == 15):
            print('AMEX')
        elif f >= 51 and f <= 55 and n == 16:
            print('MASTERCARD')
        elif (f >= 40 and f <= 49 and n == 13) or (f >= 40 and f <= 49 and n == 16):
            print('VISA')
        else:
            print('INVALID')
    elif last_digit != 0:
        print('INVALID')


main()
