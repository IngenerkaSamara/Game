#include "TXLib.h"
#include "car.cpp"
#include "JerryCan.cpp"
#include "track.cpp"

//Машина берет топливо
void getFuel(Car* car, JerryCan* can1, int xTrack, int yTrack)
{
    if (car->x - 40 < can1->x - xTrack + 50 &&
        car->x + 40 > can1->x - xTrack &&
        car->y - 40 < can1->y - yTrack + 70 &&
        car->y + 40 > can1->y - yTrack &&
        can1->visible)
    {
        can1->visible = false;
        car->fuel = car->fuel + 10;

        //Размер бака топливного
        if (car->fuel > 20)
            car->fuel = 20;
    }
}

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

    int N_CAN = 5;
    JerryCan can[N_CAN];
    can[0] = { 800, 1000, txLoadImage("Pictures/jerrycan.bmp"), 0, true};
    can[1] = {1800, 1400, can[0].picture, 0, true};
    can[2] = {1200,  920, can[0].picture, 0, true};
    can[3] = {1000,  350, can[0].picture, 0, true};
    can[4] = {2000,  400, can[0].picture, 0, true};

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1623, track, xTrack, yTrack);

        //Рисование бочек
        for (int i = 0; i < N_CAN; i++)
        {
            if (can[i].visible)
                txTransparentBlt(txDC(), can[i].x - xTrack, can[i].y - yTrack,
                    50, 74, can[i].picture, 50 * can[i].frame, 0, TX_WHITE);

            //Кадр канистры
            can[i].frame++;
            if (can[i].frame >= 4)
                can[i].frame = 0;
        }


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
        for (int i = 0; i < N_CAN; i++)
        {
            getFuel(&car, &can[i], xTrack, yTrack);
            getFuel(&enemy, &can[i], xTrack, yTrack);

            assert (i < N_CAN);
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

    for (int i = 0; i < N_CAN; i++)
        txDeleteDC(can[i].picture);

    return 0;
}
