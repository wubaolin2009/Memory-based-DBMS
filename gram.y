%{
#include<stdio.h>
#include<string.h>
#include<vector>
using std::vector;
#include"lex_defines.h"



int yyerror(char *msg);
int yylex();

extern DataTable g_table_result;

%}

%token SELECT FROM ID SEPARATER STMT_END AS PERIOD LT  ST EQ INTEGER REALNUM WHERE AND OR DISTINCT ASC DESC SORT BY 
%token CREATE TABLE LGB RGB LSB RSB PK NOT COLUMN_NULL TYPE_FLOAT TYPE_INTEGER TYPE_VARCHAR TYPE_CHAR
%token INSERT INTO VALUES SET DELETE UPDATE INDEX ON
%token FK REF BEGIN_TR END_TR TRANSACTION CMD_HELP

%% /* Grammar rules and actions follow */
command: declaration {return 0;}
	| transaction_begin
	| transaction_end
	| help_cmd
	;
help_cmd: CMD_HELP { $$.MakeHelp(); return 9;}
transaction_begin: BEGIN_TR TRANSACTION ID {Simple_Log::StartTransaction( (string)$3 ); return 0;}
	;
transaction_end : END_TR TRANSACTION {Simple_Log::EndTransaction();return 0;}
	;
 
declaration: SELECT DISTINCT attr_list FROM from_list where_clause sort_clause STMT_END{g_table_result = $$.MakeSelectNode($3,$5,$6,$7,1);return 0;}
	|SELECT attr_list FROM from_list where_clause sort_clause STMT_END{g_table_result = $$.MakeSelectNode($2,$4,$5,$6,0);return 0;}
	|create_clause
	|insert_clause
	|delete_clause
	|update_clause
	|create_index_clause
	;
from_list:  from_list SEPARATER from_val {
											$$.AppendNameEntry($1,$3);
										  }
	|  from_val {
					$$= (vector<NameEntry>*)$1;
					
				}
	;
from_val: ID {  NameEntry tmp_entry($1,"");
				$$=&tmp_entry;}
	| ID AS ID{ NameEntry tmp_entry($1,$3); 
				$$=&tmp_entry;}
	| ID ID { NameEntry tmp_entry($1,$2); 
				$$=&tmp_entry;}			 
	;
attr_list:  attr_list SEPARATER attr_name {
											$$.AppendAttrEntry($1,$3.GetAttr());
										  }
	|  attr_name {
					Attribute attr = $$.GetAttr();
					vector<Attribute> new_attrs;
					new_attrs.push_back(attr);
					$$ = &new_attrs;
				 }
					
	;
attr_name: ID PERIOD ID { NameEntry tmp_entry($1,$3); Attribute new_attr(tmp_entry,""); 
						  $$.SetAttr(new_attr);}
	| ID {  NameEntry tmp_entry("",$1); Attribute new_attr(tmp_entry,"");
				$$.SetAttr(new_attr);}
	| ID AS ID{ NameEntry tmp_entry("",$1); Attribute new_attr(tmp_entry,$3); 
				$$.SetAttr(new_attr);}
	| attr_name AS ID{ NameEntry tmp_entry = $1.GetAttr().GetName(); Attribute new_attr(tmp_entry,$3); 
				$$.SetAttr(new_attr);}
	| attr_name ID{ NameEntry tmp_entry = $1.GetAttr().GetName(); Attribute new_attr(tmp_entry,$2); 
				$$.SetAttr(new_attr);}
	| ID ID { NameEntry tmp_entry("",$1); Attribute new_attr(tmp_entry,$2); 
				$$.SetAttr(new_attr);}	
	
	;

where_clause: /*empty*/ {$$.SetAvailable(false);}
	| WHERE condition {$$=$2;}
	;

attr_name_in_where: ID { NameEntry new_entry("",$1); $$.SetSimpleExprOperand1(new_entry);}
	| ID PERIOD ID {NameEntry new_entry($1,$3); $$.SetSimpleExprOperand1(new_entry);}
	;
operator_in_where: LT {$$.SetSimpleOperator(SimpleExpr::LargeThan);}
	| EQ {$$.SetSimpleOperator(SimpleExpr::Equal);}
	| ST {$$.SetSimpleOperator(SimpleExpr::SmallThan);}
	;
operand2_in_where: INTEGER { SimpleExpr::SecondOperand operand2; 
							 operand2.iVal = $1; operand2.oper_type = SimpleExpr::IntValue;
							 $$.SetSimpleExprOperand2(operand2);}			 
	| REALNUM  { SimpleExpr::SecondOperand operand2; 
				 operand2.dVal = $1; operand2.oper_type = SimpleExpr::RealValue;
				 $$.SetSimpleExprOperand2(operand2);}
	| attr_name_in_where { SimpleExpr::SecondOperand operand2; 
						   operand2.name_entry = $1.GetSimpleExprOperand1(); 
						   if( operand2.name_entry.GetSecondName()[0] == 39)
						  	{	operand2.oper_type == SimpleExpr::StrValue;operand2.strVal= operand2.name_entry.GetSecondName(); }
						   else
								operand2.oper_type = SimpleExpr::AttrName;
								
						   $$.SetSimpleExprOperand2(operand2);
						   }			

	;	
condition: attr_name_in_where operator_in_where operand2_in_where { SimpleExpr new_expr($1.GetSimpleExprOperand1(),$3.GetSimpleExprOperand2(),$2.GetSimpleOperator());
																    Conditions new_cond( new_expr); $$=new_cond;}

		
	| condition AND condition { Conditions cond2 = $3; Conditions::ConditionOperator oper = Conditions::conditionAND;
								Conditions cond1 = $1; cond1.AppendCondition(oper,&cond2); $$ = cond1;}
								
	| condition OR  condition { Conditions cond2 = $3; Conditions::ConditionOperator oper = Conditions::conditionOR;
								Conditions cond1 = $1; cond1.AppendCondition(oper,&cond2); $$ = cond1;}
	;
sort_clause: {$$.SetAvailable(false);}
	| SORT BY attr_list sort_order { $$=$3; $$=(int)$4;}
	;
sort_order: {$$=1;}
	| ASC {$$=1;}
	| DESC {$$=2;}
	;
create_clause: CREATE TABLE ID LGB column_info_list RGB STMT_END { $$.MakeCreateTable($3,$5);  return 1;}
	;
column_info_list: column_info_list SEPARATER column_info {$$.AppendColumnInfo($1.GetColumnInfo(),$3.GetColumnInfo() );}
	| column_info {$$.AppendColumnInfo($1.GetColumnInfo() ); }
	;
column_info: ID /*column name*/ column_type column_null_info pk_info fk_info { ColumnInfo info; info.name=(string)$1; string type = (string)$2;
																		if(type == "int")
																		{
																			info.type = DataColumn::COLUMN_TYPE_INTEGER;
																		}
																		if(type == "float")
																		{
																			info.type = DataColumn::COLUMN_TYPE_REAL;
																		}
																		if(type == "varchar")
																		{
																			info.type = DataColumn::COLUMN_TYPE_VARCHAR;
																			info.append_val = $2;
																		}
																		if(type == "char")
																		{
																			info.type = DataColumn::COLUMN_TYPE_CHAR;
																			info.append_val = $2;
																		}
																		info.b_null = (int)$3 == 1;
																		info.b_pk = (int)$4 == 1;
																		info.b_fk = (int)$5 == 1;
																		if(info.b_fk)
																		{
																			
																			info.fk_table_name = $5.m_fk_info.ref_table_name;
																			info.fk_col_name = $5.m_fk_info.ref_col_name;
																		
																		}
																		vector<ColumnInfo> infos; infos.push_back(info);
																		$$.AppendColumnInfo(infos);
																	  }
																		
	;
column_type:TYPE_INTEGER {$$="int";}
	| TYPE_FLOAT {$$="float";}
	| TYPE_VARCHAR LSB INTEGER RSB {$$="varchar"; $$=(int)$3;}
	| TYPE_CHAR LSB INTEGER RSB {$$="char"; $$=(int)$3;}
	;
column_null_info: {$$=0;}
	| NOT COLUMN_NULL {$$=0;}
	| COLUMN_NULL {$$=1;}
	;
fk_info: {$$=0;}
	| FK REF ID ID { $$=1; Fk_Info info; info.ref_table_name=(string)$3; info.ref_col_name=(string)$4; $$.m_fk_info=info; }
	;
pk_info: {$$ = 0;}
	| PK {$$ = 1;}
	;
insert_clause: INSERT INTO ID VALUES LSB id_list RSB STMT_END { $$.MakeInsert($3,$6); return 2;}
	;
id_list: id_list SEPARATER data_value {$$.AppendValue($1.GetValue(),$3.GetValue() ); }
	| data_value {$$.SetValue($1.GetValue() ); }
	;
data_value: INTEGER {$$.AppendValue((int)$1 ); }
	| REALNUM {$$.AppendValue( (double)$1) ;}
	| ID {$$.AppendValue( (string)$1 ); }
	;
update_clause: UPDATE ID SET update_column_value where_clause STMT_END {$$.MakeUpdate($2,$4,$5); return 3; }
	;
update_column_value: attr_name_in_where operator_in_where operand2_in_where { SimpleExpr new_expr($1.GetSimpleExprOperand1(),$3.GetSimpleExprOperand2(),$2.GetSimpleOperator());
																    Conditions new_cond( new_expr); $$=new_cond;}
	;
	
delete_clause: DELETE FROM ID where_clause STMT_END {$$.MakeDelete($3,$4);  return 4;}
	;
create_index_clause: CREATE INDEX ON ID ID STMT_END { $$.CreateIndex($4,$5); return 5; }
	;
	                                                                               
%%   

int yyerror(char *msg)
{
printf("Error encountered: %s \n", msg);
return 0;

}