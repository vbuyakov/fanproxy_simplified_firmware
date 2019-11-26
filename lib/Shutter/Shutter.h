#ifndef Shutter_h
#define Shutter_h

#include <Config.h>
#include <Servo.h>
#include <vector>


#define MIN_ANGLE 0
#define MAX_ANGLE 90

class Shutter 
{
    public:
    Shutter();
    void attach(u_int pin);
    int setPosition(int pos);
    String getLastError();
    private:
    uint8_t _pin;
    uint8_t _min_angle;
    uint8_t _max_angle;
    String _operationError;
    Servo _servo;
    boolean _attached;
};


class Shutters
{
    public: 
    Shutters();
    void init(const std::vector <uint8_t> shuttersPins);
    int setPostionOf(uint8_t shutterNumb, int pos);
    String getLastError();
    private:
    String _operationError;
    std::vector<Shutter> _shutters;
    boolean _initializated;
    int _shuttersLen;
};

#endif
