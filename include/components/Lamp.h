#ifndef LAMP_H
#define LAMP_H

#include <Arduino.h>

class Lamp
{
public:
    uint8_t pin;
    Lamp(uint8_t pin,uint8_t defaultVal): pin{pin} {
        pinMode(pin,OUTPUT);
        digitalWrite(pin,defaultVal);
    };

    void setValue(uint8_t value){
        digitalWrite(pin,value);
    };
};



#endif //LAMP_h