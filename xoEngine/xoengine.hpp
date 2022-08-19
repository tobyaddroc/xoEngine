#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <wininet.h>
#include <sstream>

#pragma comment (lib, "wininet.lib")
#pragma comment (lib, "urlmon.lib")

#ifndef IntegratedXO
#define IntegratedXO

#define undefined	0
#define toServerIP(ip) ServerIP(ip)

typedef short PoolObject;
typedef short* Gamehandle;
typedef short Gameobject;
typedef short ClientTurn;
typedef char* ServerIP;

typedef const enum States {
	n,
	x,
	o,
	t
} ObjectState;


class xoEngine {
public:
	typedef struct Gamepool {
		static PoolObject object1;
		static PoolObject object2;
		static PoolObject object3;
		static PoolObject object4;
		static PoolObject object5;
		static PoolObject object6;
		static PoolObject object7;
		static PoolObject object8;
		static PoolObject object9;
		static PoolObject object10;
		static PoolObject object11;
		static PoolObject object12;
		static PoolObject object13;
		static PoolObject object14;
		static PoolObject object15;
		static PoolObject object16;
		static ClientTurn turn;
	} Gamepool;
	Gamepool pool;
	std::string generateToken();
	std::string replaceAll(std::string subject, const std::string& search, const std::string& replace);
	std::string readServer(std::string URL);
	std::string stodp(Gameobject _Gameobject);
	ClientTurn generateTurn();
	void drawPool();
	void switchTurn(ClientTurn thisClient);
	bool syncDown(ServerIP ip, char* passwd);
	bool syncUp(ServerIP ip, char* passwd);
	ClientTurn checkWin();
	void syncReset(ServerIP ip, char* passwd);
	bool connect(ServerIP _IP, const char* _Password);
	bool writeObject(std::string strHandle, ClientTurn _TeamHandle);
	Gamehandle stringToHandle(std::string _StringPointHandle);
	//ObjectState	readObject(Gameobject _PointObject);
	//Gameobject handleToObject(Gamehandle _PointHandle);
};

#define CreateXOEngine(variablename) xoEngine variablename
#endif