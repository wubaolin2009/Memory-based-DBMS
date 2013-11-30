#include<stdio.h>
#include "lex_defines.h"
#include "excutor.h"
#include "algebra.h"
#include "storage.h"
#include<iostream>
#include <vector>
#include <deque>
using namespace std;
//YYlVal yylval;
extern FILE* yyin;
#include "index.h"
#include "simple_log.h"
#include "common.h"
//#define TABLE_NAME "tabletestt"

//#include "lex.yy.cpp"


DataTable g_table_result;


int main()
{
	/*

	DataColumn c1;
	c1.SetAppendVal(0);
	c1.SetCanNull(0);
	c1.SetColType(DataColumn::COLUMN_TYPE_INTEGER);
	c1.SetTableName(TABLE_NAME);
	NameEntry entry1("intval","");
	c1.SetName(entry1);

	DataColumn c2;
	c2.SetAppendVal(8);
	c2.SetCanNull(0);
	c2.SetColType(DataColumn::COLUMN_TYPE_CHAR);
	c2.SetTableName(TABLE_NAME);
	NameEntry entry2("cval","");
	c2.SetName(entry2);

	DataColumn c3;
	c3.SetAppendVal(10);
	c3.SetCanNull(0);
	c3.SetColType(DataColumn::COLUMN_TYPE_VARCHAR);
	c3.SetTableName(TABLE_NAME);
	NameEntry entry3("vcval","");
	c3.SetName(entry3);

	DataColumn c4;
	c4.SetAppendVal(0);
	c4.SetCanNull(0);
	c4.SetColType(DataColumn::COLUMN_TYPE_REAL);
	c4.SetTableName(TABLE_NAME);
	NameEntry entry4("rval","");
	c4.SetName(entry4);

	vector<DataColumn> cols;
	cols.push_back(c1);
	cols.push_back(c2);
	cols.push_back(c3);
	cols.push_back(c4);


	MetaFile file(TABLE_NAME);
	file.WriteColumnInfo(cols);
	//vector<DataColumn> col = file.GetColumnsInfo();
	DataTable dt;
	dt.SetName(TABLE_NAME);
	dt.AddColumn(cols);

	DataRow r1;
	Data d1(1);
	Data d2("cstr1");
	Data d3("vcstr1");
	Data d4(1.11);
	r1.AddData(d1);
	r1.AddData(d2);
	r1.AddData(d3);
	r1.AddData(d4);

	DataRow r2;
	Data d5(2);
	Data d6("cstr2");
	Data d7("vcstr2");
	Data d8(2.22);
	r2.AddData(d5);
	r2.AddData(d6);
	r2.AddData(d7);
	r2.AddData(d8);

	DataRow r3;
	Data da(3);
	Data db("cstr3");
	Data dc("vcstr3");
	Data dd(3.33);
	r3.AddData(da);
	r3.AddData(db);
	r3.AddData(dc);
	r3.AddData(dd);

	DataFile df;
	df.CreateNewTable(TABLE_NAME);
	df.AddDataRow(dt,r1);
	df.AddDataRow(dt,r2);
	df.AddDataRow(dt,r3);

	
	DataTable dtm ;
	dtm.SetName(TABLE_NAME);

	MetaFile mfm(TABLE_NAME);
	dtm.SetColumns(mfm.GetColumnsInfo() );
	DataFile dfm;
	//dfm.FillDataTable(dtm);
	
	dfm.DelRow(dtm,r1);
	dfm.DelRow(dtm,r3);
	dfm.DelRow(dtm,r2);

	DataTable dfm2;
	dfm2.SetName(TABLE_NAME);
	dfm.FillDataTable(dfm2);*/

	
	
	//yy_scan_string("select * from table");
	cout<<"My Simple DB version 0.10" << endl;
	cout<<"=======================================================" <<endl;
	cout<<"Your can input help for commands" <<endl;
	cout<<"=>";

Simple_Log::Init();
	while(1)
	{
		yyparse();
		yyrestart(stdin);
		cout<<"=>";
	}
		//yyin = stdin;
	
	g_table_result;
	/*SimpleIndex index;
	SimpleIndexFile sif("table1","intval");
	sif.FillInSimpleIndex(index);*/
	return 0;
}

