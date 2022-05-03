#pragma once

#include<SFML/Graphics.hpp>

class screen{
    public:
        virtual int run(sf::RenderWindow &window) = 0;
};