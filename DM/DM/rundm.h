#ifndef RUNDM_H
#define RUNDM_H

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

namespace SemKirkels
{
    class RunDM
    {
        public:
            RunDM();
            void Run_DM_Main(void);
            void SelectModifier(void);
            void selectDice(void);
            void enterPlayers(void);
            void sendMessage(void);
            void recvMessage(void);
            ~RunDM();

        protected:
            void setupSockets(void);

        private:
            QString subTopic    = "Service>DICE!>DC>";
            QString pushTopic   = "Service>DICE?>DC>";
            QString message     = "";
            zmq::context_t context;
            zmq::socket_t push;
            zmq::socket_t subscriber;
            zmq::message_t *msg = new zmq::message_t();
    };
}
#endif // RUNDM_H
