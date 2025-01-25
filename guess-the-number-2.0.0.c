#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

void plotSequence(int sequence[], int length);
int guessAnumber(int lower, int upper);

struct Setter
{
    int secretNumber;
    int upper;
    int lower;
    int guess;
    int numberofGuesses;
    int guesses[50];
};

int main()
{

    struct Setter game = {0, MAX, 1, 0, 0, {0}};

    // create the secret number
    srand(time(NULL));
    game.secretNumber = rand() % game.upper + 1;

    // Game start here
    printf("Guess will be betwwen 1 and %d.\n", game.upper);
    game.guess = guessAnumber(game.lower, game.upper);
    game.guesses[game.numberofGuesses] = game.guess;
    game.numberofGuesses++;

    // Evalute user Guesses
    while (game.guess != game.secretNumber)
    {
        if (game.secretNumber > game.guess)
        {
            game.lower = game.guess;
        }
        else
        {
            game.upper = game.guess;
        }
        game.guess = guessAnumber(game.lower, game.upper);
        game.guesses[game.numberofGuesses] = game.guess;
        game.numberofGuesses++;
    }

    // Print the result
    printf("Excellent, the number is: %d\nYou made %d guesses:\n", game.guess, game.numberofGuesses);
    for (int i = 0; i < game.numberofGuesses; i++)
        printf("%d ", game.guesses[i]);
    printf("\n");
    plotSequence(game.guesses, game.numberofGuesses);

    return 0;
}

void plotSequence(int sequence[], int length)
{
    // Open a pipe to the Gnuplot process
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

    // Send commands to the Gnuplot process via the pipe
    fprintf(gnuplotPipe, "plot '-' with lines\n");
    for (int i = 0; i < length; i++)
        fprintf(gnuplotPipe, "%d %d\n", i + 1, sequence[i]);
    fprintf(gnuplotPipe, "e\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

int guessAnumber(int lower, int upper)
{
    int guess;
    guess = (rand() % (upper - lower + 1)) + lower;
    return guess;
}