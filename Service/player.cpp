#include "player.h"

ServiceSemKirkels::player::player()
{

}

void ServiceSemKirkels::player::writeModifiers(QString playerName)
{
    std::fstream inputFile;

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    // Write Modifiers
}

int ServiceSemKirkels::player::readModifiers(QString playerName, QString modifier_Request)
{
    int modifier_int = 0;
    std::fstream inputFile;

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    if(modifier_Request == "Strength")
    {

    }
    else if(modifier_Request == "Dexterity")
    {

    }
    else if(modifier_Request == "Constitution")
    {

    }
    else if(modifier_Request == "Intelligence")
    {

    }
    else if(modifier_Request == "Wisdom")
    {

    }
    else if(modifier_Request == "Charisma")
    {

    }
    else
    {

    }

    return modifier_int;
}

ServiceSemKirkels::player::~player()
{

}
