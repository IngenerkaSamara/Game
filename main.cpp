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

    Car car = {600, 400, 10.0, 5, 120, 63, 104,
                txLoadImage ("Pictures/Cars/Acura/Left.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Right.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Up.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Down.bmp"), car.Left};
    Car enemy = {620, 420, 10.0, 5, 120, 51, 102,
                txLoadImage ("Pictures/Cars/Mercedes/Left.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Right.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Up.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Down.bmp"), enemy.Left};

    HDC jerrycan = txLoadImage("Pictures/jerrycan.bmp");
    int xCan = 800;
    int yCan = 1000;
    int frameCan = 0;
    bool visibleCan = true;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1623, track, xTrack, yTrack);
        if (visibleCan)
            txTransparentBlt(txDC(), xCan-xTrack, yCan-yTrack,
                50, 74, jerrycan, 50 * frameCan, 0, TX_WHITE);

        //Кадр канистры
        frameCan++;
        if (frameCan >= 4)
            frameCan = 0;

        car.draw();
        enemy.draw();


        //Строка состояния
        txSetFillColor(TX_WHITE);
        txRectangle( 0, HEIGHT - 50, WIDTH, HEIGHT);
        txTextOut  (10, HEIGHT - 40, "Машина");

        char toplivo[50];
        sprintf(toplivo, "Топливо: %.2f/20", car.fuel);
        txTextOut(100, HEIGHT - 40, toplivo);




        //КОнтакт с канистрой
        if (car.x - 40 < xCan-xTrack + 50 &&
            car.x + 40 > xCan-xTrack &&
            car.y - 40 < yCan-yTrack + 70 &&
            car.y + 40 > yCan-yTrack &&
            visibleCan)
        {
            visibleCan = false;
            car.fuel = car.fuel + 10;
        }


        //Движение
        car.moving();
        enemy.moving2();

        //Движение карты
        trackMovingX(&car.x, &enemy.x, &xTrack, car.speed);
        trackMovingY(&car.y, &enemy.y, &yTrack, car.speed);


        //Проверка выхода за пределы экрана
        xTrack = checkLimitX(xTrack);
        yTrack = checkLimitY(yTrack);

        txSleep(20);
        txEnd();
    }

    txDeleteDC (track);
    txDeleteDC (car.pic);      txDeleteDC (car.Left);      txDeleteDC (car.Right);
    txDeleteDC (car.Up);       txDeleteDC (car.Down);

    txDeleteDC (enemy.pic);    txDeleteDC (enemy.Left);    txDeleteDC (enemy.Right);
    txDeleteDC (enemy.Up);     txDeleteDC (enemy.Down);

    txDeleteDC(jerrycan);

    return 0;
}
