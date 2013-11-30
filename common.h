#ifndef _COMMON_H
#define _COMMON_H
#include <string>
using std::string;

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string(const char*);
void yyrestart (FILE *input_file  );

class NameEntry //Represent the tablename1 as A , or , columnname1 as B
{
public:
	NameEntry(){};
	NameEntry(std::string real,std::string sname):first_name(real),second_name(sname)
	{
	}
	std::string GetFirstName()
	{
		return first_name;
	}
	void SetFirstName(std::string name)
	{
		first_name = name;
	}
	std::string GetSecondName()
	{
		return second_name;
	}
	void SetSecondName(std::string name)
	{
		second_name = name;
	}
private:	
	std::string first_name;
	std::string second_name;
};


#endif
