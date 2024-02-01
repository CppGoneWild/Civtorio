#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"

#include "hex.hh"
#include "hex_sfml.hh"
#include "hex_imgui.hh"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "sfml_ext/sfml_vector_array.hh"



struct cursor_t
{
    cursor_t()
    : off_coord()
    , coord()
    , to_draw(sf::Triangles)
    , color_to_draw(sf::Color::White)
    {}

    void update(sf::Window const & win)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(win);
        sf::Vector2f posf(pos.x, pos.y);

        hex::from_pixel(posf, coord);
        off_coord = hex::OffsetCoord(coord);

        to_draw.clear();
        hex::append_hex_vertice(to_draw, coord, 3.f, color_to_draw);
    }

    void imgui()
    {
        ImGui::Begin("Mouse Cursor");

        ImGui::SeparatorText("Hover");

        ImGui::Value("Hex", coord);
        ImGui::Value("Off", off_coord);

        ImGui::End();
    }


    hex::OffsetCoord off_coord;
    hex::Coord coord;

    VectorArray to_draw;
    sf::Color color_to_draw;
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo Hex");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    cursor_t cursor;
    VectorArray array(sf::Triangles);

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

        cursor.update(window);

        cursor.imgui();


        array.clear();
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(0, 0)), sf::Color::White);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(-1, -1)), sf::Color::Red);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(0, 1)), sf::Color::Blue);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(1, 0)), sf::Color::Green);
        hex::append_hex(array, hex::Coord(hex::OffsetCoord(1, 1)), sf::Color::Yellow);

        window.clear();

        window.draw(array);
        window.draw(cursor.to_draw);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    return 0;
}
