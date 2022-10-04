// Checks validity of credit card number and return whether it is AMEX, VISA, MASTERCARD or INVALID

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Declare functions
int main(void)
{
    // Declare variables
    long n;

    // Get credit card number from user
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);

    int num_len = floor(log10(n) + 1);

    // 1. Multiply every second digit of credit card number by 2 and sum

    // 1.1. Create array with length as length of input from user

    int first_array[num_len];

    // 1.2. Make number into a long double (to store decimals)

    double temp_num = (double) n;

    // 1.3. Store each digit into array
    // Using int and long datatypes characteristic, dividing a number by 10^n will yield the desired number in a hundreds, thousands, etc.
    int i = 0;
    double post;
    long pre;
    while (i < num_len)
    {
        temp_num = temp_num / 10; // 1234 becomes 123.4
        pre = (long) temp_num; // pre = 123
        post = temp_num - pre; // post = 0.4
        temp_num = temp_num - post; // temp_num = 123

        // to deal with zeros
        if (post == 0)
        {
            first_array[i] = 0;
        }
        else
        {
            first_array[i] = (int) (round(post * 10));
        }
        post = 0; // reset post to 0 to make sure no rounding issues further into the loop
        i++;
    }

    // 1.4. Multiply second digit of array starting with second last by 2 and sum
    int first_sum = 0;
    int second_array[num_len];
    for (i = 0; i < num_len; i++)
    {
        second_array[i] = first_array[i];
    }

    for (i = 1; i < num_len; i+=2) // start loop at index 0
    {
        second_array[i] = second_array[i]*2;
        float bef = (float) second_array[i] / 10;
        float dec = bef - (int) bef;
        first_sum += (int) bef + (int) (dec * 10);
    }


    // 2. Sum the number from step 1 with every second digit that was not accounted for in step 1.
    int second_sum = 0;

    for (i = 0; i < num_len; i+=2) // start loop at index 1
    {
        second_sum += second_array[i];
    }


    // 3. Determine type and validity of card
    int sum_all = first_sum + second_sum;
    if (sum_all % 10 == 0)
    {
        if (first_array[num_len - 1] == 4)
        {
            printf("VISA\n");
        }
        else if (first_array[num_len - 1] == 3 && (first_array[num_len - 2] == 4 || first_array[num_len - 2] == 7))
        {
            printf("AMEX\n");
        }
        else if (first_array[num_len - 1] == 5 && (first_array[num_len - 2] > 0 && first_array[num_len - 2] < 6))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }

}