#include "show_info.hh"

#include "imgui.h"


#include <algorithm> // find




/*******************************************************************************
               ____    _____ __                  ____      ____
              /  _/   / ___// /_  ____ _      __/  _/___  / __/___
              / /     \__ \/ __ \/ __ \ | /| / // // __ \/ /_/ __ \
            _/ /     ___/ / / / / /_/ / |/ |/ // // / / / __/ /_/ /
           /___/____/____/_/ /_/\____/|__/|__/___/_/ /_/_/  \____/
              /_____/
*******************************************************************************/




static void ensure_name_is_correct_format(std::string & name)
{
	static const std::string precursor_name = "[ShowInfo] ";
	static const std::size_t precursor_name_size = precursor_name.size();

	if (name.compare(0, precursor_name_size, precursor_name) != 0)
		name = precursor_name + name;
}



win_mngr::I_ShowInfo::~I_ShowInfo()
{}

win_mngr::I_ShowInfo::I_ShowInfo(std::string const & show_info_name)
: m_show_info_is_open(false)
, m_show_info_name(show_info_name)
{
	ensure_name_is_correct_format(m_show_info_name);
}

std::string const & win_mngr::I_ShowInfo::show_info_name() const
{
	return (m_show_info_name);
}

bool win_mngr::I_ShowInfo::show_info_is_open() const
{
	return (m_show_info_is_open);
}

void win_mngr::I_ShowInfo::show_info_open() const
{
	m_show_info_is_open = true;
	show_info_windows._push_show_info_win(*this);
}




/*******************************************************************************
   _____ __                  ____      ____    _       ___           __
  / ___// /_  ____ _      __/  _/___  / __/___| |     / (_)___  ____/ /___ _      _______
  \__ \/ __ \/ __ \ | /| / // // __ \/ /_/ __ \ | /| / / / __ \/ __  / __ \ | /| / / ___/
 ___/ / / / / /_/ / |/ |/ // // / / / __/ /_/ / |/ |/ / / / / / /_/ / /_/ / |/ |/ (__  )
/____/_/ /_/\____/|__/|__/___/_/ /_/_/  \____/|__/|__/_/_/ /_/\__,_/\____/|__/|__/____/

*******************************************************************************/




win_mngr::ShowInfoWindows win_mngr::show_info_windows;


win_mngr::ShowInfoWindows::ShowInfoWindows()
: m_show_info_stack()
{}


/*static*/ void win_mngr::ShowInfoWindows::display_imgui()
{
	show_info_windows._display_imgui();
}















//// Called by class I_ShowInfo
//
void win_mngr::ShowInfoWindows::_push_show_info_win(I_ShowInfo const & obj)
{
	const auto found = std::find(m_show_info_stack.begin(),
	                             m_show_info_stack.end(),
	                             &obj);
	if (found != m_show_info_stack.end())
		return ;
	m_show_info_stack.push_front(&obj);
}


void win_mngr::ShowInfoWindows::_pop_show_info_win(I_ShowInfo const & obj)
{
	obj.m_show_info_is_open = false;
	auto found = std::find(m_show_info_stack.begin(),
	                       m_show_info_stack.end(),
	                       &obj);
	if (found == m_show_info_stack.end())
		return ;
	m_show_info_stack.erase(found);
}



//
/////////////////////////////




void win_mngr::ShowInfoWindows::_display_imgui()
{
	std::list<decltype(m_show_info_stack)::const_iterator> to_erase;

	for (auto it = m_show_info_stack.begin();
	          it != m_show_info_stack.end();
	          ++it)
	{
		I_ShowInfo const & current = **it;

		if (current.m_show_info_is_open == true)
		{
			if (ImGui::Begin(current.show_info_name().c_str(), &current.m_show_info_is_open))
				current._display_show_info_imgui();
			ImGui::End();
		}

		// Do not use else, ImGui::Begin can change m_show_info_is_open.
		if (current.m_show_info_is_open == false)
			to_erase.push_back(it);
	}

	for (auto it = to_erase.begin(); it != to_erase.end(); ++it)
		m_show_info_stack.erase(*it);
}


