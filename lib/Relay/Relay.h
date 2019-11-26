#ifndef Relay_h
#define Relay_h

#include <Config.h>
#include <vector>

#define RELAY_ON LOW
#define RELAY_OFF HIGH
#define RELAY_DEFAULT_STATE HIGH

class Relay {
    public:
        Relay();
        void attach(u_int pin);
        uint8_t setState(uint8_t state);
        uint8_t getState();
        String getLastError();
    private: 
        uint8_t _pin;
        uint8_t _state;
        boolean _attached;
        String _operationError;
};

class Relays {
    public: 
        Relays();
        void init(const std::vector <uint8_t> relaysPins);
        uint8_t setStateOf(uint8_t relayNumb, uint8_t state);
        uint8_t getStateOf(uint8_t relayNumb);
        uint8_t getRelaysCount();
        String getLastError();
    private:
        String _operationError;
        std::vector<Relay> _relays;
        boolean _initializated;
        boolean _validateRelayNumber(int8_t relayNumb);
        int _relaysLen;
};

#endif

