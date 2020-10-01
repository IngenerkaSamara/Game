#include "TXLib.h"

int main()
{
    txCreateWindow (800, 600);

    int y = 100;    int x = 500;    double speed = 5;

    int x2 = 400;   int y2 = 500;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_BLACK);
        txClear();

        txCircle(x, y, 20);

        txRectangle(x2, y2, x2 + 50, y2 + 50);

        //Столкновение
        if (x > x2 &&
            x < x2 + 50 &&
            y > y2 &&
            y < y2 + 50)
        {
            x = x2 - 10;
        }


        //Движение
        if (GetAsyncKeyState(VK_LEFT))
            x = x - speed;
        else if (GetAsyncKeyState(VK_RIGHT))
            x = x + speed;

        if (GetAsyncKeyState(VK_UP))
            y = y - speed;
        else if (GetAsyncKeyState(VK_DOWN))
            y = y + speed;


        /*
        speed = speed * 0.9;
        */

        //Проверка выхода за пределы экрана
        if (x < 0)
            x = 0;
        if (x > 800)
            x = 800;

        txSleep(20);
    }

    return 0;
}

