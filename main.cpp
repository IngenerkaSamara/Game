#include "TXLib.h"

int main()
{
    txCreateWindow (1200, 800);

    HDC track = txLoadImage ("Pictures/Tracks/Spa.bmp");
    int xTrack = -100;
    int yTrack = 700;

    HDC carLeft = txLoadImage ("Pictures/Cars/Acura/Left.bmp");
    HDC carRight = txLoadImage ("Pictures/Cars/Acura/Right.bmp");
    HDC carUp = txLoadImage ("Pictures/Cars/Acura/Up.bmp");
    HDC carDown = txLoadImage ("Pictures/Cars/Acura/Down.bmp");
    HDC car = carLeft;
    int yCar = 400;    int xCar = 600;    double speed = 5;


    int x2 = 400;   int y2 = 500;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1623, track, xTrack, yTrack);
        if (car == carLeft || car == carRight)
            txTransparentBlt (txDC(), xCar - 40, yCar - 40, 120, 63, car, 0, 0, TX_WHITE);
        else
            txTransparentBlt (txDC(), xCar - 40, yCar - 40, 63, 120, car, 0, 0, TX_WHITE);



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
        {
            xTrack = xTrack - speed;
            car = carLeft;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            xTrack = xTrack + speed;
            car = carRight;
        }

        if (GetAsyncKeyState(VK_UP))
        {
            yTrack = yTrack - speed;
            car = carUp;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            yTrack = yTrack + speed;
            car = carDown;
        }


        //Проверка выхода за пределы экрана
        if (xCar < 0)
            xCar = 0;
        if (xCar > txGetExtentX())
            xCar = txGetExtentX();

        txSleep(20);
        txEnd();
    }

    txDeleteDC (track);
    txDeleteDC (car);
    txDeleteDC (carLeft);
    txDeleteDC (carRight);
    txDeleteDC (carUp);
    txDeleteDC (carDown);

    return 0;
}

