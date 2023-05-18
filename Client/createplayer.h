#ifndef CREATEPLAYER_H
#define CREATEPLAYER_H

#include <iostream>
#include <QString>
#include <QStringList>
#include <QTextStream>

namespace ClientSemKirkels
{
    class CreatePlayer
    {
        public:
            CreatePlayer();

            QString getPlayerName()                 { return playerName; }
            void    setPlayerName(QString input)    { playerName = input; }

            QString getStrength()                   { return strength; }
            void    setStrength(QString input)      { strength = input; }

            QString getDexterity()                  { return dexterity; }
            void    setDexterity(QString input)     { dexterity = input; }

            QString getConstitution()               { return constitution; }
            void    setConstitution(QString input)  { constitution = input; }

            QString getIntelligence()               { return intelligence; }
            void    setIntelligence(QString input)  { intelligence = input; }

            QString getWisdom()                     { return wisdom; }
            void    setWisdom(QString input)        { wisdom = input; }

            QString getCharisma()                   { return charisma; }
            void    setCharisma(QString input)      { charisma = input; }

            void    enterPlayerName();
            void    enterModifiers();
            ~CreatePlayer();
        protected:

        private:
            QString playerName;
            QString strength;
            QString dexterity;
            QString constitution;
            QString intelligence;
            QString wisdom;
            QString charisma;
    };
}

#endif // CREATEPLAYER_H
