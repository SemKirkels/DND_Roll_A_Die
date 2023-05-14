#include "RunService.h"

ServiceSemKirkels::RunService::RunService() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Service" << std::endl << std::endl;
}

void ServiceSemKirkels::RunService::setupSockets()
{
    // Connect sockets
    //push.connect("tcp://localhost:24041");
    //subscriber.connect("tcp://localhost:24042");
    push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTopic.toStdString().c_str(), subTopic.length());
}

void ServiceSemKirkels::RunService::handleMessage()
{
    // Declare Variables
    QString rollResult;
    QString concatMSG;
    Dice newDice;
    zmq::message_t *msg = new zmq::message_t();
    int modifier_int = 0;

    // Send / Receive phase
    subscriber.recv(msg);

    // Print message (Debug)
    std::cout << "[Debug] Received: " << std::string((char*) msg->data(), msg->size()) << std::endl;

    // put msg in new QString
    QString fullMSG((char *) msg->data());
    QString rollRequest = fullMSG.split('>').at(2);
    QString modifier_str = fullMSG.split('>').at(3);

    modifier_int = modifier_str.toInt();

    // Print modifier (Debug)
    std::cout << "[Debug] Modifier: " << modifier_str.toStdString().c_str() << std::endl;

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
    concatMSG.append(rollResult);
    concatMSG.append(">");

    // Push result
    push.send(concatMSG.toStdString().c_str(), concatMSG.length());
}

void ServiceSemKirkels::RunService::runService()
{
    srand(time(NULL));

    try
    {
        while(subscriber.connected())
        {
            // Setup sockets
            setupSockets();

            // Handle incomming messages
            handleMessage();
        }
    }
    catch(zmq::error_t &ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

ServiceSemKirkels::RunService::~RunService()
{
    std::cout << std::endl;
    std::cout << "Shutting down Service!" << std::endl;
    std::cout << "Bye" << std::endl;
}
