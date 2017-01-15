#include "GameWindow.h"
#include <time.h>
#include "settings.h"

GameWindow::GameWindow(sf::RenderWindow &window): D2Window(window)
{
    srand(time(0));
    window.setFramerateLimit(60);
}

GameWindow::~GameWindow()
{
    //dtor
}

int GameWindow::load()
{
    if (!texture.loadFromFile("res/background.png"))
        return EXIT_FAILURE;

    int n=0;
    for(int i=0; i < 4; i++)
        for(int j=0; j < 4; j++)
        {
            n++;
            sprite[n].setTexture(texture);
            sprite[n].setTextureRect(sf::IntRect(i*spriteWidth, j*spriteWidth, spriteWidth, spriteWidth));
            grid[i+1][j+1] = n;
        }

    return 1;
}

int GameWindow::run()
{
    load();

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    int x = pos.x / spriteWidth + 1;
                    int y = pos.y / spriteWidth + 1;

                    int dx=0;
                    int dy=0;

                    if (grid[x+1][y] == 16){dx =  1; dy =  0;}
                    if (grid[x][y+1] == 16){dx =  0; dy =  1;}
                    if (grid[x][y-1] == 16){dx =  0; dy = -1;}
                    if (grid[x-1][y] == 16){dx = -1; dy =  0;}

                    int n = grid[x][y];
                    grid[x][y] = 16;
                    grid[x+dx][y+dy] = n;

                    sprite[16].move(-dx*spriteWidth, -dy*spriteWidth);
                    float speed = 3;

                    for (int i=0; i < spriteWidth; i += speed)
                    {
                        sprite[n].move(speed*dx, speed*dy);
                        window.draw(sprite[16]);
                        window.draw(sprite[n]);
                        window.display();
                    }
                }
            }
        }
        show();
    }

    return 1;
}

void GameWindow::show()
{
    // Clear screen
    window.clear();
    window.draw(bg);

    for(int i=0; i < 4; i++)
        for(int j=0; j < 4; j++)
        {
            int n = grid[i+1][j+1];
            sprite[n].setPosition(i*spriteWidth, j*spriteWidth);
            window.draw(sprite[n]);
        }

    // Draw the sprite
    // window.draw(sprite);

    // Update the window
    window.display();

}
