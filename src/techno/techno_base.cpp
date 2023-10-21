#include "techno_base.hh"


#include <cassert>




techno::Categorie::Categorie(id_t id, std::string const & n)
: m_id(id), m_name(n)
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





bool operator==(techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() == rhs);
}

bool operator!=(techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() != rhs);
}

bool operator< (techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() <  rhs);
}

bool operator> (techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() >  rhs);
}

bool operator<=(techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() <= rhs);
}

bool operator>=(techno::Categorie const & lhs, techno::Categorie::id_t rhs)
{
	return (lhs.id() >= rhs);
}




bool operator==(techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs == rhs.id());
}

bool operator!=(techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs != rhs.id());
}

bool operator< (techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs <  rhs.id());
}

bool operator> (techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs >  rhs.id());
}

bool operator<=(techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs <= rhs.id());
}

bool operator>=(techno::Categorie::id_t lhs, techno::Categorie const & rhs)
{
	return (lhs >= rhs.id());
}









techno::BaseTechno::BaseTechno(techno_id_t tid, Categorie::id_t cid,
                               std::string const & n, std::string const & d,
                               std::vector<Prerequist> const & p,
                               int cost, int mult)
: m_techno_id(tid)
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





bool operator==(techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() == rhs);
}

bool operator!=(techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() != rhs);
}

bool operator< (techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() <  rhs);
}

bool operator> (techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() >  rhs);
}

bool operator<=(techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() <= rhs);
}

bool operator>=(techno::BaseTechno const & lhs, techno::techno_id_t rhs)
{
	return (lhs.techno_id() >= rhs);
}


bool operator==(techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs == rhs.techno_id());
}

bool operator!=(techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs != rhs.techno_id());
}

bool operator< (techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs <  rhs.techno_id());
}

bool operator> (techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs >  rhs.techno_id());
}

bool operator<=(techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs <= rhs.techno_id());
}

bool operator>=(techno::techno_id_t lhs, techno::BaseTechno const & rhs)
{
	return (lhs >= rhs.techno_id());
}












techno::Categorie const * techno::CommonDB::add(Categorie const & c)
{
	auto res = m_categories.insert(c);

	assert(res.second);

	return (&(*(res.first)));
}

techno::BaseTechno const * techno::CommonDB::add(BaseTechno const & t)
{
	auto res = m_techno.insert(t);

	assert(res.second);

	return (&(*(res.first)));
}


techno::Categorie const * techno::CommonDB::find(Categorie::id_t id) const
{
	auto res = m_categories.find(id);
	return (res == m_categories.cend() ? nullptr : &(*res));
}

techno::BaseTechno const * techno::CommonDB::find(techno_id_t id) const
{
	auto res = m_techno.find(id);
	return (res == m_techno.cend() ? nullptr : &(*res));
}


std::set<techno::Categorie> const & techno::CommonDB::categories() const
{
	return (m_categories);
}

std::set<techno::BaseTechno> const & techno::CommonDB::techno() const
{
	return (m_techno);
}
