#include "TXLib.h"
#include "car.cpp"
#include "JerryCan.cpp"
#include "track.cpp"

//������ ����� �������
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

        //������ ���� ����������
        if (car->fuel > 20)
            car->fuel = 20;
    }
}

int main()
{
    const int WIDTH = 1200;
    const int HEIGHT = 800;
    txCreateWindow (WIDTH, HEIGHT);

    HDC track1 = txLoadImage ("Pictures/Tracks/Spa.bmp");
    HDC track2 = txLoadImage ("Pictures/Tracks/Marina Bay.bmp");
    HDC track;
    int xTrack = -100;
    int yTrack = 700;

    Car car = {650, 400, 15.0, 4, 96, 51, 84,
                txLoadImage ("Pictures/Cars/Acura/Left.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Right.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Up.bmp"),
                txLoadImage ("Pictures/Cars/Acura/Down.bmp"),
                txLoadImage ("Pictures/Cars/Acura/UpLeft.bmp"),
                txLoadImage ("Pictures/Cars/Acura/UpRight.bmp"),
                txLoadImage ("Pictures/Cars/Acura/DownLeft.bmp"),
                txLoadImage ("Pictures/Cars/Acura/DownRight.bmp"), car.Left};
    Car enemy = {620, 436, 15.0, 4, 96, 41, 82,
                txLoadImage ("Pictures/Cars/Mercedes/Left.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Right.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Up.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/Down.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/UpLeft.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/UpRight.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/DownLeft.bmp"),
                txLoadImage ("Pictures/Cars/Mercedes/DownRight.bmp"), enemy.Left};

    const COLORREF ENEMY_COLOR = RGB(0, 0, 0);
    const COLORREF FINISH_COLOR = RGB(255, 255, 0);
    int oldCarX = 0, oldCarY = 0;
    int laps = 0, lapTime = 0;

    int level = 1;
    string PAGE = "����";

    int N_CAN = 8;
    JerryCan can[N_CAN];
    can[0] = { 800, 1050, txLoadImage("Pictures/jerrycan.bmp"), 0, true};
    can[1] = {1800, 1400, can[0].picture, 0, true};
    can[2] = {1200,  920, can[0].picture, 0, true};
    can[3] = {1100,  380, can[0].picture, 0, true};
    can[4] = {2000,  400, can[0].picture, 0, true};
    can[5] = { 600,  600, can[0].picture, 0, true};
    can[6] = {1500,  500, can[0].picture, 0, true};
    can[7] = {1900,  900, can[0].picture, 0, true};

    bool startGame = false;
    while (!startGame)
    {
        txBegin();
        txSetColor(TX_BLACK, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        Win32::TransparentBlt (txDC(), 300, 100, 240, 160, track1, 0, 0, 2400, 1623, TX_YELLOW);
        Win32::TransparentBlt (txDC(), 600, 100, 240, 160, track2, 0, 0, 2400, 1665, TX_YELLOW);

        if (txMouseX() >= 300 &&
            txMouseY() >= 100 &&
            txMouseX() <= 540 &&
            txMouseY() <= 260 &&
            txMouseButtons() == 1)
        {
            track = track1;
            startGame = true;
        }

        if (txMouseX() >= 600 &&
            txMouseY() >= 100 &&
            txMouseX() <= 840 &&
            txMouseY() <= 260 &&
            txMouseButtons() == 1)
        {
            track = track2;
            startGame = true;
        }

        txEnd();
        txSleep(20);
    }


    while (!GetAsyncKeyState(VK_ESCAPE) && level < 3)
    {
        txBegin();
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_WHITE);
        txClear();

        txBitBlt (txDC(), 0, 0, 2400, 1665, track, xTrack, yTrack);

        if (PAGE == "����")
        {
            txSetColor(TX_BLACK, 5);
            txRectangle(300, 400, 500, 500);
            txDrawText(300, 400, 500, 500, "���������");

            txRectangle(600, 400, 800, 500);
            txDrawText(600, 400, 800, 500, "�����");

            if (txMouseX() >= 300 &&                 txMouseY() >= 400 &&
                txMouseX() <= 500 &&                 txMouseY() <= 500 &&
                txMouseButtons() == 1)
            {
                PAGE = "����";
                txSleep(200);
            }

            if (txMouseX() >= 600 &&                 txMouseY() >= 400 &&
                txMouseX() <= 800 &&                 txMouseY() <= 500 &&
                txMouseButtons() == 1)
            {
                break;
            }
        }

        else if (PAGE == "����")
        {
            if (GetAsyncKeyState('P'))
                PAGE = "����";

            if (txGetPixel(car.x, car.y) == FINISH_COLOR && lapTime > 20000)
            {
                laps++;
                lapTime = 0;
            }

            //����� ������
            if (laps >= 1)
            {
                level++;

                if (level == 2)
                {
                    track = txLoadImage ("Pictures/Tracks/Marina Bay.bmp");
                    xTrack = -100;                 yTrack = 700;

                    car.x = 700;                   car.y = 400;                  car.fuel = 15.0;
                    enemy.x = 700;                 enemy.y = 400;                enemy.fuel = 15.0;

                    laps = 0;                      lapTime = 0;

                    N_CAN = 6;
                    can[0] = { 800, 1050, txLoadImage("Pictures/jerrycan.bmp"), 0, true};
                    can[1] = {1800, 1400, can[0].picture, 0, true};
                    can[2] = {1200,  920, can[0].picture, 0, true};
                    can[3] = {1100,  380, can[0].picture, 0, true};
                    can[4] = {2000,  400, can[0].picture, 0, true};
                    can[5] = { 600,  600, can[0].picture, 0, true};
                }
            }




            enemy.enemyMoving(ENEMY_COLOR);

            //����� �� ������� ������
            car.trackLimits();

            //��������� �����
            for (int i = 0; i < N_CAN; i++)
            {
                if (can[i].visible)
                    txTransparentBlt(txDC(), can[i].x - xTrack, can[i].y - yTrack,
                        50, 74, can[i].picture, 50 * can[i].frame, 0, TX_WHITE);

                //���� ��������
                can[i].frame++;
                if (can[i].frame >= 4)
                    can[i].frame = 0;
            }


            car.draw();
            enemy.draw();

            //������ ���������
            txSetFillColor(TX_WHITE);
            txRectangle( 0, HEIGHT - 50, WIDTH, HEIGHT);
            txTextOut  (10, HEIGHT - 40, "������");

            char toplivo[50];
            sprintf(toplivo, "�������: %.2f/20", car.fuel);
            txTextOut(100, HEIGHT - 40, toplivo);

            sprintf(toplivo, "�����: %d", laps);
            txTextOut(350, HEIGHT - 40, toplivo);

            //������� � ���������
            for (int i = 0; i < N_CAN; i++)
            {
                getFuel(&car, &can[i], xTrack, yTrack);
                getFuel(&enemy, &can[i], xTrack, yTrack);

                assert (i < N_CAN);
            }

            //��������
            oldCarX = car.x;
            oldCarY = car.y;
            car.moving();

            //�������� �����
            trackMovingX(&car.x, &enemy.x, &xTrack, car.speed);
            trackMovingY(&car.y, &enemy.y, &yTrack, car.speed);

            //�������� ������ �� ������� ������
            xTrack = checkLimitX(xTrack);
            yTrack = checkLimitY(yTrack);

            lapTime += 20;
        }

        txSleep(20);
        txEnd();
    }


    if (level >= 3)
    {
        txTextOut(100, 100, "�������!!!");
    }

    txDeleteDC (track);
    car.deletePics();
    enemy.deletePics();

    for (int i = 0; i < N_CAN; i++)
        txDeleteDC(can[i].picture);

    return 0;
}
