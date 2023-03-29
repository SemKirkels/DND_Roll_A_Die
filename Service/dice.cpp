#include "dice.h"

Dice::Dice()
{

}

int Dice::rollD4()
{
    dice = (rand() % 4) + 1;

    return dice;
}

int Dice::rollD6()
{
    dice = (rand() % 6) + 1;

    return dice;
}

int Dice::rollD8()
{
    dice = (rand() % 8) + 1;

    return dice;
}

int Dice::rollD10()
{
    dice = (rand() % 10) + 1;

    return dice;
}

int Dice::rollD12()
{
    dice = (rand() % 12) + 1;

    return dice;
}

int Dice::rollD20()
{
    dice = (rand() % 20) + 1;

    return dice;
}

Dice::~Dice()
{

}
