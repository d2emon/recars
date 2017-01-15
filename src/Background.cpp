#include "Background.h"
#include <time.h>

int backgroundsCount = 10;
sf::String background = "res/background.png";

sf::String bgFile()
{
    return background;
}

Background::Background()
{
    if (texture.loadFromFile(bgFile()))
        setTexture(texture);
    //ctor
}
