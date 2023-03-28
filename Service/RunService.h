#ifndef RUNSERVICE_H
#define RUNSERVICE_H

#include <iostream>
#include <zmq.hpp>
#include <QString>
#include <QStringList>

#include "dice.h"

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

namespace ServiceSemKirkels
{
    class RunService
    {
        public:
            RunService();
            void runService();
            ~RunService();

        protected:
            void setupSockets(void);
            void handleMessage();

        private:
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;
    };
}

#endif // RUNSERVICE_H
