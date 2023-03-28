#ifndef RUNCLIENT_H
#define RUNCLIENT_H

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

/*
 * Service>DICE?> -> Client to Service
 * Service>DICE!> -> Service to Client
 */

namespace ClientSemKirkels
{
    class RunService
    {
        public:
            RunService();
            void runService();
            ~RunService();

        protected:
            void setupSockets(void);
            void menu(void);

        private:
            QString subTopic    = "Service>DICE!>"; // Client receives answer
            QString pushTopic   = "Service>DICE?>"; // Client asks question
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;
    };
}
#endif // RUNCLIENT_H
