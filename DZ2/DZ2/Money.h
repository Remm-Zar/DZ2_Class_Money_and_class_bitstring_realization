#pragma once
#include "Array.h"
#include <iostream>
#include <initializer_list>
using namespace std;
class Money :public Array
{
	long m_main = 0;//Rubles
	unsigned char m_k = 0;//kopeyki
public:
	Money() {};
	Money(long R, int k)
	{
		m_main = R;
		m_k = (unsigned char)k;
	}
	/*Money(const initializer_list<unsigned char>& list) :Array(list)
	{}
	Money(long R, int k,short len):Array(len)
	{
		m_main = R;
		m_k = (unsigned char)k;
	}*/
	~Money()override
	{}
	ostream& operator<<(ostream& out)
	{
		out << m_main << "," << (int)m_k;
		return out;
	}
	void print()const override
	{
		cout << "\nIt's Money object: "<<m_main << "," << (int)m_k;
	}
	bool SetSum(long R, int K)
	{
		if ((K < 0) || (R < 0))
		{
			return 1;
		}
		else
		{
			m_k = K % 100;
			m_main = R + K / 100;
		}
		return 0;
	}
	long GetRubles()const
	{
		return m_main;
	}
	unsigned char GetKopeyki()const
	{
		return m_k;
	}
	Money operator+(const Money& n)
	{
		unsigned char K = m_k + n.m_k;
		long R = m_main + n.m_main + K / 100;
		K = K % 100;
		return Money(R, K);
	}
	Money& By_elem_plus(const Array& a, const Array& b)override
	{
		m_k += dynamic_cast<Money&>(const_cast<Array&>(a)).m_k + dynamic_cast<Money&>(const_cast<Array&>(b)).m_k;
		m_main += dynamic_cast<Money&>(const_cast<Array&>(a)).m_main + dynamic_cast<Money&>(const_cast<Array&>(a)).m_main + m_k / 100;
		m_k = m_k % 100;
		return *this;
	}
	friend Money operator-(const Money& m, const Money& n)
	{
		int total = (m.m_main * 100 + m.m_k) - (n.m_main * 100 + n.m_k);
		long R = total / 100;
		unsigned char K = total % 100;
		return Money(R, K);
	}
	friend Money operator/(const Money& m, const Money& n)
	{
		double total = ((double)m.m_main * 100 + m.m_k) / ((double)n.m_main * 100 + n.m_k);
		long R = int(total);
		unsigned char K = (int)(total * 100.0) % 100;
		return Money(R, K);
	}
	Money operator/(double n)
	{
		double total = ((double)m_main * 100 + m_k) / (n * 100);
		long R = int(total);
		unsigned char K = (int)(total * 100.0) % 100;
		return Money(R, K);
	}
	bool operator==(const Money& m)
	{
		return (m_main * 100 + m_k == m.m_main * 100 + m.m_k);
	}
	bool operator!=(const Money& m)
	{
		return !(*this==m);
	}
	bool operator>(const Money& m)
	{
		return (m_main * 100 + m_k > m.m_main * 100 + m.m_k);
	}
	bool operator<(const Money& m)
	{
		return !((*this>m) || (*this==m));
	}
	bool operator>=(const Money& m)
	{
		return !(*this < m);
	}
	bool operator<=(const Money& m)
	{
		return !(*this>m);
	}	
	operator double()
	{
		return (double(m_main) * 100.0 + double(m_k)) / 100.0;
	}
	bool operator==(double n)
	{
		if (abs(double(*this) - n) < 0.00000001)
		{
			return true;
		}
		return false;
	}
	bool operator==(int n)
	{
		return (double(*this) == n);
	}
	friend class Account;
};
Money operator*(const Money& m, double n);
Money operator*(double n, const Money& m);