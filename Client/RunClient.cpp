#include "RunClient.h"

ClientSemKirkels::RunService::RunService() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Client" << std::endl;
}

void ClientSemKirkels::RunService::setupSockets()
{
    // Connect sockets
    push.connect("tcp://localhost:24041");
    subscriber.connect("tcp://localhost:24042");
    //push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    //subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "Service>DICE!>", strlen("Service>DICE!>"));
}

void ClientSemKirkels::RunService::menu()
{
    int input = 0;

    while(1)
    {
       std::cout << "Roll A Dice" << std::endl;
       std::cout << "1. D4" << std::endl;
       std::cout << "2. D6" << std::endl;
       std::cout << "3. D8" << std::endl;
       std::cout << "4. D10" << std::endl;
       std::cout << "5. D12" << std::endl;
       std::cout << "Select a dice: ";
       std::cin >> input;

       if(input < 1 || input > 5)
       {
           std::cout << "Invalid Input!" << std::endl;
           // Do noting
       }
       else
       {
           break;
       }
    }

    switch(input)
    {
        case 1:
            push.send("Service>DICE?>D4>", strlen("Service>DICE?>D4>"));
            std::cout << "Rolled a D4" << std::endl;
            break;
        case 2:
            push.send("Service>DICE?>D6>", strlen("Service>DICE?>D6>"));
            std::cout << "Rolled a D6" << std::endl;
            break;
        case 3:
            push.send("Service>DICE?>D8>", strlen("Service>DICE?>D8>"));
            std::cout << "Rolled a D8" << std::endl;
            break;
        case 4:
            push.send("Service>DICE?>D10>", strlen("Service>DICE?>D10>"));
            std::cout << "Rolled a D10" << std::endl;
            break;
        case 5:
            push.send("Service>DICE?>D10>", strlen("Service>DICE?>D10>"));
            std::cout << "Rolled a D10" << std::endl;
            break;
        default:
            break;
    }
}

void ClientSemKirkels::RunService::runService()
{
    try
    {
        // Declare Variables
        zmq::message_t *msg = new zmq::message_t();

        setupSockets();

        menu();

        subscriber.recv(msg);
        std::cout << "Received: " << std::string((char*) msg->data(), msg->size()) << std::endl;
    }
    catch(zmq::error_t &ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

ClientSemKirkels::RunService::~RunService()
{
    std::cout << std::endl;
    std::cout << "Shutting down client!" << std::endl;
    std::cout << "Bye" << std::endl;
}
