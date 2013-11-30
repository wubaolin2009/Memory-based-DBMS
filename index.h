#ifndef _INDEX_H
#define _INDEX_H
#include "data_represent.h"
#include <stdio.h>
#include <map>
using std::map;


class SimpleIndex
{
private:
	Data::DataType m_type;
	map<Data,vector<int> > m_datas;
	
public:
	static bool IndexExist(string table_name,string column_name)
	{
		string file_name = table_name + "." + column_name + ".index";
		FILE* file = fopen(file_name.c_str(),"r");
		if(file == NULL)
			return false;
		fclose(file);
		return true;
	}
	static void RebuildIndex(DataTable& dt);

	SimpleIndex()
	{
		m_type = Data::INT;
	}
	Data::DataType GetType()
	{
		return m_type;
	}
	void SetType(Data::DataType type)
	{
		m_type = type;
	}

	void AddData(Data& data,int offset)
	{
		m_datas[data].push_back(offset);
	}

	map<Data,vector<int> >& GetAllData()
	{
		return m_datas;
	}
	vector<int> operator[](const Data& data_to_find) //Binary Search
	{
		 return m_datas[data_to_find];
	}
	
};


#endif

