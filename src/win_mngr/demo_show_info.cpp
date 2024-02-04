#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "sfml_ext/sfml_vector_array.hh"


#include "show_info.hh"





class TestShowInfo : public win_mngr::I_ShowInfo
{
public:
    TestShowInfo(int i)
    : win_mngr::I_ShowInfo(std::string("TestShowInfo:") + std::to_string(i))
    , m_i(i)
    {}

    virtual ~TestShowInfo()
    {}

protected:
    //// Called by class ShowInfoWindows
    //
    virtual void _display_show_info_imgui() const
    {
        ImGui::Text("bla bla : %i", m_i);
    }
    //
    /////////////////////////////

private:
    int m_i;
};





int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo Hex");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();


    TestShowInfo t1(1);
    TestShowInfo t2(2);
    TestShowInfo t3(3);
    TestShowInfo t4(4);
    TestShowInfo t5(5);


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


        ImGui::Begin("Test");
        if (ImGui::Button("ShowInfo 1")) t1.show_info_open();
        if (ImGui::Button("ShowInfo 2")) t2.show_info_open();
        if (ImGui::Button("ShowInfo 3")) t3.show_info_open();
        if (ImGui::Button("ShowInfo 4")) t4.show_info_open();
        if (ImGui::Button("ShowInfo 5")) t5.show_info_open();
        ImGui::End();


        win_mngr::ShowInfoWindows::display_imgui();


        window.clear();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    return (0);
}
