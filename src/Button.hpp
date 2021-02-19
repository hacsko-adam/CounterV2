#ifndef FOOP_H
#define FOOP_H
#include <Arduino.h>

class Button
{
    int buttonPin;
    int btnCurrentVal;
    int btnLastVal;
    unsigned long downStart;
public:
    Button(int pin){
        this->buttonPin = pin;
        pinMode(this->buttonPin, INPUT);
        btnCurrentVal = LOW;
        btnLastVal = LOW;
    }

    int checkButton() 
    {   
        int event = 0;
        btnCurrentVal = digitalRead(this->buttonPin);
        if(btnLastVal == LOW && btnCurrentVal == HIGH)
        {
            downStart = millis();
        }
        if(btnLastVal == HIGH && btnCurrentVal == LOW)
        {
            if(millis() - downStart < 500)
            {
                event = 1;
            }
            else
            {
                if(millis() - downStart < 3000)
                {
                    event = 2;
                }
                else if(millis()-downStart < 10000)
                {
                    event = 3;
                }
            }
        }

        btnLastVal = btnCurrentVal;
        return event;
    }
};
#endif