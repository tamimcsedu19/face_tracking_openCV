#ifndef SERIAL_SENDER_H
#define SERIAL_SENDER_H
#include <bits/stdc++.h>
using namespace std;

class serial_sender
{
    public:
        serial_sender(const string &port)
        {
            file = fopen(port.c_str(), "w");
        }
        void send(int servoID,int angle)
        {
            if(file == NULL)
                return;
            fprintf(file, "%d%d\n",servoID,angle);

        }
        ~serial_sender()
        {
            if(file!=NULL)
                fclose(file);
        }
    private:
        FILE *file;

};
#endif // SERIAL_SENDER_H
