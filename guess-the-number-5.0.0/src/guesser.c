#include "guesser.h"


#include <stdlib.h>


void guessAnumber(Guesser *self)
{
    *self->guess = (rand() % (*self->upper - *self->lower + 1)) + *self->lower;
}