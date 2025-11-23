#include <iostream>
#include <vector>
#include <SFML/Audio.hpp> // if computer can't find: with VS2019 - close VS and de;lete the hidden .vs directory in the project directory. the compile again
#include <SFML/Graphics.hpp>
#include <random>

#include <string>



// sigs
float randomVal(float low, float high);
bool ballIsTouchingPaddle(sf::RectangleShape leftPaddle, sf::RectangleShape rightPaddle, sf::CircleShape ball);
void reset();

// constants
int WIN_WIDTH = 800;
int WIN_HEIGHT = 800;

float VERT_BALL_VELOCITY = 0.f;
float HORIZ_BALL_VELOCITY = 0.f;

sf::CircleShape ball(10);
sf::RectangleShape rightPaddle({ 20, 70 });
sf::RectangleShape leftPaddle({ 20, 70 });



enum class GameState {
    NOT_STARTED,
    STARTED
};

GameState states = GameState::NOT_STARTED;

int main()
{
    sf::Clock clock;
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "Pong", sf::Style::Titlebar | sf::Style::Close);


    int rightScore = 0;
    int leftScore = 0;

    // create the shapes
    sf::Font minecraftia_font("Minecraftia_Regular.ttf");
    sf::Text leftText(minecraftia_font);
    leftText.setString(std::to_string(leftScore));
    leftText.setCharacterSize(100);
    leftText.setOutlineThickness(2.f);
    leftText.setPosition(sf::Vector2f(200- 12, 150));

    sf::Text rightText(minecraftia_font);
    rightText.setString(std::to_string(rightScore));
    rightText.setCharacterSize(100);
    rightText.setOutlineThickness(2.f);
    rightText.setFillColor(sf::Color::White);
    rightText.setPosition(sf::Vector2f(600-12, 150));

    // line down midddle
    std::vector<sf::RectangleShape> line = {};
    int x = 400.f-2.f;
    int y = 0.f;
    for (int i = 0; i < 100; i++) {
        sf::RectangleShape temp({ 4, 26 });
        temp.setPosition(sf::Vector2f( x + 0.f,y + 0.f ));
        y += 33.f;
        line.push_back(temp);
    }


    ball.setFillColor(sf::Color::White);
    ball.setPosition({ 400-10, 400-10 });
    ball.setOutlineColor(sf::Color::Black);
    leftPaddle.setFillColor(sf::Color::Red);
    leftPaddle.setPosition({ 0 , 800 / 2 - 35 });
    rightPaddle.setFillColor(sf::Color::Red);
    rightPaddle.setPosition({ 800 - 20 , 800 / 2 - 35 });


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);



        switch (states) {
        case GameState::NOT_STARTED:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                HORIZ_BALL_VELOCITY = (400.f);
                VERT_BALL_VELOCITY = randomVal(-200.f, 200.f);
                states = GameState::STARTED;

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                HORIZ_BALL_VELOCITY = -(400.f);
                VERT_BALL_VELOCITY = randomVal(-200.f, 200.f);
                states = GameState::STARTED;

            }

            break;

        case GameState::STARTED:
            if (ballIsTouchingPaddle(leftPaddle, rightPaddle, ball)) {
                HORIZ_BALL_VELOCITY *= -1;
            }


            if (ball.getPosition().x >= WIN_WIDTH+20) {
                leftScore++;
                leftText.setString(std::to_string(leftScore));
                reset();

            }
            if (ball.getPosition().x <= -20) {
                rightScore++;
                rightText.setString(std::to_string(rightScore));
                reset();

            }


            break;

        }

        // controls
        float vertSpeed = 500.0f;
        float dt = clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            leftPaddle.move({ 0.f, -vertSpeed * dt });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            leftPaddle.move({ 0.f, vertSpeed * dt });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            rightPaddle.move({ 0.f, -vertSpeed * dt });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            rightPaddle.move({ 0.f, vertSpeed * dt });
        }


       // yop and bottom border
        if (ball.getPosition().y >= WIN_HEIGHT-10) {
            VERT_BALL_VELOCITY *= -1;
        }
        if (ball.getPosition().y <= 0) {
            VERT_BALL_VELOCITY *= -1;
        }

        ball.move({ HORIZ_BALL_VELOCITY * dt, VERT_BALL_VELOCITY *dt});


        window.draw(leftText);
        window.draw(rightText);

        window.draw(ball);
        window.draw(leftPaddle);
        window.draw(rightPaddle);

        for (int i = 0; i < 100; i++) {
            window.draw(line[i]);
        }

     
        // end the current frame
        window.display();
    }
}


float randomVal(float low, float high) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(low, high);
    return distrib(gen);
}


bool ballIsTouchingPaddle(sf::RectangleShape leftPaddle, sf::RectangleShape rightPaddle, sf::CircleShape ball) {
    sf::FloatRect leftP = leftPaddle.getGlobalBounds();
    sf::FloatRect rightP = rightPaddle.getGlobalBounds();
    sf::FloatRect ballInfo = ball.getGlobalBounds();

    if (leftP.contains(ballInfo.getCenter()) || rightP.contains(ballInfo.getCenter())) return true;
    return false;
}

void reset() {
    VERT_BALL_VELOCITY = 0.f;
    HORIZ_BALL_VELOCITY = 0.f;
    ball.setPosition({ 400 - 10, 400 - 10 });
    rightPaddle.setPosition({ 800 - 20 , 800 / 2 - 35 });
    leftPaddle.setPosition({ 0 , 800 / 2 - 35 });

    states = GameState::NOT_STARTED;
    

}