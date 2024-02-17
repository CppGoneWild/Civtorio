#include "techno.hh"


#include "techno_base.hh"
#include "imgui.h"

#include <cmath>




static double __get_damp_factor(int step)
{
	static const double damp_factor = -0.009274;

	if (step == 0)
		return (0.0);

	if (step == 1)
		return (1.0);

	--step;

	return (std::exp(damp_factor * static_cast<double>(step * step)));
}

static double __get_dampened_prod(int nbr_of_source)
{
	double res = 0;
	for (int i = 0; i < nbr_of_source; ++i)
		res += __get_damp_factor(i);
	return (res);
}



static int __next_level_cost(int base_cost, int multiplier, int level_target)
{
	if (level_target >= 5)
		return (0);

	int res = base_cost * std::pow(multiplier, level_target);

	return (res);
}


/*
 * 0 : b
 * 1 : b*m
 * 2 : b*m*m
 * 3 : b*m*m*m
 * 4 : b*m*m*m*m
 * 5 : b*m*m*m*m*m
 */







techno::techno_id_t techno::Techno::id() const
{
	return (m_id);
}

techno::BaseTechno const * techno::Techno::base() const
{
	return (m_base);
}

techno::Categorie const * techno::Techno::categorie() const
{
	return (m_categorie);
}

std::vector<techno::Techno::Prerequist> const & techno::Techno::prerequists() const
{
	return (m_prerequists);
}




bool techno::Techno::can_be_researched() const
{
	for (auto it = m_prerequists.cbegin(); it != m_prerequists.cbegin(); ++it)
	{
		if (it->tech->level() < it->level)
			return (false);
	}
	return (true);
}




int techno::Techno::level() const
{
	return (m_level);
}

int techno::Techno::cost_to_next_level() const
{
	return (m_cost_to_next_level);
}

double techno::Techno::invested_to_next_level() const
{
	return (m_invested_to_next_level);
}

double techno::Techno::remaining_to_next_level() const
{
	return (static_cast<double>(m_cost_to_next_level) - m_invested_to_next_level);
}




double techno::Techno::invest(double val)
{
	if (m_level >= 5)
		return (val);

	double max = remaining_to_next_level();
	if (max < val)
	{
		++m_level;
		m_invested_to_next_level = 0;
		m_cost_to_next_level = __next_level_cost(m_base->base_cost(), m_base->multiplier(), m_level + 1);
		return (val - max);
	}

	m_invested_to_next_level += val;
	return (0.);
}




techno::Techno::Techno(BaseTechno const & t, Categorie const & c)
: m_id(t.techno_id())
, m_base(&t)
, m_categorie(&c)
, m_prerequists()
, m_level(0)
, m_cost_to_next_level(m_base->base_cost())
, m_invested_to_next_level(0)
{}








bool operator==(techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() == rhs.id());
}

bool operator!=(techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() != rhs.id());
}

bool operator< (techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() <  rhs.id());
}

bool operator> (techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() >  rhs.id());
}

bool operator<=(techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() <= rhs.id());
}

bool operator>=(techno::Techno const & lhs, techno::Techno const & rhs)
{
	return (lhs.id() >= rhs.id());
}




bool operator==(techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() == rhs);
}

bool operator!=(techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() != rhs);
}

bool operator< (techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() <  rhs);
}

bool operator> (techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() >  rhs);
}

bool operator<=(techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() <= rhs);
}

bool operator>=(techno::Techno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.id() >= rhs);
}




bool operator==(techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs == rhs.id());
}

bool operator!=(techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs != rhs.id());
}

bool operator< (techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs <  rhs.id());
}

bool operator> (techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs >  rhs.id());
}

bool operator<=(techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs <= rhs.id());
}

bool operator>=(techno::techno_id_t lhs, techno::Techno const & rhs)
{
	return (lhs >= rhs.id());
}




bool operator==(techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() == rhs.id());
}

bool operator!=(techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() != rhs.id());
}

bool operator< (techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() <  rhs.id());
}

bool operator> (techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() >  rhs.id());
}

bool operator<=(techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() <= rhs.id());
}

bool operator>=(techno::BaseTechno const & lhs, techno::Techno const & rhs)
{
	return (lhs.techno_id() >= rhs.id());
}




bool operator==(techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() == rhs.techno_id());
}

bool operator!=(techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() != rhs.techno_id());
}

bool operator< (techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() <  rhs.techno_id());
}

bool operator> (techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() >  rhs.techno_id());
}

bool operator<=(techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() <= rhs.techno_id());
}

bool operator>=(techno::Techno const & lhs, techno::BaseTechno const & rhs)
{
	return (lhs.id() >= rhs.techno_id());
}
















void techno::TechnoDB::build(CommonDB const & db)
{
	assert(m_common_db == nullptr);
	assert(m_techno.empty());

	m_common_db = &db;

	for (auto it = db.techno().cbegin(); it != db.techno().cend(); ++it)
	{
		Categorie const * cat = db.categorie(it->second.categorie_id());
		assert(cat);
		m_techno[it->second.techno_id()] = Techno(it->second, *cat);

	}

	for (auto tech = m_techno.begin(); tech != m_techno.end(); ++tech)
	{
		auto const & base_prereq = tech->second.base()->prerequists();
		
		for (auto it_prereq = base_prereq.cbegin(); it_prereq != base_prereq.cend(); ++it_prereq)
		{
			auto const & tech_found = m_techno.find(it_prereq->id);
			assert(tech_found != m_techno.end());
			tech->second.m_prerequists.emplace_back(&(tech_found->second), it_prereq->level);
		}
	}
}




techno::Techno const * techno::TechnoDB::find(techno_id_t id) const
{
	auto res = m_techno.find(id);
	return (res == m_techno.cend() ? nullptr : &(res->second));
}




techno::CommonDB const * techno::TechnoDB::common_db() const
{
	return (m_common_db);
}

std::map<techno::techno_id_t, techno::Techno> const & techno::TechnoDB::techno() const
{
	return (m_techno);
}

std::map<techno::techno_id_t, techno::Techno> & techno::TechnoDB::techno()
{
	return (m_techno);
}












/*




techno::TechnoDB const & techno::TechnoManager::db() const
{
	return (m_db);
}

techno::TechnoDB & techno::TechnoManager::db()
{
	return (m_db);
}

techno::TechnoManager::tech_source_map_t const & techno::TechnoManager::tech_source() const
{
	return (m_tech_source);
}

techno::TechnoManager::tech_source_map_t & techno::TechnoManager::tech_source()
{
	return (m_tech_source);
}



double techno::TechnoManager::get_tech_prod(Categorie::id_t id) const
{
	auto found = m_tech_source.find(id);
	if (found == m_tech_source.cend())
		return (0);

	int nb_source = 0;
	for (auto it = found->cbegin(); it != found->cend(); ++it)
		if (it->active())
			++nb_source;

	return (__get_dampened_prod(nb_source));
}

double techno::TechnoManager::get_next_efficiency(Categorie::id_t id) const
{
	auto found = m_tech_source.find(id);
	if (found == m_tech_source.cend())
		return (0);

	int nb_source = 0;
	for (auto it = found->cbegin(); it != found->cend(); ++it)
		if (it->active())
			++nb_source;

	return (__get_damp_factor(nb_source + 1));
}

void techno::TechnoManager::add_to_stock(Categorie::id_t id, double val)
{
	m_stock[id] += val;
}

void techno::TechnoManager::add_tech_source(I_TechSource const & src)
{
	m_tech_source[src.categorie_id()].push_back(src);
}

void techno::TechnoManager::del_tech_source(I_TechSource const & src)
{
}

void techno::TechnoManager::clr_tech_source(Categorie::id_t id)
{
	auto found = m_tech_source.find(id);
	if (found != m_tech_source.end())
		m_tech_source.erase(found);
}

void techno::TechnoManager::clr_tech_source()
{
	m_tech_source.clear();
}



std::list<techno::Techno *> const & techno::TechnoManager::research_queue() const
{
	return (m_research_queue);
}

std::list<techno::Techno *> & techno::TechnoManager::research_queue()
{
	return (m_research_queue);
}

techno::Techno const * techno::TechnoManager::currently_researched() const
{
	return (m_research_queue.empty() ? nullptr : m_research_queue.front());
}




double techno::TechnoManager::nb_day_remaining() const
{
	Techno const * tmp = currently_researched();
	if (tmp == nullptr)
		return (0.);

	double prod = get_tech_prod(tmp->categorie->id());
	if (prod <= 0.)
		return (999999.);

	double remaining = tmp->remaining_to_next_level();

	return (prod / remaining);
}



void techno::TechnoManager::advance_one_day()
{
	Techno const * tmp = currently_researched();
	if (tmp)
	{
		const int lvl_before = tmp->level();
		auto & stock = m_stock[tmp->categorie()->id()];

		double prod = get_tech_prod(tmp->categorie()->id()) + stock;
		stock = tmp->invest(prod);

		if (tmp->level() > lvl_before)
			m_research_queue.pop_front();
	}
}

*/