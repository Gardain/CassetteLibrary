#pragma once
#include "imports.h"
#include "cUser.h"
#include "cСassette.h"

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

// Функция для подсчета разницы между двумя датами
int countDays(Сassette::DateReceiv dateRec, Сassette::DateReturn date2) {
    int count = 0;

    // Подсчет дней в годах
    for (int i = dateRec.year; i < date2.year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
            count += 366;
        else
            count += 365;
    }

    // Подсчет дней в месяцах
    for (int i = dateRec.month; i < date2.month; i++)
        count += countDaysInMonth(i, date2.year);

    // Подсчет дней
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
        datePart.push_back(std::stoi(part)); // Преобразование строки в int
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

void createCassettes(vector<Сassette>& bk, Сassette c)
{
    Сassette newUs(c);

    bk.push_back(newUs);
}
bool existCasset(vector<Сassette>& bk, Сassette book)
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

bool PassCasset(vector<User>& usrs, string idUser, vector<Сassette>& bk, Сassette& bok, Сassette::DateReceiv dateRec, Сassette::DateReturn dateRet)
{
    for (int i = 0; i < usrs.size(); i++)
    {
        if (usrs[i].retName().id == idUser) // поиск пользователя в базе
        {
            if (existCasset(bk, bok))  // поиск книги и проверка забрал ли её кто-то(2 в 1)
            {
                for (int j = 0; j < bk.size(); j++)
                {
                    if (bk[j].GetName() == bok.GetName())  // ищем книгу по массиву, опираясь на имя
                    {
                        int allDays = countDays(dateRec, dateRet);
                        int price = allDays = allDays * bk[j].GetPriceDay();
                        bk[j].PutDate(dateRec, dateRet, price);  // установка даты выдачи/возврата
                        usrs[i].putBook(bk[j]); // помещаем найденую книгу к пользователю
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
        vector<Сassette> bookGoted = usrs[i].retBooks();
        if (bookGoted.size() > 0)
        {
            cout << "Пользователь: ID- " << usrs[i].retName().id << " Фамилия: " << usrs[i].retName().second_name << endl;
            for (Сassette t : bookGoted)
            {
                cout  << "Название: " << t.GetName() << "\nРежисёр: " << t.GetAuthor().name << " " << t.GetAuthor().second_name << "\n";
                cout  << "Цена аренды: " << t.GetPriceRent() << "\n";
                cout << "Дата выдачи: " << t.GetDateReceiv().day << "." << t.GetDateReceiv().month << "." << t.GetDateReceiv().year <<"\n";
                cout << "Дата возврата: " << t.GetDateReturn().day << "." << t.GetDateReturn().month << "." << t.GetDateReturn().year << endl << endl;
            }

            cout << endl << endl << endl;
        }
    }
}

void ShowAllCasset(vector<Сassette>& casset)
{
    for (int i = 0; i < casset.size(); i++)
    {
        cout << "Название: " << casset[i].GetName() << "\nРежисёр: " << casset[i].GetAuthor().name << " " << casset[i].GetAuthor().second_name << "\n";
        cout << "Цена: " << casset[i].GetPriceDay() << "\n";
        cout << "Брали: " << casset[i].GetInfoTaking() << " раз" << endl << endl;
    }
}

bool RemoveCasset(vector<Сassette>& bk, Сassette& bok)
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

bool RemoveDate(vector<Сassette>& bk, Сassette& bok)
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

bool RemoveBookOnUser(vector<User>& usrs, vector<Сassette>& bk, Сassette& bok)
{
    if (!existCasset(bk, bok))
    {
        for (int i = 0; i < usrs.size(); i++)
        {
            vector<Сassette>& books = usrs[i].retBooks();
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