#ifndef SETTER_H
#define SETTER_H

#include <stdbool.h>

typedef struct Setter
{
    int upper;
    int lower;
    int guess;
    int secretNumber;
    int numberofGuesses;
    bool correctGuess;
    int *guesses;
    void (*createSecretNumber)(struct Setter *self);
    void (*evaluteGuess)(struct Setter *self);
    void (*getScore)(struct Setter *self);
    void (*plot)(struct Setter *self);

} Setter;



// Setter functions
void createSecretNumber(struct Setter *self);
void evaluteGuess(struct Setter *self);
void plotSequence(struct Setter *self);
void getScore(struct Setter *self);




#endif // SETTER_H