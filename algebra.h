#ifndef _ALGEBRE_H
#define _ALGEBRE_H
/*this file is used to define Different Node of Relational
 *Algebra, in order to excute the Query
**/
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include <map>
#include "common.h"
#include "data_represent.h"





using std::cout;
using std::string;
using std::vector;
using std::deque;
using std::map;
class IFetchable
{
public:
	virtual void* GetData(int line,int column);
};

struct Column_NameMap
{
	Column_NameMap()
	{
		table_index = 0;
		column_index = 0;
	}
	int table_index;
	int column_index;
};

class SimpleExpr
{
public:
	enum SimpleExprOperator{LargeThan=0,SmallThan,Equal};
	enum SimpleExprOperatorType{AttrName=0,IntValue,RealValue,StrValue};
	typedef struct _S_Operand
	{
		_S_Operand()
		{
			oper_type = SimpleExpr::StrValue;
		}
		NameEntry name_entry;
		Column_NameMap name_map2;
		int iVal;
		double dVal;
		string strVal;
		SimpleExprOperatorType oper_type;

	}SecondOperand;
public:
	SimpleExpr();
	SimpleExpr(NameEntry operand1,SecondOperand operand2,SimpleExprOperator operate);


	int table_index1;
	int table_index2;
	NameEntry m_operand1;
	Column_NameMap name_map1;
	SecondOperand m_operand2;
	SimpleExprOperator m_operator;
};


class Conditions;
class RelationNode //Represent A Relation
{
public:
	enum RelationOperator{NONE=0,JOIN};
	RelationNode();
	RelationNode(std::string name,RelationOperator oper,RelationNode* second_relation);

	void SetOperator(RelationOperator oper);

	
	void AppendRelation(RelationNode* oper);


	void SetResult(vector<DataTable>& tables_to_tes);

	DataTable GetResult();

	void SetConditons(vector< vector<SimpleExpr> >& exprs)
	{
		m_exprs = exprs;
	}

	void PrintTable();//TestFunction

	DataTable DoJoin(vector<DataTable>& tables,Conditions* conditions_to_translate);

	
private:
	RelationOperator m_operator;
	std::string m_relation_name;
	RelationNode* m_second_oprand;
	vector< vector<SimpleExpr> > m_exprs;

	//test
	vector<DataTable> m_tables_to_test;

	DataTable m_result;

};



class Attribute
{
public:
	Attribute(){};
	Attribute(NameEntry& name,std::string second_name);
	NameEntry GetName()
	{
		return m_real_name;
	}
	std::string GetSecondName()
	{
		return m_second_name;
	}
	void SetName(NameEntry& entry)
	{
		m_real_name = entry;
			 
	}
	void SetSecondName(string& name)
	{
		m_second_name = name;
	}



private:
	NameEntry m_real_name;
	std::string m_second_name;


};

class Conditions;



class NameTransLater
{
public:
	static int TransLateToRealName(vector<NameEntry>& table_name_map,vector<Attribute>& attr_name_map,vector<DataTable>& tables,SimpleExpr& simple_expr,int left_right);

	static vector<Column_NameMap> TranslateName(vector<NameEntry>& table_name_map,vector<Attribute>& attr_name_map,vector<DataTable>& tables,vector<NameEntry>& name_translates,int left_right);


	static string GetUniqueTableNameByColumnName(string& column_name,vector<DataTable>& tables)
	{
		for(int i = 0;i<tables.size();i++)
		{
			vector<DataColumn> columns = tables[i].GetColumns();
			for(int j = 0;j<columns.size();j++)
			{
				
				if(columns[j].GetName().GetFirstName() == column_name)
				return tables[i].GetName();
			}

		}

		std::cerr<<"Can't find Column Name " << column_name <<std::endl;
		return "";

	}

	static void TranslateSingleTable(DataTable& table,SimpleExpr& expr)
	{
		expr.name_map1.table_index = 0;
		
		expr.name_map1.column_index = table.GetColumnIndex(expr.m_operand1 );

		if(expr.m_operand2.oper_type == SimpleExpr::AttrName)
		{
			expr.m_operand2.name_map2.table_index = 0;
			expr.m_operand2.name_map2.column_index = table.GetColumnIndex(expr.m_operand2.name_entry);
		}

	}
};



class Conditions
{
public:
	enum ConditionOperator{NONE=0,conditionOR,conditionAND};

public:
	Conditions();

	Conditions(SimpleExpr& expr,ConditionOperator operator1 = NONE);

	void SetSimpleExpr(SimpleExpr& expr);

	SimpleExpr& GetSimpleExpr();

	void AppendCondition(ConditionOperator operte,Conditions* conditionNext);

	vector<Conditions>& GetConditions()
	{
		return m_conditions;
	}
	void SetOperator(Conditions::ConditionOperator oper)
	{
		m_operator = oper;
	}

	bool IsConditionMatch(DataTable& table,DataRow& row);

	void TransLateToRealName(vector<NameEntry>& table_name_map,vector<Attribute>& attr_name_map,vector<DataTable>& tables,Conditions* the_condition=NULL)
	{
		
		int index = NameTransLater::TransLateToRealName(table_name_map,attr_name_map,tables,m_simple_expr,1);
		


		//Other Condition
		for(int j = 0;j<m_conditions.size();j++)
		{
			Conditions the_condition = m_conditions[j];
			SimpleExpr expr = the_condition.GetSimpleExpr();
			
			NameTransLater::TransLateToRealName(table_name_map,attr_name_map,tables,expr,1);
			
			the_condition.SetSimpleExpr(expr);
			m_conditions[j] = the_condition;
		}

		
	}

	vector< vector<SimpleExpr> > GetOrAndFormal()
	{
		vector<vector<SimpleExpr> > rets;
		if(m_operator == Conditions::NONE)
		{
			vector<SimpleExpr> simple_exprs;
			simple_exprs.push_back(m_simple_expr);
			rets.push_back(simple_exprs );
			return rets;
		}
		if(m_operator == Conditions::conditionOR)
		{	
			vector<SimpleExpr> simple_exprs;
			simple_exprs.push_back(m_simple_expr);
			rets.push_back(simple_exprs );
			simple_exprs.clear();
		}
		vector<SimpleExpr> simple_exprs;
		if(m_operator == Conditions::conditionAND)
		{
			simple_exprs.push_back(m_simple_expr);
		}			
		vector<int> ors;
		for(int i = 0;i<m_conditions.size();i++)
		{
			if(m_conditions[i].m_operator == Conditions::conditionOR || m_conditions[i].m_operator == Conditions::NONE)
				ors.push_back(i);
		}
		
		//Find First Or
		int index = 0;
		int m  = 0;
		while(index< ors.size())
		{
			int or_offset = ors[index];
			for(m;m<=or_offset;m++)
				simple_exprs.push_back(m_conditions[m].m_simple_expr);
			rets.push_back(simple_exprs);
			simple_exprs.clear();
			index++;
		}
		return rets;
		

	}


private:	
	SimpleExpr m_simple_expr;
	ConditionOperator m_operator;
	vector<Conditions> m_conditions;
};

class SelectNode
{
	RelationNode m_relation_to_operate;
	Conditions m_condition;
	bool m_has_condition;
	void TransLateToRealName(vector<DataTable>& tables) //Translate the where-claues' second name to its real name(realtablename.realname);
	{
		m_condition.TransLateToRealName(m_table_name_map,m_attr_name_map,tables);
	}
	vector<NameEntry> m_table_name_map;
	vector<Attribute> m_attr_name_map;
public:
	SelectNode()
	{
		m_has_condition = false;
	}
	void SetRelation(const RelationNode& oprand);

	void SetCondition(const Conditions& condition);

	void SetTableNameMap(vector<NameEntry>* entries)
	{
		m_table_name_map = *entries;

	}
	void SetAttrNameMap(vector<Attribute>* entries)
	{
		m_attr_name_map = *entries;

	}

		
	RelationNode GetRelation();

	Conditions GetCondition();

	RelationNode Excute(vector<DataTable> tables); //TestFunction

	

};


class ProjectionNode
{
private:
	RelationNode m_relation_to_operate;
	vector<Column_NameMap> m_map;
	

public:
	void SetRelation(const RelationNode& oprand);

	RelationNode GetRelation();

	void SetAttrs(const std::vector<Attribute>& attrs);

	void AddAttrs(const Attribute& attr_to_add);

	void SetMap(vector<Column_NameMap> maps)
	{
		m_map = maps;
	}

	RelationNode Excute();

};

template<class T,typename AppendType = int>
class HashTable
{
typedef vector<T> VT;
protected:
	map<int,vector<T> > m_map;

	virtual int ComputeHashId(int id_to_compute) = 0;
	virtual int ComputeHashId(std::string id_to_compute) = 0;
	virtual int ComputeHashId(double id_to_compute) = 0;
	virtual bool OnAddElement(T& element,int id,AppendType append_val) = 0; 
public:
	void AddNewData(T new_row,int id,AppendType append_val)
	{
		int id_compute = ComputeHashId(id);
		if(OnAddElement(new_row,id_compute,append_val))
		{
			m_map[id_compute].push_back(new_row);
			m_vec_rows.push_back(new_row);
		}
	}
	void AddNewData(T new_row,string id,AppendType append_val)
	{
		int id_compute = ComputeHashId(id);
		if(OnAddElement(new_row,id_compute,append_val))
		{
			m_map[id_compute].push_back(new_row);
			m_vec_rows.push_back(new_row);
		}

	}
	void AddNewData(T new_row,double id,AppendType append_val)
	{
		int id_compute = ComputeHashId(id);
		if(OnAddElement(new_row,id_compute,append_val))
		{
			m_map[id_compute].push_back(new_row);
			m_vec_rows.push_back(new_row);
		}
	}


	vector<DataRow> GetAllData()
	{
		
		return m_vec_rows;
	}

	vector<T> m_vec_rows;
};


template<int GroupSize>
class HashTableDuplicate : public HashTable<DataRow,vector<DataColumn> >
{
protected:
	virtual int ComputeHashId(int id_to_compute)
	{
		return id_to_compute % GroupSize;

	}
	virtual int ComputeHashId(std::string id_to_compute)
	{
		char c = id_to_compute[0];
		return ( (int)c ) % GroupSize;

	}
	virtual int ComputeHashId(double id_to_compute) 
	{
		int i = (int)id_to_compute;
		return i % GroupSize;

	}
	virtual bool OnAddElement(DataRow& element,int id,vector<DataColumn> append_val)
	{
		vector<DataRow>& rows = m_map[id];
		//int type = element[0].
		bool b_is_duplicate = true;
		
		if(rows.size() == 0)
			return true;
		
		for(int i = 0;i<rows.size();i++)
		{
			for(int j = 0;j< element.GetCount() ;j++)
			{
				Data data = element[j];
				Data data_former = rows[i][j];
				int type = append_val[j].GetColType();
				if(type == DataColumn::COLUMN_TYPE_INTEGER)
				{
					if(data.GetInt() != data_former.GetInt() )
						b_is_duplicate = false;
				}
				else if (type == DataColumn::COLUMN_TYPE_REAL)
				{
					if(data.GetRealNum() != data_former.GetRealNum() )
						b_is_duplicate = false;

				}
				else
				{
					if(data.GetStr() != data.GetStr() )
						b_is_duplicate = false;

				}
			
			}
			if(b_is_duplicate)
				return false;
			b_is_duplicate = true;
		}
		return true;

	}

};

class EliminateDuplicateNode
{
private:
	RelationNode m_relation;
public:
	RelationNode GetRelation()
	{
		return m_relation;

	}
	void SetRelation(RelationNode& relation)
	{
		m_relation = relation;
	}

	RelationNode Excute()
	{
		//Copy Table's skeleton
		DataTable dt_ret;
		DataTable dt_former = m_relation.GetResult();
		dt_ret.SetName(dt_former.GetName() );
		dt_ret.SetColumns( dt_former.GetColumns() );
		dt_ret.SetJoinInfo( dt_former.GetJoinInfo() );

		HashTableDuplicate<2> hash_table;
		vector<DataColumn> columns = dt_former.GetColumns();
		DataColumn::DataColumnType col1_type = columns[0].GetColType();
		for(int i = 0;i<dt_former.GetCount();i++)
		{
			DataRow dr = dt_former[i];
			if(col1_type == DataColumn::COLUMN_TYPE_REAL )
				hash_table.AddNewData(dr,dr[0].GetRealNum(),columns);
			else if (col1_type == DataColumn::COLUMN_TYPE_INTEGER)
				hash_table.AddNewData(dr,dr[0].GetInt(),columns);
			else 
				hash_table.AddNewData(dr,dr[0].GetStr(),columns);

		}
		
		vector<DataRow> new_rows = hash_table.GetAllData();
		for(int i = 0;i<new_rows.size();i++)
		{
			dt_ret.AddRow(new_rows[i] );
		}
		vector<DataTable> list_table;
		list_table.push_back(dt_ret);
		RelationNode node("elimate_duplicate_node",RelationNode::NONE,NULL);

		node.SetResult(list_table);
		return node;
	}

};

class SortNode
{
private:
	RelationNode m_relation_to_operate;
	vector<Column_NameMap> maps;
	
	int m_asc ;  //1 asc 2 desc
public:
	SortNode(int asc)
	{
		m_asc = asc;
	}
	void SetMaps(vector<Column_NameMap>& name_maps)
	{
		maps = name_maps;
	}
	void SetRelation(const RelationNode& oprand)
	{
		m_relation_to_operate = oprand;
	}

	RelationNode GetRelation()
	{
		return m_relation_to_operate;
	}

	RelationNode Excute();
	
};

#endif

