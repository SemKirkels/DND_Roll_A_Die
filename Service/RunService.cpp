#include "RunService.h"

ServiceSemKirkels::RunService::RunService() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Service" << std::endl << std::endl;
}

void ServiceSemKirkels::RunService::setupSockets()
{
    // Connect sockets
    push.connect("tcp://localhost:24041");
    subscriber.connect("tcp://localhost:24042");
    //push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    //subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "Service>DICE?>", strlen("Service>DICE?>"));
}

void ServiceSemKirkels::RunService::handleMessage()
{
    // Declare Variables
    zmq::message_t *msg = new zmq::message_t();
    Dice newDice;

    // Send / Receive phase
    subscriber.recv(msg);
    std::cout << "Roll: " << std::string((char*) msg->data(), msg->size()) << std::endl;

    // put msg in new QString
    QString fullMessage((char *) msg->data());
    QString rollRequest = fullMessage.split('>').at(2);

    if(rollRequest == "D4")
    {
        std::cout << "Received request for D4" << std::endl;
        // Call rollD4
        newDice.rollD4();
    }
    else if(rollRequest == "D6")
    {
        std::cout << "Received request for D6" << std::endl;
        // Call rollD6
        newDice.rollD6();
    }
    else if(rollRequest == "D8")
    {
        std::cout << "Received request for D8" << std::endl;
        // Call rollD8
        newDice.rollD8();
    }
    else if(rollRequest == "D10")
    {
        std::cout << "Received request for D10" << std::endl;
        // Call rollD10
        newDice.rollD10();
    }
    else if(rollRequest == "D12")
    {
        std::cout << "Received request for D12" << std::endl;
        // Call rollD12
        newDice.rollD12();
    }
    else
    {
        std::cout << rollRequest.toStdString() << " is an invalid Request" << std::endl;
    }
}

void ServiceSemKirkels::RunService::runService()
{
    try
    {
        setupSockets();

        handleMessage();

        push.send("Service>DICE!>Result", strlen("Service>DICE!>Result"));
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
