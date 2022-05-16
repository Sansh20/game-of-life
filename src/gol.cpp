#include<screens/gol.hpp>


int gol::run(sf::RenderWindow &window) {

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::Texture playTexture, pauseTexture;
    sf::Sprite play, pause;

    if(!playTexture.loadFromFile("./res/pngs/play.png")){
        std::cout<<"Unable to load Play Texture";
    }
    
    if(!pauseTexture.loadFromFile("./res/pngs/pause.png")){
        std::cout<<"Unable to load Pause Texture";
    }

    sf::Text info;
    sf::Font rWM;

    if(!rWM.loadFromFile("./res/fonts/Raleway-Medium.ttf")){
        std::cout<<"Unable to load the Raleway Medium";
    }

    info.setFont(rWM);
    info.setString("K - Pause/Play, R - Reset, Up/Down Arrow - Increase/Decrease Speed");
    info.setPosition(40, 6);
    info.setFillColor(sf::Color::Black);
    info.setOutlineColor(sf::Color(169, 169, 169, 255));
    info.setOutlineThickness(0.5);

    play.setTexture(playTexture);
    pause.setTexture(pauseTexture);

    play.setPosition(10, 10);
    pause.setPosition(10, 10);
    
    float blockSize= 17;
    bool isPaused = true;
    sf::Time delay = sf::milliseconds(100);
    

    const int nCols = std::ceil(desktop.height/blockSize);
    const int nRows = std::ceil(desktop.width/blockSize);

    // std::vector<std::vector<int>> grid(nRows, std::vector(nCols, 0));

    // std::vector<std::vector<int>> newGrid;

    int grid[nRows][nCols];

    memset(grid, 0, sizeof(grid));

    int newGrid[nRows][nCols];

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
                    break;        

                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::K){
                        isPaused = !isPaused;
                    }
                    else if(event.key.code == sf::Keyboard::R){
                        for(int i=0; i<nRows; i++){
                            for(int j=0; j<nCols; j++){
                                grid[i][j] = 0;
                            }
                        }
                        isPaused = true;
                    }
                    else if(event.key.code == sf::Keyboard::Up){
                        delay+=sf::milliseconds(100);
                    }
                    else if(event.key.code == sf::Keyboard::Down){
                        delay-=sf::milliseconds(100);
                    }
                    break;

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
                if(!isPaused){

                    newGrid[i][j] = grid[i][j];

                    for(int x=-1; x<2; x++){
                        for(int y=-1; y<2; y++){
                            neighbourCount+=grid[i+x][j+y];
                        }
                    }

                    neighbourCount -= grid[i][j];
                    
                    if(grid[i][j]==1 && (neighbourCount>3 || neighbourCount<2)){
                        newGrid[i][j] = 0;
                    }
                    else if(neighbourCount==3){
                        newGrid[i][j] = 1;
                    }
                }

            }
        }

        if(!isPaused){
            for(int i=0; i<nRows; i++){
                for(int j=0; j<nCols; j++){
                    grid[i][j] = newGrid[i][j];
                }
            }
            window.draw(pause);
        }
        else{
            window.draw(play);
        }

        window.draw(info);

        window.display();

        if(!isPaused){
            sf::sleep(delay);
        }
    }

    return -1;
}