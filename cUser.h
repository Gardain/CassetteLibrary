#pragma once
#include "imports.h"
#include "cÑassette.h"


class User
{
public:
	struct sUs_initials
	{
		string name;
		string second_name;
		string id;
	};
	User() = default;
	User(sUs_initials author);

	sUs_initials retName();
	vector<Ñassette>& retBooks();
	void putBook(Ñassette cc);
private:
	sUs_initials initials;
	vector<Ñassette> booksGoted = vector<Ñassette>();
};

