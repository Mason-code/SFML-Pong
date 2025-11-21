#include <iostream>
#include <vector>
#include <SFML/Audio.hpp> // if computer can't find: with VS2019 - close VS and de;lete the hidden .vs directory in the project directory. the compile again
#include <SFML/Graphics.hpp>


// constants
int WIN_WIDTH = 800;
int WIN_HEIGHT = 800;

float VERT_BALL_VELOCITY = .5f;
float HORIZ_BALL_VELOCITY = .0f;


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "My window", sf::Style::Titlebar | sf::Style::Close);





    // create the shapes
    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition({ 200, 10 });





    sf::RectangleShape leftPaddle({ 20, 70 });
    leftPaddle.setFillColor(sf::Color::Red);
    leftPaddle.setPosition({ 0 , 800 / 2 - 35 });

    sf::RectangleShape rightPaddle({ 20, 70 });
    rightPaddle.setFillColor(sf::Color::Red);
    rightPaddle.setPosition({ 800 - 20 , 800 / 2 - 35 });




    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {

            float vertSpeed = 30.f;

            /*

            If you have a regular object, you use the dot '.' operator:
            sf::Event event;
            event.type; // access the 'type' member of the event object

            If you have a pointer to an object, you use the arrow '->' operator:
            sf::Event* eventPtr = &event;
            eventPtr->type; // access the 'type' member through the pointer

            */

            
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) { //Check if the current event is a KeyPressed event. | If it is, get a pointer to the KeyPressed data and store it in 'key'.

                if (key->code == sf::Keyboard::Key::W) {
                    leftPaddle.move(sf::Vector2f(0.f, -vertSpeed));
                }
                if (key->code == sf::Keyboard::Key::S) {
                    leftPaddle.move(sf::Vector2f(0.f, vertSpeed));
                }

                if (key->code == sf::Keyboard::Key::Up) {
                    rightPaddle.move(sf::Vector2f(0.f, -vertSpeed));
                }
                if (key->code == sf::Keyboard::Key::Down) {
                    rightPaddle.move(sf::Vector2f(0.f, vertSpeed));
                }
               
            }

            

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

       
        if (ball.getPosition().y >= WIN_HEIGHT) {
            std::cout << "4" << "\n";
            VERT_BALL_VELOCITY *= -1;
            //ball.setPosition({ 0,749 });
        }

        ball.move({ HORIZ_BALL_VELOCITY, VERT_BALL_VELOCITY });
        window.draw(ball);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
     
        // end the current frame
        window.display();
    }
}