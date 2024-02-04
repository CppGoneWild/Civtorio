#ifndef TECHNO_BASE_HH
#define TECHNO_BASE_HH


#include <cstdint>
#include <string>
#include <vector>
#include <map>


#include "techno_types.hh"

#include "win_mngr/show_info.hh"



/*******************************************************************************
                   ______      __                        _
                  / ____/___ _/ /____  ____ _____  _____(_)__
                 / /   / __ `/ __/ _ \/ __ `/ __ \/ ___/ / _ \
                / /___/ /_/ / /_/  __/ /_/ / /_/ / /  / /  __/
                \____/\__,_/\__/\___/\__, /\____/_/  /_/\___/
                                    /____/
*******************************************************************************/



namespace techno
{


class Categorie : public win_mngr::I_ShowInfo
{
public:
	using id_t = std::uint64_t;

	Categorie()                  = default;
	Categorie(Categorie const &) = default;
	Categorie(Categorie &&)      = default;
	virtual ~Categorie() = default;

	Categorie & operator=(Categorie const &) = default;
	Categorie & operator=(Categorie &&)      = default;

	Categorie(id_t, std::string const &, std::string const & = "");

	id_t id() const;
	std::string const & name() const;
	std::string const & description() const;

protected:
	//// Called by class ShowInfoWindows
	//
	virtual void _display_show_info_imgui() const;
	//
	/////////////////////////////

private:
	id_t m_id = 0;
	std::string m_name;
	std::string m_description;
};


} // techno




bool operator==(techno::Categorie const &, techno::Categorie const &);
bool operator!=(techno::Categorie const &, techno::Categorie const &);
bool operator< (techno::Categorie const &, techno::Categorie const &);
bool operator> (techno::Categorie const &, techno::Categorie const &);
bool operator<=(techno::Categorie const &, techno::Categorie const &);
bool operator>=(techno::Categorie const &, techno::Categorie const &);




bool operator==(techno::Categorie const &, techno::Categorie::id_t const);
bool operator!=(techno::Categorie const &, techno::Categorie::id_t const);
bool operator< (techno::Categorie const &, techno::Categorie::id_t const);
bool operator> (techno::Categorie const &, techno::Categorie::id_t const);
bool operator<=(techno::Categorie const &, techno::Categorie::id_t const);
bool operator>=(techno::Categorie const &, techno::Categorie::id_t const);

bool operator==(techno::Categorie::id_t const, techno::Categorie const &);
bool operator!=(techno::Categorie::id_t const, techno::Categorie const &);
bool operator< (techno::Categorie::id_t const, techno::Categorie const &);
bool operator> (techno::Categorie::id_t const, techno::Categorie const &);
bool operator<=(techno::Categorie::id_t const, techno::Categorie const &);
bool operator>=(techno::Categorie::id_t const, techno::Categorie const &);













/*******************************************************************************
                ____                ______          __
               / __ )____ _________/_  __/__  _____/ /_  ____  ____
              / __  / __ `/ ___/ _ \/ / / _ \/ ___/ __ \/ __ \/ __ \
             / /_/ / /_/ (__  )  __/ / /  __/ /__/ / / / / / / /_/ /
            /_____/\__,_/____/\___/_/  \___/\___/_/ /_/_/ /_/\____/
            
*******************************************************************************/



namespace techno
{


class BaseTechno : public win_mngr::I_ShowInfo
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
	virtual ~BaseTechno()                      = default;

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

protected:
	//// Called by class ShowInfoWindows
	//
	virtual void _display_show_info_imgui() const;
	//
	/////////////////////////////

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




bool operator==(techno::BaseTechno const &, techno::techno_id_t const);
bool operator!=(techno::BaseTechno const &, techno::techno_id_t const);
bool operator< (techno::BaseTechno const &, techno::techno_id_t const);
bool operator> (techno::BaseTechno const &, techno::techno_id_t const);
bool operator<=(techno::BaseTechno const &, techno::techno_id_t const);
bool operator>=(techno::BaseTechno const &, techno::techno_id_t const);

bool operator==(techno::techno_id_t const, techno::BaseTechno const &);
bool operator!=(techno::techno_id_t const, techno::BaseTechno const &);
bool operator< (techno::techno_id_t const, techno::BaseTechno const &);
bool operator> (techno::techno_id_t const, techno::BaseTechno const &);
bool operator<=(techno::techno_id_t const, techno::BaseTechno const &);
bool operator>=(techno::techno_id_t const, techno::BaseTechno const &);









/*******************************************************************************
              ______                                      ____  ____
             / ____/___  ____ ___  ____ ___  ____  ____  / __ \/ __ )
            / /   / __ \/ __ `__ \/ __ `__ \/ __ \/ __ \/ / / / __  |
           / /___/ /_/ / / / / / / / / / / / /_/ / / / / /_/ / /_/ /
           \____/\____/_/ /_/ /_/_/ /_/ /_/\____/_/ /_/_____/_____/
           
*******************************************************************************/



namespace techno
{


class CommonDB
{
public:
	CommonDB()  = default;
	~CommonDB() = default;

	Categorie const * add(Categorie const &);
	BaseTechno const * add(BaseTechno const &);

	Categorie const * categorie(Categorie::id_t) const;
	BaseTechno const * techno(techno_id_t) const;

	std::map<Categorie::id_t, Categorie> const & categories() const;
	std::map<techno_id_t, BaseTechno> const & techno() const;

private:
	CommonDB(CommonDB const &)             = delete;
	CommonDB(CommonDB &&)                  = delete;
	CommonDB & operator=(CommonDB const &) = delete;
	CommonDB & operator=(CommonDB &&)      = delete;

	std::map<Categorie::id_t, Categorie> m_categories;
	std::map<techno_id_t, BaseTechno> m_techno;
};


} // techno






#endif // TECHNO_BASE_HH