#include "simple_log.h"
#include "common.h"

#include <sstream>


extern DataTable g_table_result;


vector<Simple_Log_Entry> Simple_Log::m_entries;
string Simple_Log::m_transaction_name;
bool Simple_Log::m_b_starting = false;


void Simple_Log::Undo(string tran_name)
{
	if(!m_b_starting)
		return;
	//m_b_starting = false;
	FlushLog();
	
	vector<Simple_Log_Entry> logs = GetAllLogUndo(tran_name);

	for(int i = logs.size()-1;i >=0;i--)
	{
		Simple_Log_Entry entry = logs[i];

		if(entry.m_oper == Simple_Log_Entry::LOG_ADD_ENTRY)
		{
			//Delete
			std::stringstream ss;
			ss <<"delete from " << entry.m_table_name << " where " << entry.m_column_name << "="<<entry.m_old_val <<";";
			string cmd = ss.str();
			yy_scan_string( cmd.c_str() );
			yyparse();

		}
		else if (entry.m_oper == Simple_Log_Entry::LOG_DEL_ENTRY)
		{
			std::stringstream ss;
			ss <<"insert into " << entry.m_table_name << " values( " << entry.m_old_val <<");";
			string cmd = ss.str();
			yy_scan_string( cmd.c_str() );
			yyparse();

		}
	}
	cerr<<"Transaction Aborted!" <<endl;
	fflush(stdin);
	yyrestart(stdin);
	EndTransaction();
	

	
	
}