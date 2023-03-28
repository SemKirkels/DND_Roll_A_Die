#ifndef DICE_H
#define DICE_H


class Dice
{
    public:
        Dice();
        int rollD4();
        int rollD6();
        int rollD8();
        int rollD10();
        int rollD12();
        ~Dice();
    protected:
        int dice = 0;
};

#endif // DICE_H
