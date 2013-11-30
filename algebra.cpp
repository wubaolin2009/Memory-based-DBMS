#include "algebra.h"
#include "excutor.h"

SimpleExpr::SimpleExpr(){ table_index1 = -1;table_index2 = -1;};
SimpleExpr::SimpleExpr(NameEntry operand1,SecondOperand operand2,SimpleExprOperator operate)
{
	table_index2 = table_index1 = -1;
	m_operand1 = operand1;
	m_operand2 = operand2;
	m_operator = operate;
	
	
}


Conditions::Conditions(){
	m_operator = NONE;
};
Conditions::Conditions(SimpleExpr& expr,ConditionOperator operator1)
{

	m_operator = operator1;
	m_simple_expr = expr;
	//m_next_condition = next_condition;
}
void Conditions::SetSimpleExpr(SimpleExpr& expr)
{
	m_simple_expr = expr;
}
SimpleExpr& Conditions::GetSimpleExpr()
{
	return m_simple_expr;
}
void Conditions::AppendCondition(ConditionOperator operte,Conditions* conditionNext)
{
	if(m_conditions.size() )
	{
		m_conditions[m_conditions.size() -1 ].m_operator = operte;
	}
	m_operator = operte;
	Conditions new_condition(conditionNext->m_simple_expr,conditionNext->m_operator);
	new_condition.m_simple_expr = conditionNext->m_simple_expr;
	m_conditions.push_back(new_condition);
	for(int i = 0;i<conditionNext->m_conditions.size();i++)
	{
		m_conditions.push_back( (conditionNext->m_conditions)[i] );
	}
}

bool Conditions::IsConditionMatch(DataTable& table,DataRow& row)
{
	deque<bool> test_operands;
	deque<Conditions::ConditionOperator> test_operators;

	SimpleExpr expr_to_test = GetSimpleExpr();

	
	test_operands.push_back( SimpleExprCompute::Compute(row,expr_to_test,table) );
	if(m_operator != NONE)
		test_operators.push_back(m_operator);

	for(int j = 0; j<m_conditions.size(); j++)
	{
		Conditions condition_to_test = m_conditions[j];
		SimpleExpr expr_to_test = condition_to_test.GetSimpleExpr();
		int column_index = table.GetColumnIndex(expr_to_test.m_operand1,expr_to_test.table_index1);
		test_operands.push_back( SimpleExprCompute::Compute(row,expr_to_test,table) );
		if(condition_to_test.m_operator != NONE)
			test_operators.push_back(condition_to_test.m_operator);

	}
	return AndOrCompute::Compute(test_operands,test_operators);
}


void SelectNode::SetRelation(const RelationNode& oprand)
{
	m_relation_to_operate = oprand;
}
void SelectNode::SetCondition(const Conditions& condition)
{
	m_has_condition = true;
	m_condition = condition;
}

RelationNode SelectNode::GetRelation()
{
	return m_relation_to_operate;
}
Conditions SelectNode::GetCondition()
{
	return m_condition;
}
RelationNode SelectNode::Excute(vector<DataTable> tables) //TestFunction
{
	DataTable table_select = m_relation_to_operate.GetResult();
	DataTable table_result;
	table_result.SetColumns( table_select.GetColumns());

	if(m_has_condition)
		TransLateToRealName(tables);

	for(int i = 0;i < table_select.GetCount();i++)
	{
		DataRow row = table_select[i];
		if(m_has_condition)
		{
			if( m_condition.IsConditionMatch(table_select,row) )
				table_result.AddRow(row);
		}
		else
			table_result.AddRow(row);
	}
	RelationNode result("select_result",RelationNode::NONE,NULL);
	vector<DataTable> list_table;
	list_table.push_back(table_result);
	result.SetResult(list_table);
	
	return result;
	


}
void RelationNode::PrintTable()//TestFunction
{
	
	DataTable table = m_tables_to_test[0];
	cout<<"============================================"<<std::endl;
	vector<DataColumn> cols = table.GetColumns();
	for(int i = 0;i<cols.size() ;i++)
	{
		string str_print = cols[i].GetName().GetFirstName();
		if(cols[i].GetName().GetSecondName() != "")
			str_print = cols[i].GetName().GetSecondName();
		cout<<str_print<<"    ";
	}
	cout<<std::endl;

	for(int j = 0;j<table.GetCount();j++)
	{
		for(int m = 0; m<table[j].GetCount();m++)
		{
			if(table.GetColumns()[m].GetColType() == DataColumn::COLUMN_TYPE_CHAR)
				cout<<table[j][m].GetStr()<<"    ";
			if(table.GetColumns()[m].GetColType() == DataColumn::COLUMN_TYPE_VARCHAR)
				cout<<table[j][m].GetStr()<<"    ";
			if(table.GetColumns()[m].GetColType() == DataColumn::COLUMN_TYPE_INTEGER)
				cout<<table[j][m].GetInt()<<"    ";
			if(table.GetColumns()[m].GetColType() == DataColumn::COLUMN_TYPE_REAL)
				cout<<table[j][m].GetRealNum()<<"    ";
		}
		cout<<std::endl<<std::endl;
	}
	cout<< table.GetCount() << " Rows returned.";
	cout<<std::endl<<std::endl;
}


Attribute::Attribute(NameEntry& name,std::string second_name)
{
	m_real_name = name;
	m_second_name = second_name;
}


void ProjectionNode::SetRelation(const RelationNode& oprand)
{
	m_relation_to_operate = oprand;
}
RelationNode ProjectionNode::GetRelation()
{
	return m_relation_to_operate;
}






RelationNode::RelationNode(){};
RelationNode::RelationNode(std::string name,RelationOperator oper,RelationNode* second_relation)
{
	m_operator = oper;
	if(second_relation)
		m_second_oprand = new RelationNode(*second_relation);
	else
		m_second_oprand = NULL;

	m_relation_name = name;
}

void RelationNode::SetOperator(RelationOperator oper)
{

	m_operator = oper;
}

void RelationNode::AppendRelation(RelationNode* oper)
{
	m_second_oprand = new RelationNode(*oper);
}

void RelationNode::SetResult(vector<DataTable>& tables_to_tes)
{
	m_tables_to_test = tables_to_tes;
}

DataTable RelationNode::GetResult()
{
	if( m_tables_to_test.size() == 1)
		return m_tables_to_test[0];

	int index_to_fetch = -1;
	
	for(int i = 0;i<m_tables_to_test.size();i++)
	{
		if(m_relation_name == m_tables_to_test[i].GetName() )
			index_to_fetch = i;
	}

	if(index_to_fetch == -1)	
	{
		std::cerr<<"Unknown Relation " << m_relation_name<<std::endl;
	}
	
	
	DataTable table_to_return = m_tables_to_test[index_to_fetch];/*
	if(m_operator == JOIN)
	{
		DataTable dt = m_second_oprand->GetResult();
		vector<int> info = dt.GetJoinInfo();
		table_to_return = JoinOperator::GetResult(table_to_return,dt);
		info.push_back (table_to_return.GetColumns().size());
		table_to_return.SetJoinInfo(info);
		//
		
	}
	else
	{
		vector<int> info = table_to_return.GetJoinInfo();
		info.push_back (table_to_return.GetColumns().size());
		table_to_return.SetJoinInfo(info);
	}*/
	return table_to_return;

}



RelationNode ProjectionNode::Excute()
{
	DataTable dt = m_relation_to_operate.GetResult();
	vector<int> column_indexs;
	for(int i = 0;i<m_map.size();i++)
	{
		int index = SelectOperator::GetJoinedTableColumnIndex(dt.GetJoinInfo(),m_map[i] );

		column_indexs.push_back(index);
	}
	DataTable dt_ret =  ProjectionOperator::Compute(dt,column_indexs);
	vector<DataTable> list_table;
	list_table.push_back(dt_ret);
	RelationNode node;	
	node.SetResult(list_table);
	return node;
}

RelationNode SortNode::Excute()
{
	DataTable table_result = m_relation_to_operate.GetResult();

	//TranslateName
	vector<int> sort_indexs;
	for(int i = 0;i<maps.size();i++)
	{
		int index = SelectOperator::GetJoinedTableColumnIndex(table_result.GetJoinInfo(),maps[i]);
		
		sort_indexs.push_back(index);
	}

	RelationNode node;
	SortOperation::DoSort(table_result,sort_indexs,m_asc);
	vector<DataTable> dt;
	dt.push_back(table_result);
	node.SetResult(dt);
	return node;

}


int NameTransLater::TransLateToRealName(vector<NameEntry>& table_name_map,vector<Attribute>& attr_name_map,vector<DataTable>& tables,SimpleExpr& simple_expr,int left_right)
{
	int former_index = -1;

	//Translate Column Name  
	string columnname = simple_expr.m_operand1.GetSecondName();
	//if it's a second name 
	for(int i = 0;i<attr_name_map.size();i++)
	{
		if(columnname == attr_name_map[i].GetSecondName() ) //Yes , a second Name
		{
			simple_expr.m_operand1.SetSecondName(attr_name_map[i].GetName().GetSecondName());
			// if its table name can't be ensured
			if( attr_name_map[i].GetName().GetFirstName() != "" )
			{
				simple_expr.m_operand1.SetFirstName(attr_name_map[i].GetName().GetFirstName());
			}
		}
	}

	//Translate Table
	for(int i = 0;i<table_name_map.size();i++)
	{
		string tablename = simple_expr.m_operand1.GetFirstName();
		if(tablename != "" && table_name_map[i].GetSecondName()== tablename)
		{
			if(left_right == 1)
			{
				simple_expr.table_index1 = former_index = i;
			}
			if(left_right == 2)
			{
				simple_expr.table_index2 = former_index = i;
			}
			simple_expr.m_operand1.SetFirstName( table_name_map[i].GetFirstName() );
		}
	}


	//Translate if table name is ""
	if(simple_expr.m_operand1.GetFirstName() == "")
	{
		string column_name = simple_expr.m_operand1.GetSecondName();
		simple_expr.m_operand1.SetFirstName( GetUniqueTableNameByColumnName(column_name,tables));
	}

	//Translate seconde Table
	if(simple_expr.m_operand2.oper_type == SimpleExpr::AttrName)
	{
		SimpleExpr tmp_expr;
		SimpleExpr::SecondOperand oper2;
		oper2.oper_type = SimpleExpr::IntValue;
		tmp_expr.m_operand2 = oper2;
		tmp_expr.m_operand1 = simple_expr.m_operand2.name_entry;

		TransLateToRealName(table_name_map,attr_name_map,tables,tmp_expr,2);
		simple_expr.m_operand2.name_entry = tmp_expr.m_operand1;
		simple_expr.table_index2 = tmp_expr.table_index2;
	}
	if(former_index == -1)
	{
		for(int i = 0;i<tables.size();i++)
		{
			if(tables[i].GetName() == simple_expr.m_operand1.GetFirstName() )
				former_index = i;
		}
	}
	//if(former_index)
		//std::cerr<<"error In Get Column Index!" <<std::endl;
	return former_index;

}

vector<Column_NameMap> NameTransLater::TranslateName(vector<NameEntry>& table_name_map,vector<Attribute>& attr_name_map,vector<DataTable>& tables,vector<NameEntry>& name_translates,int left_right)
{
	vector<Column_NameMap> rets;
	for(int i = 0;i<name_translates.size();i++)
	{
		SimpleExpr expr;
		expr.m_operand1 = name_translates[i];
		expr.m_operand2.oper_type = SimpleExpr::IntValue;
		int table_index = TransLateToRealName(table_name_map,attr_name_map,tables,expr,1);
		Column_NameMap ret;
		ret.table_index = table_index;
		ret.column_index = tables[table_index].GetColumnIndex(expr.m_operand1);
		rets.push_back(ret);
	}
	return rets;
}

DataTable RelationNode::DoJoin(vector<DataTable>& tables,Conditions* p_conditions_to_translate)
{
	vector< vector<SimpleExpr> > ret ;
	Conditions conditions_to_translate;
	if(p_conditions_to_translate != NULL)
	{
		conditions_to_translate = *p_conditions_to_translate;
		ret = conditions_to_translate.GetOrAndFormal();

	}
	DataTable dt = JoinOperator::GetResult(tables,ret,conditions_to_translate);	
	vector<DataTable> dts;
	dts.push_back(dt);
	SetResult(dts);
	return dt;
	
}







