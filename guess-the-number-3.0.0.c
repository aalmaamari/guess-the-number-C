#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 100

int **upper;
int **lower;
int **guess;

typedef struct
{
    int secretNumber;
    int upper;
    int lower;
    int guess;
    int numberofGuesses;
    int guesses[50];

} Setter;

typedef struct
{
    int *upper;
    int *lower;
    int *guess;

    int *guessAnumber;
} Guesser;


int *guessAnumber();
void plotSequence(int sequence[], int length);




int main()
{
    
    srand(time(NULL));
    Setter setter = {0, 100, 1, 0, 0, {0}};
    Guesser guesser = {&setter.upper, &setter.lower, &setter.guess, NULL};
    upper = &guesser.upper;
    lower = &guesser.lower;
    guess = &guesser.guess;
    // guesser.guessAnumber = guessAnumber();


    // create the secret number
    setter.secretNumber = rand() % setter.upper + 1;

    // Game start here
    printf("Guess will be betwwen 1 and %d.\n", setter.upper);
    guesser.guessAnumber = guessAnumber();
    setter.guesses[setter.numberofGuesses] = setter.guess;
    setter.numberofGuesses++;

    // Evalute user Guesses
    while (setter.guess != setter.secretNumber)
    {
        if (setter.secretNumber > setter.guess)
        {
            setter.lower = setter.guess;
        }
        else
        {
            setter.upper = setter.guess;
        }
        guessAnumber();
        setter.guesses[setter.numberofGuesses] = setter.guess;
        setter.numberofGuesses++;
    }

    // Print the result
    printf("Excellent, the number is: %d\nYou made %d guesses:\n", setter.guess, setter.numberofGuesses);
    for (int i = 0; i < setter.numberofGuesses; i++)
        printf("%d ", setter.guesses[i]);
    printf("\n");
    plotSequence(setter.guesses, setter.numberofGuesses);

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

int *guessAnumber()
{
    **guess = (rand() % (**upper - **lower + 1)) + **lower;
    return *guess;
}