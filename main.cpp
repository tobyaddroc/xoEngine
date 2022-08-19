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
		cout << "������� IP ����� ������� ��� �����������: ";
		cin >> ip;
		cout << "������� ������: ";
		cin >> pass;
		cout << "�����������...";
		if (!xo.connect(toServerIP(ip.c_str()), (char*)pass.c_str())) {
			cout << "\n�� ������� ����������� � �������� " << ip << "\n������� ����� ������� ����� ����������...";
			system("pause>nul");
			goto checkpoint1;
		}
		xo.syncReset(toServerIP(ip.c_str()), (char*)pass.c_str());
		break;
	}
	while (true) {
		checkpoint2:
		if (!xo.syncDown(toServerIP(ip.c_str()), toServerIP(pass.c_str()))) {
			cout << "\n������ �������������\n";
			system("pause>nul");
			goto checkpoint1;
		}
		system("cls");
		xo.drawPool();
		if (xo.checkWin() == x) {
			cout << " �������� �������: X\r";
			Sleep(900);
			cout << " �������� �������: x\r";
			Sleep(900);
			cout << " �������� �������: X\r";
			Sleep(900);
			cout << " �������� �������: x\r";
			Sleep(900);
			cout << " �������� �������: X\r";
			Sleep(900);
			goto checkpoint1;
		}
		else if (xo.checkWin() == o) {
			cout << " �������� �������: O\r";
			Sleep(900);
			cout << " �������� �������: o\r";
			Sleep(900);
			cout << " �������� �������: O\r";
			Sleep(900);
			cout << "�������� �������: o\r";
			Sleep(900);
			cout << "�������� �������: O\r";
			Sleep(900);
			goto checkpoint1;
		}
		else if (xo.checkWin() == t) {
			cout << " �����!\r";
			Sleep(900);
			cout << " �����!\r";
			Sleep(900);
			cout << " �����!\r";
			Sleep(900);
			cout << " �����!\r";
			Sleep(900);
			cout << " �����!\r";
			Sleep(900);
			goto checkpoint1;
		}
		else {
			if (xo.pool.turn != thisClient) {
				cout << "�������� ���������...\n";
				Sleep(3000);
				xo.syncDown(toServerIP(ip.c_str()), toServerIP(pass.c_str()));
				goto checkpoint2;
			}
			cout << "��� ���: ";
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