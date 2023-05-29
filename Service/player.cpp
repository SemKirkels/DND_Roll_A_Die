#include "player.h"

ServiceSemKirkels::player::player()
{

}

void ServiceSemKirkels::player::writeModifiers(QString playerName, QString modifierStr)
{
    std::ofstream inputFile;

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    // Write Modifiers
    inputFile << modifierStr.toStdString().c_str();
}

int ServiceSemKirkels::player::readModifiers(QString playerName, QString modifier_Request)
{
    std::ifstream inputFile;    // file handle

    char mod_char[6];           // Stores all the modifiers as char
    char bin;                   // Used as garbage bin

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    inputFile >> mod_char[0] >> bin >> mod_char[1] >> bin >> mod_char[2] >> bin >> mod_char[3] >> bin >> mod_char[4] >> bin >> mod_char[5];

    if(DEBUG_ENABLE == 1)
    {
        for(int i = 0; i < 6; i++)
        {
            std::cout << "[Debug]: Modifier[" << i << "]: " << mod_char[i] << std::endl;
        }
    }

    // return the right modifier
    if(modifier_Request == "Strength")
    {
        return (int)mod_char[0] - 48;
    }
    else if(modifier_Request == "Dexterity")
    {
        return (int)mod_char[1] - 48;
    }
    else if(modifier_Request == "Constitution")
    {
        return (int)mod_char[2] - 48;
    }
    else if(modifier_Request == "Intelligence")
    {
        return (int)mod_char[3] - 48;
    }
    else if(modifier_Request == "Wisdom")
    {
        return (int)mod_char[4] - 48;
    }
    else if(modifier_Request == "Charisma")
    {
        return (int)mod_char[5] - 48;
    }
    else
    {
        return 100;
    }
}

bool ServiceSemKirkels::player::checkExistingPlayer(QString Playername)
{
    QString filename;

    // Concat filename
    filename = Playername;
    filename.append(".txt");
    if(DEBUG_ENABLE == 1)
    {
        std::cout << "[Debug] filename: " << filename.toStdString().c_str() << std::endl;
    }

    // Open playerfile
    std::ifstream playerFile;
    playerFile.open(filename.toStdString().c_str());

    if(playerFile.is_open())
    {
        // playerfile is open
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug] File opened"<< std::endl;
        }

        playerFile.close();
        return true;
    }
    else
    {
        // playerfile is not open
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug] File not opened" << std::endl;
        }

        playerFile.close();
        return false;
    }
}

ServiceSemKirkels::player::~player()
{

}
