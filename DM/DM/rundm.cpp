#include "rundm.h"

SemKirkels::RunDM::RunDM(): context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{

}

void SemKirkels::RunDM::setupSockets()
{
    push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTopic.toStdString().c_str(), subTopic.length());
}

void SemKirkels::RunDM::Run_DM_Main()
{
    int Diff = 0;
    QString Diff_Str;

    setupSockets();

    while(push.connected())
    {
        while(1)
        {
            std::cout << "Enter a difficulty [0 - 100]: ";
            std::cin >> Diff;
            std::cout << std::endl;

            if(Diff >= 0 && Diff <= 100)
            {
                // Message looks like this: Service>Dice?>DC>Diff>
                Diff_Str.setNum(Diff);
                message.append(pushTopic);
                message.append(Diff_Str);
                message.append(">");

                break;
            }
            else
            {
                std::cout << "Invalid input!" << std::endl;
            }
        }

        SelectModifier();

        selectDice();

        enterPlayers();

        sendMessage();

        recvMessage();
        recvMessage();

        std::cout << std::endl;
    }
}

void SemKirkels::RunDM::SelectModifier()
{
    int input = 0;

    // Message looks like this: Service>DICE?>DC>Modifier>
    // Menu to select modifier
    while(1)
    {
        std::cout << "Modifiers " << std::endl;
        std::cout << "1. Strength" << std::endl;
        std::cout << "2. Dexterity" << std::endl;
        std::cout << "3. Constitution" << std::endl;
        std::cout << "4. Intelligence" << std::endl;
        std::cout << "5. Wisdom" << std::endl;
        std::cout << "6. Charisma" << std::endl;
        std::cout << "Select a modifier: ";
        std::cin >> input;

        if(input < 1 || input > 7)
        {
           std::cout << "Invalid Input!" << std::endl << std::endl;
           // Do noting
        }
        else
        {
            break;
        }
    }

    // Switch case to concat requestMSG
    switch(input)
    {
        case 1:
            message.append("Strength>");
            std::cout << "Requested Strength" << std::endl;
            break;
        case 2:
            message.append("Dexterity>");
            std::cout << "Requested Dexterity" << std::endl;
            break;
        case 3:
            message.append("Constitution>");
            std::cout << "Requested Constitution" << std::endl;
            break;
        case 4:
            message.append("Intelligence>");
            std::cout << "Requested Intelligence" << std::endl;
            break;
        case 5:
            message.append("Wisdom>");
            std::cout << "Requested Wisdom" << std::endl;
            break;
        case 6:
            message.append("Charisma>");
            std::cout << "Requested Charisma" << std::endl;
            break;
        default:
            break;
    }

    std::cout << std::endl;
}

void SemKirkels::RunDM::selectDice()
{
    int input = 0;

    // Message looks like this: Service>DICE?>DC>Modifier>Dice>
    // Menu to select dice

    while(1)
    {
       std::cout << "Roll A Dice" << std::endl;
       std::cout << "1. D4" << std::endl;
       std::cout << "2. D6" << std::endl;
       std::cout << "3. D8" << std::endl;
       std::cout << "4. D10" << std::endl;
       std::cout << "5. D12" << std::endl;
       std::cout << "6. D20" << std::endl;
       std::cout << "Select a dice: ";
       std::cin >> input;

        if(input < 1 || input > 7)
        {
            std::cout << "Invalid Input!" << std::endl << std::endl;
            // Do noting
        }
        else
        {
            break;
        }
    }

    // Message looks like this: Service>DICE?>DC>Modifier>Dice>
    // Switch case to concat message
    switch(input)
    {
        case 1:
            message.append("D4>");
            std::cout << "Requested a D4" << std::endl;
            break;
        case 2:
            message.append("D6>");
            std::cout << "Requested a D6" << std::endl;
            break;
        case 3:
            message.append("D8>");
            std::cout << "Requested a D8" << std::endl;
            break;
        case 4:
            message.append("D10>");
            std::cout << "Requested a D10" << std::endl;
            break;
        case 5:
            message.append("D12>");
            std::cout << "Requested a D12" << std::endl;
            break;
        case 6:
            message.append("D20>");
            std::cout << "Requested a D20" << std::endl;
            break;
        default:
            break;
    }

    std::cout << std::endl;
}

void SemKirkels::RunDM::enterPlayers()
{
    int numberOfPlayers = 0;
    QString numberOfPlayers_Str;

    while(1)
    {
        std::cout << "Enter the number of players [1 - 100]" << std::endl;
        std::cin >> numberOfPlayers;

        if(numberOfPlayers > 0 && numberOfPlayers <= 100)
        {
            // Message looks like this: Service>DICE?>DC>Modifier>Dice>numberOfPlayers>
            numberOfPlayers_Str.setNum(numberOfPlayers);
            message.append(numberOfPlayers_Str);
            message.append(">");

            break;
        }
        else
        {
            std::cout << "Invalid input" << std::endl;
        }
    }

    QString playerNames[numberOfPlayers];

    for(int i = 0; i < numberOfPlayers; i++)
    {
        std::string inputString;

        std::cout << "Enter a charactername: " << std::endl;
        std::cin >> inputString;
        playerNames[i] = (QString(inputString.c_str()));
    }

    for(int i = 0; i < numberOfPlayers; i++)
    {
        std::cout << "Player[" << i << "]: " << playerNames[i].toStdString().c_str() << std::endl;
    }

    for(int i = 0; i < numberOfPlayers; i++)
    {
        message.append(playerNames[i]);
        message.append(">");
    }

    std::cout << std::endl;
    std::cout << "Message: " << message.toStdString().c_str() << std::endl;
    std::cout << std::endl;
}

void SemKirkels::RunDM::sendMessage()
{
    push.send(message.toStdString().c_str(), message.length());
    std::cout << std::endl;
}

void SemKirkels::RunDM::recvMessage()
{
    zmq::message_t *msg_Result = new zmq::message_t();

    // Receive message
    subscriber.recv(msg_Result);
    std::cout << "[Debug] Received:" << std::string((char*) msg_Result->data(), msg_Result->size()) << std::endl;
}

SemKirkels::RunDM::~RunDM()
{

}


