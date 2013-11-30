#include "lex_defines.h"
#include "data_represent.h"
#include "common.h"
#include <sstream>
#include "simple_log.h"
extern DataTable g_table_result;
vector<DataRow> YYlVal::MakeDelete(YYlVal name,YYlVal where_clause)
{
	string table_name = name;
	Conditions conditions = where_clause;
	MetaFile meta_file(table_name);
	if(!meta_file.TableExist() )
	{
		cerr << "Table Not Exist !" <<endl;
		vector<DataRow> ret;
		return  ret;
	}

	//Get The Table
	DataTable table_select;
	table_select.SetName(table_name); 
	table_select.SetColumns( meta_file.GetColumnsInfo() );
	DataFile df ;
	df.FillDataTable( table_select);

	//Translate Name
	NameTransLater::TranslateSingleTable(table_select,conditions.GetSimpleExpr() );
	for(int i = 0;i<conditions.GetConditions().size();i++)
	{
		NameTransLater::TranslateSingleTable(table_select,conditions.GetConditions()[i].GetSimpleExpr() );
	}
	
	DataTable table_result;
	table_result.SetName(table_name);
	table_result.SetColumns( table_select.GetColumns());

	

	for(int i = 0;i < table_select.GetCount();i++)
	{
		DataRow row = table_select[i];
		if(where_clause.GetAvailable() == false)
			table_result.AddRow(row);
		else if( conditions.IsConditionMatch(table_select,row) )
			table_result.AddRow(row);
	}
	vector<DataRow> rows_to_del = table_result.GetRows();
	for(int i = 0;i<rows_to_del.size();i++)
	{
		Simple_Log::AddLogEntry(Simple_Log_Entry::LOG_DEL_ENTRY,table_select.GetName(),table_select.GetColumns()[0].GetName().GetFirstName(),rows_to_del[i][0].GetInt() );
		Simple_Log::FlushLog();
		df.DelRow(table_select,rows_to_del[i]);
	}
	cout<<rows_to_del.size() <<" lines effected!" <<endl;
	SimpleIndex::RebuildIndex(table_result);
	return rows_to_del; 
}


void YYlVal::MakeUpdate(YYlVal name,YYlVal cond,YYlVal where_clause)
{
	string table_name = name;
	Conditions column_value = cond;
	SimpleExpr spexpr = column_value.GetSimpleExpr();
	string column_name = spexpr.m_operand1.GetSecondName();
	

	vector<DataRow> row_del = MakeDelete(name,where_clause);	
	
	//Add New Rows
	MetaFile meta_file(table_name);
	vector<DataColumn> cols = meta_file.GetColumnsInfo();
	if(!meta_file.TableExist() )
	{
		//cerr << "Table Not Exist !" <<endl;
		return ;
	}
	
	DataTable table;
	table.SetName(table_name);
	table.SetColumns(meta_file.GetColumnsInfo() );

	NameEntry column_index_entry(table_name,column_name);
	int column_index = table.GetColumnIndex(column_index_entry);
	if(column_index == -1)
	{
		cerr<< "Column Can't find1" <<endl;
		return ;
	}
	for(int i = 0;i<row_del.size();i++)
	{
		DataRow ro = row_del[i];
		if(spexpr.m_operand2.oper_type == SimpleExpr::IntValue)
		{
			ro[column_index] = spexpr.m_operand2.iVal;
		}
		else if(spexpr.m_operand2.oper_type == SimpleExpr::RealValue)
		{
			ro[column_index] = spexpr.m_operand2.dVal;
		}
		else
		{
			ro[column_index] = spexpr.m_operand2.strVal;
		}
		row_del[i] = ro;	
		
	}
	DataFile df;
	for(int i = 0;i<row_del.size();i++)
	{
		DataRow row = row_del[i];

		for(int i = 0;i<cols.size();i++)
		{
			DataColumn col = cols[i];
			if(col.HasFk() )
			{
				string ref_tbl_name = col.GetFkTableName();
				string ref_col_name = col.GetFkColName();


				std::stringstream ss;

				ss<< "select * from " << ref_tbl_name << " where " << ref_col_name << "=" << row[i].GetInt() <<";";
				yy_scan_string( ss.str().c_str() );
				yyparse();


				//Result
				if(g_table_result.GetRows().size() ==0)
				{
					cerr<<"Fk volatation! detected! "<<endl;
					Simple_Log::Undo();

					return;
				}
			}
		}

		Simple_Log::AddLogEntry(Simple_Log_Entry::LOG_ADD_ENTRY,table_name,cols[0].GetName().GetFirstName(),row[0].GetInt() );
		df.AddDataRow(table,row);

	}
	SimpleIndex::RebuildIndex(table);
}

void YYlVal::CreateIndex(YYlVal table_name,YYlVal col_name)
{
	string name = table_name;
	string column_name = col_name;
	string file_name = name + "." + column_name + ".index";
	FILE* file = fopen(file_name.c_str(),"r" );
	if(file != NULL)
	{
		cerr <<"Index Has Already Exist!" <<endl;
		fclose(file);
		return ;
	}
	SimpleIndexFile simple_file(name,column_name);
	simple_file.BuildIndexFile();

}

void YYlVal::MakeInsert(YYlVal name,YYlVal value)
{
	string table_name = name;
	vector<string> values = value.GetValue();
	MetaFile meta_file(table_name);
	if(!meta_file.TableExist() )
	{
		cerr << "Table Not Exist !" <<endl;
		return ;
	}
	DataTable table;
	table.SetName(table_name);
	vector<DataColumn> cols = meta_file.GetColumnsInfo();
	table.SetColumns( cols );
	DataFile df;
	DataRow new_row;
	for(int i = 0;i<cols.size();i++)
	{
		DataColumn dc = cols[i];
		string data_str = values[i];
		if(dc.GetColType() == DataColumn::COLUMN_TYPE_INTEGER)
		{
			int intval;
			std::stringstream ss(data_str);
			ss>>intval;
			Data data(intval);
			new_row.AddData(data);
		}
		else if(dc.GetColType() == DataColumn::COLUMN_TYPE_REAL)
		{
			double dval;
			std::stringstream ss(data_str);
			ss>>dval;
			Data data(dval);
			new_row.AddData(data);
		}
		else //String
		{
			string new_str = data_str;
			if(data_str[0] == '\'')
			{
				new_str = data_str.substr(1,data_str.size() - 2);
			}
			Data data(new_str);
			new_row.AddData(data);				
		}

	}

	//Check Pk 
	int pk_index = 0;
	MetaFile mf(table_name);
	vector<int> pk_indexs = mf.GetPkIndexs();
	if(pk_indexs.size() > 0)
	{
		pk_index = pk_indexs[0];
		std::stringstream ss;
		string pk_column_name = table.GetColumn(pk_index).GetName().GetFirstName();
		ss<< "select * from " << table.GetName() << " where " << pk_column_name << "=" << new_row[pk_index ].GetInt() <<";";
		yy_scan_string( ss.str().c_str() );
		yyparse();


		//Result
		if(g_table_result.GetRows().size() > 0)
		{
			cerr<<" Pk encludtion! detected! "<<endl;
			Simple_Log::Undo();
			return;
		}
	}
	//Check Fk
	
	for(int i = 0;i<cols.size();i++)
	{
		DataColumn col = cols[i];
		if(col.HasFk() )
		{
			string ref_tbl_name = col.GetFkTableName();
			string ref_col_name = col.GetFkColName();

			
			std::stringstream ss;
			
			ss<< "select * from " << ref_tbl_name << " where " << ref_col_name << "=" << new_row[i].GetInt() <<";";
			yy_scan_string( ss.str().c_str() );
			yyparse();


			//Result
			if(g_table_result.GetRows().size() ==0)
			{
				cerr<<"Fk volatation! detected! "<<endl;
				Simple_Log::Undo();
				
				return;
			}
		}
	}

	Simple_Log::AddLogEntry(Simple_Log_Entry::LOG_ADD_ENTRY,table_name,cols[0].GetName().GetFirstName(),new_row[0].GetInt() );

	df.AddDataRow(table,new_row);
	Simple_Log::FlushLog();

	SimpleIndex::RebuildIndex(table);

};


