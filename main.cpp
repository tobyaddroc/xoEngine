#include "xoEngine/xoengine.hpp"

using namespace std;


#if defined _CONFIG_O
const ClientTurn thisClient = o;
#endif

#if defined _CONFIG_X
const ClientTurn thisClient = x;
#endif

int main()
{
	setlocale(0, "rus");
	string ip;
	string pass;
	CreateXOEngine(xo);
	while (true) {
		checkpoint1:
		system("cls");
		cout << "Введите IP адрес сервера для подключения: ";
		cin >> ip;
		cout << "Введите пароль: ";
		cin >> pass;
		cout << "Подключение...";
		if (!xo.connect(toServerIP(ip.c_str()), (char*)pass.c_str())) {
			cout << "\nНе удается соединиться с сервером " << ip << "\nНажмите любую клавишу чтобы продолжить...";
			system("pause>nul");
			goto checkpoint1;
		}
		xo.syncReset(toServerIP(ip.c_str()), (char*)pass.c_str());
		break;
	}
	while (true) {
		checkpoint2:
		if (!xo.syncDown(toServerIP(ip.c_str()), toServerIP(pass.c_str()))) {
			cout << "\nОшибка синхронизации\n";
			system("pause>nul");
			goto checkpoint1;
		}
		system("cls");
		xo.drawPool();
		if (xo.checkWin() == x) {
			cout << " Победила команда: X\r";
			Sleep(900);
			cout << " Победила команда: x\r";
			Sleep(900);
			cout << " Победила команда: X\r";
			Sleep(900);
			cout << " Победила команда: x\r";
			Sleep(900);
			cout << " Победила команда: X\r";
			Sleep(900);
			goto checkpoint1;
		}
		else if (xo.checkWin() == o) {
			cout << " Победила команда: O\r";
			Sleep(900);
			cout << " Победила команда: o\r";
			Sleep(900);
			cout << " Победила команда: O\r";
			Sleep(900);
			cout << "Победила команда: o\r";
			Sleep(900);
			cout << "Победила команда: O\r";
			Sleep(900);
			goto checkpoint1;
		}
		else if (xo.checkWin() == t) {
			cout << " Ничья!\r";
			Sleep(900);
			cout << " НИЧЬЯ!\r";
			Sleep(900);
			cout << " Ничья!\r";
			Sleep(900);
			cout << " НИЧЬЯ!\r";
			Sleep(900);
			cout << " Ничья!\r";
			Sleep(900);
			goto checkpoint1;
		}
		else {
			if (xo.pool.turn != thisClient) {
				cout << "Ожидание соперника...\n";
				Sleep(3000);
				xo.syncDown(toServerIP(ip.c_str()), toServerIP(pass.c_str()));
				goto checkpoint2;
			}
			cout << "Ваш ход: ";
			string handle;
			cin >> handle;
			bool Result = xo.writeObject(handle, thisClient);
			if (!Result)
				goto checkpoint2;
			xo.switchTurn(thisClient);
			xo.syncUp(toServerIP(ip.c_str()), toServerIP(pass.c_str()));
		}
	}
}