#ifndef _EXCUTOR_H
#define _EXCUTOR_H

#include<vector>
#include<string>
#include<deque>
#include<algorithm>

#include <stdlib.h>
#include "algebra.h"
#include "data_represent.h"
#include "storage.h"
#include "index.h"

using std::vector;
using std::string;
using std::deque;

class SelectOperator
{
private:
	static void AppendVector(vector<DataRow>& vec_to_append,vector<DataRow>& vec_append)
	{
		for(int i = 0;i<vec_append.size();i++)
			vec_to_append.push_back(vec_append[i]);
	};
public:
	static vector<DataRow> GetSelectResult(DataTable& dt1,int index1,vector<vector<SimpleExpr> >* pcondition) 
	{
		//First Select , like a.intval <3 ,making table smaller
		//Get Column Related SimpleExpr
		vector<vector<SimpleExpr> >exprs_to_test_table1;

		for(int i = 0;i<pcondition->size();i++)
		{
			vector<SimpleExpr> exprs = (*pcondition)[i];
			vector<SimpleExpr> v1;
			for(int i = 0;i<exprs.size();i++)
			{
				SimpleExpr& expr = exprs[i];

				if(expr.m_operand2.oper_type!= SimpleExpr::AttrName)
				{
					if( expr.name_map1.table_index == index1)
						v1.push_back(expr);

				}
			}
			exprs_to_test_table1.push_back(v1);

		}
		//Can't confirm 
		bool b_find = false;
		for(int i = 0;i<exprs_to_test_table1.size();i++)
		{
			if(exprs_to_test_table1[i].size() == 0)
				b_find = true;
		}
		//Not Expr 
		if(exprs_to_test_table1.size() == 0 || b_find)
		{
			DataFile df;
			df.FillDataTable(dt1);
			return dt1.GetRows();
		}

		//Try To Use Index
		int b_use_index = false;
		if(exprs_to_test_table1.size() == 1)
		{
			if(exprs_to_test_table1[0].size() == 1)
			{
				SimpleExpr se = exprs_to_test_table1[0][0];
				if(se.m_operator == SimpleExpr::Equal && se.m_operand2.oper_type!= SimpleExpr::AttrName)
				{
					if(SimpleIndex::IndexExist(dt1.GetName(),dt1.GetColumns()[se.name_map1.column_index].GetName().GetFirstName() ))
					{
						b_use_index = true;
						SimpleIndex s_index;
						SimpleIndexFile sif(dt1.GetName(),dt1.GetColumns()[se.name_map1.column_index].GetName().GetFirstName());

						sif.FillInSimpleIndex(s_index);
						vector<int> offsets;
						vector<DataRow> rows;
						if(se.m_operand2.oper_type == SimpleExpr::IntValue)
						{
							Data data(se.m_operand2.iVal);
							offsets = s_index[data];

						}
						else if(se.m_operand2.oper_type == SimpleExpr::RealValue)
						{
							Data data(se.m_operand2.dVal);
							offsets = s_index[data];

						}
						else //Str
						{
							Data data(se.m_operand2.strVal);
							offsets = s_index[data];
						}

						for(int i = 0;i<offsets.size();i++)
						{
							rows.push_back( sif.GetRowByIndex(offsets[0]) );
						}
						dt1.SetRows(rows);

					}

				}
			}
		}
		if(!b_use_index)
		{
			DataFile df;
			df.FillDataTable(dt1);

		}


		vector<DataRow> rows1;

		//Do Select 
		vector<DataRow> table_1_rows = dt1.GetRows();


		for(int i = 0;i<table_1_rows.size();i++)
		{
			//vector<bool> result;
			for(int j = 0; j<exprs_to_test_table1.size();j++)
			{
				vector<SimpleExpr> expr = exprs_to_test_table1[j];
				bool b_ok = true;
				for(int m = 0;m<expr.size();m++)
				{
					if(! IsConditionMatch(dt1,table_1_rows[i],expr[m]))
					{
						b_ok = false;
						break;
					}
				}
				if(b_ok)
				{
					rows1.push_back(table_1_rows[i]);
					break;
				}

			}
		}
		return rows1;


	}
	static bool ConditionMatch(DataRow& row1,DataRow row2,vector<int> joint_info,vector<int> joined_table,int join_table,vector<vector<SimpleExpr> >* pcond)
	{
		vector<vector<SimpleExpr> >simple_exprs = GetRelatedExpr(joined_table,join_table,pcond);
		//Fetch data
		for(int i = 0;i<simple_exprs.size();i++)
		{
			vector<SimpleExpr> vec_ex = simple_exprs[i];
			bool b_ok = true;
			for(int j =0;j<vec_ex.size();j++)
			{
				SimpleExpr se = vec_ex[j];
				Column_NameMap data_map1 = se.name_map1;
				Column_NameMap data_map2 = se.m_operand2.name_map2;

				if(se.name_map1.table_index == join_table) //
				{
					int data_offset1 = se.name_map1.column_index;
					int data_offset2 = GetJoinedTableColumnIndex(joint_info,data_map2);
					if( !IsConditionMatch(row2[data_offset1],row1[data_offset2],se.m_operator) )
						b_ok = false;
				}
				else
				{
					int data_offset1 = GetJoinedTableColumnIndex(joint_info,data_map1);
					int data_offset2 = data_map2.column_index;
					if( !IsConditionMatch(row1[data_offset1],row2[data_offset2],se.m_operator) )
						b_ok = false;
				}



			}
			if(b_ok == true)
				return true;
		}

		return true;
		//Get If it confirms other condition
		//vector<vector<SimpleExpr> > simple_exprs2 = GetUnRelatedExpr(joined_table,join_table,pcond);


		return false;
	}

public:
	static int GetJoinedTableColumnIndex(const vector<int> & join_info,Column_NameMap& maps)
	{
		if(join_info.size() == 0)
			return maps.column_index;

		int t_index= maps.table_index;
		int c_index = maps.column_index;
		int ret = 0;
		for(int i = 0;i< t_index;i++)
		{
			ret += join_info[i];
		}
		return ret + c_index;

	}
	static vector<vector<SimpleExpr> >GetRelatedExpr(vector<int> joined_table,int join_table,vector<vector<SimpleExpr> >* p_condition)
	{
		vector<vector<SimpleExpr> > ret_vec;
		for(int i = 0;i< p_condition->size();i++)
		{
			vector<SimpleExpr> rets;
			vector<SimpleExpr> simple_expr = (*p_condition)[i];
			for(int j = 0;j<simple_expr.size();j++)
			{
				SimpleExpr expr = simple_expr[j];
				if(expr.m_operand2.oper_type == SimpleExpr::AttrName)
				{
					if(expr.name_map1.table_index == join_table)
					{
						if( find(joined_table.begin(),joined_table.end(),expr.m_operand2.name_map2.table_index) != joined_table.end() )
						{
							rets.push_back(expr);						
						}
					}
					else if (expr.m_operand2.name_map2.table_index == join_table)
					{
						if( find(joined_table.begin(),joined_table.end(),expr.name_map1.table_index) != joined_table.end() )
						{
							rets.push_back(expr);						
						}
					}
				}
			}
			if(rets.size() > 0)
				ret_vec.push_back(rets);
		}
		return ret_vec;
	}

	static vector<vector<SimpleExpr> >GetUnRelatedExpr(vector<int> joined_table,int join_table,vector<vector<SimpleExpr> >* p_condition)
	{
		vector<vector<SimpleExpr> > ret_vec;
		for(int i = 0;i< p_condition->size();i++)
		{
			vector<SimpleExpr> rets;
			vector<SimpleExpr> simple_expr = (*p_condition)[i];
			for(int j = 0;j<simple_expr.size();j++)
			{
				SimpleExpr expr = simple_expr[j];
				if(expr.m_operand2.oper_type != SimpleExpr::AttrName)
				{
					if(expr.name_map1.table_index == join_table)
					{
						rets.push_back(expr);						
					}
					else if(find(joined_table.begin(),joined_table.end(),expr.name_map1.table_index) != joined_table.end())
					{
						rets.push_back(expr);
					}

				}
			}
			if(rets.size() > 0)
				ret_vec.push_back(rets);
		}
		return ret_vec;
	}
	static bool IsConditionMatch(DataTable& table,DataRow& row,SimpleExpr expr);

	static bool IsConditionMatch(Data& data_1,Data& data_2,SimpleExpr::SimpleExprOperator opera)
	{
		if(opera == SimpleExpr::LargeThan) //Large
		{
			return data_1 > data_2;

		}
		if(opera == SimpleExpr::Equal) //Equsl
		{
			return data_1 == data_2;

		}
		//less
		return data_1 < data_2; 

	}



};


class JoinOperator
{
public:
	static DataTable GetResult(vector<DataTable>& opers,vector<vector<SimpleExpr> > vec_condition,Conditions condition)
	{
		vector<vector<SimpleExpr> > * p_condition = &vec_condition;

		//Get All Rows
		vector<vector<DataRow> > rows;
		for(int i = 0;i<opers.size() ;i++)
		{
			rows.push_back(SelectOperator::GetSelectResult(opers[i],i,p_condition) );
		}
		DataTable dt_ret;

		dt_ret.SetColumns(opers[0].GetColumns());
		dt_ret.SetRows(rows[0]);
		dt_ret.GetJoinInfo().push_back(dt_ret.GetColumns().size() );

		//Begin Join 
		vector<int> joined_table;
		joined_table.push_back(0);
		int to_join = 1;
		if(opers.size() > 1)
		{
			while(to_join < opers.size() )
			{
				vector<DataRow> new_rows;
				vector<DataRow>& rows1 = dt_ret.GetRows();
				vector<DataRow> rows2 = rows[to_join];
				//vector<SimpleExpr> expr = SelectOperator::GetRelatedExpr(joined_table,to_join,p_condition);
				for(int i = 0;i<rows1.size();i++)
				{
					for(int j= 0;j<rows2.size();j++)
					{
						vector<DataColumn> col1 = dt_ret.GetColumns();
						vector<DataColumn> col2 = opers[to_join].GetColumns();

						DataRow new_row;

						if(SelectOperator::ConditionMatch(rows1[i],rows2[j],dt_ret.GetJoinInfo(),joined_table,to_join,p_condition) )
						{
							for(int m=0;m<col1.size();m++ )
							{
								new_row.AddData(rows1[i][m]);
							}
							for(int m=0;m<col2.size();m++)
							{
								new_row.AddData(rows2[j][m]);
							}
							new_rows.push_back(new_row);
						}
					}
				}
				dt_ret.SetRows(new_rows);

				dt_ret.AddColumn(opers[to_join].GetColumns() );
				int col_size = opers[to_join].GetColumns().size();

				dt_ret.GetJoinInfo().push_back(col_size);

				joined_table.push_back(to_join ++ );
			}


		}

		if(vec_condition.size() != 0)
		{
			vector<DataRow> last_row = dt_ret.GetRows();
			vector<DataRow> ret_row;
			for(int i = 0;i<last_row.size();i++)
			{
				if( condition.IsConditionMatch(dt_ret,last_row[i]) )
					ret_row.push_back(last_row[i]);
			}
			dt_ret.SetRows(ret_row);
		}
		return dt_ret;
	}




};

class SimpleExprCompute
{
public:
	static bool Compute(DataRow& row_to_computer,SimpleExpr& expr,DataTable& table_info)
	{

		int column_index1 = SelectOperator::GetJoinedTableColumnIndex(table_info.GetJoinInfo(),expr.name_map1);

		Data data = row_to_computer[column_index1];
		SimpleExpr::SimpleExprOperator oper_type = expr.m_operator;


		switch(expr.m_operand2.oper_type)
		{
		case SimpleExpr::IntValue:
			if(oper_type == SimpleExpr::LargeThan)
			{
				return  data.GetInt() > expr.m_operand2.iVal;				
			}
			if(oper_type == SimpleExpr::SmallThan)
			{
				return  data.GetInt() < expr.m_operand2.iVal;	

			}
			if(oper_type == SimpleExpr::Equal)
			{
				return  data.GetInt() == expr.m_operand2.iVal;	

			}
		case SimpleExpr::RealValue:
			if(oper_type == SimpleExpr::LargeThan)
			{
				return  data.GetRealNum() > expr.m_operand2.dVal;				
			}
			if(oper_type == SimpleExpr::SmallThan)
			{
				return  data.GetRealNum() < expr.m_operand2.dVal;	

			}
			if(oper_type == SimpleExpr::Equal)
			{
				return  data.GetRealNum() == expr.m_operand2.dVal;	

			}
		case SimpleExpr::StrValue:
			if(expr.m_operand2.strVal[0]=='\'')
				expr.m_operand2.strVal = expr.m_operand2.strVal.substr(1, expr.m_operand2.strVal.size() - 2);
			if(oper_type == SimpleExpr::LargeThan)
			{
				return  data.GetStr() > expr.m_operand2.strVal;				
			}
			if(oper_type == SimpleExpr::SmallThan)
			{
				return  data.GetStr() < expr.m_operand2.strVal;	

			}
			if(oper_type == SimpleExpr::Equal)
			{
				return  data.GetStr() == expr.m_operand2.strVal;	

			}
		case SimpleExpr::AttrName:
			Data data2 = row_to_computer[SelectOperator::GetJoinedTableColumnIndex(table_info.GetJoinInfo(),expr.m_operand2.name_map2)];
			if(oper_type == SimpleExpr::LargeThan)
			{
				return  data > data2;				
			}
			if(oper_type == SimpleExpr::SmallThan)
			{
				return  data < data2;		

			}
			if(oper_type == SimpleExpr::Equal)
			{
				return  data == data2;	

			}

		}
		return false;
	};
};
class AndOrCompute
{
public:
	static bool Compute(deque<bool>& operands,deque<Conditions::ConditionOperator> operators)
	{
		if(operands.size() == 1)
			return operands[0];
		vector<bool> stack_operands;
		vector<Conditions::ConditionOperator> stack_operator;

		stack_operands.push_back( operands[0]);
		stack_operands.push_back( operands[1]);
		stack_operator.push_back(operators[0]);
		operands.pop_front();
		operands.pop_front();
		operators.pop_front();
		while(operands.size() )
		{
			Conditions::ConditionOperator top_operator = stack_operator.back();
			Conditions::ConditionOperator top_operator_former = operators.front();
			if( top_operator >= top_operator_former)
			{
				ComputeStack(stack_operands,stack_operator);				
			}
			else
			{
				stack_operands.push_back( operands.front() );
				operands.pop_front();
				stack_operator.push_back( operators.front() );
				operators.pop_front();
			}

			if( stack_operands.size() == 1)
			{
				stack_operands.push_back( operands.front() );
				operands.pop_front();

			}
			else if ( stack_operands.size() == 0)
			{
				stack_operands.push_back( operands.front() );
				operands.pop_front();
				stack_operands.push_back( operands.front() );
				operands.pop_front();

			}

			if(stack_operator.size() == 0)
			{
				stack_operator.push_back( operators.front() );
				operators.pop_front();

			}
		}

		while(stack_operands.size() >1 )
		{
			ComputeStack(stack_operands,stack_operator);

		}
		return stack_operands[0];
	}

	static void ComputeStack(vector<bool>& op1,vector<Conditions::ConditionOperator>& op2)
	{
		if(op1.size() < 2)
			return;
		bool stack1,stack2;
		stack1 = op1.back();
		op1.pop_back();
		stack2 = op1.back();
		op1.pop_back();

		if(op2.back() == Conditions::conditionAND)
		{
			op1.push_back( stack1 && stack2);
		}
		else
		{
			op1.push_back( stack1 || stack2);
		}
		op2.pop_back();
	}


};

class ProjectionOperator
{
public:
	static DataTable Compute(DataTable table_former,vector<int> column_indexs)
	{
		DataTable dt_result;
		for(int j = 0 ;j<table_former.GetCount();j++)
		{
			DataRow row;
			DataRow row_former = table_former[j];

			for(int i = 0;i<column_indexs.size();i++)
			{
				int index = column_indexs[i];
				row.AddData(row_former[index] );

			}
			dt_result.AddRow(row);

		}

		//Rebuild Column Info
		vector<DataColumn> columns = table_former.GetColumns();
		for(int i = 0;i<column_indexs.size();i++)
		{
			int index = column_indexs[i];
			dt_result.AddColumn( columns[index]);

		}
		return dt_result;
	}
};



class DataRowCompute
{
public:
	static bool LargeThan(DataRow& row1,DataRow& row2,vector<int>& sort_indexs)
	{
		bool b_large = false;
		if(sort_indexs.size() == 0)
			sort_indexs.push_back(0);

		int i = 0;
		while(i < sort_indexs.size() )
		{
			int index = sort_indexs[i];
			if(index == -1)
				index = 0;
			Data data1 = row1[index];
			Data data2 = row2[index];

			if(DataCmp(data1,data2) > 0)
			{
				b_large = true;
				break;
			}
			else if(DataCmp(data1,data2) == 0)
			{
				i++;
			}
			else
			{
				b_large = false;
				break;
			}


		}
		return b_large;   
	}
	static bool SmallThan(DataRow& row1,DataRow& row2,vector<int>& sort_indexs)
	{
		bool b_small = false;
		if(sort_indexs.size() == 0)
			sort_indexs.push_back(0);

		int i = 0;
		while(i < sort_indexs.size() )
		{
			int index = sort_indexs[i];
			if(index == -1)
				index = 0;
			Data data1 = row1[index];
			Data data2 = row2[index];

			if(DataCmp(data1,data2) < 0)
			{
				b_small = true;
				break;
			}
			else if(DataCmp(data1,data2) == 0)
			{
				i++;
			}
			else
			{
				b_small = false;
				break;
			}
		}
		return b_small;   
	}
private:
	/* 1 >, 0 = , -1 <*/
	static int DataCmp(Data& data1,Data& data2)
	{
		Data::DataType type = data1.GetType();
		if(type == Data::INT)
		{
			if( data1.GetInt() > data2.GetInt() )
				return 1;
			if( data1.GetInt() == data2.GetInt() )
				return 0;
			return -1;
		}
		else if (type == Data::REAL)
		{
			if(data1.GetRealNum() > data2.GetRealNum() )
				return 1;
			if( data1.GetRealNum() == data2.GetRealNum() )
				return 0;
			return -1;
		}
		else    //String
		{
			if(data1.GetStr() > data2.GetStr() )
				return 1;
			if(data1.GetStr() == data2.GetStr() )
				return 0;
			return -1;

		}
		return  -1;
	}

};



class SortOperation
{
public:
	enum SortOrder{SORT_ASC=0,SORT_DESC};

	static void DoSort(DataTable& table,vector<int>& sort_indexs,int asc)
	{
		vector<DataRow>& row = table.GetRows();
		if(asc == 1)
			SortAsc(row,0,row.size()-1,sort_indexs);
		else
			SortDesc(row,0,row.size()-1,sort_indexs);
	}

private:
	//asc
	static void SortAsc(vector<DataRow>& A,int left,int right,vector<int>& sort_indexs)
	{
		if(left>right)
			return ;
		int i = left;
		int j = right;
		DataRow tmp =A[(left+right)/2];
		do{
			while( DataRowCompute::SmallThan(A[i],tmp,sort_indexs)&&i<right) i++;
			while( DataRowCompute::LargeThan(A[j],tmp,sort_indexs)&&j>left) j--;
			if(i<=j){
				swap(A[i],A[j]);
				i++;
				j--;
			}
		}while(i<=j);

		if(left<j) SortAsc(A,left,j,sort_indexs);
		if(i<right) SortAsc(A,i,right,sort_indexs);

	}

	static void SortDesc(vector<DataRow>& A,int left,int right,vector<int>& sort_indexs)
	{
		if(left>right)
			return;
		int i = left;
		int j = right;
		DataRow tmp =A[(left+right)/2];
		do{
			while( DataRowCompute::LargeThan(A[i],tmp,sort_indexs)&&i<right) i++;
			while( DataRowCompute::SmallThan(A[j],tmp,sort_indexs)&&j>left) j--;
			if(i<=j){
				swap(A[i],A[j]);
				i++;
				j--;
			}
		}while(i<=j);

		if(left<j) SortDesc(A,left,j,sort_indexs);
		if(i<right) SortDesc(A,i,right,sort_indexs);

	}

	static void swap(DataRow& row1,DataRow& row2)
	{
		DataRow row = row1;
		row1 = row2;
		row2 = row;
	}


};




#endif
