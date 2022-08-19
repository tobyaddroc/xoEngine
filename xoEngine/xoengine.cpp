#include "xoengine.hpp"

#ifdef IntegratedXO

PoolObject xoEngine::Gamepool::object1 = n;
PoolObject xoEngine::Gamepool::object2 = n;
PoolObject xoEngine::Gamepool::object3 = n;
PoolObject xoEngine::Gamepool::object4 = n;
PoolObject xoEngine::Gamepool::object5 = n;
PoolObject xoEngine::Gamepool::object6 = n;
PoolObject xoEngine::Gamepool::object7 = n;
PoolObject xoEngine::Gamepool::object8 = n;
PoolObject xoEngine::Gamepool::object9 = n;
ClientTurn xoEngine::Gamepool::turn = x;
ServerIP ipaddr = undefined;
char* globalpasswd = undefined;

std::string xoEngine::generateToken() {
	CONST std::string symbols = "abcdefghijklmnopqrtuvwxyz0123456789";
	std::string token;
	srand(time(0));
	while (token.length() < 12)
		token += symbols[rand() % symbols.length()];
	return token;
}

std::string xoEngine::replaceAll(std::string subject, const std::string& search, const std::string& replace) {
	using std::string;
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string xoEngine::readServer(std::string URL) {
	system("ipconfig/flushdns > nul");
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}

std::string xoEngine::stodp(Gameobject _Gameobject) {
	switch (_Gameobject)
	{
	case n:
		return ".";
	case x:
		return "X";
	case o:
		return "O";
	default:
		return "?";
	}
}

ClientTurn xoEngine::generateTurn() {
	srand(time(0));
	switch (rand() % 2 + 1)
	{
	case x:
		return x;
	case o:
		return o;
	default:
		return x - 2;
	}
}

void xoEngine::drawPool() {
	using std::cout;
	cout << "\n " << stodp(Gamepool::object1) << " " << stodp(Gamepool::object2) << " " << stodp(Gamepool::object3) << "\n ";
	cout << stodp(Gamepool::object4) << " " << stodp(Gamepool::object5) << " " << stodp(Gamepool::object6) << "\n ";
	cout << stodp(Gamepool::object7) << " " << stodp(Gamepool::object8) << " " << stodp(Gamepool::object9) << "\n\n";
}

void xoEngine::switchTurn(ClientTurn thisClient) {
	if (thisClient == x)
		xoEngine::Gamepool::turn = o;
	else if (thisClient == o) 
		xoEngine::Gamepool::turn = x;
}

bool xoEngine::syncDown(ServerIP ipF, char* passwd) {
	using std::stringstream;
	using std::ifstream;
	// downld'in
	Sleep(200);
	stringstream ip;
	ip << "http://" << ipF << "/xoengine/xo.bin";
	HRESULT hSync = URLDownloadToFileA(NULL, ip.str().c_str(), "xo.bin", NULL, NULL);
	if (hSync != S_OK)
		return false;
	std::string down;
	ifstream downAll("xo.bin");
	std::getline(downAll, down);
	for (int i = 0; i <= 9; i++)
	{
		if (i == 0) {
			std::string tmp;
			tmp = down[0];
			Gamepool::object1 = std::stoi(tmp);
		}
		else if (i == 1) {
			std::string tmp;
			tmp = down[1];
			Gamepool::object2 = std::stoi(tmp);
		}
		else if (i == 2) {
			std::string tmp;
			tmp = down[2];
			Gamepool::object3 = std::stoi(tmp);
		}
		else if (i == 3) {
			std::string tmp;
			tmp = down[3];
			Gamepool::object4 = std::stoi(tmp);
		}
		else if (i == 4) {
			std::string tmp;
			tmp = down[4];
			Gamepool::object5 = std::stoi(tmp);
		}
		else if (i == 5) {
			std::string tmp;
			tmp = down[5];
			Gamepool::object6 = std::stoi(tmp);
		}
		else if (i == 6) {
			std::string tmp;
			tmp = down[6];
			Gamepool::object7 = std::stoi(tmp);
		}
		else if (i == 7) {
			std::string tmp;
			tmp = down[7];
			Gamepool::object8 = std::stoi(tmp);
		}
		else if (i == 8) {
			std::string tmp;
			tmp = down[8];
			Gamepool::object9 = std::stoi(tmp);
		}
		else if (i == 9) {
			std::string tmp;
			tmp = down[9];
			Gamepool::turn = std::stoi(tmp);
		}
	}
	
	DeleteFileA("xo.bin");
	return true;
}

bool xoEngine::syncUp(ServerIP ip, char* passwd) {
	std::stringstream push;
	push << Gamepool::object1 << Gamepool::object2 << Gamepool::object3 << Gamepool::object4 <<
		Gamepool::object5 << Gamepool::object6 << Gamepool::object7 << Gamepool::object8 << Gamepool::object9 <<
		Gamepool::turn;
	readServer("http://" + (std::string)ipaddr + "/xoengine/pushup.php?binarydata=" + push.str() + "&usepassword=" + passwd + "&requestToken=" + generateToken());
	return true;
}

ClientTurn xoEngine::checkWin() {
	if (
		(this->pool.object1 & this->pool.object2 & this->pool.object3) == x ||
		(this->pool.object4 & this->pool.object5 & this->pool.object6) == x ||
		(this->pool.object7 & this->pool.object8 & this->pool.object9) == x ||

		(this->pool.object1 & this->pool.object4 & this->pool.object7) == x ||
		(this->pool.object2 & this->pool.object5 & this->pool.object8) == x ||
		(this->pool.object3 & this->pool.object6 & this->pool.object9) == x ||

		(this->pool.object1 & this->pool.object5 & this->pool.object9) == x ||
		(this->pool.object3 & this->pool.object5 & this->pool.object7) == x
		)
		return x;
	else if (
		(this->pool.object1 & this->pool.object2 & this->pool.object3) == o ||
		(this->pool.object4 & this->pool.object5 & this->pool.object6) == o ||
		(this->pool.object7 & this->pool.object8 & this->pool.object9) == o ||

		(this->pool.object1 & this->pool.object4 & this->pool.object7) == o ||
		(this->pool.object2 & this->pool.object5 & this->pool.object8) == o ||
		(this->pool.object3 & this->pool.object6 & this->pool.object9) == o ||

		(this->pool.object1 & this->pool.object5 & this->pool.object9) == o ||
		(this->pool.object3 & this->pool.object5 & this->pool.object7) == o
		)
		return o;
	else if (
		(this->pool.object1 & this->pool.object2 & this->pool.object3 &
			this->pool.object4 & this->pool.object5 & this->pool.object6 &
			this->pool.object7 & this->pool.object8 & this->pool.object9
			) != n)
		return t;
}

void xoEngine::syncReset(ServerIP ip, char* passwd) {
	readServer("http://" + std::string(ip) + "/xoengine/connect.php?usepassword=" + passwd + "&requestToken=" + generateToken());
}

bool xoEngine::connect(ServerIP _IP, const char* _Password) {
	using std::stringstream;
	stringstream ss;
	ss << _IP;
	if (readServer("http://" + ss.str() + "/xoengine/connect.php?logintest" + "&requestToken=" + generateToken()) == "0x1: Welcome") {
		if (readServer("http://" + ss.str() + "/xoengine/connect.php?usepassword=" + _Password + "&requestToken=" + generateToken()) == "0x391: Bad password")
			return false;
		else if (readServer("http://" + ss.str() + "/xoengine/connect.php?usepassword=" + _Password + "&requestToken=" + generateToken()) == "0x2: Connection allowed") {
			ipaddr = _IP;
			globalpasswd = (char*)(_Password);
			return true;
		}
	}
	return false;
}

bool xoEngine::writeObject(std::string strHandle, ClientTurn _TeamHandle) {
	if (strHandle == "1" && xoEngine::Gamepool::object1 == n)
		xoEngine::Gamepool::object1 = _TeamHandle;
	else if (strHandle == "2" && xoEngine::Gamepool::object2 == n)
		xoEngine::Gamepool::object2 = _TeamHandle;
	else if (strHandle == "3" && xoEngine::Gamepool::object3 == n)
		xoEngine::Gamepool::object3 = _TeamHandle;
	else if (strHandle == "4" && xoEngine::Gamepool::object4 == n)
		xoEngine::Gamepool::object4 = _TeamHandle;
	else if (strHandle == "5" && xoEngine::Gamepool::object5 == n)
		xoEngine::Gamepool::object5 = _TeamHandle;
	else if (strHandle == "6" && xoEngine::Gamepool::object6 == n)
		xoEngine::Gamepool::object6 = _TeamHandle;
	else if (strHandle == "7" && xoEngine::Gamepool::object7 == n)
		xoEngine::Gamepool::object7 = _TeamHandle;
	else if (strHandle == "8" && xoEngine::Gamepool::object8 == n)
		xoEngine::Gamepool::object8 = _TeamHandle;
	else if (strHandle == "9" && xoEngine::Gamepool::object9 == n)
		xoEngine::Gamepool::object9 = _TeamHandle;
	else
		return false;
	return true;
}

Gamehandle xoEngine::stringToHandle(std::string _StringPointHandle) {
	if (_StringPointHandle == "1")
		return &Gamepool::object1;
	else if (_StringPointHandle == "2")
		return &Gamepool::object2;
	else if (_StringPointHandle == "3")
		return &Gamepool::object3;
	else if (_StringPointHandle == "4")
		return &Gamepool::object4;
	else if (_StringPointHandle == "5")
		return &Gamepool::object5;
	else if (_StringPointHandle == "6")
		return &Gamepool::object6;
	else if (_StringPointHandle == "7")
		return &Gamepool::object7;
	else if (_StringPointHandle == "8")
		return &Gamepool::object8;
	else if (_StringPointHandle == "9")
		return &Gamepool::object9;
	else 
		return undefined;
}

#endif