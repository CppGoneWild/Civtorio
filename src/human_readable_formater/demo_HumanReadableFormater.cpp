#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"

#include "HumanReadableFormater.hh"
#include "HumanReadableFormater_imgui.hh"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int main()
{
    HumanReadableFormater::format_short_t format_short;
    HumanReadableFormater::format_exact_t format_exact;
    double value_short;
    double value_exact;


    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo HumanReadableFormater");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        {
            ImGui::Begin("Short Form");

            ImGui::Widget(format_short);

            ImGui::Separator();

            ImGui::DragScalar(" Input", ImGuiDataType_Double, &value_short, 50.f);
            ImGui::ValueShort("Output:", value_short, format_short);

            ImGui::End();
        }


        {
            ImGui::Begin("Exact Form");

            ImGui::Widget(format_exact);

            ImGui::Separator();

            ImGui::DragScalar(" Input", ImGuiDataType_Double, &value_exact, 50.f);
            ImGui::ValueExact("Output:", value_exact, format_exact);


            ImGui::End();
        }


        window.clear();



        ImGui::SFML::Render(window);
        window.display();
    }

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    return 0;
}
