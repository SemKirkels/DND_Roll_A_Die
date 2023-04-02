#include "RunClient.h"

ClientSemKirkels::RunClient::RunClient() : context(1), push(context, ZMQ_PUSH), subscriber(context, ZMQ_SUB)
{
    std::cout << "Starting Client" << std::endl;
}

void ClientSemKirkels::RunClient::setupSockets()
{
    // Connect sockets
    push.connect("tcp://localhost:24041");
    subscriber.connect("tcp://localhost:24042");
    //push.connect("tcp://benternet.pxl-ea-ict.be:24041");
    //subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

    // Set Socket options
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTopic.toStdString().c_str(), subTopic.length());
}

void ClientSemKirkels::RunClient::menu()
{
    int input = 0;
    QString requestMSG;

    requestMSG.append(pushTopic);

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
       else if(input == 6)
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

    // Send request to service

    push.send(requestMSG.toStdString().c_str(), requestMSG.length());
    std::cout << std::endl;
}

void ClientSemKirkels::RunClient::runService()
{
    try
    {
        // Declare Variables
        zmq::message_t *msg = new zmq::message_t();

        while(push.connected())
        {
            // Setup socket
            setupSockets();

            // Enter menu and send message
            menu();

            // Receive message
            subscriber.recv(msg);

            // Print message (Debug)
            std::cout << "[Debug] Received:" << std::string((char*) msg->data(), msg->size()) << std::endl;

            // Convert message type
            QString fullMessage((char *) msg->data()); // Convert ZMQ message to QString
            QString result = fullMessage.split('>').at(2);

            // Print message
            std::cout << "You rolled a: " << result.toStdString().c_str() << std::endl;
        }
    }
    catch(zmq::error_t &ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

ClientSemKirkels::RunClient::~RunClient()
{
    std::cout << std::endl;
    std::cout << "Shutting down client!" << std::endl;
    std::cout << "Bye" << std::endl;
}
