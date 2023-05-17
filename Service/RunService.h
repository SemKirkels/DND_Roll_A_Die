#ifndef RUNSERVICE_H
#define RUNSERVICE_H

#include <iostream>
#include <zmq.hpp>
#include <QString>
#include <QStringList>

#include "dice.h"
#include "player.h"

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
            void runService(void);
            ~RunService();

        protected:
            void setupSockets(void);
            void handleMessage(void);
            void handleRollRequest(void);
            void handleCreatePlayer(void);
            void handleExistingPlayer(QString Playername);

        private:
            QString subTopic    = "Service>DICE?>";
            QString pushTopic   = "Service>DICE!>";
            QString playerName  = "";
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;
            zmq::message_t *msg = new zmq::message_t();
    };
}

#endif // RUNSERVICE_H
