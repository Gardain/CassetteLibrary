#pragma once
#include "imports.h"

class Ñassette
{
public:
	struct sAuthor
	{
		string name;
		string second_name;
	};
	struct DateReceiv
	{
		int day = 0;
		int month = 0;
		int year = 0;
	};
	struct DateReturn
	{
		int day = 0;
		int month = 0;
		int year = 0;
	};
	Ñassette() = default;
	Ñassette(string nam, sAuthor auth, int price);
	string GetName();
	sAuthor GetAuthor();
	int GetInfoTaking();
	
	void PutDate(DateReceiv dRc, DateReturn dRt, int allPrice);
	void RemoveDate();
	DateReceiv GetDateReceiv();
	DateReturn GetDateReturn();

	int GetPriceDay();
	int GetPriceRent();
	void RemovePriceRent();
private:
	string name;
	sAuthor author;
	int taked = 0;
	int RentMoneyDay = 0;
	int RentMoneyAll = 0;
	DateReceiv dateRec;
	DateReturn dateRet;
};