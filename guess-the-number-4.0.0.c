#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 1000
#define BAD_GUESS !setter.correctGuess

typedef struct Setter
{
    int upper;
    int lower;
    int guess;
    int secretNumber;
    int numberofGuesses;
    bool correctGuess;
    int guesses[50];
    void (*createSecretNumber)(struct Setter *self);
    void (*evaluteGuess)(struct Setter *self);
    void (*getScore)(struct Setter *self);
    void (*plot)(struct Setter *self);

} Setter;

typedef struct Guesser
{
    int *upper;
    int *lower;
    int *guess;
    void (*guessAnumber)(struct Guesser *self);

} Guesser;

// Setter functions
void createSecretNumber(struct Setter *self);
void evaluteGuess(struct Setter *self);
void plotSequence(struct Setter *self);
void getScore(struct Setter *self);

// Guesser functions
void guessAnumber(struct Guesser *self);

int main()
{

    Setter setter = {MAX, 0, 0, 0, 0,  false, {0}, createSecretNumber, evaluteGuess, getScore, plotSequence};
    Guesser guesser = {&setter.upper, &setter.lower, &setter.guess, guessAnumber};
    
    setter.createSecretNumber(&setter);

    while (BAD_GUESS)
    {
        guesser.guessAnumber(&guesser);
        setter.evaluteGuess(&setter);
    }

    setter.getScore(&setter);
    setter.plot(&setter);

    return 0;
}

void plotSequence(struct Setter *self)
{
    // Open a pipe to the Gnuplot process
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    // Send commands to the Gnuplot process via the pipe
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    for (int i = 0; i < self->numberofGuesses; i++)
        fprintf(gnuplotPipe, "%d %d\n", i + 1, self->guesses[i]);
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void guessAnumber(Guesser *self)
{
    *self->guess = (rand() % (*self->upper - *self->lower + 1)) + *self->lower;
}

void evaluteGuess(Setter *self)
{
    if (self->secretNumber > self->guess)
    {
        self->lower = self->guess;
    }
    else if (self->secretNumber < self->guess)
    {
        self->upper = self->guess;
    }
    else
    {
        self->correctGuess = true;
    }

    self->guesses[self->numberofGuesses] = self->guess;
    self->numberofGuesses++;
}

void getScore(struct Setter *self)
{
    printf("Excellent, the number is: %d\nYou made %d guesses:\n", self->guess, self->numberofGuesses);
    for (int i = 0; i < self->numberofGuesses; i++)
        printf("%d ", self->guesses[i]);
    printf("\n");
}

void createSecretNumber(struct Setter *self)
{
    srand(time(NULL));
    self->secretNumber = (rand() % (self->upper - self->lower + 1)) + self->lower;
}