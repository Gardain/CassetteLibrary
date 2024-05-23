#pragma once
#include "imports.h"
#include "cUser.h"
#include "cÑassette.h"

int countDaysInMonth(int month, int year) {
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29;
        else
            return 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

// Ôóíêöèÿ äëÿ ïîäñ÷åòà ðàçíèöû ìåæäó äâóìÿ äàòàìè
int countDays(Ñassette::DateReceiv dateRec, Ñassette::DateReturn date2) {
    int count = 0;

    // Ïîäñ÷åò äíåé â ãîäàõ
    for (int i = dateRec.year; i < date2.year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
            count += 366;
        else
            count += 365;
    }

    // Ïîäñ÷åò äíåé â ìåñÿöàõ
    for (int i = dateRec.month; i < date2.month; i++)
        count += countDaysInMonth(i, date2.year);

    // Ïîäñ÷åò äíåé
    count += date2.day - dateRec.day;

    return abs(count);
}

std::string generateRandomString(size_t length) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 35);
    const std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::string randomString;
    randomString.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        randomString += allowedChars[distribution(generator)];
    }

    return randomString;
}
std::vector<std::vector<int>> convertDateStringToVector(const std::string& dateString) {
    std::vector<std::vector<int>> dateVector;
    std::stringstream ss(dateString);
    std::string part;
    int i = 0;

    while (getline(ss, part, '.')) {
        std::vector<int> datePart;
        datePart.push_back(std::stoi(part)); // Ïðåîáðàçîâàíèå ñòðîêè â int
        dateVector.push_back(datePart);
        i++;
    }

    return dateVector;
}

void createUser(vector<User>& usrs, User::sUs_initials s)
{
	User newUs(s);

	usrs.push_back(newUs);
}

void createCassettes(vector<Ñassette>& bk, Ñassette c)
{
    Ñassette newUs(c);

    bk.push_back(newUs);
}
bool existCasset(vector<Ñassette>& bk, Ñassette book)
{
    for (int i = 0; i < bk.size(); i++)
    {
        if (bk[i].GetName() == book.GetName())
        {
            if (bk[i].GetDateReceiv().day == 0)
            {
                return true;
            }
            break;
        }
    }

    return false;
}

bool PassCasset(vector<User>& usrs, string idUser, vector<Ñassette>& bk, Ñassette& bok, Ñassette::DateReceiv dateRec, Ñassette::DateReturn dateRet)
{
    for (int i = 0; i < usrs.size(); i++)
    {
        if (usrs[i].retName().id == idUser) // ïîèñê ïîëüçîâàòåëÿ â áàçå
        {
            if (existCasset(bk, bok))  // ïîèñê êíèãè è ïðîâåðêà çàáðàë ëè å¸ êòî-òî(2 â 1)
            {
                for (int j = 0; j < bk.size(); j++)
                {
                    if (bk[j].GetName() == bok.GetName())  // èùåì êíèãó ïî ìàññèâó, îïèðàÿñü íà èìÿ
                    {
                        int allDays = countDays(dateRec, dateRet);
                        int price = allDays = allDays * bk[j].GetPriceDay();
                        bk[j].PutDate(dateRec, dateRet, price);  // óñòàíîâêà äàòû âûäà÷è/âîçâðàòà
                        usrs[i].putBook(bk[j]); // ïîìåùàåì íàéäåíóþ êíèãó ê ïîëüçîâàòåëþ
                        break;
                    }
                }

                return true;
            }
            break;
        }
    }

    return false;
}

void OccupiedCasset(vector<User>& usrs)
{
    for (int i = 0; i < usrs.size(); i++)
    {
        vector<Ñassette> bookGoted = usrs[i].retBooks();
        if (bookGoted.size() > 0)
        {
            cout << "Ïîëüçîâàòåëü: ID- " << usrs[i].retName().id << " Ôàìèëèÿ: " << usrs[i].retName().second_name << endl;
            for (Ñassette t : bookGoted)
            {
                cout  << "Íàçâàíèå: " << t.GetName() << "\nÐåæèñ¸ð: " << t.GetAuthor().name << " " << t.GetAuthor().second_name << "\n";
                cout  << "Öåíà àðåíäû: " << t.GetPriceRent() << "\n";
                cout << "Äàòà âûäà÷è: " << t.GetDateReceiv().day << "." << t.GetDateReceiv().month << "." << t.GetDateReceiv().year <<"\n";
                cout << "Äàòà âîçâðàòà: " << t.GetDateReturn().day << "." << t.GetDateReturn().month << "." << t.GetDateReturn().year << endl << endl;
            }

            cout << endl << endl << endl;
        }
    }
}

void ShowAllCasset(vector<Ñassette>& casset)
{
	cout << "№\t" << "Название\t" << "Режиссёр\t" << "Цена\t" << "Брали (раз)" << endl;
	for (int i = 0; i < casset.size(); i++)
	{
		cout << i + 1 << "\t" << casset[i].GetName() << "\t" << casset[i].GetAuthor().name << " " << casset[i].GetAuthor().second_name  << "\t";
		cout << casset[i].GetPriceDay() << "\t" << casset[i].GetInfoTaking() << endl << endl;
	}
}

bool RemoveCasset(vector<Ñassette>& bk, Ñassette& bok)
{
    for (int i = 0; i < bk.size(); i++)
    {
        if (bk[i].GetName() == bok.GetName())
        {
            bk.erase(bk.begin() + i);
            return true;
        }
    }

    return false;
}

bool RemoveDate(vector<Ñassette>& bk, Ñassette& bok)
{
    for (int i = 0; i < bk.size(); i++)
    {
        if (bk[i].GetName() == bok.GetName())
        {
            bk[i].RemoveDate();
            bk[i].RemovePriceRent();
            return true;
        }
    }

    return false;
}
//bool is_date_valid(const std::string& str) {
//    std::regex pattern("^\\d{2}\\.\\d{2}\\.\\d{2}$");
//    return std::regex_match(str, pattern);
//}

bool is_date_valid(const std::string& str) {
    if (str.size() != 8) {
        return false;
    }

    for (int i = 0; i < str.size(); ++i) {
        if (i == 2 || i == 5) {
            if (str[i] != '.') {
                return false;
            }
        }
        else {
            if (!isdigit(str[i])) {
                return false;
            }
        }
    }

    return true;
}

bool RemoveBookOnUser(vector<User>& usrs, vector<Ñassette>& bk, Ñassette& bok)
{
    if (!existCasset(bk, bok))
    {
        for (int i = 0; i < usrs.size(); i++)
        {
            vector<Ñassette>& books = usrs[i].retBooks();
            for (int c = 0; c < books.size(); c++)
            {
                if (books[c].GetName() == bok.GetName())
                {
                    RemoveCasset(books, books[c]);
                    RemoveDate(bk, bok);
                    return true;
                }
            }
        }
    }

    return false;
}
