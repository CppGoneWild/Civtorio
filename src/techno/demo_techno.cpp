#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "sfml_ext/sfml_vector_array.hh"


#include "techno_base.hh"
#include "techno.hh"




void imgui_common_db(techno::CommonDB const & db)
{
    if (ImGui::BeginTable("Cat.", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupScrollFreeze(0, 1);

        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("ShowInfo", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();


        for (auto it  = db.categories().cbegin();
                  it != db.categories().cend();
                  ++it)
        {
            ImGui::TableNextRow();

            ImGui::PushID(it->second.id());

            ImGui::TableNextColumn();
            ImGui::Text("%lu", it->second.id());
            ImGui::TableNextColumn();
            ImGui::Text("%s", it->second.name().c_str());
            ImGui::TableNextColumn();
            if (ImGui::SmallButton("ShowInfo"))
                it->second.show_info_open();

            ImGui::PopID();
        }

        ImGui::EndTable();
    }



    if (ImGui::BeginTable("Tech", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupScrollFreeze(0, 1);

        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("ShowInfo", ImGuiTableColumnFlags_WidthFixed);

        ImGui::TableHeadersRow();


        for (auto it  = db.techno().cbegin();
                  it != db.techno().cend();
                  ++it)
        {
            ImGui::TableNextRow();

            ImGui::PushID(it->second.techno_id());

            ImGui::TableNextColumn();
            ImGui::Text("%lu", it->second.techno_id());
            ImGui::TableNextColumn();
            ImGui::Text("%s", it->second.name().c_str());
            ImGui::TableNextColumn();
            if (ImGui::SmallButton("ShowInfo"))
                it->second.show_info_open();

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}







void imgui_techno_db(techno::TechnoDB const & db)
{
    if (ImGui::BeginTable("Techno", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders))
    {
        ImGui::TableSetupScrollFreeze(0, 1);

        ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("ShowInfo", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();


        for (auto it  = db.techno().cbegin();
                  it != db.techno().cend();
                  ++it)
        {
            ImGui::TableNextRow();

            ImGui::PushID(it->second.id());

            ImGui::TableNextColumn();
            ImGui::Text("%lu", it->second.id());
            ImGui::TableNextColumn();
            ImGui::Text("%s", it->second.base()->name().c_str());
            ImGui::TableNextColumn();
            if (ImGui::SmallButton("ShowInfo"))
                ; //it->second.show_info_open();

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}







int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo Hex");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();


    techno::CommonDB commonDB;
    techno::TechnoDB technoDB;

    commonDB.add(techno::Categorie(1, "Food Production"));
    commonDB.add(techno::Categorie(2, "Others"));

    commonDB.add(techno::BaseTechno(1, 1, "Hunting", "", {}, 100, 2));
    commonDB.add(techno::BaseTechno(2, 1, "Forraging", "", {}, 100, 2));
    commonDB.add(techno::BaseTechno(3, 1, "Fishing", "", {}, 100, 2));

    commonDB.add(techno::BaseTechno(4, 2, "Boat Building", "", {}, 100, 3));
    commonDB.add(techno::BaseTechno(5, 2, "Archery ", "", {}, 100, 3));

    commonDB.add(techno::BaseTechno(6, 1, "Adv. Hunting", "", {{1, 3}, {5, 1}}, 500, 3));
    commonDB.add(techno::BaseTechno(7, 1, "Adv. Fishing", "", {{3, 3}, {4, 1}}, 500, 3));


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

        ImGui::Begin("CommonDB");
        if (ImGui::Button("Build TechTree"))
            technoDB.build(commonDB);
        imgui_common_db(commonDB);
        ImGui::End();

        ImGui::Begin("TechnoDB");
        imgui_techno_db(technoDB);
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
