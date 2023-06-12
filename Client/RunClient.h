#ifndef RUNCLIENT_H
#define RUNCLIENT_H

#include <iostream>
#include <zmq.hpp>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "createplayer.h"
#include "defines.h"

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
            void setupSockets(void);                // Sets up the sub and push
            int createPlayer(void);                 // Lets the user enter a name and modifiers
            int selectModifier(void);               // Lets the user select the modifier used for the roll
            int selectDice(void);                   // Lets the user select the dice
            void handleSendMsg(void);               // Sends a message to the broker
            void handleRecvRoll(void);              // Receives the roll result and parces it
            void handleRecvExistingPlayer(void);    // Receives the reply to the question: "Does this player exist?"
            void checkExistingPlayer(void);         // Sends a request to find out if the player exists
            void clearTopic(void);                  // Clears the push topic and resets it to default
            void removePlayer();

            QString subTopic    = "Service>DICE!>"; // Client receives answer
            QString pushTopic   = "Service>DICE?>"; // Client asks question

        private:
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;

            QString playerName;
            QString requestMSG;
            QString recvExistingPlayer;
            QString recvAckCreatePlayer;

            CreatePlayer newPlayer;
    };
}
#endif // RUNCLIENT_H
