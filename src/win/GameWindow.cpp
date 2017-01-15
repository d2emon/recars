#include "GameWindow.h"
#include <time.h>
#include "settings.h"

int points[num][2] = {
    300, 1600,
    600, 1600,
    500, 1800,
};


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

    carSprite.setTexture(texture);
    carSprite.setPosition(300, 300);
    carSprite.setOrigin(22, 22);

    return 1;
}

int GameWindow::run()
{
    load();

    const int N=5;
    Car car[N];
    for (int i=0; i < N; i++)
    {
        car[i].x =  300 + i*50;
        car[i].y = 1700 + i*80;
        car[i].speed = 7 + i;
    }

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

        car[0].speed = speed;
        car[0].angle = angle;

        for(int i=0; i < N; i++)
            car[i].move();

        float R=22;

        for (int i=0; i < N; i++)
            for (int j=0; j < N; j++)
            {
                int dx = car[i].x - car[j].x;
                int dy = car[i].y - car[j].y;
                if (dx * dx + dy * dy < 4*R*R)
                {
                    car[i].x += dx/10;
                    car[i].x += dy/10;
                    car[j].x += dx/10;
                    car[j].y += dy/10;
                }
                //
            }

        if (car[0].x>320) offsetX = car[0].x - 320;
        if (car[0].y>240) offsetY = car[0].y - 320;

        bg.setPosition(-offsetX, -offsetY);

        // Clear screen
        window.clear();
        window.draw(bg);

        sf::Color colors[10] = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Magenta,
            sf::Color::Blue,
            sf::Color::White
        };

        for (int i=0; i < N; i++)
        {
            carSprite.setPosition(car[i].x - offsetX, car[i].y - offsetY);
            carSprite.setRotation(car[i].angle * 180/3.141592);

            // Draw the sprite
            carSprite.setColor(colors[i]);
            window.draw(carSprite);
        }


        show();
    }

    return 1;
}

void GameWindow::show()
{
    // Update the window
    window.display();

}
