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
PoolObject xoEngine::Gamepool::object10 = n;
PoolObject xoEngine::Gamepool::object11 = n;
PoolObject xoEngine::Gamepool::object12 = n;
PoolObject xoEngine::Gamepool::object13 = n;
PoolObject xoEngine::Gamepool::object14 = n;
PoolObject xoEngine::Gamepool::object15 = n;
PoolObject xoEngine::Gamepool::object16 = n;
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
	cout << "\n " << stodp(Gamepool::object1) << " " << stodp(Gamepool::object2) << " " << stodp(Gamepool::object3) << " " << stodp(Gamepool::object4) << "\n " <<
		stodp(Gamepool::object5) << " " << stodp(Gamepool::object6) << " " << stodp(Gamepool::object7) << " " << stodp(Gamepool::object8) << "\n " <<
		stodp(Gamepool::object9) << " " << stodp(Gamepool::object10) << " " << stodp(Gamepool::object11) << " " << stodp(Gamepool::object12) << "\n " <<
		stodp(Gamepool::object13) << " " << stodp(Gamepool::object14) << " " << stodp(Gamepool::object15) << " " << stodp(Gamepool::object16) << "\n\n ";
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
	for (int i = 0; i <= 16; i++)
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
			Gamepool::object10 = std::stoi(tmp);
		}
		else if (i == 10) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object11 = std::stoi(tmp);
		}
		else if (i == 11) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object12 = std::stoi(tmp);
		}
		else if (i == 12) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object13 = std::stoi(tmp);
		}
		else if (i == 13) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object14 = std::stoi(tmp);
		}
		else if (i == 14) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object15 = std::stoi(tmp);
		}
		else if (i == 15) {
			std::string tmp;
			tmp = down[i];
			Gamepool::object16 = std::stoi(tmp);
		}
		else if (i == 16) {
			std::string tmp;
			tmp = down[i];
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
		Gamepool::object10 << Gamepool::object11 << Gamepool::object12 << Gamepool::object13 << Gamepool::object14 << Gamepool::object15 << Gamepool::object16 << Gamepool::turn;
	readServer("http://" + (std::string)ipaddr + "/xoengine/pushup.php?binarydata=" + push.str() + "&usepassword=" + passwd + "&requestToken=" + generateToken());
	return true;
}

ClientTurn xoEngine::checkWin() {
	if ( // horizontal
		(this->pool.object1 & this->pool.object2 & this->pool.object3) == x || // xxx. [1] 
		(this->pool.object2 & this->pool.object3 & this->pool.object4) == x || // .xxx [1]

		(this->pool.object5 & this->pool.object6 & this->pool.object7) == x || // xxx. [2] 
		(this->pool.object6 & this->pool.object7 & this->pool.object8) == x || // .xxx [2]

		(this->pool.object9 & this->pool.object10 & this->pool.object11) == x || // xxx. [3]
		(this->pool.object10 & this->pool.object11 & this->pool.object12) == x || // .xxx [3]

		(this->pool.object13 & this->pool.object14 & this->pool.object15) == x || // xxx. [4]
		(this->pool.object14 & this->pool.object15 & this->pool.object16) == x || // .xxx [4]

		// vertical
		(this->pool.object1 & this->pool.object5 & this->pool.object9) == x || // xxx. [1] 
		(this->pool.object5 & this->pool.object9 & this->pool.object13) == x || // .xxx [1]

		(this->pool.object2 & this->pool.object6 & this->pool.object10) == x || // xxx. [2] 
		(this->pool.object6 & this->pool.object10 & this->pool.object14) == x || // .xxx [2]

		(this->pool.object3 & this->pool.object7 & this->pool.object11) == x || // xxx. [3]
		(this->pool.object7 & this->pool.object11 & this->pool.object15) == x || // .xxx [3]

		(this->pool.object4 & this->pool.object8 & this->pool.object12) == x || // xxx. [4]
		(this->pool.object8 & this->pool.object12 & this->pool.object16) == x || // .xxx [4]

		// diagonal
		(this->pool.object1 & this->pool.object6 & this->pool.object11) == x || // xxx. [1] 
		(this->pool.object6 & this->pool.object11 & this->pool.object16) == x || // .xxx [1]

		(this->pool.object2 & this->pool.object7 & this->pool.object12) == x || // xxx [2] 

		(this->pool.object5 & this->pool.object10 & this->pool.object15) == x ||  // xxx [3]


		(this->pool.object4 & this->pool.object7 & this->pool.object10) == x || // xxx. [1] 
		(this->pool.object7 & this->pool.object10 & this->pool.object13) == x || // .xxx [1]

		(this->pool.object3 & this->pool.object6 & this->pool.object9) == x || // xxx [2] 

		(this->pool.object8 & this->pool.object11 & this->pool.object14) == x  // xxx [3]
		)
		return x;
	else if (
		(this->pool.object1 & this->pool.object2 & this->pool.object3) == o || // ooo. [1] 
		(this->pool.object2 & this->pool.object3 & this->pool.object4) == o || // .ooo [1]

		(this->pool.object5 & this->pool.object6 & this->pool.object7) == o || // ooo. [2] 
		(this->pool.object6 & this->pool.object7 & this->pool.object8) == o || // .ooo [2]

		(this->pool.object9 & this->pool.object10 & this->pool.object11) == o || // ooo. [3]
		(this->pool.object10 & this->pool.object11 & this->pool.object12) == o || // .ooo [3]

		(this->pool.object13 & this->pool.object14 & this->pool.object15) == o || // ooo. [4]
		(this->pool.object14 & this->pool.object15 & this->pool.object16) == o || // .ooo [4]

		// vertical
		(this->pool.object1 & this->pool.object5 & this->pool.object9) == o || // ooo. [1] 
		(this->pool.object5 & this->pool.object9 & this->pool.object13) == o || // .ooo [1]

		(this->pool.object2 & this->pool.object6 & this->pool.object10) == o || // ooo. [2] 
		(this->pool.object6 & this->pool.object10 & this->pool.object14) == o || // .ooo [2]

		(this->pool.object3 & this->pool.object7 & this->pool.object11) == o || // ooo. [3]
		(this->pool.object7 & this->pool.object11 & this->pool.object15) == o || // .ooo [3]

		(this->pool.object4 & this->pool.object8 & this->pool.object12) == o || // ooo. [4]
		(this->pool.object8 & this->pool.object12 & this->pool.object16) == o || // .ooo [4]

		// diagonal
		(this->pool.object1 & this->pool.object6 & this->pool.object11) == o || // ooo. [1] 
		(this->pool.object6 & this->pool.object11 & this->pool.object16) == o || // .ooo [1]

		(this->pool.object2 & this->pool.object7 & this->pool.object12) == o || // ooo [2] 

		(this->pool.object5 & this->pool.object10 & this->pool.object15) == o ||  // ooo [3]


		(this->pool.object4 & this->pool.object7 & this->pool.object10) == o || // ooo. [1] 
		(this->pool.object7 & this->pool.object10 & this->pool.object13) == o || // .ooo [1]

		(this->pool.object3 & this->pool.object6 & this->pool.object9) == o || // ooo [2] 

		(this->pool.object8 & this->pool.object11 & this->pool.object14) == o  // ooo [3]
		)
		return o;
	else if (
		(this->pool.object1 && this->pool.object2 && this->pool.object3 &&
			this->pool.object4 && this->pool.object5 && this->pool.object6 &&
			this->pool.object7 && this->pool.object8 && this->pool.object9 && 
			this->pool.object10 && this->pool.object11 && this->pool.object12 && 
			this->pool.object13 && this->pool.object14 && this->pool.object15 && this->pool.object16
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
	else if (strHandle == "10" && xoEngine::Gamepool::object10 == n)
		xoEngine::Gamepool::object10 = _TeamHandle;
	else if (strHandle == "11" && xoEngine::Gamepool::object11 == n)
		xoEngine::Gamepool::object11 = _TeamHandle;
	else if (strHandle == "12" && xoEngine::Gamepool::object12 == n)
		xoEngine::Gamepool::object12 = _TeamHandle;
	else if (strHandle == "13" && xoEngine::Gamepool::object13 == n)
		xoEngine::Gamepool::object13 = _TeamHandle;
	else if (strHandle == "14" && xoEngine::Gamepool::object14 == n)
		xoEngine::Gamepool::object14 = _TeamHandle;
	else if (strHandle == "15" && xoEngine::Gamepool::object15 == n)
		xoEngine::Gamepool::object15 = _TeamHandle;
	else if (strHandle == "16" && xoEngine::Gamepool::object16 == n)
		xoEngine::Gamepool::object16 = _TeamHandle;
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