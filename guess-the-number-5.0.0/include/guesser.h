#ifndef GUESSER_H
#define GUESSER_H



typedef struct Guesser
{
    int *upper;
    int *lower;
    int *guess;
    void (*guessAnumber)(struct Guesser *self);

} Guesser;


// Guesser functions
void guessAnumber(struct Guesser *self);


#endif // GUESSER_H