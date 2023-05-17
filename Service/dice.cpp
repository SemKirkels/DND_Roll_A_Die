#include "dice.h"

ServiceSemKirkels::Dice::Dice()
{

}

int ServiceSemKirkels::Dice::rollD4(int modifier)
{
    dice = (rand() % 4) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

int ServiceSemKirkels::Dice::rollD6(int modifier)
{
    dice = (rand() % 6) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

int ServiceSemKirkels::Dice::rollD8(int modifier)
{
    dice = (rand() % 8) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

int ServiceSemKirkels::Dice::rollD10(int modifier)
{
    dice = (rand() % 10) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

int ServiceSemKirkels::Dice::rollD12(int modifier)
{
    dice = (rand() % 12) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

int ServiceSemKirkels::Dice::rollD20(int modifier)
{
    dice = (rand() % 20) + 1;

    std::cout << "[Debug]: rolled [No modifier]: " << dice << std::endl;

    dice += modifier;

    return dice;
}

ServiceSemKirkels::Dice::~Dice()
{

}
