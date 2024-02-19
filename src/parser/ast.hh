#ifndef PARSER_AST_HH
#define PARSER_AST_HH



#include "types.hh"


#include <iostream>
#include <string>
#include <vector>



namespace parser
{



struct opt_t
{
	enum comment_style_t
	{
	  C       = 1
	, PreProc = 2

	, All = C | PreProc
	};

	char separator[3] = " \t";

	bool always_keep_new_line = false;
	comment_style_t comment_style = All;

	/*virtual*/ bool is_alpha_num(char) const;
};



} // parser



#endif // PARSER_AST_HH