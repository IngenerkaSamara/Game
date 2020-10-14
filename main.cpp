#include "TXLib.h"
#include "car.cpp"
#include "track.cpp"

int main()
{
    int WIDTH = 1200;
    int HEIGHT = 800;
    txCreateWindow (WIDTH, HEIGHT);

    HDC track = txLoadImage ("Pictures/Tracks/Spa.bmp");
    int xTrack = -100;
    int yTrack = 700;

    HDC carLeft = txLoadImage ("Pictures/Cars/Acura/Left.bmp");
    HDC carRight = txLoadImage ("Pictures/Cars/Acura/Right.bmp");
    HDC carUp = txLoadImage ("Pictures/Cars/Acura/Up.bmp");
    HDC carDown = txLoadImage ("Pictures/Cars/Acura/Down.bmp");
    HDC car = carLeft;
    int xCar = 600;    int yCar = 400;    double speed = 5; float fuelCar = 10;


    HDC enemyLeft = txLoadImage ("Pictures/Cars/Mercedes/Left.bmp");
    HDC enemyRight = txLoadImage ("Pictures/Cars/Mercedes/Right.bmp");
    HDC enemyUp = txLoadImage ("Pictures/Cars/Mercedes/Up.bmp");
    HDC enemyDown = txLoadImage ("Pictures/Cars/Mercedes/Down.bmp");
    HDC enemy = enemyLeft;
    int xEnemy = 620;   int yEnemy = 420;

    HDC jerrycan = txLoadImage("Pictures/jerrycan.bmp");
    int xCan = 800;
    int yCan = 1000;
    bool visibleCan = true;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1623, track, xTrack, yTrack);
        if (visibleCan)
            txTransparentBlt(txDC(), xCan-xTrack, yCan-yTrack, 50, 70, jerrycan, 0, 0, TX_WHITE);

        drawCar(xCar, yCar, 120, 63, car, carLeft, carRight);
        drawCar(xEnemy, yEnemy, 120, 51, enemy, enemyLeft, enemyRight);

        //Уровень топлива
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txRectangle(xCar - 40, yCar - 50, xCar - 40 + 100, yCar - 40);
        txSetFillColor(TX_GREEN);
        txRectangle(xCar - 40, yCar - 50, xCar - 40 + 5 * fuelCar, yCar - 40);




        //Строка состояния
        txSetFillColor(TX_WHITE);
        txRectangle( 0, HEIGHT - 50, WIDTH, HEIGHT);
        txTextOut  (10, HEIGHT - 40, "Машина");

        char toplivo[50];
        sprintf(toplivo, "Топливо: %.2f/20", fuelCar);
        txTextOut(100, HEIGHT - 40, toplivo);




        //КОнтакт с канистрой
        if (xCar - 40 < xCan-xTrack + 50 &&
            xCar + 40 > xCan-xTrack &&
            yCar - 40 < yCan-yTrack + 70 &&
            yCar + 40 > yCan-yTrack &&
            visibleCan)
        {
            visibleCan = false;
            fuelCar = fuelCar + 10;
        }


        //Движение
        moveCar(&xCar, &yCar, speed, &car,
                carLeft, carRight, carUp, carDown);
        moveEnemy(&xEnemy, &yEnemy, speed, &enemy,
                enemyLeft, enemyRight, enemyUp, enemyDown);


        //Движение карты
        trackMovingX(&xCar, &xEnemy, &xTrack, speed);
        trackMovingY(&yCar, &yEnemy, &yTrack, speed);


        //Проверка выхода за пределы экрана
        xTrack = checkLimitX(xTrack);
        yTrack = checkLimitY(yTrack);

        txSleep(20);
        fuelCar = fuelCar - 0.01;
        txEnd();
    }

    txDeleteDC (track);
    txDeleteDC (car);          txDeleteDC (carLeft);      txDeleteDC (carRight);
    txDeleteDC (carUp);        txDeleteDC (carDown);

    txDeleteDC (enemy);        txDeleteDC (enemyLeft);    txDeleteDC (enemyRight);
    txDeleteDC (enemyUp);      txDeleteDC (enemyDown);

    txDeleteDC(jerrycan);

    return 0;
}
