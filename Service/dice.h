#ifndef DICE_H
#define DICE_H

#include <ctime>
#include <cstdlib>
#include <iostream>

namespace ServiceSemKirkels
{
    class Dice
    {
        public:
            Dice();
            int rollD4(int modifier);
            int rollD6(int modifier);
            int rollD8(int modifier);
            int rollD10(int modifier);
            int rollD12(int modifier);
            int rollD20(int modifier);
            ~Dice();
    
        protected:
            int dice = 0;
    
        private:
    };
}
#endif // DICE_H
