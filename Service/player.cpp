#include "player.h"

ServiceSemKirkels::player::player()
{

}

void ServiceSemKirkels::player::writeModifiers(QString playerName, QString modifierStr)
{
    std::ofstream inputFile;
    QString modifier_Arr[6];

    // Put all the modifiers in an array
    for(int i = 0; i < 6; i++)
    {
        modifier_Arr[i] = modifierStr.split(',').at(i);
    }

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    // Write Modifiers line by line
    for(int i = 0; i < 6; i++)
    {
        inputFile << modifier_Arr[i].toStdString().c_str() << "\r\n";
    }

    inputFile.close();
}

int ServiceSemKirkels::player::readModifiers(QString playerName, QString modifier_Request)
{
    std::ifstream inputFile;    // file handle

    // Append .txt for filename
    playerName.append(".txt");

    // Openfile
    inputFile.open(playerName.toStdString().c_str());

    std::vector<std::string> mod_Vector; // Stores all the lines of the file
    std::string mod_String; // Temp storage for each line

    // read the file line by line and put it in the vector
    while(std::getline(inputFile, mod_String))
    {
        mod_Vector.push_back(mod_String);
    }

    inputFile.close();

    // return the right modifier
    if(modifier_Request == "Strength")
    {
        return std::stoi(mod_Vector[0]);
    }
    else if(modifier_Request == "Dexterity")
    {
        return std::stoi(mod_Vector[1]);
    }
    else if(modifier_Request == "Constitution")
    {
        return std::stoi(mod_Vector[2]);
    }
    else if(modifier_Request == "Intelligence")
    {
        return std::stoi(mod_Vector[3]);
    }
    else if(modifier_Request == "Wisdom")
    {
        return std::stoi(mod_Vector[4]);
    }
    else if(modifier_Request == "Charisma")
    {
        return std::stoi(mod_Vector[5]);
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
            std::cout << "[Debug]: File opened"<< std::endl;
        }

        playerFile.close();
        return true;
    }
    else
    {
        // playerfile is not open
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug]: File not opened" << std::endl;
        }

        playerFile.close();
        return false;
    }
}

ServiceSemKirkels::player::~player()
{

}
