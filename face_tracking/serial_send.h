#ifndef SERIAL_SEND_H_INCLUDED
#define SERIAL_SEND_H_INCLUDED
#include <string>
using namespace std;
class SerialSend
{
    public:
        SerialSend(const string &port)
        {
            file = fopen(port.c_str(), "w");
        }
        void send(int servoID,int angle)
        {
            fprintf(file, "%d%d\n",servoID,angle);

        }
        ~SerialSend()
        {
            if(file!=NULL)
                fclose(file);
        }
    private:
        FILE *file;

};


#endif // SERIAL_SEND_H_INCLUDED
