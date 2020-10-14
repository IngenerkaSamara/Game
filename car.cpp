#include "TXLib.h"

//Рисование машины
void drawCar(int xCar, int yCar, int width, int height, HDC car, HDC carLeft, HDC carRight)
{
    if (car == carLeft || car == carRight)
        txTransparentBlt (txDC(), xCar - 40, yCar - 40, width, height, car, 0, 0, TX_WHITE);
    else
        txTransparentBlt (txDC(), xCar - 40, yCar - 40, height, width, car, 0, 0, TX_WHITE);
}

//Движение машины
void moveCar(int *xCar, int* yCar, double speed, HDC *car,
            HDC carLeft, HDC carRight, HDC carUp, HDC carDown)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        *xCar = round(*xCar - speed);
        *car = carLeft;
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        *xCar = round(*xCar + speed);
        *car = carRight;
    }

    if (GetAsyncKeyState(VK_UP))
    {
        *yCar = round(*yCar - speed);
        *car = carUp;
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        *yCar = round(*yCar + speed);
        *car = carDown;
    }
}

//Движение врага
void moveEnemy(int *xEnemy, int* yEnemy, double speed, HDC *enemy,
            HDC enemyLeft, HDC enemyRight, HDC enemyUp, HDC enemyDown)
{
    if (GetAsyncKeyState('A'))
    {
        *xEnemy = *xEnemy - speed;
        *enemy = enemyLeft;
    }
    else if (GetAsyncKeyState('D'))
    {
        *xEnemy = *xEnemy + speed;
        *enemy = enemyRight;
    }

    if (GetAsyncKeyState('W'))
    {
        *yEnemy = *yEnemy - speed;
        *enemy = enemyUp;
    }
    else if (GetAsyncKeyState('S'))
    {
        *yEnemy = *yEnemy + speed;
        *enemy = enemyDown;
    }
}
