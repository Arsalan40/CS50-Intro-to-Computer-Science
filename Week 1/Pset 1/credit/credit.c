#include <cs50.h>
#include <stdio.h>

int main(void)
{

    long card_number = get_long("Number: ");      //user input card number
    int digits = 0;
    long card = card_number;
    while (card > 0)
    {                                           // get the length of card
        card = card / 10;
        digits++;
    }
    if (digits<13 ||digits>16)
    {
        printf("INVALID\n");                      // checking if valid or not
        return 0;
    }

    int not_multiply_two = 0;
    int multiply_two = 0;
    long new_card = card_number;
    int total = 0;
    int digit1;
    int digit2;
    int last_digit;
    int secondlast_digit;
    do
    {

        last_digit = new_card % 10;       //remove end digit
        new_card = new_card / 10;
        not_multiply_two = not_multiply_two + last_digit;

        secondlast_digit = new_card % 10;
        new_card = new_card / 10;        //remove second last one

        secondlast_digit = secondlast_digit * 2;
        digit1 = secondlast_digit % 10;             // applying luhns algo
        digit2 = secondlast_digit / 10;
        multiply_two = multiply_two + digit1 + digit2;
    }
    while (new_card > 0);
    total = not_multiply_two + multiply_two;          //sum both and get total

    if (total % 10 != 0)                           //checking if valid (0)
    {
        printf("INVALID\n");
        return 0;
    }

    long start = card_number;
    do                                         //checking starting digits are of which card type
    {
        start = start / 10;
    }
    while (start > 58);

    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
                                                  //4012888888881881 visa
    }
}