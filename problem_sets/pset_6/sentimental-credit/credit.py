def main():
    # Get CC as string
    credit_card = input('Number: ')

    # Make containers for values
    sum_digits_times_2 = 0
    sum_other_digits = 0

    card_length = len(credit_card)

    # Scan through card digits and modify according to Luhn's algorithm
    for number in range(card_length):
        # Work in reverse order, taking into consideration index position vs length
        cc_digit = int(credit_card[card_length - number - 1])
        if number % 2 != 0:
            digits = cc_digit * 2
            if digits < 10:
                sum_digits_times_2 += digits
            else:
                # Number will not be greather than 99 so take 10's digit and 1's digit
                sum_digits_times_2 += digits % 10
                sum_digits_times_2 += digits // 10
        else:
            sum_other_digits += cc_digit

    total = sum_digits_times_2 + sum_other_digits

    # Handle invalid cards
    if total % 10 != 0:
        print('INVALID')
        return
    # Make lists of strings to compare first two numbers against
    amex = ['34', '37']
    mastercard = ['51', '52', '53', '54', '55']

    # Check cards vs conditions
    if len(credit_card) == 15 and credit_card[0:2] in amex:
        print('AMEX')
        return
    elif len(credit_card) == 16:
        if credit_card[0:2] in mastercard:
            print('MASTERCARD')
            return
        elif credit_card[0] == '4':
            print('VISA')
            return
    elif len(credit_card) == 13 and credit_card[0] == '4':
        print('VISA')
        return

    print('INVALID')
    return


if __name__ == '__main__':
    main()