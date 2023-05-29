#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <fstream>
#include <iostream>

#include "defines.h"

namespace ServiceSemKirkels
{
    class player
    {
        public:
            player();
            void writeModifiers(QString playerName, QString modifierStr);
            int readModifiers(QString playerName, QString modifier_Request);
            bool checkExistingPlayer(QString Playername);
            ~player();

        protected:

        private:
    };
}
#endif // PLAYER_H

/*
 * Modifier_type
 * int modifier_type is used to identify the modifier type and to find the place in the txt file.
 *
 * 0. Strength
 * 1. Dexterity
 * 2. Constitution
 * 3. Intelligence
 * 4. Wisdom
 * 5. Charisma
 */
