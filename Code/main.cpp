//Made by Mario and Ethan

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

using namespace std;
using namespace sf;

int main()
{
    int pixelWidth = VideoMode::getDesktopMode().width;
    int pixelHeight = VideoMode::getDesktopMode().height;

    VideoMode vm(pixelWidth, pixelHeight);

    RenderWindow RenderWindow(vm, "Mandelbrot", Style::Default);

    Font font;

    if (!font.loadFromFile("Sawasdee-Bold.ttf"))
    {
        cout << "Error loading font!!";
        return 1;
    }

    Text text;

    text.setFont(font);

    text.setString("test");

    text.setCharacterSize(24);

    text.setFillColor(Color::White);

    ComplexPlane veryComplex(pixelWidth, pixelHeight);
    Vector2i mouseLocation, clickPos;

    while (RenderWindow.isOpen())
    {

        /*
        ****************************************
        Handle input
        ****************************************
        */

        Event event;
        while (RenderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) RenderWindow.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "the left button was pressed" << endl;

                    clickPos = {event.mouseButton.x, event.mouseButton.y};
                    veryComplex.zoomIn();
                    veryComplex.setCenter(clickPos);
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    cout << "the Right button was pressed" << endl;

                    clickPos = {event.mouseButton.x, event.mouseButton.y};
                    veryComplex.zoomOut();
                    veryComplex.setCenter(clickPos);
                }
            }
            if (event.type == sf::Event::MouseMoved)
            {
                mouseLocation = {event.mouseMove.x, event.mouseMove.y};

                veryComplex.setMouseLocation(mouseLocation);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            RenderWindow.close();
        }

        /*
        ****************************************
        Draw the scene
        ****************************************
        */

        //Update scene
        veryComplex.updateRender();
        veryComplex.loadText(text);

        //Draw scene (plane and text)
        RenderWindow.clear();
        RenderWindow.draw(veryComplex);
        RenderWindow.draw(text);
        RenderWindow.display();
    }
    return 0;
}
