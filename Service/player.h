#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <fstream>

namespace ServiceSemKirkels
{
    class player
    {
        public:
            player();
            void parceModifiers(QString modifier);
            void writeModifiers(QString playerName);
            int readModifiers(QString playerName, QString modifier_Request);
            ~player();

        protected:

        private:
            int modifiers[6];
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
