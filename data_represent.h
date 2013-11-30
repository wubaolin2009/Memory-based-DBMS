#ifndef _DATA_REPRESENT_H
#define _DATA_REPRESENT_H
#include <vector>
#include <string>
#include "common.h"
using std::vector;
using std::string;

class Data
{
public:
	enum DataType{STR=0,INT,REAL};
public:
	Data(){};
	Data(const string& val):m_strval(val){};
	Data(int ival)
	{
		m_type = INT;
		m_ival = ival;
	}
	Data(double dval)
	{
		m_type = REAL;
		m_dval = dval;
	}
	string GetStr()
	{
		m_type = STR;
		return m_strval;
	}
	int GetInt()
	{
		return m_ival;
	}
	double GetRealNum()
	{
		return m_dval;
	}
	DataType GetType()
	{
		return m_type;
	}
	bool operator==(const Data& data) const;
	
	bool operator!=(const Data& data) const;
	
	bool operator<(const Data& data) const;
	
	bool operator>(const Data& data) const;
	
	
	bool operator<=(const Data& data) const;
	
	bool operator>=(const Data& data) const;
	
	bool operator()(const Data& data1,const Data& data2) const;	
	
private:
	string m_strval;
	int m_ival;
	double m_dval;
	DataType m_type;


};

class DataTable;

class DataRow
{
public:
	DataRow(){};
	Data& operator[](int index)
	{
		return m_datas[index];
	}
	void AddData(Data& data_to_add)
	{
		m_datas.push_back(data_to_add);
	}
	int GetCount()
	{
		return m_datas.size();
	}

	bool operator==(const DataRow& row)
	{
		vector<Data> datas = row.m_datas;
		for(int i = 0;i<m_datas.size();i++)
		{
			if(datas[i] != m_datas[i])
			{
				return false;
			}
		}
		return true;
	}


private:
	vector<Data> m_datas;	
	

};

class DataColumn
{

public:
	enum DataColumnType{COLUMN_TYPE_REAL =0 ,COLUMN_TYPE_INTEGER,COLUMN_TYPE_CHAR,COLUMN_TYPE_VARCHAR};
	DataColumn(){m_b_fk = false;};

	DataColumn(NameEntry& entry,std::string& table_name)
	{
		m_name = entry;
		m_table_name = table_name;
		m_b_fk = false;
	}
	DataColumnType GetColType()
	{
		return m_col_type;
	}
	void SetColType(DataColumnType type)
	{
		m_col_type = type;
	}
	bool GetCanNull()
	{
		return m_can_null;
	}
	void SetCanNull(bool can_null)
	{
		m_can_null = can_null;
	}
	int GetAppendVal()
	{
		return m_append_val;
	}
	void SetAppendVal(int append_val)
	{
		m_append_val = append_val;
	}

	void SetName(NameEntry& entry)
	{
		m_name = entry;
	}
	NameEntry GetName()
	{
		return m_name;
	}
	void SetTableName(std::string table_name)
	{
		m_table_name = table_name;
	}
	std::string GetTableName()
	{
		return m_table_name;
	}
	void SetTableIndex(int index)
	{
		m_table_index = index;
	}
	int GetTableIndex()
	{
		return m_table_index;
	}

	bool HasFk()
	{
		return m_b_fk;
	}
	std::string GetFkTableName()
	{
		return m_ref_table_name;
	}
	void SetFkTableName(string str)
	{
		m_b_fk = true;
		m_ref_table_name = str;
	}
	string GetFkColName()
	{
		return m_ref_col_name;
	}
	void SetFkColName(std::string str)
	{
		m_b_fk = true;
		m_ref_col_name = str;
	}


private:
	NameEntry m_name;
	std::string m_table_name;
	DataColumnType m_col_type;
	bool m_can_null;
	int m_append_val; //Append Value
	int m_table_index ;
	bool m_b_fk;
	std::string m_ref_table_name;
	std::string m_ref_col_name;
};

class DataTable
{
public:
	DataRow& operator[](int index)
	{
		return m_rows[index];
	}
	void AddRow(DataRow& row_to_add)
	{
		m_rows.push_back(row_to_add);
	}
	inline int GetCount() const
	{
		return m_rows.size();
	}
	void AddColumn(DataColumn& new_column)
	{
		DataColumn column = new_column;
		m_columns.push_back(new_column);
	}
	void AddColumn(const vector<DataColumn>& new_columns)
	{
		for(int i = 0;i<new_columns.size(); i++)
		{
			m_columns.push_back(new_columns[i]);
		}
	}
	int GetColumnIndex(NameEntry& column_name,int index = -1)
	{
		for(int i = 0;i<m_columns.size() ;i++)
		{
			NameEntry name_entry = m_columns[i].GetName();
			if(name_entry.GetFirstName() == column_name.GetSecondName() )
			{	
				if(index != -1 && m_columns[i].GetTableIndex() != index)
				{
					continue;
				}
				string table_name = m_columns[i].GetTableName(); 
				if(table_name == "" || column_name.GetFirstName()==""  || table_name == column_name.GetFirstName())
					return i;
			};
		}
		return -1;
	}
	vector<DataColumn>& GetColumns()
	{
		return m_columns;
	}
	void SetColumns(const vector<DataColumn>& columns)
	{
		m_columns = columns;
	}
	DataColumn& GetColumn(int index)
	{
		return m_columns[index];
	}

	string GetName()
	{
		return m_table_name;
	}
	void SetName(string str)
	{
		m_table_name = str;
	}

	DataTable(){

	};

	DataTable(string str):m_table_name(str){};

	void SetJoinInfo(vector<int> info)
	{
		m_join_table_info = info;
		if(info.size() > 0)
		{
			int i = info.back();
			int start_index = 0;
			if(info.size() > 1)
			{
				start_index = info[info.size()-2];
				
			}
		
			for(int i = start_index;i<m_columns.size();i++)
			{
				m_columns[i].SetTableIndex(info.size() -1 );
			}
		}
	}
	vector<int>& GetJoinInfo()
	{
		return m_join_table_info;
	}
	vector<DataRow> & GetRows()
	{
		return m_rows;
	}
	void SetRows(vector<DataRow>& rows)
	{
		m_rows = rows;
	}

private:
	vector<int> m_join_table_info;
	vector<DataRow> m_rows;
	vector<DataColumn> m_columns;
	string m_table_name;

};
#endif




