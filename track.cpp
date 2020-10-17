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
    if (*xCar < 200 || *xEnemy < 200)
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
    if (*yCar < 200 || *yEnemy < 200)
    {
        *yEnemy = *yEnemy + speed;
        *yCar = *yCar + speed;
        *yTrack = *yTrack - speed;
    }

    else if (*yCar > 600 || *yEnemy > 600)
    {
        *yEnemy = *yEnemy - speed;
        *yCar = *yCar - speed;
        *yTrack = *yTrack + speed;
    }
}
