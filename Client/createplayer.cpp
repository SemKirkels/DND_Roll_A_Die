#include "createplayer.h"

ClientSemKirkels::CreatePlayer::CreatePlayer()
{

}

void ClientSemKirkels::CreatePlayer::enterPlayerName()
{
    std::string inputString;

    std::cout << "Enter a charactername: " << std::endl;
    std::cin >> inputString;
    setPlayerName(QString(inputString.c_str()));
}

void ClientSemKirkels::CreatePlayer::enterModifiers()
{
    std::string inputString;

    // Strength
    std::cout << "Enter a strength modifier: " << std::endl;
    std::cin >> inputString;
    setStrength(QString(inputString.c_str()));

    // Dexterity
    std::cout << "Enter a dexterity modifier: " << std::endl;
    std::cin >> inputString;
    setDexterity(QString(inputString.c_str()));

    // Constitution
    std::cout << "Enter a constitution modifier: " << std::endl;
    std::cin >> inputString;
    setConstitution(QString(inputString.c_str()));

    // Intelligence
    std::cout << "Enter a intelligence modifier: " << std::endl;
    std::cin >> inputString;
    setIntelligence(QString(inputString.c_str()));

    // Wisdom
    std::cout << "Enter a wisdom modifier: " << std::endl;
    std::cin >> inputString;
    setWisdom(QString(inputString.c_str()));

    // Charisma
    std::cout << "Enter a charisma modifier: " << std::endl;
    std::cin >> inputString;
    setCharisma(QString(inputString.c_str()));
}

ClientSemKirkels::CreatePlayer::~CreatePlayer()
{

}
