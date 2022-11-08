/*Anthony Wade - B00610872
COM326 - MakeItSnow Application*/

#include <iostream>  
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <random>
#include <vector>
using namespace std;

// Define render window size constants
#define winWidth 1024
#define winHeight 700

void createBackFlake(std::vector<sf::CircleShape>& arr);

int main() {

    // Elapsed time since last snowflake spawn with random seeding.
    int elapsed = 0;
    srand((int)time(0));

    //Max number of flakes on screen.
    int numOfSnowFlakes = 200;

    // Setting delay between the respawn of flakes.
    int delay = 5;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Merry Christmas");

    // Texture set up
    sf::Texture tex_background, tex_snowman, tex_chimney, tex_signpost;
    tex_background.loadFromFile("assets/winter_forest_scene.jpg");
    tex_snowman.loadFromFile("assets/alSnow.png");
    tex_chimney.loadFromFile("assets/chimney.png");
    tex_signpost.loadFromFile("assets/signpost.png");

    // Sprite set up
    sf::Sprite spr_background, spr_snowman, spr_chimney, spr_signpost;
    spr_background.setTexture(tex_background);
    spr_snowman.setTexture(tex_snowman);
    spr_chimney.setTexture(tex_chimney);
    spr_signpost.setTexture(tex_signpost);
    spr_signpost.scale(sf::Vector2f(0.70f, 0.70f));
    spr_signpost.setPosition(sf::Vector2f(100.0f, 400.0f)); // Absolute position
    spr_chimney.scale(sf::Vector2f(0.50, 0.50f));
    spr_chimney.setPosition(sf::Vector2f(600.0f, 520.0f)); // Absolute position
    spr_snowman.scale(sf::Vector2f(0.80f, 0.80f));
    spr_snowman.setPosition(sf::Vector2f(640.0f, -400.0f)); // Start position
    sf::Vector2f alSnowSpd = sf::Vector2f(0.0f, 0.3f); // Speed to make sprite go down the y axis

    // Import font file
    sf::Font font;
    font.loadFromFile("Assets/blacknorthfont.otf");

    // Text set-up & alignment with signpost sprite
    sf::Text text;
    text.setFont(font);
    text.setString("Let it \n    'AL'   \nSNOW");
    text.setCharacterSize(36);
    text.setFillColor(sf::Color(255, 42, 0));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(220.0f, 445.0f));

    // Music set-up
    sf::Music music;
    music.openFromFile("assets/Jingle-Bells-3.ogg");
    music.setLoop(true);
    music.play();
    
    std::vector<sf::CircleShape> snowflakesBack;

    // Run the program as long as the window is open
    while (window.isOpen()) {
        
        elapsed++;

        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // If to create another snowflake if the delay has bpassed and max num of snowflakes has not been reached
        if (elapsed >= delay && snowflakesBack.size() < numOfSnowFlakes) {
            createBackFlake(snowflakesBack);
            elapsed = 0;
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // All drawings
        window.draw(spr_background);
        window.draw(spr_snowman);
        spr_snowman.move(alSnowSpd);
        window.draw(spr_chimney);
        window.draw(spr_signpost);
        window.draw(text);
        
        for (int i = 0; i < snowflakesBack.size(); i++) {
            snowflakesBack[i].move(rand() % 1, snowflakesBack[i].getRadius() * 0.1f);
            window.draw(snowflakesBack[i]);

            // If to stop snowflakes from being drawn outside the window (only applicable to y axis as they arent being drawn on the x axis)
            if (snowflakesBack[i].getPosition().y >= winHeight) {
                snowflakesBack.erase(snowflakesBack.begin() + i);
            }
        }

        // If to make the sprite loop from top
        if (spr_snowman.getPosition().y >= winHeight) {
            spr_snowman.setPosition(sf::Vector2f(640.0f, -400.0f));
            cout << "al loops";
        }
        // End the current frame
        window.display();

    }
    return 0;
}

// Creating a snowflake and storing it in an array
void createBackFlake(std::vector<sf::CircleShape>& arr) {
    sf::CircleShape Backflake(float(rand()) / (float)(RAND_MAX / 4.0f) + 0.3f);
    Backflake.setFillColor(sf::Color(200, 200, 200));
    Backflake.setPosition(float(rand() % winWidth), 0.0f);

    arr.emplace_back(Backflake);
}
/*References
Stefan, Ivanovski. (2019) "falling-snow", https://github.com/limepixl/falling-snow. [Accessed on 01/11/2022] */