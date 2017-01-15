#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <math.h>

#include "D2Window.h"
#include "Background.h"

const int num=8;
extern int points[num][2];

struct Car
{
    float x;
    float y;
    float speed;
    float angle;
    int n;

    Car() {speed=2; angle=0; n=0;}

    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }

    void findTarget()
    {
        float tx = points[n][0];
        float ty = points[n][1];
        float beta = angle - atan2(tx-x, -ty+y);
        if (sin(beta) < 0)
            angle += 0.005 * speed;
        else
            angle -= 0.005 * speed;

        if ((x-tx) * (x-tx) + (y-ty) * (y-ty) < 25*25)
            n = (n + 1) % num;
    }
};

class GameWindow : public D2Window
{
    public:
        GameWindow(sf::RenderWindow &window);
        virtual ~GameWindow();

        Background bg;
        sf::Texture texture;
        sf::Sprite carSprite;

        int grid[6][6];

        int load();
        int run();
        void show();
    protected:
    private:
};

#endif // GAMEWINDOW_H
