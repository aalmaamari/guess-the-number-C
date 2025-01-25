#include "setter.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


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

    // allocate
    int *temp = realloc(self->guesses,(self->numberofGuesses +1) * sizeof(int));
    if (temp == NULL) {
            printf("Memory allocation failed!\n");
            free(self->guesses); // Free the previously allocated memory before exiting
            exit(1);
        }
    self->guesses = temp;
    self->guesses[self->numberofGuesses] = self->guess;
    
    printf(" guess: %d \n", self->guesses[self->numberofGuesses]);
    // printf("%d*%d\n",  temp, self->guesses[self->numberofGuesses]);
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
    self->secretNumber = (rand() % (self->upper - self->lower + 1)) + self->lower;
}