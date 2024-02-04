#include "techno_base.hh"


#include "imgui.h"

#include <cassert>



/*******************************************************************************
                   ______      __                        _
                  / ____/___ _/ /____  ____ _____  _____(_)__
                 / /   / __ `/ __/ _ \/ __ `/ __ \/ ___/ / _ \
                / /___/ /_/ / /_/  __/ /_/ / /_/ / /  / /  __/
                \____/\__,_/\__/\___/\__, /\____/_/  /_/\___/
                                    /____/
*******************************************************************************/



techno::Categorie::Categorie(id_t id,
                             std::string const & n,
                             std::string const & d)
: win_mngr::I_ShowInfo(n), m_id(id), m_name(n), m_description(d)
{
	assert(id);
}

techno::Categorie::id_t techno::Categorie::id() const
{
	return (m_id);
}

std::string const & techno::Categorie::name() const
{
	return (m_name);
}

std::string const & techno::Categorie::description() const
{
	return (m_description);
}


void techno::Categorie::_display_show_info_imgui() const
{
	ImGui::Text("Name : %s", name().c_str());
	ImGui::Separator();
	ImGui::Text("Description : ");
	ImGui::TextWrapped("%s", description().c_str());
}




bool operator==(techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() == rhs.id());
}

bool operator!=(techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() != rhs.id());
}

bool operator< (techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() <  rhs.id());
}

bool operator> (techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() >  rhs.id());
}

bool operator<=(techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() <= rhs.id());
}

bool operator>=(techno::Categorie const & lhs, techno::Categorie const & rhs)
{
	return (lhs.id() >= rhs.id());
}





bool operator==(techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() == rhs);
}

bool operator!=(techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() != rhs);
}

bool operator< (techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() <  rhs);
}

bool operator> (techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() >  rhs);
}

bool operator<=(techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() <= rhs);
}

bool operator>=(techno::Categorie const & lhs, techno::Categorie::id_t const rhs)
{
	return (lhs.id() >= rhs);
}




bool operator==(techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs == rhs.id());
}

bool operator!=(techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs != rhs.id());
}

bool operator< (techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs <  rhs.id());
}

bool operator> (techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs >  rhs.id());
}

bool operator<=(techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs <= rhs.id());
}

bool operator>=(techno::Categorie::id_t const lhs, techno::Categorie const & rhs)
{
	return (lhs >= rhs.id());
}













/*******************************************************************************
                ____                ______          __
               / __ )____ _________/_  __/__  _____/ /_  ____  ____
              / __  / __ `/ ___/ _ \/ / / _ \/ ___/ __ \/ __ \/ __ \
             / /_/ / /_/ (__  )  __/ / /  __/ /__/ / / / / / / /_/ /
            /_____/\__,_/____/\___/_/  \___/\___/_/ /_/_/ /_/\____/
            
*******************************************************************************/



techno::BaseTechno::BaseTechno(techno_id_t tid, Categorie::id_t cid,
                               std::string const & n, std::string const & d,
                               std::vector<Prerequist> const & p,
                               int cost, int mult)
: win_mngr::I_ShowInfo(n)
, m_techno_id(tid)
, m_categorie_id(cid)
, m_name(n)
, m_description(d)
, m_prerequists(p)
, m_base_cost(cost)
, m_multiplier(mult)
{
	assert(m_techno_id);
	assert(m_categorie_id);
	assert(m_base_cost);
	assert(m_multiplier);
}

techno::techno_id_t techno::BaseTechno::techno_id() const
{
	return (m_techno_id);
}

techno::Categorie::id_t techno::BaseTechno::categorie_id() const
{
	return (m_categorie_id);
}


std::string const & techno::BaseTechno::name() const
{
	return (m_name);
}

std::string const & techno::BaseTechno::description() const
{
	return (m_description);
}


std::vector<techno::BaseTechno::Prerequist> const & techno::BaseTechno::prerequists() const
{
	return (m_prerequists);
}


int techno::BaseTechno::base_cost() const
{
	return (m_base_cost);
}

int techno::BaseTechno::multiplier() const
{
	return (m_multiplier);
}


void techno::BaseTechno::_display_show_info_imgui() const
{
	if (ImGui::BeginTable("ShowInfo", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders))
	{
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Data");

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Name");
        ImGui::TableNextColumn();
		ImGui::Text("%s", name().c_str());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Description");
        ImGui::TableNextColumn();
		ImGui::TextWrapped("%s", description().c_str());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Technologie ID");
        ImGui::TableNextColumn();
		ImGui::Text("%lu", techno_id());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Categorie ID");
        ImGui::TableNextColumn();
		ImGui::Text("%lu", categorie_id());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Base Cost");
        ImGui::TableNextColumn();
		ImGui::Text("%i", base_cost());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Cost Multiplier");
        ImGui::TableNextColumn();
		ImGui::Text("%i", multiplier());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
		ImGui::Text("Prerequists");
        ImGui::TableNextColumn();
        if (prerequists().empty())
        {
			ImGui::Text("None");
        }
		else if (ImGui::BeginTable("PrerequistsTable", 2, ImGuiTableFlags_Borders))
		{
	        ImGui::TableSetupColumn("Tech. ID", ImGuiTableColumnFlags_WidthFixed);
	        ImGui::TableSetupColumn("Level", ImGuiTableColumnFlags_WidthFixed);
	        ImGui::TableHeadersRow();

			for (auto it = prerequists().cbegin(); it != prerequists().cend(); ++it)
			{
        		ImGui::TableNextRow();
		        ImGui::TableNextColumn();
				ImGui::Text("%lu", it->id);
		        ImGui::TableNextColumn();
				ImGui::Text("%i", it->level);
			}

	        ImGui::EndTable();
		}

        ImGui::EndTable();
	}
}






bool operator==(techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() == rhs.techno_id());
}

bool operator!=(techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() != rhs.techno_id());
}

bool operator< (techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() <  rhs.techno_id());
}

bool operator> (techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() >  rhs.techno_id());
}

bool operator<=(techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() <= rhs.techno_id());
}

bool operator>=(techno::BaseTechno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.techno_id() >= rhs.techno_id());
}





bool operator==(techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() == rhs);
}

bool operator!=(techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() != rhs);
}

bool operator< (techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() <  rhs);
}

bool operator> (techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() >  rhs);
}

bool operator<=(techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() <= rhs);
}

bool operator>=(techno::BaseTechno const & lhs, techno::techno_id_t const rhs)
{
	return (lhs.techno_id() >= rhs);
}


bool operator==(techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs == rhs.techno_id());
}

bool operator!=(techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs != rhs.techno_id());
}

bool operator< (techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs <  rhs.techno_id());
}

bool operator> (techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs >  rhs.techno_id());
}

bool operator<=(techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs <= rhs.techno_id());
}

bool operator>=(techno::techno_id_t const lhs, techno::BaseTechno const & rhs)
{
	return (lhs >= rhs.techno_id());
}









/*******************************************************************************
              ______                                      ____  ____
             / ____/___  ____ ___  ____ ___  ____  ____  / __ \/ __ )
            / /   / __ \/ __ `__ \/ __ `__ \/ __ \/ __ \/ / / / __  |
           / /___/ /_/ / / / / / / / / / / / /_/ / / / / /_/ / /_/ /
           \____/\____/_/ /_/ /_/_/ /_/ /_/\____/_/ /_/_____/_____/
           
*******************************************************************************/



techno::Categorie const * techno::CommonDB::add(Categorie const & c)
{
	auto res = m_categories.emplace(c.id(), c);

	assert(res.second);

	return (&(res.first->second));
}

techno::BaseTechno const * techno::CommonDB::add(BaseTechno const & t)
{
	auto res = m_techno.emplace(t.techno_id(), t);

	assert(res.second);

	return (&(res.first->second));
}


techno::Categorie const * techno::CommonDB::categorie(Categorie::id_t id) const
{
	auto res = m_categories.find(id);
	return (res == m_categories.cend() ? nullptr : &(res->second));
}

techno::BaseTechno const * techno::CommonDB::techno(techno_id_t id) const
{
	auto res = m_techno.find(id);
	return (res == m_techno.cend() ? nullptr : &(res->second));
}


std::map<techno::Categorie::id_t, techno::Categorie> const & techno::CommonDB::categories() const
{
	return (m_categories);
}

std::map<techno::techno_id_t, techno::BaseTechno> const & techno::CommonDB::techno() const
{
	return (m_techno);
}
