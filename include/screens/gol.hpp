#include "../screen.hpp"
#include<cstring>
#include<iostream>
#include<cmath>

class gol : public screen {

    public:
        virtual int run(sf::RenderWindow &window);
};

