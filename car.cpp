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
    HDC UpLeft;
    HDC UpRight;
    HDC DownLeft;
    HDC DownRight;
    HDC pic;

    //Рисование машины
    void draw()
    {
        //Сама машина
        if (pic == Left || pic == Right)
            txTransparentBlt (txDC(), x - 30, y - 30, width, height, pic, 0, 0, TX_WHITE);
        else if (pic == Up || pic == Down)
            txTransparentBlt (txDC(), x - 30, y - 30, height, width, pic, 0, 0, TX_WHITE);
        else
            txTransparentBlt (txDC(), x - 30, y - 30, diagonal, diagonal, pic, 0, 0, TX_WHITE);


        //Уровень топлива
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txRectangle(x - 40, y - 50, x - 40 + 60, y - 40);
        if (fuel > 0)
        {
            txSetFillColor(TX_GREEN);
            txRectangle(x - 40, y - 50, x - 40 + 3 * fuel, y - 40);
        }
    }

    //Движение врага
    void enemyMoving(COLORREF enemyColor)
    {
        //Движется влево
        if (pic == Left || pic == UpLeft || pic == DownLeft)
        {
            if (txGetPixel(x - speed, y) == enemyColor)
            {
                x -= speed;
                pic = Left;
            }
            else if (txGetPixel(x - speed, y - speed) == enemyColor)
            {
                x -= speed;
                y -= speed;
                pic = UpLeft;
            }
            else if (txGetPixel(x - speed, y + speed) == enemyColor)
            {
                x -= speed;
                y += speed;
                pic = DownLeft;
            }
            else if (txGetPixel(x, y - speed) == enemyColor)
            {
                y -= speed;
                pic = Up;
            }
            else if (txGetPixel(x, y + speed) == enemyColor)
            {
                y += speed;
                pic = Down;
            }
        }
        //Движется вправо
        else if (pic == Right || pic == UpRight || pic == DownRight)
        {
            if (txGetPixel(x + speed, y) == enemyColor)
            {
                x += speed;
                pic = Right;
            }
            else if (txGetPixel(x + speed, y - speed) == enemyColor)
            {
                x += speed;
                y -= speed;
                pic = UpRight;
            }
            else if (txGetPixel(x + speed, y + speed) == enemyColor)
            {
                x += speed;
                y += speed;
                pic = DownRight;
            }
            else if (txGetPixel(x, y - speed) == enemyColor)
            {
                y -= speed;
                pic = Up;
            }
            else if (txGetPixel(x, y + speed) == enemyColor)
            {
                y += speed;
                pic = Down;
            }
        }
        //Движется вверх
        else if (pic == Up)
        {
            if (txGetPixel(x, y - speed) == enemyColor)
            {
                y -= speed;
                pic = Up;
            }
            else if (txGetPixel(x - speed, y) == enemyColor)
            {
                x -= speed;
                pic = Left;
            }
            else if (txGetPixel(x + speed, y) == enemyColor)
            {
                x += speed;
                pic = Right;
            }
        }
        //Движется вниз
        else if (pic == Down)
        {
            if (txGetPixel(x, y + speed) == enemyColor)
            {
                y += speed;
                pic = Down;
            }
            else if (txGetPixel(x - speed, y) == enemyColor)
            {
                x -= speed;
                pic = Left;
            }
            else if (txGetPixel(x + speed, y) == enemyColor)
            {
                x += speed;
                pic = Right;
            }
        }
    }

    void deletePics()
    {
        txDeleteDC (pic);
        txDeleteDC (Left);      txDeleteDC (Right);        txDeleteDC (Up);       txDeleteDC (Down);
        txDeleteDC (UpLeft);    txDeleteDC (UpRight);      txDeleteDC (DownLeft); txDeleteDC (DownRight);
    }

    //Движение
    void moving()
    {
        fuel = fuel - 0.01;

        if (fuel <= 0)
            return;

        if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_UP))
        {
            x = round(x - speed);
            y = round(y - speed);
            pic = UpLeft;
        }
        else if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_DOWN))
        {
            x = round(x - speed);
            y = round(y + speed);
            pic = DownLeft;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_UP))
        {
            x = round(x + speed);
            y = round(y - speed);
            pic = UpRight;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_DOWN))
        {
            x = round(x + speed);
            y = round(y + speed);
            pic = DownRight;
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            x = round(x - speed);
            pic = Left;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            x = round(x + speed);
            pic = Right;
        }

        else if (GetAsyncKeyState(VK_UP))
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

    //Выезд за пределы трассы
    void trackLimits()
    {
        bool returnBack = false;
        for (int x1 = x - 15; x1 <= x + 15; x1 = x1 + 5)
        {
            for (int y1 = y - 15; y1 <= y + 15; y1 = y1 + 5)
            {
                if (txGetPixel(x1, y1) == RGB(0,96,0))
                {
                    returnBack = true;
                }
            }
        }

        if (returnBack && fuel > 0.1)
        {
            fuel = fuel - 0.1;
        }
    }
};
