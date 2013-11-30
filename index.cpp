#include "index.h"
#include "storage.h"

void SimpleIndex::RebuildIndex(DataTable& dt)
{
	string table_name = dt.GetName();
	vector<DataColumn> cols = dt.GetColumns();
	for(int i = 0;i<cols.size();i++)
	{
		string column_name = cols[i].GetName().GetFirstName();
		if(IndexExist(table_name,column_name) )
		{
			SimpleIndexFile sif(table_name,column_name);
			sif.BuildIndexFile();
		}
	}

}

