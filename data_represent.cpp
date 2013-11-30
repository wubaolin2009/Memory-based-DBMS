#include "data_represent.h"
 
bool Data::operator==(const Data& data) const
{
	if(m_type == INT)
	{

		return data.m_ival == m_ival;
	}
	if(m_type == REAL)
	{
		return data.m_dval == m_dval;

	}
	//Str
	return  data.m_strval == m_strval;
}
bool Data::operator!=(const Data& data) const
{
	return !( (*this) == data);
}
bool Data::operator<(const Data& data) const
{
	if(m_type == INT)
	{

		return data.m_ival  > m_ival;
	}
	if(m_type == REAL)
	{
		return data.m_dval > m_dval;

	}
	//Str
	return  data.m_strval > m_strval;
}
bool Data::operator>(const Data& data) const
{
	if(m_type == INT)
	{

		return data.m_ival < m_ival;
	}
	if(m_type == REAL)
	{
		return data.m_dval < m_dval;

	}
	//Str
	return  data.m_strval < m_strval;
}

bool Data::operator<=(const Data& data) const
{
	return  ( (*this) < data ) || ( (*this) == data );
}
bool  Data::operator>=(const Data& data) const
{

	return  ( (*this) >data )|| ( (*this) == data );
}
bool Data::operator()(const Data& data1,const Data& data2) const
{
	return data1 < data2;
}


