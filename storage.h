#ifndef _STORAGE_H
#define _STORAGE_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cerr;
using std::endl;
#include <stdio.h>
#include "data_represent.h"
#include "index.h"


#define MAX_COLUMN_NAME 1024
class FileReader //Before use ,must set offset of FILE pointer
{
public:
	static string GetString(FILE* file)
	{
		char buffer[MAX_COLUMN_NAME];
		fread(buffer,4,1,file);
		int length = * ( (int*)buffer);
		char str_column_name[1024];
		fread(str_column_name,1,length,file);
		str_column_name[length] = '\0';
		string column_name(str_column_name);
		return column_name;

	}
	static int GetInt(FILE* file)
	{
		char buffer[sizeof(int) ];
		fread(buffer,sizeof(int),1,file);
		/*
		char buffer_int[sizeof(int)];
		for(int i = 0;i<sizeof(int);i++)
		{
		buffer_int[i] = buffer[sizeof(int)-1-i];
		}*/
		int ret_val = * ((int*)buffer);
		return ret_val;

	}
	static double GetRealNum(FILE* file)
	{
		char buffer[sizeof(double) ];
		fread(buffer,sizeof(double),1,file);
		double ret_val = * ((double*)buffer);
		return ret_val;

	}
	static void GetByte(FILE* file,int size,/*out*/char* buffer)
	{
		fread(buffer,1,size,file);
	}
	static vector<int> GetIntVector(FILE* file)
	{
		vector<int> rets;
		int size = GetInt(file);
		for(int i = 0;i<size;i++)
		{
			rets.push_back( GetInt(file) );
		}
		return rets;
	}
};

class FileWrite //Before use ,must set offset of FILE pointer
{
public:
	static void WriteString(FILE* file,string& str_to_write)
	{
		int str_leng = str_to_write.size();
		WriteInt(file,str_leng);
		fwrite(str_to_write.c_str(),sizeof(char),str_leng,file);		

	}
	static void WriteInt(FILE* file,int ival_to_write)
	{
		//char buffer[sizeof(int)];
		char * buffer = (char*)&ival_to_write;
		size_t t = fwrite(buffer,4,1,file);
	}
	static void WriteByte(FILE* file,char* buffer,int size)
	{
		fwrite(buffer,size,1,file);

	}

	static void WriteRealNum(FILE* file,double dval_to_write)
	{
		fwrite((char*)&dval_to_write,sizeof(double),1,file);

	}
	static void WriteIntVector(FILE* file,vector<int> vector_to_write)
	{
		int size = vector_to_write.size();
		WriteInt(file,size);
		for(int i = 0;i<size;i++)
		{
			WriteInt(file,vector_to_write[i]);
		}
	}
};



class MetaFile
{
public: 
	bool TableExist()
	{
		std::string file_name = m_table_name + ".meta";
		FILE* file;
		if( (file = fopen(file_name.c_str(),"r") ) != NULL)
		{
			fclose(file);
			return true;
		}
		return false;
	}
	MetaFile(std::string table_name)
	{
		m_table_name = table_name;

	}
	vector<DataColumn> GetColumnsInfo()
	{
		string file_name = m_table_name + ".meta";
		m_meta_file = fopen(file_name.c_str(),"rb");
		vector<DataColumn> column_infos;
		int offset = GetOffsetOfFirstCol(); //Initial Offset
		DataColumn column_info;
		column_info.SetTableName(m_table_name);
		while(GetColumn(column_info,offset))
		{
			column_infos.push_back(column_info);
		}
		column_infos.push_back(column_info);
		fclose(m_meta_file);
		GetColumFkInfo(column_infos);

		return column_infos;

	}
	vector<int> GetPkIndexs()
	{
		string file_name = m_table_name + ".pk";
		FILE* file = fopen(file_name.c_str(),"rb");

		int pk_count = FileReader::GetInt(file);

		vector<int> rets;
		for(int i = 0;i<pk_count;i++)
		{
			rets.push_back( FileReader::GetInt(file) );
		}
		fclose(file);
		return rets;

	}
	void SetPkIndexs(vector<int>& pks)
	{
		string file_name = m_table_name + ".pk";
		FILE* file = fopen(file_name.c_str(),"wb+");
		int count = pks.size();
		FileWrite::WriteInt(file,count);
		for(int i = 0;i<count;i++)
		{
			FileWrite::WriteInt(file,pks[i]);			
		}
		fclose(file);
	}


	void WriteColumnInfo(vector<DataColumn>& column_infos)
	{
		string file_name = m_table_name + ".meta";
		m_meta_file = fopen(file_name.c_str(),"wb+");
		//point to the start
		fseek(m_meta_file,0,SEEK_SET);

		//Write Table Name
		FileWrite::WriteString(m_meta_file,m_table_name);
		//Write All Column
		for(int i = 0;i<column_infos.size();i++)
		{
			DataColumn column = column_infos[i];
			//Next Offset
			int offset_now = ftell(m_meta_file);
			FileWrite::WriteInt(m_meta_file,0); 

			//Can be Null
			bool can_be_null = column.GetCanNull();
			char char_be_null = can_be_null?1:0;
			FileWrite::WriteByte(m_meta_file,&char_be_null,sizeof(char));

			//Type
			int type = (int)column.GetColType();
			FileWrite::WriteInt(m_meta_file,type);

			//String
			string column_name = column.GetName().GetFirstName();
			FileWrite::WriteString(m_meta_file,column_name);

			//Append
			int append = column.GetAppendVal();
			FileWrite::WriteInt(m_meta_file,append);
			//Get CurrentOffset
			int last_offset = ftell(m_meta_file);

			if(i<column_infos.size() -1 )  //Not THe Last Column
			{
				fseek(m_meta_file,offset_now,SEEK_SET);
				FileWrite::WriteInt(m_meta_file,last_offset);
				fseek(m_meta_file,last_offset,SEEK_SET);
			}

		}
		fclose(m_meta_file);

		//Fk Info
		string fk_file_name = m_table_name + ".fk";
		FILE* file = fopen(fk_file_name.c_str(),"wb+");
		FileWrite::WriteInt(file,0);
		int count = 0;
		for(int i = 0;i<column_infos.size();i++)
		{
			
			DataColumn col = column_infos[i];
			
			if(col.HasFk() )
			{
				string table_name = col.GetFkTableName();
				string col_name = col.GetFkColName();
				int col_index = i;
				FileWrite::WriteInt(file,col_index);
				FileWrite::WriteString(file,table_name);
				FileWrite::WriteString(file,col_name);
				count++;
			}

		}
		if(count>0)
		{
			fseek(file,0,SEEK_SET);
			FileWrite::WriteInt(file,count);
		}
		fclose(file);

	}
private:
	bool GetColumn(/*out*/ DataColumn& column_info,/*in,out*/ int& offset)
	{
		//int size_of_col = 0;

		//point to the start of the column
		fseek(m_meta_file,offset,SEEK_SET);
		//Get Next Offset

		int next_offset = FileReader::GetInt(m_meta_file);	
		//size_of_col += sizeof(int);


		//Get Can be Null
		char buffer_bool;
		FileReader::GetByte(m_meta_file,1,&buffer_bool);

		bool can_null = buffer_bool?true:false;
		//size_of_col += sizeof(char);


		//GetType
		int type = FileReader::GetInt(m_meta_file);
		//size_of_col += sizeof(int);

		//GetColumnName
		string column_name = FileReader::GetString(m_meta_file);
		//size_of_col += (sizeof(int) + column_name.size() );


		//Get Append Value
		int append_val = FileReader::GetInt(m_meta_file);
		//size_of_col += sizeof(int);

		//Build Column Info
		//Name 
		NameEntry new_entry(column_name,"");
		column_info.SetName(new_entry);

		//can null
		column_info.SetCanNull(can_null);

		//type
		column_info.SetColType((DataColumn::DataColumnType)type);

		//append val
		column_info.SetAppendVal(append_val);		

		offset = next_offset;
		return next_offset != 0;
	}
	int GetOffsetOfFirstCol()
	{
		//ReadTableName
		fseek(m_meta_file,0,SEEK_SET);
		string table_name = FileReader::GetString(m_meta_file);
		return sizeof(int) + table_name.size();
	}
	void GetColumFkInfo(vector<DataColumn>& cols)
	{
		string fk_file_name = m_table_name + ".fk";
		FILE* file = fopen(fk_file_name.c_str(),"r");
		if(file == NULL)
			return;
		int count = FileReader::GetInt(file);
		for(int i = 0;i<count;i++)
		{
			int index = FileReader::GetInt(file);
			string tbl_name = FileReader::GetString(file);
			string col_name = FileReader::GetString(file);
			cols[index].SetFkTableName(tbl_name);
			cols[index].SetFkColName(col_name);
		}
		fclose(file);

	}
	std::string m_table_name;
	FILE * m_meta_file;

};

class DataFile
{
public:
	/* dt's name must be set */
	void FillDataTable(DataTable& dt)
	{
		dt.GetRows().clear();
		string table_name = dt.GetName();
		string file_name = table_name + ".data";
		if(dt.GetColumns().size() == 0)
		{
			MetaFile meta_table(dt.GetName());
			dt.AddColumn( meta_table.GetColumnsInfo() );
		}
		FILE* file = fopen(file_name.c_str(),"rb");
		fseek(file,sizeof(int),SEEK_SET);
		//Get Data's Offset
		int offset_data = FileReader::GetInt(file);


		vector<DataColumn> columns = dt.GetColumns();

		while(offset_data != -1)
		{
			int row_offset = offset_data ;
			fseek(file,offset_data ,SEEK_SET);
			//Skip available
			int available = FileReader::GetInt(file);
			//Next offset
			offset_data = FileReader::GetInt(file);

			DataRow new_row;

			for(int i = 0 ;i<columns.size();i++)
			{
				//Index's Index
				int offset = sizeof(int) + sizeof(int) + sizeof(int) *i + row_offset ;
				fseek(file,offset,SEEK_SET);
				int data_offset = FileReader::GetInt(file) ;
				fseek(file,data_offset,SEEK_SET);

				DataColumn::DataColumnType type = columns[i].GetColType();
				if(type == DataColumn::COLUMN_TYPE_CHAR)
				{
					string str = FileReader::GetString(file);
					Data data_add(str);
					new_row.AddData(data_add);
				}
				else if (type == DataColumn::COLUMN_TYPE_INTEGER)
				{
					int ival = FileReader::GetInt(file);
					Data data_add(ival);
					new_row.AddData(data_add);

				}
				else if (type == DataColumn::COLUMN_TYPE_REAL)
				{
					double dval = FileReader::GetRealNum(file);
					Data data_add(dval);
					new_row.AddData(data_add);
				}
				else if (type == DataColumn::COLUMN_TYPE_VARCHAR)
				{
					string str = FileReader::GetString(file);
					Data data_add(str);
					new_row.AddData(data_add);
				}

			}
			if(available)
				dt.AddRow(new_row);
		}
		fclose(file);


	}

	void CreateNewTable(string name)
	{
		string table_name = name + ".data";
		FILE* file = fopen(table_name.c_str(),"wb+");
		FileWrite::WriteInt(file,-1);
		FileWrite::WriteInt(file,-1);
		fclose(file);
	}

	void AddDataRow(DataTable& table,DataRow& new_row)
	{
		//Create New Data Block
		string table_name = table.GetName();
		string file_name = table_name + ".data";
		FILE* file = fopen(file_name.c_str(),"rb+");

		//Get First Empty Block
		int empty_offset = FileReader::GetInt(file);
		if(empty_offset != -1)
		{
			//Test THe Block can contain the newrow;
			//We Skip Here;
		}
		fseek(file,0,SEEK_END);
		int last_offset = ftell(file);

		fseek(file,sizeof(int),SEEK_SET );
		int former_off = FileReader::GetInt(file);

		fseek(file,sizeof(int),SEEK_SET);
		FileWrite::WriteInt(file,last_offset);
		fseek(file,0,SEEK_END);
		//Append The New Data
		FileWrite::WriteInt(file,1); //available
		FileWrite::WriteInt(file,former_off);

		vector<DataColumn> columns = table.GetColumns();
		//Append The Columns's offset
		for(int i = 0;i<new_row.GetCount();i++)
		{
			FileWrite::WriteInt(file,0);
		}

		for(int i = 0;i<new_row.GetCount();i++)
		{
			int cur_offset = ftell(file);
			//Rewrite the column offset
			fseek(file,last_offset + sizeof(int)*2 + i * sizeof(int),SEEK_SET);
			FileWrite::WriteInt(file,cur_offset);
			fseek(file,cur_offset,SEEK_SET);
			Data data = new_row[i];
			DataColumn::DataColumnType type = columns[i].GetColType();
			if(type == DataColumn::COLUMN_TYPE_CHAR)
			{
				string str = data.GetStr();
				int column_len = columns[i].GetAppendVal();
				if(str.size() > column_len )
				{
					str = str.substr(0,column_len);
					FileWrite::WriteString(file,str);
				}
				else
				{
					int left_size = column_len - str.size();
					string str_empty(left_size,' ');
					FileWrite::WriteString(file,str);
					FileWrite::WriteByte(file,(char*)str_empty.c_str(),left_size);
				}

			}
			else if (type == DataColumn::COLUMN_TYPE_INTEGER)
			{
				int ival = data.GetInt();
				FileWrite::WriteInt(file,ival);


			}
			else if (type == DataColumn::COLUMN_TYPE_REAL)
			{
				double dval = data.GetRealNum();
				FileWrite::WriteRealNum(file,dval);

			}
			else if (type == DataColumn::COLUMN_TYPE_VARCHAR)
			{
				string str = data.GetStr();
				int column_len = columns[i].GetAppendVal();
				if(str.size() > column_len )
				{
					str = str.substr(0,column_len);
					FileWrite::WriteString(file,str);
				}
				else
				{
					int left_size = str.size();
					string str_empty(left_size,' ');
					FileWrite::WriteString(file,str);
					FileWrite::WriteByte(file,(char*)str_empty.c_str(),left_size);
				}

			}


		}
		fclose(file);
	}

	bool DelRow(DataTable& dt,DataRow row_to_del)
	{
		string table_name = dt.GetName();
		string file_name = table_name + ".data";

		FILE* file = fopen(file_name.c_str(),"rb+");
		fseek(file,sizeof(int),SEEK_SET);
		int t = ftell(file);
		//Get Data's Offset
		int offset_data = FileReader::GetInt(file);

		auto int i;
		vector<DataColumn> columns = dt.GetColumns();

		while(offset_data != -1)
		{
			int row_offset = offset_data;
			fseek(file,offset_data ,SEEK_SET);
			//Skip available
			int available = FileReader::GetInt(file);
			//Next offset
			offset_data = FileReader::GetInt(file);

			DataRow new_row;

			for(int i = 0 ;i<columns.size();i++)
			{
				//Index's Index
				int offset = sizeof(int) + sizeof(int) + sizeof(int) *i + row_offset ;
				fseek(file,offset,SEEK_SET);
				int data_offset = FileReader::GetInt(file) ;
				fseek(file,data_offset,SEEK_SET);

				DataColumn::DataColumnType type = columns[i].GetColType();
				if(type == DataColumn::COLUMN_TYPE_CHAR)
				{
					string str = FileReader::GetString(file);
					Data data_add(str);
					new_row.AddData(data_add);
				}
				else if (type == DataColumn::COLUMN_TYPE_INTEGER)
				{
					int ival = FileReader::GetInt(file);
					Data data_add(ival);
					new_row.AddData(data_add);

				}
				else if (type == DataColumn::COLUMN_TYPE_REAL)
				{
					double dval = FileReader::GetRealNum(file);
					Data data_add(dval);
					new_row.AddData(data_add);
				}
				else if (type == DataColumn::COLUMN_TYPE_VARCHAR)
				{
					string str = FileReader::GetString(file);
					Data data_add(str);
					new_row.AddData(data_add);
				}

			}

			if(available && (new_row == row_to_del) )
			{
				fseek(file,row_offset,SEEK_SET);
				//Set Available
				FileWrite::WriteInt(file,0);
				fclose(file);
				return true;
			}
		}
		fclose(file);
		return false;
	}
};

class SimpleIndexFile
{
public:
	SimpleIndexFile(const string& table_name,const string& column_name)
	{
		m_table_name = table_name;
		m_col_name = column_name;
	}
	//File Style
	// line_count  DataType     line1  .... ................ linen
	//                       Data offset
	void FillInSimpleIndex(SimpleIndex& index_to_fill)
	{
		string file_name = m_table_name + "." + m_col_name + ".index";
		FILE* file = fopen(file_name.c_str(),"r");
		if(file == NULL)
		{
			cerr << "Index Not Exist!" <<endl;
			return ;
		}
		int line_count = FileReader::GetInt(file);
		Data::DataType dt = (Data::DataType)FileReader::GetInt(file);
		index_to_fill.SetType(dt);
		for(int i = 0;i<line_count;i++)
		{

			if(dt == Data::INT)
			{
				int ival = FileReader::GetInt(file);
				Data new_data(ival);
				vector<int> offset = FileReader::GetIntVector(file);
				for(int i = 0;i<offset.size();i++)
				{
					index_to_fill.AddData(new_data,offset[i]);
				}
			}
			else if (dt == Data::REAL)
			{
				double rval = FileReader::GetRealNum(file);
				Data new_data(rval);
				vector<int> offset = FileReader::GetIntVector(file);
				for(int i = 0;i<offset.size();i++)
				{
					index_to_fill.AddData(new_data,offset[i]);
				}

			}
			else  //str
			{
				string str = FileReader::GetString(file);
				Data new_data(str);
				vector<int> offset = FileReader::GetIntVector(file);
				for(int i = 0;i<offset.size();i++)
				{
					index_to_fill.AddData(new_data,offset[i]);
				}
			}
		}
		fclose(file);


	}

	void BuildIndexFile()
	{
		DataTable dt;
		dt.SetName(m_table_name);
		MetaFile meta_file(m_table_name);
		dt.SetColumns(meta_file.GetColumnsInfo() );
		NameEntry col_name_entry(m_table_name,m_col_name);
		int col_index = dt.GetColumnIndex(col_name_entry);		

		string file_name = m_table_name + ".data";

		FILE* file = fopen(file_name.c_str(),"rb+");
		fseek(file,sizeof(int),SEEK_SET);
		int t = ftell(file);
		//Get Data's Offset
		int offset_data = FileReader::GetInt(file);


		vector<DataColumn> columns = dt.GetColumns();

		vector<Data> data_write_to_file;
		vector<int> offset_write_to_file;

		SimpleIndex simple_index;

		while(offset_data != -1)
		{
			int row_offset = offset_data;
			fseek(file,offset_data ,SEEK_SET);
			//Skip available
			int available = FileReader::GetInt(file);
			//Next offset
			offset_data = FileReader::GetInt(file);

			DataRow new_row;

			

			for(int i = 0 ;i<columns.size();i++)
			{
				//Index's Index
				int offset = sizeof(int) + sizeof(int) + sizeof(int) *i + row_offset ;
				fseek(file,offset,SEEK_SET);
				int data_offset = FileReader::GetInt(file) ;
				fseek(file,data_offset,SEEK_SET);

				DataColumn::DataColumnType type = columns[i].GetColType();
				

				if(type == DataColumn::COLUMN_TYPE_CHAR)
				{
					simple_index.SetType(Data::STR);
					string str = FileReader::GetString(file);
					Data data_add(str);
					if(i == col_index && available==1)
					{
						//data_write_to_file.push_back(data_add);
						//offset_write_to_file.push_back(row_offset);
						simple_index.AddData(data_add,row_offset);
					}
					
					//new_row.AddData(data_add);
				}
				else if (type == DataColumn::COLUMN_TYPE_INTEGER)
				{
					simple_index.SetType(Data::INT);
					int ival = FileReader::GetInt(file);
					Data data_add(ival);
					//new_row.AddData(data_add);
					if(i == col_index && available==1)
					{
						//data_write_to_file.push_back(data_add);
						//offset_write_to_file.push_back(row_offset);
						simple_index.AddData(data_add,row_offset);
					}


				}
				else if (type == DataColumn::COLUMN_TYPE_REAL)
				{
					simple_index.SetType(Data::REAL);
					double dval = FileReader::GetRealNum(file);
					Data data_add(dval);
					//new_row.AddData(data_add);
					if(i == col_index && available==1)
					{
						//data_write_to_file.push_back(data_add);
						//offset_write_to_file.push_back(row_offset);
						simple_index.AddData(data_add,row_offset);
					}
				}
				else if (type == DataColumn::COLUMN_TYPE_VARCHAR)
				{
					simple_index.SetType(Data::STR);
					string str = FileReader::GetString(file);
					Data data_add(str);
					//new_row.AddData(data_add);
					if(i == col_index && available==1)
					{
						//data_write_to_file.push_back(data_add);
						//offset_write_to_file.push_back(row_offset);
						simple_index.AddData(data_add,row_offset);
					}
				}

			}		
		}
		fclose(file);
		
		
		WriteIndexToFile(simple_index);

	}
private:
	void WriteIndexToFile(SimpleIndex index)
	{
		map<Data,vector<int> >maps = index.GetAllData();
	
		string file_name = m_table_name + "." + m_col_name + ".index";
		FILE* file = fopen(file_name.c_str(),"wb+");
		int line_count = maps.size();
		map<Data,vector<int> >::iterator ir = maps.begin();
		Data data1 = ir->first;
		int type = (int)(data1.GetType() );
		
		FileWrite::WriteInt(file,line_count);
		FileWrite::WriteInt(file,type);
		for(map<Data,vector<int> >::iterator ir = maps.begin();ir!= maps.end();ir++)
		{
			Data data = ir->first;
			if(type == Data::INT)
			{
				FileWrite::WriteInt(file,data.GetInt() );

			}
			else if (type == Data::REAL)
			{
				FileWrite::WriteRealNum(file,data.GetRealNum() );

			}
			else
			{
				string str = data.GetStr();
				FileWrite::WriteString(file,str );

			}
			vector<int> indexs = ir->second;
			FileWrite::WriteIntVector(file,indexs);
		}
		fclose(file);

	}
public:
	DataRow GetRowByIndex(int offset)
	{
		DataTable dt;
		dt.SetName(m_table_name);
		MetaFile meta_file(m_table_name);
		dt.SetColumns( meta_file.GetColumnsInfo() );
		
		string file_name = m_table_name + ".data";

		FILE* file = fopen(file_name.c_str(),"rb+");
		
		int t = ftell(file);
		//Get Data's Offset
		
		vector<DataColumn> columns = dt.GetColumns();
		int row_offset = offset;
		fseek(file,row_offset ,SEEK_SET);
		//Skip available
		int available = FileReader::GetInt(file);
		//Next offset
		int offset_data = FileReader::GetInt(file);

		DataRow new_row;

		for(int i = 0 ;i<columns.size();i++)
		{
			//Index's Index
			int offset = sizeof(int) + sizeof(int) + sizeof(int) *i + row_offset ;
			fseek(file,offset,SEEK_SET);
			int data_offset = FileReader::GetInt(file) ;
			fseek(file,data_offset,SEEK_SET);

			DataColumn::DataColumnType type = columns[i].GetColType();

			if(type == DataColumn::COLUMN_TYPE_CHAR)
			{
				string str = FileReader::GetString(file);
				Data data_add(str);
				new_row.AddData(data_add);
			}
			else if (type == DataColumn::COLUMN_TYPE_INTEGER)
			{
				int ival = FileReader::GetInt(file);
				Data data_add(ival);
				new_row.AddData(data_add);
				
			}
			else if (type == DataColumn::COLUMN_TYPE_REAL)
			{
				double dval = FileReader::GetRealNum(file);
				Data data_add(dval);
				new_row.AddData(data_add);
				
			}
			else if (type == DataColumn::COLUMN_TYPE_VARCHAR)
			{
				string str = FileReader::GetString(file);
				Data data_add(str);
				new_row.AddData(data_add);
			
			}

		}	
		fclose(file);
		return new_row;

		
	}
	string m_table_name;
	string m_col_name;
};




#endif
