#include "RunService.h"

ServiceSemKirkels::RunService::RunService() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Service" << std::endl << std::endl;
}

void ServiceSemKirkels::RunService::runService()
{
    srand(time(NULL));

    try
    {
        // Setup sockets
        setupSockets();

        while(subscriber.connected())
        {
            // Handle incomming messages
            handleMessage();
        }
    }
    catch(zmq::error_t &ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

void ServiceSemKirkels::RunService::setupSockets()
{
    if(RUN_LOCAL == 1)
    {
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug]: Running local" << std::endl;
        }

        push.connect("tcp://localhost:24041");
        subscriber.connect("tcp://localhost:24042");
    }
    else
    {
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug]: Running online" << std::endl;
        }

        push.connect("tcp://benternet.pxl-ea-ict.be:24041");
        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
    }

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTopic.toStdString().c_str(), subTopic.length());
}

void ServiceSemKirkels::RunService::handleMessage()
{   
    // Send / Receive phase
    subscriber.recv(msg);

    if(DEBUG_ENABLE == 1)
    {
        // Print message (Debug)
        std::cout << "[Debug] Received: " << std::string((char*) msg->data(), msg->size()) << std::endl;
    }

    QString fullMSG((char *) msg->data());

    if(fullMSG.split('>').at(2) == "Roll")
    {
        std::cout << "Roll a dice" << std::endl;
        handleRollRequest(fullMSG.split('>').at(3));
    }
    else if(fullMSG.split('>').at(2) == "RegisterPlayer")
    {
        std::cout << "Create a player" << std::endl;
        handleCreatePlayer(fullMSG.split('>').at(3), fullMSG.split('>').at(4));
    }
    else if(fullMSG.split('>').at(2) == "ExistingPlayer")
    {
        std::cout << "Check player" << std::endl;
        handleExistingPlayer(fullMSG.split('>').at(3));
    }
    else if(fullMSG.split('>').at(2) == "DeletePlayer")
    {
        std::cout << "Delete a player" << std::endl;
        handleDeletePlayer(fullMSG.split('>').at(3));
    }
    else if(fullMSG.split('>').at(2) == "DC")
    {
        std::cout << "Difficulty check" << std::endl;
        handleDiffCheck();
    }
    else
    {
        std::cout << "Invalid Request!" << std::endl;
    }
}

void ServiceSemKirkels::RunService::handleRollRequest(QString Playername)
{
    // Declare Variables
    QString rollResult;
    QString concatMSG;
    ServiceSemKirkels::player newPlayer;
    ServiceSemKirkels::Dice newDice;
    int modifier_int = 0;

    // put msg in new QString
    QString fullMSG((char *) msg->data());
    QString rollRequest = fullMSG.split('>').at(5);
    QString modifier_str = fullMSG.split('>').at(4);

    // Read Modifiers from file
    modifier_int = newPlayer.readModifiers(Playername, modifier_str);

    if(DEBUG_ENABLE == 1)
    {
        // Print modifier (Debug)
        std::cout << "[Debug] Modifier: " << modifier_str.toStdString().c_str() << std::endl;
    }

    // Call different function for each dice
    if(rollRequest == "D4")
    {
        std::cout << "Received request for D4" << std::endl;
        rollResult.setNum(newDice.rollD4(modifier_int));
    }
    else if(rollRequest == "D6")
    {
        std::cout << "Received request for D6" << std::endl;
        rollResult.setNum(newDice.rollD6(modifier_int));
    }
    else if(rollRequest == "D8")
    {
        std::cout << "Received request for D8" << std::endl;
        rollResult.setNum(newDice.rollD8(modifier_int));
    }
    else if(rollRequest == "D10")
    {
        std::cout << "Received request for D10" << std::endl;
        rollResult.setNum(newDice.rollD10(modifier_int));
    }
    else if(rollRequest == "D12")
    {
        std::cout << "Received request for D12" << std::endl;
        rollResult.setNum(newDice.rollD12(modifier_int));
    }
    else if(rollRequest == "D20")
    {
        std::cout << "Received request for D20" << std::endl;
        rollResult.setNum(newDice.rollD20(modifier_int));
    }
    else
    {
        std::cout << rollRequest.toStdString() << " is an invalid Request" << std::endl;
    }

    // Print result
    std::cout << "Rolled a: " << rollResult.toStdString().c_str() << std::endl;

    // Construct string to push
    concatMSG.append(pushTopic);
    concatMSG.append(Playername);
    concatMSG.append(">");
    concatMSG.append(rollResult);
    concatMSG.append(">");

    // Push result
    push.send(concatMSG.toStdString().c_str(), concatMSG.length());
}

void ServiceSemKirkels::RunService::handleCreatePlayer(QString Playername, QString modifierStr)
{
    QString concatMSG;
    ServiceSemKirkels::player newPlayer;

    // Write modifiers to file using player object
    newPlayer.writeModifiers(Playername, modifierStr);

    concatMSG.append(pushTopic);
    concatMSG.append(Playername);
    concatMSG.append(">");

    concatMSG.append("Reg_Player_Success>");

    push.send(concatMSG.toStdString().c_str(), concatMSG.length());
}

void ServiceSemKirkels::RunService::handleExistingPlayer(QString Playername)
{
    ServiceSemKirkels::player newPlayer;
    QString filename;
    QString concatMSG;

    // Append topic
    concatMSG.append(pushTopic);
    concatMSG.append(Playername);
    concatMSG.append(">");
    concatMSG.append("ExistingPlayer>");

    // Check if playerfile exists
    bool fileIsOpen = newPlayer.checkExistingPlayer(Playername);

    if(fileIsOpen == true)
    {
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug]: Player found!" << std::endl;
        }

        // append result
        concatMSG.append("Player_Found>");
    }
    else
    {
        if(DEBUG_ENABLE == 1)
        {
            std::cout << "[Debug]: Player not found!" << std::endl;
        }

        // append result
        concatMSG.append("Player_Not_Found>");
    }

    if(DEBUG_ENABLE == 1)
    {
        std::cout << "[Debug] send: " << concatMSG.toStdString().c_str() << std::endl;
    }
    push.send(concatMSG.toStdString().c_str(), concatMSG.length());
}

void ServiceSemKirkels::RunService::handleDeletePlayer(QString Playername)
{
    ServiceSemKirkels::player newPlayer;

    if(DEBUG_ENABLE == 1)
    {
        std::cout << "[Debug] Request received to remove player: " << Playername.toStdString().c_str() << std::endl;
    }

    newPlayer.deletePlayer(Playername);
}

void ServiceSemKirkels::RunService::handleDiffCheck()
{
    int numberOfPlayers = 0;
    int diff;
    QString diff_Str;
    QString numberOfPlayers_Str;
    QString DC_Input_MSG((char *) msg->data());
    QString Modifier_Req;
    QString Dice;

    QString message_Passed;
    QString message_Failed;

    message_Passed.append("Service>Dice!>DC>");
    message_Failed.append("Service>Dice!>DC>");

    // Parce all the data from the message
    diff_Str = DC_Input_MSG.split('>').at(3);
    diff = diff_Str.toInt();
    std::cout << "Difficulty: " << diff << std::endl;
    message_Passed.append(diff_Str);
    message_Passed.append(">");
    message_Failed.append(diff_Str);
    message_Failed.append(">");

    Modifier_Req = DC_Input_MSG.split('>').at(4);
    std::cout << "Modifier: " << Modifier_Req.toStdString().c_str() << std::endl;
    message_Passed.append(Modifier_Req);
    message_Passed.append(">");
    message_Failed.append(Modifier_Req);
    message_Failed.append(">");

    Dice = DC_Input_MSG.split('>').at(5);
    std::cout << "Dice: " << Dice.toStdString().c_str() << std::endl;

    numberOfPlayers_Str = DC_Input_MSG.split('>').at(6);
    numberOfPlayers = numberOfPlayers_Str.toInt();
    std::cout << "Number of players: " << numberOfPlayers << std::endl;

    message_Passed.append("Succes");
    message_Passed.append(">");
    message_Failed.append("Fail");
    message_Failed.append(">");

    // Create variables that store all the names, results, modifiers, ...
    QString playerResults_Str[numberOfPlayers]; // Saves the rolled result in str
    int playerResults[numberOfPlayers]; // Saves the rolled result in int
    int modifier[numberOfPlayers]; // Saves the modifier of the player
    ServiceSemKirkels::Dice newDice[numberOfPlayers]; // Creates a dice object for each player
    ServiceSemKirkels::player newPlayer[numberOfPlayers]; // Creates a player object for each player
    QString playerNames[numberOfPlayers]; // Saves the names of the players

    // put all the playernames in an array
    for(int i = 0; i < numberOfPlayers; i++)
    {
        playerNames[i] = DC_Input_MSG.split('>').at(7 + i);
    }

    // read the selected modifier for all the players
    for(int i = 0; i < numberOfPlayers; i++)
    {
        modifier[i] = newPlayer[i].readModifiers(playerNames[i], Modifier_Req);
    }

    // throw the dice with modifier for each player
    for(int i = 0; i < numberOfPlayers; i++)
    {
        // Call different function for each dice
        if(Dice == "D4")
        {
            playerResults[i] = newDice[i].rollD4(modifier[i]);
        }
        else if(Dice == "D6")
        {
            playerResults[i] = newDice[i].rollD6(modifier[i]);
        }
        else if(Dice == "D8")
        {
            playerResults[i] = newDice[i].rollD8(modifier[i]);
        }
        else if(Dice == "D10")
        {
            playerResults[i] = newDice[i].rollD10(modifier[i]);
        }
        else if(Dice == "D12")
        {
            playerResults[i] = newDice[i].rollD12(modifier[i]);
        }
        else if(Dice == "D20")
        {
            playerResults[i] = newDice[i].rollD20(modifier[i]);
        }
        else
        {
            std::cout << Dice.toStdString() << " is an invalid Request" << std::endl;
        }

        // Print result
        std::cout << "Rolled a: " << playerResults[i] << std::endl;

        playerResults_Str[i].setNum(playerResults[i]);
    }

    // Check if each player has passed the diff check
    for(int i = 0; i < numberOfPlayers; i++)
    {
        if(playerResults[i] > diff)
        {
            message_Passed.append(playerNames[i]);
            message_Passed.append(": ");
            message_Passed.append(playerResults_Str[i]);
            message_Passed.append(">");
        }
        else
        {
            message_Failed.append(playerNames[i]);
            message_Failed.append(": ");
            message_Failed.append(playerResults_Str[i]);
            message_Failed.append(">");
        }
    }

    std::cout << "[Debug] send: " << message_Passed.toStdString().c_str() << std::endl;
    std::cout << "[Debug] send: " << message_Failed.toStdString().c_str() << std::endl;

    push.send(message_Passed.toStdString().c_str(), message_Passed.length());
    push.send(message_Failed.toStdString().c_str(), message_Failed.length());
}

ServiceSemKirkels::RunService::~RunService()
{
    std::cout << std::endl;
    std::cout << "Shutting down Service!" << std::endl;
    std::cout << "Bye" << std::endl;
}
