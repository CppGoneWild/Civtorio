#include "types.hh"



/*******************************************************************************
                 __                 __  _                 __
                / /___  _________ _/ /_(_)___  ____      / /_
               / / __ \/ ___/ __ `/ __/ / __ \/ __ \    / __/
              / / /_/ / /__/ /_/ / /_/ / /_/ / / / /   / /_
             /_/\____/\___/\__,_/\__/_/\____/_/ /_/____\__/
                                                 /_____/
*******************************************************************************/

parser::location_t::location_t(std::size_t l)
: filename()
, line(l)
, column(0)
{}

parser::location_t::location_t(std::size_t l, std::size_t c)
: filename()
, line(l)
, column(c)
{}

parser::location_t::location_t(std::string const & f, std::size_t l, std::size_t c)
: filename(f)
, line(l)
, column(c)
{}




std::ostream & operator<<(std::ostream & os, parser::location_t const & l)
{
	os << l.filename << ':' << l.line << ':' << l.column;
	return (os);
}



/*******************************************************************************
                     __
   _______  ______  / /_____ __  __    ___  ______________  _____
  / ___/ / / / __ \/ __/ __ `/ |/_/   / _ \/ ___/ ___/ __ \/ ___/
 (__  ) /_/ / / / / /_/ /_/ />  <    /  __/ /  / /  / /_/ / /
/____/\__, /_/ /_/\__/\__,_/_/|_|____\___/_/  /_/   \____/_/
     /____/                    /_____/
*******************************************************************************/




parser::syntax_error::syntax_error(std::string const & e,
                                   location_t const & l)
: location(l)
, error_str(e)
, inner_errors()
{}


parser::syntax_error::syntax_error(std::string && e,
                                   location_t && l)
: location(l)
, error_str(e)
, inner_errors()
{}


parser::syntax_error::syntax_error(std::string const & e,
                                   location_t const & l,
                                   syntax_error && i)
: location(l)
, error_str(e)
, inner_errors(std::move(i.inner_errors))
{
	inner_errors.emplace_back(std::move(i.error_str), std::move(i.location));
}




static void print_orig(std::ostream & os, parser::syntax_error const & e)
{
	os << e.location << " : " << e.error_str << std::endl;
}

static void print_from(std::ostream & os, parser::syntax_error const & e)
{
	os << "\t" << "From (" << e.location << " : " << e.error_str << ")" << std::endl;
}


std::ostream & operator<<(std::ostream & os, parser::syntax_error const & s)
{
	if (s.inner_errors.size() >= 1)
	{
		std::size_t i = s.inner_errors.size() - 1;
		print_orig(os, s.inner_errors[i]);


		if (s.inner_errors.size() > 1)
		{
			--i;
			for (; i >= 0; --i)
				print_from(os, s.inner_errors[i]);
		}
		print_from(os, s);
	}
	else
	{
		print_orig(os, s);
  }

	return (os);
}
