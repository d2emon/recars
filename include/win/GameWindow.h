#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "D2Window.h"
#include "Background.h"


class GameWindow : public D2Window
{
    public:
        GameWindow(sf::RenderWindow &window);
        virtual ~GameWindow();

        Background bg;
        sf::Texture texture;
        sf::Sprite car;

        int grid[6][6];

        int load();
        int run();
        void show();
    protected:
    private:
};

#endif // GAMEWINDOW_H
