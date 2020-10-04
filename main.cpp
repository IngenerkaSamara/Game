#include "TXLib.h"

int main()
{
    txCreateWindow (1200, 800);

    HDC track = txLoadImage ("Spa.bmp");
    int xTrack = 0;
    int yTrack = 0;

    HDC car = txLoadImage ("Acura2.bmp");
    int yCar = 100;    int xCar = 500;    double speed = 5;


    int x2 = 400;   int y2 = 500;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_BLACK);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1623, track);
        txTransparentBlt (txDC(), xCar, yCar, 120, 63, car, 0, 0, TX_WHITE);



        txRectangle(x2, y2, x2 + 50, y2 + 50);

        //Столкновение
        if (xCar > x2 &&
            xCar < x2 + 50 &&
            yCar > y2 &&
            yCar < y2 + 50)
        {
            xCar = x2 - 10;
        }


        //Движение
        if (GetAsyncKeyState(VK_LEFT))
            xCar = xCar - speed;
        else if (GetAsyncKeyState(VK_RIGHT))
            xCar = xCar + speed;

        if (GetAsyncKeyState(VK_UP))
            yCar = yCar - speed;
        else if (GetAsyncKeyState(VK_DOWN))
            yCar = yCar + speed;


        //Проверка выхода за пределы экрана
        if (xCar < 0)
            xCar = 0;
        if (xCar > txGetExtentX())
            xCar = txGetExtentX();

        txSleep(20);
    }

    txDeleteDC (track);
    txDeleteDC (car);

    return 0;
}

