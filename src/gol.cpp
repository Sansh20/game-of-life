#include "../include/screens/gol.hpp"


int gol::run(sf::RenderWindow &window) {

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    float blockSize= 17;
    bool isPaused = true;

    int nCols = std::ceil(desktop.height/blockSize);
    int nRows = std::ceil(desktop.width/blockSize);

    int grid[nRows][nCols];

    memset(grid, 0, sizeof(grid));

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left && isPaused){
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        int x = (mousePos.x / blockSize);
                        int y = (mousePos.y / blockSize);
                        grid[x][y] = !grid[x][y];
                    }          

                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::K){
                        isPaused = !isPaused;
                    }

                default:
                    break;
            }
    
        }

        window.clear(sf::Color::White);
        sf::Vector2f blockSize2f(blockSize, blockSize);

        for(int i=0; i<nRows; i++){
            for(int j=0; j<nCols; j++){

                int neighbourCount=0;
                sf::RectangleShape block;

                block.setSize(blockSize2f);
                block.setOutlineColor(sf::Color::Black);
                block.setOutlineThickness(1);
                block.setFillColor((grid[i][j]) ? sf::Color::Black : sf::Color::White);
                block.setPosition(i * blockSize, j * blockSize);

                window.draw(block);
                
                // neighbourCount+=grid[i-1][j-1];
                // neighbourCount+=grid[i][j-1];
                // neighbourCount+=grid[i+1][j-1];
                // neighbourCount+=grid[i-1][j];
                // neighbourCount+=grid[i+1][j];
                // neighbourCount+=grid[i-1][j+1];
                // neighbourCount+=grid[i][j+1];
                // neighbourCount+=grid[i+1][j+1];

            }
        }

        window.display();
    }

    return -1;
}