#include<SFML/Graphics.hpp>
#include "../include/screens/gol.hpp"


int main(){

    std::vector<screen*> screens;
    int screenIdx = 0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(
        sf::VideoMode(desktop.width/1.2, desktop.height/1.2),
        "Game Of Life", sf::Style::Close
    );

    sf::Vector2i winPos = window.getPosition();
    winPos.y -= 40;

    window.setPosition(winPos);

    gol screen1;
    screens.push_back(&screen1);

    while(screenIdx>=0){
        screenIdx = screens[screenIdx]->run(window);
    }

    window.close();

    return 0;

}