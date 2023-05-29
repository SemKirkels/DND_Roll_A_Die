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
            int runService();
            ~RunClient();

        protected:
            void setupSockets(void);
            void createPlayer(void);
            int selectModifier(void);
            int selectDice(void);
            void handleSendMsg(void);
            void handleRecvRoll(void);
            void handleRecvExistingPlayer(void);
            void clearTopic(void);

        private:
            QString subTopic    = "Service>DICE!>"; // Client receives answer
            QString pushTopic   = "Service>DICE?>"; // Client asks question

            zmq::message_t *msg_Roll_Result = new zmq::message_t();
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;

            QString playerName;
            QString requestMSG;
            QString recvExistingPlayer;

            CreatePlayer newPlayer;
    };
}
#endif // RUNCLIENT_H
