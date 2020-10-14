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
        txSetFillColor(TX_GREEN);
        txRectangle(x - 40, y - 50, x - 40 + 5 * fuel, y - 40);
    }

    //Движение
    void moving()
    {
        fuel = fuel - 0.01;

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

        if (GetAsyncKeyState('A'))
        {
            x = round(x - speed);
            pic = Left;
        }
        else if (GetAsyncKeyState('D'))
        {
            x = round(x + speed);
            pic = Right;
        }

        if (GetAsyncKeyState('W'))
        {
            y = round(y - speed);
            pic = Up;
        }
        else if (GetAsyncKeyState('S'))
        {
            y = round(y + speed);
            pic = Down;
        }
    }

};

//Рисование машины
void drawCar(int xCar, int yCar, int width, int height, HDC car, HDC carLeft, HDC carRight)
{
    if (car == carLeft || car == carRight)
        txTransparentBlt (txDC(), xCar - 40, yCar - 40, width, height, car, 0, 0, TX_WHITE);
    else
        txTransparentBlt (txDC(), xCar - 40, yCar - 40, height, width, car, 0, 0, TX_WHITE);
}

//Движение машины
Car moveCar(Car car)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        car.x = round(car.x - car.speed);
        car.pic = car.Left;
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        car.x = round(car.x + car.speed);
        car.pic = car.Right;
    }

    if (GetAsyncKeyState(VK_UP))
    {
        car.y = round(car.y - car.speed);
        car.pic = car.Up;
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        car.y = round(car.y + car.speed);
        car.pic = car.Down;
    }

    return car;
}

void moveCar1(Car* car)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        car->x = round(car->x - car->speed);
        car->pic = car->Left;
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        car->x = round(car->x + car->speed);
        car->pic = car->Right;
    }

    if (GetAsyncKeyState(VK_UP))
    {
        car->y = round(car->y - car->speed);
        car->pic = car->Up;
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        car->y = round(car->y + car->speed);
        car->pic = car->Down;
    }
}


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
