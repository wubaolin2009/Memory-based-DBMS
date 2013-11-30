#include"algebra.h"
#include"excutor.h"



bool SelectOperator::IsConditionMatch(DataTable& table,DataRow& row,SimpleExpr expr)
{	
	return SimpleExprCompute::Compute(row,expr,table);
	//return true;
}

