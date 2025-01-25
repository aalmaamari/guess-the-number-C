#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

int guessAnumber(int lower, int upper);

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

    // Game start here
    printf("Guess will be betwwen 1 and %d.\n", upper);
    guess = guessAnumber(lower, upper);
    guesses[numberofGuesses] = guess;
    numberofGuesses++;

    // Evalute user Guesses
    while (guess != secretNumber)
    {
        if (secretNumber > guess)
        {
            lower = guess;
        }
        else
        {
            upper = guess;
        }
        guess = guessAnumber(lower, upper);
        guesses[numberofGuesses] = guess;
        numberofGuesses++;
    }

    // Print the result
    printf("Excellent, the number is: %d as you guessed.\nYou made %d guesses:\n", guess, numberofGuesses);
    for (int i = 0; i < numberofGuesses; i++)
        printf("%d ", guesses[i]);
    printf("\n");

    return 0;
}



int guessAnumber(int lower, int upper)
{
    int guess1;
    guess1 = (rand() % (upper - lower + 1)) + lower;
    return guess1;
}