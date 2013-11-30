#ifndef _SIMPLE_LOG_H
#define _SIMPLE_LOG_H
#include <string>
#include "lex_defines.h"
#include "storage.h"
using std::string;

class Simple_Log_Entry
{
public:
	enum Log_Operator{LOG_ADD_ENTRY = 0,LOG_DEL_ENTRY,LOG_BEGIN,LOG_COMMITE,LOG_ABORT,LOG_NONE};
public:
	Simple_Log_Entry()
	{
		m_oper = LOG_NONE;
		m_table_name = "n";
		m_tran_name = "n";
		m_column_name = "n";
		m_old_val = 0;
	}

public:
	std::string m_table_name;
	Log_Operator m_oper;
	std::string m_column_name;
	int m_old_val;
	string m_tran_name;

};

class Simple_Log
{
public:
	static void Init()
	{
		DelLog();
	}
	static bool IsInTran()
	{
		return m_b_starting;
	}
	static void StartTransaction(string trans_name)
	{
		m_transaction_name = trans_name;
		m_b_starting = true;
	}
	static void EndTransaction()
	{
		FlushLog();
		DelLog();
		m_b_starting = false;

	}
	static void AddLogEntry(Simple_Log_Entry::Log_Operator oper,string table_name,string column_name,int old_val)
	{
		if(!m_b_starting)
			return;
		Simple_Log_Entry entry;

		entry.m_oper = oper;
		entry.m_table_name = table_name;
		entry.m_tran_name = m_transaction_name;
		entry.m_column_name = column_name;
		entry.m_old_val = old_val;

		m_entries.push_back(entry);
	}
	static void FlushLog()
	{
		if(!m_b_starting)
			return;
		string log_file_name = "db_log.log";
		FILE* file = fopen(log_file_name.c_str(),"r" );
		if(file == NULL)
		{
			file = fopen(log_file_name.c_str(),"wb+");
			FileWrite::WriteInt(file,0);
			fclose(file);
		}
		file = fopen(log_file_name.c_str(),"r+");
		fseek(file,0,SEEK_END);
		for(int i = 0;i<m_entries.size();i++)
		{
			//Name
			FileWrite::WriteString(file,m_transaction_name);
			Simple_Log_Entry entry = m_entries[i];
			FileWrite::WriteInt( file,(int)entry.m_oper);
			FileWrite::WriteString(file,entry.m_table_name);
			FileWrite::WriteString(file,entry.m_column_name);
			FileWrite::WriteInt(file,entry.m_old_val);
		}
		fseek(file,0,SEEK_SET);
		int count_former = FileReader::GetInt(file);
		count_former += m_entries.size();
		fseek(file,0,SEEK_SET);
		FileWrite::WriteInt(file,count_former);
		m_entries.clear();
		fclose(file);
	}

	static void Undo(string tran_name = m_transaction_name);

private:
	static vector<Simple_Log_Entry> m_entries;
	static string m_transaction_name;
	static bool m_b_starting;

private:
	static void DelLog()
	{
		string log_file_name = "db_log.log";
		FILE* file = fopen(log_file_name.c_str(),"wb+" );
		FileWrite::WriteInt(file,0);
		fclose(file);

	}
	static vector<Simple_Log_Entry> GetAllLogUndo(string tran_name)
	{
		vector<Simple_Log_Entry> ret;
		string log_file_name = "db_log.log";
		FILE* file = fopen(log_file_name.c_str() ,"r");
		if(file == NULL)
			return ret;

		int count = FileReader::GetInt(file);
		for(int i = 0;i<count;i++)
		{
			ret.push_back( GetLog(file ) );
		}
		vector<Simple_Log_Entry> rets;
		for(int i = 0;i<ret.size();i++ )
		{
			if(ret[i].m_tran_name == tran_name )
				rets.push_back(ret[i] );
		}
		return rets;		
	}
	static Simple_Log_Entry GetLog(FILE* file)
	{
		Simple_Log_Entry entry;

		entry.m_tran_name = FileReader::GetString(file);
		entry.m_oper = (Simple_Log_Entry::Log_Operator)FileReader::GetInt(file);
		entry.m_table_name = FileReader::GetString(file);
		entry.m_column_name = FileReader::GetString(file);
		entry.m_old_val = FileReader::GetInt(file);
		return entry;
	}
};

#endif