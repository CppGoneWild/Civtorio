#ifndef TECHNO_BASE_HH
#define TECHNO_BASE_HH


#include <cstdint>
#include <string>
#include <vector>
#include <set>


#include "techno_types.hh"



namespace techno
{


class Categorie
{
public:
	using id_t = std::uint64_t;

	Categorie()                  = default;
	Categorie(Categorie const &) = default;
	Categorie(Categorie &&)      = default;
	~Categorie()                 = default;

	Categorie & operator=(Categorie const &) = default;
	Categorie & operator=(Categorie &&)      = default;

	Categorie(id_t, std::string const &);

	id_t id() const;
	std::string const & name() const;

private:	
	id_t m_id = 0;
	std::string m_name;
};


} // techno




bool operator==(techno::Categorie const &, techno::Categorie const &);
bool operator!=(techno::Categorie const &, techno::Categorie const &);
bool operator< (techno::Categorie const &, techno::Categorie const &);
bool operator> (techno::Categorie const &, techno::Categorie const &);
bool operator<=(techno::Categorie const &, techno::Categorie const &);
bool operator>=(techno::Categorie const &, techno::Categorie const &);




bool operator==(techno::Categorie const &, techno::Categorie::id_t);
bool operator!=(techno::Categorie const &, techno::Categorie::id_t);
bool operator< (techno::Categorie const &, techno::Categorie::id_t);
bool operator> (techno::Categorie const &, techno::Categorie::id_t);
bool operator<=(techno::Categorie const &, techno::Categorie::id_t);
bool operator>=(techno::Categorie const &, techno::Categorie::id_t);

bool operator==(techno::Categorie::id_t, techno::Categorie const &);
bool operator!=(techno::Categorie::id_t, techno::Categorie const &);
bool operator< (techno::Categorie::id_t, techno::Categorie const &);
bool operator> (techno::Categorie::id_t, techno::Categorie const &);
bool operator<=(techno::Categorie::id_t, techno::Categorie const &);
bool operator>=(techno::Categorie::id_t, techno::Categorie const &);










namespace techno
{


class BaseTechno
{
public:
	struct Prerequist
	{
		techno_id_t id = 0;
		int level = 0;
	};

	BaseTechno()                               = default;
	BaseTechno(BaseTechno const &)             = default;
	BaseTechno(BaseTechno &&)                  = default;
	BaseTechno & operator=(BaseTechno const &) = default;
	BaseTechno & operator=(BaseTechno &&)      = default;
	~BaseTechno()                              = default;

	BaseTechno(techno_id_t, Categorie::id_t,
	           std::string const &, std::string const &,
	           std::vector<Prerequist> const &,
	           int cost, int mult);

	techno_id_t techno_id() const;
	Categorie::id_t categorie_id() const;

	std::string const & name() const;
	std::string const & description() const;

	std::vector<Prerequist> const & prerequists() const;

	int base_cost() const;
	int multiplier() const;

private:

	techno_id_t     m_techno_id    = 0;
	Categorie::id_t m_categorie_id = 0;

	std::string m_name;
	std::string m_description;

	std::vector<Prerequist> m_prerequists;

	int m_base_cost;
	int m_multiplier;
};


} // techno




bool operator==(techno::BaseTechno const &, techno::BaseTechno const &);
bool operator!=(techno::BaseTechno const &, techno::BaseTechno const &);
bool operator< (techno::BaseTechno const &, techno::BaseTechno const &);
bool operator> (techno::BaseTechno const &, techno::BaseTechno const &);
bool operator<=(techno::BaseTechno const &, techno::BaseTechno const &);
bool operator>=(techno::BaseTechno const &, techno::BaseTechno const &);




bool operator==(techno::BaseTechno const &, techno::techno_id_t);
bool operator!=(techno::BaseTechno const &, techno::techno_id_t);
bool operator< (techno::BaseTechno const &, techno::techno_id_t);
bool operator> (techno::BaseTechno const &, techno::techno_id_t);
bool operator<=(techno::BaseTechno const &, techno::techno_id_t);
bool operator>=(techno::BaseTechno const &, techno::techno_id_t);

bool operator==(techno::techno_id_t, techno::BaseTechno const &);
bool operator!=(techno::techno_id_t, techno::BaseTechno const &);
bool operator< (techno::techno_id_t, techno::BaseTechno const &);
bool operator> (techno::techno_id_t, techno::BaseTechno const &);
bool operator<=(techno::techno_id_t, techno::BaseTechno const &);
bool operator>=(techno::techno_id_t, techno::BaseTechno const &);






namespace techno
{


class CommonDB
{
public:
	CommonDB()  = default;
	~CommonDB() = default;

	Categorie const * add(Categorie const &);
	BaseTechno const * add(BaseTechno const &);

	Categorie const * find(Categorie::id_t) const;
	BaseTechno const * find(techno_id_t) const;

	std::set<Categorie> const & categories() const;
	std::set<BaseTechno> const & techno() const;

private:
	CommonDB(CommonDB const &)             = delete;
	CommonDB(CommonDB &&)                  = delete;
	CommonDB & operator=(CommonDB const &) = delete;
	CommonDB & operator=(CommonDB &&)      = delete;

	std::set<Categorie> m_categories;
	std::set<BaseTechno> m_techno;
};


} // techno






#endif // TECHNO_BASE_HH