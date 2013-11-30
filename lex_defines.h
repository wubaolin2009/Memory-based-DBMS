#ifndef _LEX_DEFINES_H
#define _LEX_DEFINES_H
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "algebra.h"
#include "excutor.h"
#include "storage.h"
#include "simple_log.h"
#define YYSTYPE YYlVal

#define YY_NO_UNISTD_H  
extern "C" int yyparse();

using std::vector;
using std::string;

class ColumnInfo
{
public:
	ColumnInfo()
	{
		type = DataColumn::COLUMN_TYPE_INTEGER;
		append_val = 0;
		b_null = false;
		b_pk = false;
		b_fk = false;
	}
	string name;
	DataColumn::DataColumnType type;
	
	int append_val;
	bool b_null;
	bool b_pk;
	bool b_fk;
	std::string fk_table_name;
	std::string fk_col_name;

};

class Fk_Info
{
public:
	Fk_Info()
	{

	}
	std::string ref_table_name;
	std::string ref_col_name;
	
};

class YYlVal
{
private:
	int iVal;
	double dVal;
	std::string strVal;
	std::vector<NameEntry>* m_name_entries;
	std::vector<Attribute>*  m_attrs;
	Conditions m_condition;

	//condition operator
	//Conditions::ConditionOperator m_cond_operate;

	//a expr
	NameEntry m_expr_first_entry;
	SimpleExpr::SimpleExprOperator m_expr_oper;
	SimpleExpr::SecondOperand m_expr_operand2;
	SimpleExpr m_expr;

	//attr
	Attribute m_attr;

	//Indicate Whether the variable is available
	bool m_avail;

	//Column Info
	vector<ColumnInfo> m_column_infos;

	//Values
	vector<string> m_values;
public:		
	//Fk_Infos
	Fk_Info m_fk_info;
	
public:	
	void MakeHelp()
	{
		cout<<"1.select [distinct] col_name [as][col_rename],... from table_name" <<endl;
		cout<<"[as][table_rename],... [where col_name = | > | < value and|or other condition]" <<endl;
		cout<<"[sort by col_name,... [asc|desc] ]; " <<endl;
		cout<<"2.insert into table_name values(value,...);" <<endl;
		cout<<"3.delete from table_name [where condition];" <<endl;
		cout<<"4.update table_name set col_name = valeus[where conditon];"<<endl;
		cout<<"5.create index on table_name col_name;"<<endl;
		cout<<"6.create table tablename {" <<endl;
		cout<<"	col_name type(integer,float,varchar(n),char(n) )" <<endl;
		cout<<"	[null|not null] [pk] [fk ref table_name col_name],... "<<endl;
		cout<<"};"<<endl;
		cout<<"7.begin transaction " <<endl;
		cout<<" commands (if any command fails,the transaction will be aborted )" <<endl;
		cout<<" end transaction " <<endl;

	}
	void AppendValue(vector<string> value1,vector<string> value2)
	{
		vector<string> tmp_vec;
		for(int i = 0;i<value1.size();i++)
		{
			tmp_vec.push_back(value1[i]);			
		}
		for(int j = 0;j<value2.size();j++)
		{
			tmp_vec.push_back(value2[j]);
		}
		m_values = tmp_vec;
	}
	void SetValue(vector<string> vec_val)
	{
		m_values = vec_val;
	}
	void AppendValue(const string& str)
	{
		m_values.push_back(str);

	}
	void AppendValue(int val)
	{
		std::stringstream ss;
		ss<<val;
		m_values.push_back(ss.str() );
	}
	void AppendValue(double val)
	{
		std::stringstream ss;
		ss<<val;
		m_values.push_back(ss.str() );
	}
	vector<string>& GetValue()
	{
		return m_values;
	}

	void AppendColumnInfo(vector<ColumnInfo> infos,vector<ColumnInfo> info)
	{
		vector<ColumnInfo> tmp_infos;
		for(int i = 0;i<infos.size();i++)
		{
			tmp_infos.push_back(infos[i] );

		}
		for(int j =0;j<info.size();j++)
		{
			tmp_infos.push_back(info[j]);
		}
		m_column_infos = tmp_infos;
	}
	void AppendColumnInfo(vector<ColumnInfo> info)
	{
		vector<ColumnInfo> infos;
		for(int i = 0;i<info.size();i++)
		{
			infos.push_back(info[i] );
		}
		m_column_infos = infos;
	}
	vector<ColumnInfo>& GetColumnInfo()
	{
		return m_column_infos;
	}
		

	//Constructor 
	YYlVal()
	{
		m_avail = true;
		iVal = 0;
		dVal = 0;
		m_name_entries = NULL;
		
	}
	~YYlVal()
	{
		if(m_name_entries && m_name_entries->size() != 0)
		{
			//delete m_name_entries;
			m_name_entries = NULL;
		}
	}

	void SetAvailable(bool avail)
	{
		m_avail = avail;
	}
	bool GetAvailable()
	{
		return m_avail;
	}



	int operator=(int val)
	{
		iVal = val;
		return iVal;
	}
	double operator=(double val)
	{
		dVal = val;
		return dVal;
	}
	
	void operator=(const std::string& str_to_add)
	{
		strVal = str_to_add;
	}
	void SetAttr(Attribute& attr)
	{
		m_attr = attr;
	}
	Attribute GetAttr()
	{
		return m_attr;
	}

	
	void operator=(NameEntry* entry_to_add)
	{
		std::vector<NameEntry>* mem_buffer_delete = m_name_entries;
		m_name_entries = new std::vector<NameEntry>();
		m_name_entries->push_back(*entry_to_add);
		if(mem_buffer_delete)
			delete mem_buffer_delete;

	}

	void SetSimpleOperator(SimpleExpr::SimpleExprOperator oper)
	{
		m_expr_oper = oper;
	}
	SimpleExpr::SimpleExprOperator GetSimpleOperator()
	{
		return m_expr_oper;
	}
	void SetSimpleExprOperand1(NameEntry& entry)
	{
		m_expr_first_entry = entry;
	}
	NameEntry GetSimpleExprOperand1()
	{
		return m_expr_first_entry;
	}
	void SetSimpleExprOperand2(SimpleExpr::SecondOperand& oper2)
	{
		m_expr_operand2 = oper2;
	}
	SimpleExpr::SecondOperand GetSimpleExprOperand2()
	{
		return m_expr_operand2;
	}
	void SetSimpleExpr(SimpleExpr& expr)
	{
		m_expr = expr;
	}
	SimpleExpr GetSimpleExpr()
	{
		return m_expr;
	}

	

	void operator=(vector<NameEntry>* entries)
	{
		std::vector<NameEntry>* mem_buffer_delete = m_name_entries;
		m_name_entries = new std::vector<NameEntry>();
		for(int i = 0;i<entries->size();i++)
		{
			m_name_entries->push_back((*entries)[i]);
		}
		if(mem_buffer_delete)
			delete mem_buffer_delete;
	}
	void operator=(vector<Attribute>* entries)
	{
		std::vector<Attribute>* mem_buffer_delete = m_attrs;
		m_attrs = new std::vector<Attribute>();
		for(int i = 0;i<entries->size();i++)
		{
			m_attrs->push_back((*entries)[i]);
		}
		if(mem_buffer_delete)
			delete mem_buffer_delete;
	}

	void operator=(Conditions cond)
	{
		m_condition = cond;
	}
	operator Conditions()
	{
		return m_condition;
	}

	void operator=(NameEntry& firstentry)
	{
		//m_first_entry = firstentry;
	}

	
	void AppendNameEntry(vector<NameEntry>* entry_before,vector<NameEntry>* new_entry)
	{
		std::vector<NameEntry>* mem_buffer_delete = m_name_entries;
		m_name_entries = new std::vector<NameEntry>();
		for(int i = 0;i<entry_before->size();i++)
		{
			m_name_entries->push_back( (*entry_before)[i]);
		}
		for(int i = 0;i<new_entry->size();i++)
		{
			m_name_entries->push_back( (*new_entry)[i]);
		}
		if(mem_buffer_delete)
			delete mem_buffer_delete;

	}

	void AppendAttrEntry(vector<Attribute>* entry_before,Attribute new_entry)
	{
		std::vector<Attribute>* mem_buffer_delete = m_attrs;
		m_attrs = new std::vector<Attribute>();
		for(int i = 0;i<entry_before->size();i++)
		{
			m_attrs->push_back( (*entry_before)[i]);
		}
		m_attrs->push_back(new_entry);
		if(mem_buffer_delete)
			delete mem_buffer_delete;

	}

	void MakeCreateTable(YYlVal name,YYlVal columns)
	{
		string table_name = name;
		vector<ColumnInfo> infos = columns.GetColumnInfo();
		string file_name = table_name + ".meta";
		FILE* file ;
		if( (file = fopen(file_name.c_str(),"r")  )!= NULL)
		{
			cerr<<"Table already exists !"<<endl;
			fclose(file);
			return ;
		}
		
		//Column Vector
		vector<DataColumn> columns_new;
		vector<int> pk_indexs;
		for(int i = 0;i<infos.size();i++)
		{
			ColumnInfo info = infos[i];
			DataColumn dc;
			dc.SetAppendVal(info.append_val);
			dc.SetCanNull(info.b_null);
			dc.SetColType(info.type);
			if(info.b_fk)
			{
				dc.SetFkTableName(info.fk_table_name);
				dc.SetFkColName(info.fk_col_name);
			}
			NameEntry col_name(info.name,"");
			dc.SetName(col_name);
			dc.SetTableName(table_name);

			columns_new.push_back(dc);
			if(info.b_pk)
				pk_indexs.push_back(i);
		}
		MetaFile meta_file(table_name);
		meta_file.WriteColumnInfo(columns_new);
		meta_file.SetPkIndexs(pk_indexs);


		//Check Table
		DataFile df;
		df.CreateNewTable(table_name);

	}

private:
	void TranslateCondition(vector<NameEntry>& froms,vector<Attribute>& attrs,vector<DataTable>& list_tables,Conditions& condition_to_translate)
	{
		SimpleExpr expr = condition_to_translate.GetSimpleExpr();
		vector<NameEntry> condition_nameentry_before;
		condition_nameentry_before.push_back( expr.m_operand1);
		expr.name_map1 = NameTransLater::TranslateName(froms,attrs,list_tables,condition_nameentry_before,1)[0];
		//2nd Operand
		if(expr.m_operand2.oper_type == SimpleExpr::AttrName)
		{
			NameEntry entry = expr.m_operand2.name_entry;
			condition_nameentry_before.clear();
			condition_nameentry_before.push_back(entry);
			expr.m_operand2.name_map2 = NameTransLater::TranslateName(froms,attrs,list_tables,condition_nameentry_before,1)[0];
		}
		condition_to_translate.SetSimpleExpr(expr);
		
	}
	vector<Attribute> TranslateStar(vector<Attribute>& attrs,vector<NameEntry> froms,vector<DataTable>& list_tables)
	{
		vector<Attribute> new_attrs_no_star;
		for(int i = 0;i<attrs.size();i++)
		{
			Attribute att = attrs[i];
			if(att.GetName().GetSecondName() == "*")
			{
				int index = -1;
				for(int i = 0;i<froms.size();i++)
				{
					string tablename = att.GetName().GetFirstName();
					if(tablename != "" && froms[i].GetSecondName()== tablename)
					{
						index = i;
						//NameEntry entry(froms[i].GetFirstName(),"*");
						//att.SetName(entry);
						break;
					}
				}
		
				int table_index = index;
				if(att.GetName().GetFirstName() == "")
					table_index = 0;
				if(table_index == -1)
				{
					for(int i = 0;i<list_tables.size();i++)
					{
						if(list_tables[i].GetName() == att.GetName().GetFirstName())
						{
							table_index = i;
						}
					}
					if(table_index == -1)
					{
						cerr<<"Can't find table with name of " + att.GetName().GetFirstName();
						return new_attrs_no_star;
					}
				}
				vector<DataColumn> columns = list_tables[table_index].GetColumns();
				for(int i = 0;i<columns.size();i++)
				{
					Attribute attr = att;
					NameEntry entry(attr.GetName().GetFirstName(),columns[i].GetName().GetFirstName());
					attr.SetName(entry);
					string str = "";
					attr.SetSecondName(str);
					new_attrs_no_star.push_back(attr);
				}
			}
			else
			{
				new_attrs_no_star.push_back(attrs[i]);
			}

		}
		return new_attrs_no_star;
		
	}
public:

	DataTable MakeSelectNode(YYlVal attr_name,YYlVal from_list,YYlVal condition,YYlVal sort_list ,int need_distinct)
	{
		//Load All Table Needed		
		vector<Attribute> attrs = ( *(vector<Attribute>*)attr_name );
		
		vector<NameEntry> froms = ( *(vector<NameEntry>*)from_list );
		

		vector<DataTable> list_tables;
		
		for(int i = 0;i<froms.size();i++)
		{
			NameEntry entry =  froms[i];
			string table_name = entry.GetFirstName();
			DataTable dt;
			dt.SetName(table_name);
			MetaFile mf(dt.GetName() );
			dt.SetColumns(mf.GetColumnsInfo() );
			//DataFile df;
			//df.FillDataTable(dt);
			list_tables.push_back(dt);

		}
		
		//Codes begins here
		//Translate Names
		//Translate Attribute Names
		//Translate *
		attrs = TranslateStar(attrs,froms,list_tables);
		
		//Tranlate Attribute Name
		


		vector<Column_NameMap> attr_name_translated;
		vector<NameEntry> attr_names_before;
		for(int i = 0;i<attrs.size();i++)
		{
			Attribute attr = attrs[i];
			NameEntry entry = attr.GetName();
			attr_names_before.push_back(entry);
		}
		attr_name_translated = NameTransLater::TranslateName(froms,attrs,list_tables,attr_names_before,1);

		//Translate Condition Names
		Conditions condition_to_translate = condition;
		if(condition.GetAvailable())
		{
			
			TranslateCondition(froms,attrs,list_tables,condition_to_translate);
			vector<Conditions>& condition_append = condition_to_translate.GetConditions();
			for(int i = 0;i<condition_append.size();i++)
			{
				Conditions& condition_to_translate = condition_append[i];
				TranslateCondition(froms,attrs,list_tables,condition_to_translate);	
			}
		}

		RelationNode node_of_from_list;

		if(condition.GetAvailable() )
		{
			node_of_from_list.DoJoin(list_tables,&condition_to_translate);
		}
		else
		{
			node_of_from_list.DoJoin(list_tables,NULL);
		}


		
		//Sort Node
		RelationNode node_sorted ;
		if(sort_list.GetAvailable() )
		{
			//Translate Name
			vector<Attribute> sorts = ( *(vector<Attribute>*)sort_list );
			vector<Column_NameMap> sort_name_translated;
			vector<NameEntry> sort_names_before;
			for(int i = 0;i<sorts.size();i++)
			{
				Attribute attr = sorts[i];
				NameEntry entry = attr.GetName();
				sort_names_before.push_back(entry);
			}
			sort_name_translated = NameTransLater::TranslateName(froms,attrs,list_tables,sort_names_before,1);

			int asc = sort_list;
			SortNode node_of_sort(asc);
			node_of_sort.SetRelation(node_of_from_list);
			node_of_sort.SetMaps(sort_name_translated);
			node_sorted = node_of_sort.Excute();
		
			//result = node_of_sort.Excute(list_tables,&sorts);
		}
		else
		{
			node_sorted = node_of_from_list;
		}
		
		
		

		//Build projection node
		ProjectionNode node_of_projection;		

		node_of_projection.SetRelation(node_sorted );
		node_of_projection.SetMap(attr_name_translated);
		RelationNode node_result = node_of_projection.Excute();
		

		if(need_distinct == 1)
		{
			EliminateDuplicateNode ed_node;
			ed_node.SetRelation(node_result);
			node_result = ed_node.Excute();

		}
		node_result.PrintTable();
		return node_result.GetResult();
	}

	void MakeInsert(YYlVal name,YYlVal value);

	vector<DataRow> MakeDelete(YYlVal name,YYlVal where_clause);

	void MakeUpdate(YYlVal name,YYlVal condition,YYlVal where_clause);

	void CreateIndex(YYlVal table_name,YYlVal col_name);
	
		
	operator std::string()
	{
		return strVal;
	}


	operator vector<NameEntry>*()
	{
		return m_name_entries;
	}
	operator vector<Attribute>*()
	{
		return m_attrs;
	}
	operator int()
	{
		return iVal;
	}
	operator double()
	{
		return dVal;
	}
};






class NameList
{
private:
	std::vector<NameEntry> m_lists;
public:
	void AddEntry(NameEntry* entry_add)
	{
		NameEntry new_entry = *entry_add;
		m_lists.push_back(new_entry);
	}

};

class SelectStmt
{
	NameList m_attr_list;
	NameList m_from_list;
	
};




#endif
