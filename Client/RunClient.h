#ifndef RUNCLIENT_H
#define RUNCLIENT_H

#include <iostream>
#include <zmq.hpp>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "createplayer.h"

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
    class RunClient
    {
        public:
            RunClient();
            void runService();
            ~RunClient();

        protected:
            void setupSockets(void);
            void createPlayer(void);
            void selectDice(void);

        private:
            QString subTopic    = "Service>DICE!>"; // Client receives answer
            QString pushTopic   = "Service>DICE?>"; // Client asks question
            zmq::message_t *msg = new zmq::message_t();
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;
            QString playerName;
            QString requestMSG;
            CreatePlayer newPlayer;
    };
}
#endif // RUNCLIENT_H
