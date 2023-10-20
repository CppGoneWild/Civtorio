#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"

#include "hex.hh"
#include "hex_sfml.hh"
#include "hex_imgui.hh"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo Hex");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    sf::VertexArray array(sf::Triangles);

    sf::Clock deltaClock;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        array.clear();

        hex::append_hex(array, hex::Coord(hex::OffsetCoord(0, 0)), sf::Color::White);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(-1, -1)), sf::Color::Red);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(0, 1)), sf::Color::Blue);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(1, 0)), sf::Color::Green);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(1, 1)), sf::Color::Yellow);

        window.clear();

        window.draw(array);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    return 0;
}
