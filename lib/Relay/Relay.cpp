#include <Relay.h>
#include <Config.h>

Relay::Relay()
{
    _attached = false;
    _state = 0;
}

void Relay::attach(u_int pin)
{
    _pin = pin;
    _state = 0;
    _operationError = "";
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, RELAY_DEFAULT_STATE);
}

uint8_t Relay::setState(uint8_t state)
{
    if (state != 0 && state != 1)
    {
        _operationError = "Wrong state value should be 1 -ON, 0 - OFF";
        return -1;
    }
    if (state == 0)
    {
        digitalWrite(_pin, RELAY_OFF);
    }
    if (state == 1)
    {
        digitalWrite(_pin, RELAY_ON);
    }
    _state = state;
    _operationError = "";
#if _DBG_
    Serial.print("Set state of relay to: ");
    Serial.println(_state);
#endif
    return 0;
}

uint8_t Relay::getState()
{
    return _state;
}

String Relay::getLastError()
{
    return _operationError;
}

Relays::Relays()
{
    _operationError = "";
    _initializated = false;
    _relaysLen = 0;
}

void Relays::init(const std::vector <uint8_t> relaysPins)
{
    _relaysLen = relaysPins.size();
    for (uint8_t i = 0; i < _relaysLen; i++)
    {
        Relay relay;
        relay.attach(relaysPins[i]);
        _relays.push_back(relay);
    };
}

uint8_t Relays::setStateOf(uint8_t relayNumb, uint8_t state)
{
    if(!_validateRelayNumber(relayNumb)) {
        return -21;
    }
    int res = _relays[relayNumb - 1].setState(state);
    if (res < 0)
    {
        _operationError = _relays[relayNumb - 1].getLastError();
    }
    else
    {
        _operationError = "";
    }
    return res;
}

uint8_t Relays::getStateOf(uint8_t relayNumb)
{
    if(!_validateRelayNumber(relayNumb)) {
        return -21;
    }
    int res = _relays[relayNumb - 1].getState();
    if (res < 0)
    {
        _operationError = _relays[relayNumb - 1].getLastError();
    }
    else
    {
        _operationError = "";
    }
    return res;
}

String Relays::getLastError() {
    return _operationError;
}

boolean Relays::_validateRelayNumber(int8_t relayNumb) {
    if (relayNumb > _relaysLen)
    {
        _operationError = "Wrong value of relay number. Total installed:" + String(_relaysLen);
        return false;
    }
    if (relayNumb == 0)
    {
        _operationError = "Wrong value of relay number. Should be start from 1. Total installed:" + String(_relaysLen);
        return false;
    }
    return true;
}

uint8_t Relays::getRelaysCount() {
    return _relaysLen;
}