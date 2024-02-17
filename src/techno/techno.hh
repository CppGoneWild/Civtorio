#ifndef TECNO_TECHNO_HH
#define TECNO_TECHNO_HH


#include <vector>
#include <map>
#include <list>


#include "techno_types.hh"


namespace techno
{
	class Categorie;
	class BaseTechno;
	class CommonDB;
} // techno



namespace techno
{


class Techno
{
public:
	struct Prerequist
	{
		inline Prerequist(Techno const * t, int l) : tech(t), level(l) {}

		Techno const * tech = nullptr;
		int level = 0;
	};

	Techno()  = default;
	~Techno() = default;

	techno_id_t id() const;

	BaseTechno const * base() const;
	Categorie const * categorie() const;

	std::vector<Prerequist> const & prerequists() const;
	bool can_be_researched() const;

	int level() const;

	int cost_to_next_level() const;
	double invested_to_next_level() const;
	double remaining_to_next_level() const;
	double invest(double);

private:	
	Techno(Techno const &)             = default;
	Techno(Techno &&)                  = default;
	Techno & operator=(Techno const &) = default;
	Techno & operator=(Techno &&)      = default;

	Techno(BaseTechno const &, Categorie const &);

	techno_id_t m_id = 0;

	BaseTechno const * m_base     = nullptr;
	Categorie const * m_categorie = nullptr;

	std::vector<Prerequist> m_prerequists;

	int m_level = 0;

	int    m_cost_to_next_level     = 0;
	double m_invested_to_next_level = 0;


	friend class TechnoDB;
};




} // techno




bool operator==(techno::Techno const &, techno::Techno const &);
bool operator!=(techno::Techno const &, techno::Techno const &);
bool operator< (techno::Techno const &, techno::Techno const &);
bool operator> (techno::Techno const &, techno::Techno const &);
bool operator<=(techno::Techno const &, techno::Techno const &);
bool operator>=(techno::Techno const &, techno::Techno const &);




bool operator==(techno::Techno const &, techno::techno_id_t);
bool operator!=(techno::Techno const &, techno::techno_id_t);
bool operator< (techno::Techno const &, techno::techno_id_t);
bool operator> (techno::Techno const &, techno::techno_id_t);
bool operator<=(techno::Techno const &, techno::techno_id_t);
bool operator>=(techno::Techno const &, techno::techno_id_t);

bool operator==(techno::techno_id_t, techno::Techno const &);
bool operator!=(techno::techno_id_t, techno::Techno const &);
bool operator< (techno::techno_id_t, techno::Techno const &);
bool operator> (techno::techno_id_t, techno::Techno const &);
bool operator<=(techno::techno_id_t, techno::Techno const &);
bool operator>=(techno::techno_id_t, techno::Techno const &);




bool operator==(techno::BaseTechno const &, techno::Techno const &);
bool operator!=(techno::BaseTechno const &, techno::Techno const &);
bool operator< (techno::BaseTechno const &, techno::Techno const &);
bool operator> (techno::BaseTechno const &, techno::Techno const &);
bool operator<=(techno::BaseTechno const &, techno::Techno const &);
bool operator>=(techno::BaseTechno const &, techno::Techno const &);

bool operator==(techno::Techno const &, techno::BaseTechno const &);
bool operator!=(techno::Techno const &, techno::BaseTechno const &);
bool operator< (techno::Techno const &, techno::BaseTechno const &);
bool operator> (techno::Techno const &, techno::BaseTechno const &);
bool operator<=(techno::Techno const &, techno::BaseTechno const &);
bool operator>=(techno::Techno const &, techno::BaseTechno const &);





namespace techno
{


class TechnoDB
{
public:
	TechnoDB()  = default;
	~TechnoDB() = default;

	void build(CommonDB const &);

	Techno const * find(techno_id_t) const;

	CommonDB const * common_db() const;

	std::map<techno_id_t, Techno> const & techno() const;
	std::map<techno_id_t, Techno> & techno();

private:
	TechnoDB(TechnoDB const &)             = delete;
	TechnoDB(TechnoDB &&)                  = delete;
	TechnoDB & operator=(TechnoDB const &) = delete;
	TechnoDB & operator=(TechnoDB &&)      = delete;

	CommonDB const * m_common_db = nullptr;
	std::map<techno_id_t, Techno> m_techno;
};



} // techno







/*


namespace techno
{


class I_TechSource
{
public:
	virtual ~I_TechSource() = default;

	virtual Categorie::id_t categorie_id() const = 0;
	virtual std::string const & name() const = 0;
	virtual bool active() const = 0;

protected:
	I_TechSource()                     = default;
	I_TechSource(I_TechSource const &) = default;
	I_TechSource(I_TechSource &&)      = default;

	I_TechSource & operator=(I_TechSource const &) = default;
	I_TechSource & operator=(I_TechSource &&)      = default;
};





class TechnoManager
{
public:
	using tech_source_list_t = std::list<I_TechSource const &>;
	using tech_source_map_t = std::map<Categorie::id_t, tech_source_list_t>;
	using tech_point_stock_t = std::map<Categorie::id_t, double>;

	TechnoManager()  = default;
	~TechnoManager() = default;

	TechnoDB const & db() const;
	TechnoDB & db();


	tech_source_map_t const & tech_source() const;
	tech_source_map_t & tech_source();
	double get_tech_prod(Categorie::id_t) const;
	double get_next_efficiency(Categorie::id_t) const;
	void add_to_stock(Categorie::id_t, double);
	void add_tech_source(I_TechSource const &);
	void del_tech_source(I_TechSource const &);
	void clr_tech_source(Categorie::id_t);
	void clr_tech_source();


	std::list<Techno *> const & research_queue() const;
	std::list<Techno *> & research_queue();
	Techno const * currently_researched() const;
	double nb_day_remaining() const;

	void advance_one_day();

private:
	TechnoManager(TechnoManager const &)             = delete;
	TechnoManager(TechnoManager &&)                  = delete;
	TechnoManager & operator=(TechnoManager const &) = delete;
	TechnoManager & operator=(TechnoManager &&)      = delete;

	TechnoDB m_db;

	tech_source_map_t m_tech_source;

	tech_point_stock_t m_stock;

	std::list<Techno *> m_research_queue;
};



} // techno

*/






#endif // TECNO_TECHNO_HH
