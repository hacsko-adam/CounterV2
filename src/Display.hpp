#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include "MaxMatrix.h"
#include <SPI.h>


MaxMatrix m(13, 4, 14, 4); 

class Display
{
public:
    void write(int display, int number){
        int indexMax = (display*8)-1;
        switch (number)
        {
        case 0:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,60);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,110);
            m.setColumn(indexMax-4,126);
            m.setColumn(indexMax-5,118);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,60);
            break;
        case 1:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,24);
            m.setColumn(indexMax-2,28);
            m.setColumn(indexMax-3,24);
            m.setColumn(indexMax-4,24);
            m.setColumn(indexMax-5,24);
            m.setColumn(indexMax-6,24);
            m.setColumn(indexMax-7,126);
            break;
        case 2:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,60);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,96);
            m.setColumn(indexMax-4,56);
            m.setColumn(indexMax-5,12);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,126);
            break;
        case 3:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,60);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,96);
            m.setColumn(indexMax-4,56);
            m.setColumn(indexMax-5,96);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,60);
            break;
        case 4:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,112);
            m.setColumn(indexMax-2,120);
            m.setColumn(indexMax-3,108);
            m.setColumn(indexMax-4,102);
            m.setColumn(indexMax-5,254);
            m.setColumn(indexMax-6,96);
            m.setColumn(indexMax-7,240);
            break;
        case 5:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,126);
            m.setColumn(indexMax-2,6);
            m.setColumn(indexMax-3,62);
            m.setColumn(indexMax-4,96);
            m.setColumn(indexMax-5,96);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,60);
            break;
        case 6: 
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,56);
            m.setColumn(indexMax-2,12);
            m.setColumn(indexMax-3,6);
            m.setColumn(indexMax-4,62);
            m.setColumn(indexMax-5,102);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,60);
            break;
        case 7:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,126);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,96);
            m.setColumn(indexMax-4,48);
            m.setColumn(indexMax-5,24);
            m.setColumn(indexMax-6,24);
            m.setColumn(indexMax-7,24);
            break;
        case 8:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,60);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,102);
            m.setColumn(indexMax-4,60);
            m.setColumn(indexMax-5,102);
            m.setColumn(indexMax-6,102);
            m.setColumn(indexMax-7,60);
            break;
        case 9:
            m.setColumn(indexMax,0);
            m.setColumn(indexMax-1,60);
            m.setColumn(indexMax-2,102);
            m.setColumn(indexMax-3,102);
            m.setColumn(indexMax-4,124);
            m.setColumn(indexMax-5,96);
            m.setColumn(indexMax-6,48);
            m.setColumn(indexMax-7,28);
            break;
        default:
            break;
        }
    }

    Display()
    {
        m.init(); // MAX7219 initialization
        m.setIntensity(1); // initial led matrix intensity, 0-15
        reset();
    }
    void reset(){
        m.clear(); // Clears the displays
        m.setColumn(23, 0);
        m.setColumn(22, 126);
        m.setColumn(21, 2);
        m.setColumn(20, 2);
        m.setColumn(19, 126);
        m.setColumn(18, 2);
        m.setColumn(17, 2);
        m.setColumn(16, 126);

        m.setColumn(31, 0);
        m.setColumn(30, 126);
        m.setColumn(29, 2);
        m.setColumn(28, 2);
        m.setColumn(27, 126);
        m.setColumn(26, 2);
        m.setColumn(25, 2);
        m.setColumn(24, 2);
        write(1,0);
    }
    void WriteNo(int number){
        write(1, number);
    }
};

#endif