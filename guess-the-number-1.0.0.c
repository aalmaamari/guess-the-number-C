#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100


int main()
{

    int secretNumber;
    int upper = MAX;
    int lower = 1;
    int guess = 0;
    int numberofGuesses = 0;
    int guesses[50] = {0};

    // create the secret number
    srand(time(NULL));
    secretNumber = rand() % upper + 1;

    // Taking user input
    printf("Guess an integer betwwen 1 and %d: ", upper);
    scanf("%d", &guess);
    guesses[numberofGuesses] = guess;
    numberofGuesses++;

    // Evalute user Guesses
    while (guess != secretNumber)
    {
        if (secretNumber > guess)
        {
            printf("Go up, try again: ");
            lower = guess;
        }
        else
        {
            printf("Go down, try again: ");
            upper = guess;
        }
        scanf("%d", &guess);

        guesses[numberofGuesses] = guess;
        numberofGuesses++;
    }

    // Print the result
    printf("Excellent, the number is: %d.\nYou made %d guesses\n", guess, numberofGuesses);
    for (int i = 0; i < numberofGuesses; i++)
        printf("%d ", guesses[i]);
    printf("\n");

    return 0;
}