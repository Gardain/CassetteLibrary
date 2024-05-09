#include "cÑassette.h"

Ñassette::Ñassette(string nam, sAuthor auth, int price)
{
	name = nam;
	author = auth;
	RentMoneyDay = price;
}

string Ñassette::GetName()
{
	return name;
}

Ñassette::sAuthor Ñassette::GetAuthor()
{
	return author;
}

int Ñassette::GetInfoTaking()
{
	return taked;
}

void Ñassette::PutDate(DateReceiv dRc, DateReturn dRt, int allPrice)
{
	dateRec = dRc;
	dateRet = dRt;
	RentMoneyAll = allPrice;
	taked++;
}

void Ñassette::RemoveDate()
{
	DateReceiv d1;
	DateReturn d2;
	d1.day = 0;
	d1.month = 0;
	d1.year = 0;
	d2.day = 0;
	d2.month = 0;
	d2.year = 0;

	dateRec = d1;
	dateRet = d2;
}

Ñassette::DateReceiv Ñassette::GetDateReceiv()
{
	return dateRec;
}

Ñassette::DateReturn Ñassette::GetDateReturn()
{
	return dateRet;
}

int Ñassette::GetPriceDay()
{
	return RentMoneyDay;
}

int Ñassette::GetPriceRent()
{
	return RentMoneyAll;
}

void Ñassette::RemovePriceRent()
{
	RentMoneyAll = 0;
}
