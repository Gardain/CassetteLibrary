#include "imports.h"
#include "cControlFunctions.h"
#include "cСassette.h"
#include "cUser.h"

vector<User> users = vector<User>();
vector<Сassette> cassettes = vector<Сassette>();

int main()
{
	setlocale(0, "RU");
	
	while (true)
	{
	work:
		int n = 0;
		cout << endl << "Создать нового пользователя 1" << endl;
		cout << "Добавить кассету VHS 2" << endl;
		cout << "Выдать кассету 3" << endl;
		cout << "Принять кассету обратно 4" << endl;
		cout << "Получить занятые кассеты 5" << endl;
		cout << "Вывести все кассеты 6" << endl;
		cout << "Вывести всех пользователей 7" << endl;
		cout << "Введите вариант работы: " << endl << endl;
		cin >> n;

		switch (n)
		{
		case 1:
		{
			string n1;
			string n2;
			cout << "Введите имя: " << endl;
			cin >> n1;
			cout << "Введите фамилию: " << endl;
			cin >> n2;
			User::sUs_initials cc;
			cc.name = n1;
			cc.second_name = n2;
			cc.id = generateRandomString(15);
			User tmp(cc);

			createUser(users, cc);
			break;
		}
		case 2:
		{
			string casName;
			string aName;
			string aName2;
			int price = 0;
			cout << "Впишите название кассеты: \n";
			cin >> casName;
			cout << "Имя автора: \n";
			cin >> aName;
			cout << "Фамилия автора: \n";
			cin >> aName2;
			cout << "Цена за день: \n";
			cin >> price;

			Сassette::sAuthor c;
			c.name = aName;
			c.second_name = aName2;
			
			Сassette bo(casName, c, price);
			createCassettes(cassettes, bo);
			break;
		}
		case 3:
		{
			string id;
			string bookName;
			string dRc;
			string dRt;
			vector<std::vector<int>> dateRec;
			vector<std::vector<int>> dateRet;
			cout << "Впишите ID пользователя: " << endl;
			cin >> id;
			cout << "Впишите название кассеты: " << endl;
			cin >> bookName;
			cout << "Впишите дату выдачи (dd.mm.yy): " << endl;
			cin >> dRc;
			cout << "Впишите дату возврата (dd.mm.yy): " << endl;
			cin >> dRt;
			if (is_date_valid(dRc) && is_date_valid(dRt))
			{
				dateRec = convertDateStringToVector(dRc);
				dateRet = convertDateStringToVector(dRt);
			}
			else
			{
				cout << "Дата введена не верно" << endl;
				goto work;
			}

			Сassette::sAuthor author;
			Сassette tmp(bookName, author, 0);
			Сassette::DateReceiv Drecv;
			Сassette::DateReturn Dretu;

			Drecv.day = dateRec[0][0];
			Drecv.month = dateRec[1][0];
			Drecv.year = dateRec[2][0];

			Dretu.day = dateRet[0][0];
			Dretu.month = dateRet[1][0];
			Dretu.year = dateRet[2][0];
			cout << endl;
			if (!PassCasset(users, id, cassettes, tmp, Drecv, Dretu))
			{
				cout << "Кассета занята либо её не существует" << endl;
			}
			break;
		}
		case 4:
		{
			Сassette::sAuthor auth;
			auth.name = "";
			auth.second_name = "";
			string bName;
			cout << "Впишите название кассеты: " << endl;
			cin >> bName;
			Сassette b(bName, auth, 0);
			if (RemoveBookOnUser(users, cassettes, b))
			{
				cout << "Кассета принята" << endl;
			}
			else
			{
				cout << "Кассета cвободна" << endl;
			}
		}
		case 5:
		{
			OccupiedCasset(users);
			break;
		}
		case 6:
		{
			ShowAllCasset(cassettes);
			break;
		}
		case 7:
		{
			for (User us : users)
			{
				User::sUs_initials init = us.retName();

				cout << "Фамилия: " << init.second_name << endl;
				cout << "Имя: " << init.name << endl;
				cout << "ID: " << init.id << endl << endl;
			}
			break;
		}
		default:
		{
			break;
		}
			
		}
	}

	
}
