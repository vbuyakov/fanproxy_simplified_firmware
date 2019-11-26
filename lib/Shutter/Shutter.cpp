#include <Shutter.h>

Shutter::Shutter() {
    _min_angle = MIN_ANGLE;
    _max_angle = MAX_ANGLE;
    _attached = false;
    _operationError = "";
}

void Shutter::attach(u_int pin) {
    _servo.attach(pin);
    _attached = true;
}

int Shutter::setPosition(int pos) {
    if(! _attached ) {
        _operationError = "Shutter not initialized";
        return -1;
    } 
    if( pos < _min_angle || pos > _max_angle) {
        _operationError = "Out of range - min: " + String(_min_angle) + " max: " + String(_max_angle);
        return -2;
    }
    _servo.write(pos);
    _operationError = "";
    #if _DBG_
        Serial.print("Set shutter posintion to: ");
        Serial.println(pos);
    #endif
    return 0;
}

String Shutter::getLastError() {
    return _operationError;
}
/// Shutters
    Shutters::Shutters() {
        _operationError = "";
        _initializated = false;
        _shuttersLen = 0;
    }

    void Shutters::init(const std::vector <uint8_t> shuttersPins) {
        _shuttersLen = shuttersPins.size();
        for(uint8_t i = 0 ; i < _shuttersLen ; i++ ) {
            Shutter shutter;
            shutter.attach(shuttersPins[i]);
            _shutters.push_back(shutter);
        }
    }
    int Shutters::setPostionOf(uint8_t shutterNumb, int pos) {
        if(shutterNumb > _shuttersLen) {
            _operationError = "Wrong value of shutter number. Total installed:" + String(_shuttersLen);
            return -11;
        }
        if(shutterNumb == 0)
        {
            _operationError = "Wrong value of shutter number. Should be start from 1. Total installed:" + String(_shuttersLen);
            return -11;
        }
        int res = _shutters[shutterNumb -1].setPosition(pos);
        if(res < 0) {
            _operationError = _shutters[shutterNumb -1].getLastError();
        } else {
            _operationError = "";
        }
        return res;
    }

    String Shutters::getLastError() {
        return _operationError;
    }