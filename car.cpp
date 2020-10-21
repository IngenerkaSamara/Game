#include "TXLib.h"

//Машина
struct Car
{
    int x;
    int y;
    double fuel;
    int speed;

    int width;
    int height;
    int diagonal;

    HDC Left;
    HDC Right;
    HDC Up;
    HDC Down;
    HDC pic;

    //Рисование машины
    void draw()
    {
        //Сама машина
        if (pic == Left || pic == Right)
            txTransparentBlt (txDC(), x - 40, y - 40, width, height, pic, 0, 0, TX_WHITE);
        else
            txTransparentBlt (txDC(), x - 40, y - 40, height, width, pic, 0, 0, TX_WHITE);


        //Уровень топлива
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txRectangle(x - 40, y - 50, x - 40 + 100, y - 40);
        if (fuel > 0)
        {
            txSetFillColor(TX_GREEN);
            txRectangle(x - 40, y - 50, x - 40 + 5 * fuel, y - 40);
        }
    }

    //Движение
    void moving()
    {
        fuel = fuel - 0.01;

        if (fuel <= 0)
            return;

        if (GetAsyncKeyState(VK_LEFT))
        {
            x = round(x - speed);
            pic = Left;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            x = round(x + speed);
            pic = Right;
        }

        if (GetAsyncKeyState(VK_UP))
        {
            y = round(y - speed);
            pic = Up;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            y = round(y + speed);
            pic = Down;
        }
    }

    void moving2()
    {
        fuel = fuel - 0.01;

        if (GetAsyncKeyState('A') && fuel > 0)
        {
            x = round(x - speed);
            pic = Left;
        }
        else if (GetAsyncKeyState('D') && fuel > 0)
        {
            x = round(x + speed);
            pic = Right;
        }

        if (GetAsyncKeyState('W') && fuel > 0)
        {
            y = round(y - speed);
            pic = Up;
        }
        else if (GetAsyncKeyState('S') && fuel > 0)
        {
            y = round(y + speed);
            pic = Down;
        }
    }

};
