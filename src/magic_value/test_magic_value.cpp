#include "magic_value.hh"













#include <iostream>


class Techno : public A_MagicValueModifier
{
public:
	Techno()
	: A_MagicValueModifier(MagicValueModifierType::Ratio)
	{}

	virtual double value() const
	{
		return (_ratio * _level);
	}

	virtual bool active() const
	{
		return (_active);
	}


	double _ratio = 0.05;
	int _level = 0;
	bool _active = false;
};


class Bonus : public A_MagicValueModifier
{
public:
	Bonus()
	: A_MagicValueModifier(MagicValueModifierType::Flat)
	{}

	virtual double value() const
	{
		return (_ratio * _level);
	}

	virtual bool active() const
	{
		return (_active);
	}


	double _ratio = 2;
	int _level = 0;
	bool _active = false;
};


class Module : public A_MagicValueModifier
{
public:
	Module()
	: A_MagicValueModifier(MagicValueModifierType::RatioWithStackPenalty)
	{}

	virtual double value() const
	{
		return (_ratio);
	}

	virtual bool active() const
	{
		return (_active);
	}


	double _ratio = 2;
	bool _active = true;
};


int main()
{
	MagicValue<int> test(10);

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;

/*	Bonus bonus;
	Techno tech1;
	Techno tech2;
	tech2._ratio = -0.01;

	test.flat_modifier().push_back(&bonus);
	test.ratio_modifier().push_back(&tech1);
	test.ratio_modifier().push_back(&tech2);
*/

	Module module;
	test.add(module);

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;

	test.add(module);

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;

	test.add(module);

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;


	test.add(module);

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;

	test.add(module);


	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;


/*	bonus._active = true;
	bonus._level = 1;
	tech1._active = true;
	tech1._level = 1;

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;

	bonus._level = 5;
	tech1._level = 3;

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;
	tech2._active = true;
	tech2._level = 5;

	std::cout << "real=" << test.computed_value() <<
	             "[base=" << test.base_value() <<
	             " +(" << test.global_flat_modifier() <<
	             ") +(" << test.global_ratio_modifier() * 100. <<
	             ") +(" << test.global_ratio_with_penalty_modifier() * 100. <<
	             "% @ "<< test.global_ratio_with_penalty_efficiency() * 100. <<
	             "% eff. - stack=" << test.global_ratio_with_penalty_stack_nbr() <<
	             ")]" << std::endl;
*/

  return (0);
}