#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "setter.h"
#include "guesser.h"

#define MAX 1000
#define BAD_GUESS !setter.correctGuess


int main()
{
    srand(time(NULL));
    Setter setter = {MAX, 0, 0, 0, 0,  false, NULL, createSecretNumber, evaluteGuess, getScore, plotSequence};
    Guesser guesser = {&setter.upper, &setter.lower, &setter.guess, guessAnumber};
    
    setter.createSecretNumber(&setter);

    while (BAD_GUESS)
    {
        guesser.guessAnumber(&guesser);
        setter.evaluteGuess(&setter);
    }

    setter.getScore(&setter);
    setter.plot(&setter);

    free(setter.guesses);

    return 0;
}
