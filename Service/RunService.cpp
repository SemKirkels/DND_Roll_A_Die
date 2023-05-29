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
        std::cout << "Running local" << std::endl;
        push.connect("tcp://localhost:24041");
        subscriber.connect("tcp://localhost:24042");
    }
    else
    {
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

ServiceSemKirkels::RunService::~RunService()
{
    std::cout << std::endl;
    std::cout << "Shutting down Service!" << std::endl;
    std::cout << "Bye" << std::endl;
}
