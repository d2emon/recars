#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <math.h>

#include "D2Window.h"
#include "Background.h"

struct Car
{
    float x;
    float y;
    float speed;
    float angle;

    Car() {speed=2; angle=0;}

    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
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
