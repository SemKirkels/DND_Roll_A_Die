#include <iostream>
#include <zmq.hpp>
#include <QString>
#include <QStringList>

#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
    #define sleep(n)    Sleep(n)
#endif

int main(void)
{
    try
    {
        zmq::context_t context(1);
        zmq::message_t *msg = new zmq::message_t();

        zmq::socket_t push(context, ZMQ_PUSH);
        zmq::socket_t subscriber(context, ZMQ_SUB);

        push.connect("tcp://benternet.pxl-ea-ict.be:24041");
        subscriber.connect("tcp://benternet.pxl-ea-ict.be:24042");
    }
    catch(zmq::error_t & ex)
    {

    }

    return 0;
}
