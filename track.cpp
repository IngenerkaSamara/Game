#include "TXLib.h"

int checkLimitX(int xTrack)
{
    if (xTrack < -500)         xTrack = -500;
    if (xTrack > 2500)         xTrack = 2500;
    return xTrack;
}

int checkLimitY(int yTrack)
{
    if (yTrack < -500)         yTrack = -500;
    if (yTrack > 2500)         yTrack = 2500;
    return yTrack;
}

void trackMovingX(int *xCar, int *xEnemy, int *xTrack, double speed)
{
    if (*xCar < 100 || *xEnemy < 100)
    {
        *xEnemy = *xEnemy + speed;
        *xCar = *xCar + speed;
        *xTrack = *xTrack - speed;
    }

    else if (*xCar > 900 || *xEnemy > 900)
    {
        *xEnemy = *xEnemy - speed;
        *xCar = *xCar - speed;
        *xTrack = *xTrack + speed;
    }
}

void trackMovingY(int *yCar, int *yEnemy, int *yTrack, double speed)
{
    if (*yCar < 100 || *yEnemy < 100)
    {
        *yEnemy = *yEnemy + speed;
        *yCar = *yCar + speed;
        *yTrack = *yTrack - speed;
    }

    else if (*yCar > 700 || *yEnemy > 700)
    {
        *yEnemy = *yEnemy - speed;
        *yCar = *yCar - speed;
        *yTrack = *yTrack + speed;
    }
}
