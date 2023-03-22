#include "runservice.h"

ServiceSemKirkels::RunService::RunService()
{

}

void ServiceSemKirkels::RunService::runService()
{
    try
    {
        // Declare Variables
        zmq::context_t context(1);
        zmq::message_t *msg = new zmq::message_t();

        zmq::socket_t push(context, ZMQ_PUSH);
        zmq::socket_t subscriber(context, ZMQ_SUB);

        // Connect sockets
        push.connect("tcp://localhost:24041");
        subscriber.connect("tcp://localhost:24042");
        //push.connect("tcp://benternet.pxl-ea-ict.be:24041");
        //subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");

        // Set Socket options
        subscriber.setsockopt(ZMQ_SUBSCRIBE, "Service>RPS!>", strlen("Service>RPS!>"));

        // Send / Receive phase
        push.send("Service>RPS?>Request", strlen("Service>RPS?>Request"));
        std::cout << "Pushed: Service>RPS?>Test" << std::endl;

        subscriber.recv(msg);
        std::cout << "Received: " << std::string((char*) msg->data(), msg->size()) << std::endl;
    }
    catch(zmq::error_t & ex)
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
}

ServiceSemKirkels::RunService::~RunService()
{

}
