#include "RunClient.h"

ClientSemKirkels::RunClient::RunClient() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Client" << std::endl;
}

void ClientSemKirkels::RunClient::runService()
{
    try
    {
        // Declare Variables
        int input = 0;

        while(push.connected())
        {
            // Setup socket
            setupSockets();

            while(1)
            {
                std::cout << "1. Create a player" << std::endl;
                std::cout << "2. Roll a dice" << std::endl;
                std::cout << "3. Exit" << std::endl;
                std::cout << "Select an option: ";
                std::cin >> input;

                if(input == 1)
                {
                    // Create player
                    createPlayer();
                }
                else if(input == 2)
                {
                    if(playerName.isEmpty())
                    {
                        std::cout << "Enter a charactername: " << std::endl;
                        std::string inputString;
                        std::cin >> inputString;
                        playerName = QString(inputString.c_str());

                        // Message looks like this: Service>DICE?>ExistingPlayer>Playername>
                        // Find out if player file exists
                        requestMSG.append("ExistingPlayer>");
                        requestMSG.append(playerName);
                        requestMSG.append(">");

                        // Send msg

                        // Message looks like this: Service>DICE?>
                        // Clear requestMSG
                        requestMSG = "";
                        requestMSG.append(pushTopic);
                        // Wait for server reply if the playerfile is available

                        // If playerfile is not available create one
                        QString result = recvExistingPlayer.split('>').at(3);
                        if(result == "Player_Not_Found")
                        {
                            std::cout << "Player not found" << std::endl;
                            std::cout << "Create a new player" << std::endl;

                            createPlayer();
                        }
                    }

                    requestMSG.append("Roll>");

                    requestMSG.append(playerName);
                    requestMSG.append(">");

                    // Select Modifier
                    selectModifier();

                    // Select Dice
                    selectDice();

                    // Send Message
                    handleSendRoll();

                    // Receive Message
                    handleRecvRoll();
                }
                else if(input == 3)
                {
                    exit(1);
                }
                else
                {
                    std::cout << "Invalid input!" << std::endl;
                }

                // Clear the requestMSG after each send.
                requestMSG = "";
                requestMSG.append(pushTopic);
            }
        }
    }
    catch(zmq::error_t &ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

void ClientSemKirkels::RunClient::setupSockets()
{
    // Connect sockets
    //push.connect("tcp://localhost:24041");
    //subscriber.connect("tcp://localhost:24042");
    push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTopic.toStdString().c_str(), subTopic.length());

    requestMSG.append(pushTopic);
}

void ClientSemKirkels::RunClient::createPlayer()
{
    newPlayer.enterPlayerName();
    playerName = newPlayer.getPlayerName();

    // Message looks like this: Service>DICE?>RegisterPlayer>
    requestMSG.append("RegisterPlayer");
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>
    requestMSG.append(newPlayer.getPlayerName());
    requestMSG.append(">");

    // Enter all the modifiers
    newPlayer.enterModifiers();

    // Put the modifiers in one string
    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>
    requestMSG.append(newPlayer.getStrength());
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>Dexterity>
    requestMSG.append(newPlayer.getDexterity());
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>Dexterity>Constitution>
    requestMSG.append(newPlayer.getConstitution());
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>Dexterity>Constitution>Intelligence>
    requestMSG.append(newPlayer.getIntelligence());
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>Dexterity>Constitution>Intelligence>Wisdom>
    requestMSG.append(newPlayer.getWisdom());
    requestMSG.append(">");

    // Message looks like this: Service>DICE?>RegisterPlayer>PlayerName>Strength>Dexterity>Constitution>Intelligence>Wisdom>Charisma
    requestMSG.append(newPlayer.getCharisma());
    requestMSG.append(">");

    // Send the string
    push.send(requestMSG.toStdString().c_str(), requestMSG.length());
    std::cout << std::endl;
}

void ClientSemKirkels::RunClient::selectModifier()
{
    int input = 0;

    // Message looks like this: Service>DICE?>Roll>PlayerName>Modifier>
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
       std::cout << "7. Exit" << std::endl;
       std::cout << "Select a modifier: ";
       std::cin >> input;

       if(input < 1 || input > 7)
       {
           std::cout << "Invalid Input!" << std::endl << std::endl;
           // Do noting
       }
       else if(input == 7)
       {
           exit(1);
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
            requestMSG.append("Strength>");
            std::cout << "Requested Strength" << std::endl;
            break;
        case 2:
            requestMSG.append("Dexterity>");
            std::cout << "Requested Dexterity" << std::endl;
            break;
        case 3:
            requestMSG.append("Constitution>");
            std::cout << "Requested Constitution" << std::endl;
            break;
        case 4:
            requestMSG.append("Intelligence>");
            std::cout << "Requested Intelligence" << std::endl;
            break;
        case 5:
            requestMSG.append("Wisdom>");
            std::cout << "Requested Wisdom" << std::endl;
            break;
        case 6:
            requestMSG.append("Charisma>");
            std::cout << "Requested Charisma" << std::endl;
            break;
        default:
            break;
    }
}

void ClientSemKirkels::RunClient::selectDice()
{
    int input = 0;

    // Message looks like this: Service>DICE?>ROLL>PlayerName>Modifier>Dice>
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
       std::cout << "7. Exit" << std::endl;
       std::cout << "Select a dice: ";
       std::cin >> input;

       if(input < 1 || input > 7)
       {
           std::cout << "Invalid Input!" << std::endl << std::endl;
           // Do noting
       }
       else if(input == 7)
       {
           exit(1);
       }
       else
       {
           break;
       }
    }

    // Message looks like this: Service>DICE?>ROLL>PlayerName>Modifier>Dice>
    // Switch case to concat requestMSG
    switch(input)
    {
        case 1:
            requestMSG.append("D4>");
            std::cout << "Requested a D4" << std::endl;
            break;
        case 2:
            requestMSG.append("D6>");
            std::cout << "Requested a D6" << std::endl;
            break;
        case 3:
            requestMSG.append("D8>");
            std::cout << "Requested a D8" << std::endl;
            break;
        case 4:
            requestMSG.append("D10>");
            std::cout << "Requested a D10" << std::endl;
            break;
        case 5:
            requestMSG.append("D12>");
            std::cout << "Requested a D12" << std::endl;
            break;
        case 6:
            requestMSG.append("D20>");
            std::cout << "Requested a D20" << std::endl;
            break;
        default:
            break;
    }
}

void ClientSemKirkels::RunClient::handleSendRoll()
{
    // Send request to service
    push.send(requestMSG.toStdString().c_str(), requestMSG.length());
    std::cout << std::endl;
}

void ClientSemKirkels::RunClient::handleRecvRoll()
{
    // Receive message
    subscriber.recv(msg_Roll_Result);

    if(DEBUG_ENABLE == 1)
    {
        // Print message (Debug)
        std::cout << "[Debug] Received:" << std::string((char*) msg_Roll_Result->data(), msg_Roll_Result->size()) << std::endl;
    }

    // Convert message type
    QString fullMessage((char *) msg_Roll_Result->data()); // Convert ZMQ message to QString
    QString result = fullMessage.split('>').at(2);

    // Print message
    std::cout << "You rolled a: " << result.toStdString().c_str() << std::endl;
}

void ClientSemKirkels::RunClient::handleRecvExistingPlayer()
{
    zmq::message_t *msg_Existing_Player = new zmq::message_t();

    // Receive message
    subscriber.recv(msg_Existing_Player);

    if(DEBUG_ENABLE == 1)
    {
        // Print message (Debug)
        std::cout << "[Debug] Received:" << std::string((char*) msg_Existing_Player->data(), msg_Existing_Player->size()) << std::endl;
    }

    // Convert message type
    recvExistingPlayer((char *) msg_Existing_Player->data()); // Convert ZMQ message to QString
}

ClientSemKirkels::RunClient::~RunClient()
{
    std::cout << std::endl;
    std::cout << "Shutting down client!" << std::endl;
    std::cout << "Bye" << std::endl;
}
