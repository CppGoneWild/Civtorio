#ifndef MAGIC_VALUE_HH
#define MAGIC_VALUE_HH




#include <list>
#include <cassert>
#include <cmath>




enum class MagicValueModifierType
{
	Flat,
	Ratio,
	RatioWithStackPenalty
};




class A_MagicValueModifier
{
private:
	MagicValueModifierType _type = MagicValueModifierType::Flat;

protected:
	A_MagicValueModifier()                             = default;
	A_MagicValueModifier(A_MagicValueModifier const &) = default;
	A_MagicValueModifier(A_MagicValueModifier &&)      = default;

	A_MagicValueModifier & operator=(A_MagicValueModifier const &) = default;
	A_MagicValueModifier & operator=(A_MagicValueModifier &&)      = default;

	inline A_MagicValueModifier(MagicValueModifierType t)
	: _type(t)
	{}

	
public:
	virtual ~A_MagicValueModifier() = default;

	inline MagicValueModifierType type() const
	{
		return (_type);
	}

	
	virtual double value() const = 0;
	virtual bool active() const = 0;
};




template <class T>
class MagicValue
{
private:
	using type_t = T;
	using container_t = std::list<A_MagicValueModifier const *>;

	T _base_value = T(0);

	container_t _flat_modifier;
	container_t _ratio_modifier;
	container_t _ratio_with_penalty_modifier;

public:
	MagicValue()                      = default;
	MagicValue(MagicValue<T> const &) = default;
	MagicValue(MagicValue<T> &&)      = default;
	~MagicValue()                     = default;

	MagicValue<T> & operator=(MagicValue<T> const &) = default;
	MagicValue<T> & operator=(MagicValue<T> &&)      = default;

	MagicValue(T);

	T base_value() const;
	T computed_value() const;
	double global_flat_modifier() const;
	double global_ratio_modifier() const;
	double global_ratio_with_penalty_modifier() const;
	double global_ratio_with_penalty_efficiency() const;
	std::size_t global_ratio_with_penalty_stack_nbr() const;

	container_t const & flat_modifier() const;
	container_t & flat_modifier();

	container_t const & ratio_modifier() const;
	container_t & ratio_modifier();

	container_t const & ratio_with_penalty_modifier() const;
	container_t & ratio_with_penalty_modifier();

	void add(A_MagicValueModifier const &);
};








template <class T>
MagicValue<T>::MagicValue(T v)
: _base_value(v)
, _flat_modifier()
, _ratio_modifier()
, _ratio_with_penalty_modifier()
{}


template <class T>
T MagicValue<T>::base_value() const
{
	return (_base_value);
}

template <class T>
T MagicValue<T>::computed_value() const
{
	T tmp(_base_value);

	tmp += global_flat_modifier();
	tmp *= 1.0 + global_ratio_modifier() + global_ratio_with_penalty_modifier();

	return (tmp);
}

template <class T>
double MagicValue<T>::global_flat_modifier() const
{
	double res = 0.;

	for (auto it = _flat_modifier.cbegin(); it != _flat_modifier.cend(); ++it)
	{
		assert((*it)->type() == MagicValueModifierType::Flat);

		if ((*it)->active())
			res += (*it)->value();
	}

	return (res);
}

template <class T>
double MagicValue<T>::global_ratio_modifier() const
{
	double res = 0.;

	for (auto it = _ratio_modifier.cbegin(); it != _ratio_modifier.cend(); ++it)
	{
		assert((*it)->type() == MagicValueModifierType::Ratio);

		if ((*it)->active())
			res += (*it)->value();
	}
	return (res);
}

template <class T>
double MagicValue<T>::global_ratio_with_penalty_modifier() const
{
	double res_w_penalty = 0.;
	double penalty_counter = 0.0;

	for (auto it = _ratio_with_penalty_modifier.cbegin(); it != _ratio_with_penalty_modifier.cend(); ++it)
	{
		assert((*it)->type() == MagicValueModifierType::RatioWithStackPenalty);

		if ((*it)->active())
		{
			res_w_penalty += ((*it)->value() * std::exp(-0.140274 * penalty_counter * penalty_counter));
			penalty_counter += 1.0;
		}
	}

	return (res_w_penalty);
}

template <class T>
double MagicValue<T>::global_ratio_with_penalty_efficiency() const
{
	double penalty_value = 0.;
	double penalty_counter = 0.0;

	for (auto it = _ratio_with_penalty_modifier.cbegin(); it != _ratio_with_penalty_modifier.cend(); ++it)
	{
		assert((*it)->type() == MagicValueModifierType::RatioWithStackPenalty);

		if ((*it)->active())
		{
			penalty_value += std::exp(-0.140274 * penalty_counter * penalty_counter);
			penalty_counter += 1.0;
		}
	}

	return (penalty_value);
}

template <class T>
std::size_t MagicValue<T>::global_ratio_with_penalty_stack_nbr() const
{
	std::size_t penalty_counter = 0.0;

	for (auto it = _ratio_with_penalty_modifier.cbegin(); it != _ratio_with_penalty_modifier.cend(); ++it)
	{
		assert((*it)->type() == MagicValueModifierType::RatioWithStackPenalty);

		if ((*it)->active())
			penalty_counter += 1.0;
	}

	return (penalty_counter);
}

template <class T>
typename MagicValue<T>::container_t const & MagicValue<T>::flat_modifier() const
{
	return (_flat_modifier);
}

template <class T>
typename MagicValue<T>::container_t & MagicValue<T>::flat_modifier()
{
	return (_flat_modifier);
}


template <class T>
typename MagicValue<T>::container_t const & MagicValue<T>::ratio_modifier() const
{
	return (_ratio_modifier);
}

template <class T>
typename MagicValue<T>::container_t & MagicValue<T>::ratio_modifier()
{
	return (_ratio_modifier);
}

template <class T>
typename MagicValue<T>::container_t const & MagicValue<T>::ratio_with_penalty_modifier() const
{
	return (_ratio_with_penalty_modifier);
}

template <class T>
typename MagicValue<T>::container_t & MagicValue<T>::ratio_with_penalty_modifier()
{
	return (_ratio_with_penalty_modifier);
}


template <class T>
void MagicValue<T>::add(A_MagicValueModifier const & m)
{
	if (m.type() == MagicValueModifierType::Flat)
		_flat_modifier.push_back(&m);
	else if (m.type() == MagicValueModifierType::Ratio)
		_ratio_modifier.push_back(&m);
	else if (m.type() == MagicValueModifierType::RatioWithStackPenalty)
		_ratio_with_penalty_modifier.push_back(&m);
}


#endif // MAGIC_VALUE_HH