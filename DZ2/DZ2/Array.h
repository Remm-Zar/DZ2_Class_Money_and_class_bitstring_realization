#pragma once
#include <iostream>
#include <cstring>
#include <initializer_list>
using namespace std;
class Money;
class Array
{
protected:
	const static short s_max_len=64;//REDONE
	unsigned char m_arr[s_max_len] = { 0 };
	short m_len=0;
public:	
	Array(){}
	Array(short len)
	{
		if ((len > s_max_len) || (len < 0))
		{
			throw exception("Size error. Object's destoyed");
		}
		m_len = len;
	}
	Array(short len, unsigned char* arr) :Array(len)
	{
		for (int i = 0; i < len; ++i)
		{
			m_arr[i] = arr[i];
		}
	}
	Array(const initializer_list<unsigned char>& list):Array(static_cast<short>(list.size()))
	{
		int i = 0;
		for (auto& elem : list)
		{
			m_arr[i] = elem;
			++i;
		}
	}
	virtual ~Array()
	{}
	short Len()const
	{
		return m_len;
	}
	unsigned char& operator[](int i)
	{
		if ((i < 0) || (i > m_len - 1))
		{
			throw exception("Index error");
		}
		return m_arr[i];
	}
	unsigned char operator[](int i)const
	{
		if ((i < 0) || (i > m_len - 1))
		{
			throw exception("Index error");
		}
		return m_arr[i];
	}
	virtual Array& By_elem_plus(const Array& a,const Array&b)
	{
		if ((m_len != a.m_len)||(m_len!=b.m_len))
		{
			throw exception("Range error");
		}
		for (int i = 0; i < m_len; ++i)
		{
			m_arr[i] +=(static_cast<int>(a.m_arr[i])+b.m_arr[i])%256;
		}
		return *this;
	}
    friend ostream& operator<<(ostream& out,Array &a)
	{
		for (int i = 0; i < a.m_len; ++i)
		{
			out << a.m_arr[i];
		}
		return out;
	}
	virtual void print()const
	{
		cout << "\nIt's Array object: ";
		for (int i = 0; i < m_len; ++i)
		{
			cout << static_cast<int>(m_arr[i]);
			if (i != m_len - 1)
			{
				cout << ",";
			}
		}
	}
};

