#include "GameWindow.h"
#include <time.h>
#include <math.h>
#include "settings.h"

GameWindow::GameWindow(sf::RenderWindow &window): D2Window(window)
{
    // srand(time(0));
    window.setFramerateLimit(60);
}

GameWindow::~GameWindow()
{
    //dtor
}

int GameWindow::load()
{
    if (!texture.loadFromFile("res/car.png"))
        return EXIT_FAILURE;

    car.setTexture(texture);
    car.setPosition(300, 300);
    car.setOrigin(22, 22);

    return 1;
}

int GameWindow::run()
{
    load();

    float x=300;
    float y=300;
    float speed=0;
    float angle=0;
    float maxSpeed=12.0;
    float acc=0.2;
    float dec=0.3;
    float turnSpeed=0.08;

    int offsetX=0;
    int offsetY=0;

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
        }

        bool Up=0;
        bool Right=0;
        bool Down=0;
        bool Left=0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up   )) Up    = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) Right = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down )) Down  = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left )) Left  = 1;

        if (Up && speed<maxSpeed)
            if(speed < 0)
                speed += dec;
            else
                speed += acc;

        if (Down && speed<maxSpeed)
            if(speed < 0)
                speed -= dec;
            else
                speed -= acc;

        if (!Up && !Down)
            if (speed - dec > 0)
                speed -= dec;
            else if (speed + dec < 0)
                speed += dec;
            else
                speed = 0;

        if (Right && speed != 0) angle += turnSpeed * speed/maxSpeed;
        if (Left  && speed != 0) angle -= turnSpeed * speed/maxSpeed;

        x += sin(angle) * speed;
        y -= cos(angle) * speed;

        if (x>320) offsetX = x - 320;
        if (y>240) offsetY = y - 320;

        bg.setPosition(-offsetX, -offsetY);

        car.setPosition(x - offsetX, y - offsetY);
        car.setRotation(angle * 180/3.141592);

        show();
    }

    return 1;
}

void GameWindow::show()
{
    // Clear screen
    window.clear();
    window.draw(bg);

    // Draw the sprite
    car.setColor(sf::Color::Red);
    window.draw(car);

    // Update the window
    window.display();

}
