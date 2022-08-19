# xoEngine
### Tic-tac-toe Game Engine
- Usage:
1. open the web server so the game can access connect.php, pushup.php etc (http://(ipaddress)/xoengine/connect.php)
2. compile this source with configs X and O. 
3. you must have two versions of the game: X.exe and O.exe
4. send one of versions to a friend
5. you and your friend must enter ip of server (WITH NO PORT)
6. if the connection is made, the game field will appear and you can play
7. to put crosses or zeros, enter the serial number of the cell, for example: 1, 2, 3 and so on
8. have a nice game!

# Engine API
- CreateXOEngine(variable name)
Creates a call to the xoEngine class
CreateXOEngine(xo);
xo.pool.object1 = 0;
- typedef short PoolObject
Playing field object
- typedef short *Gamehandle
Playing field point handle
- typedef short Gameobject
Game object
- typedef short ClientTurn
Object of client-sided turn
- typedef char* ServerIP
Server IP object
- toServerIP(std::string)
Recasting to ServerIP data-type
- typedef const enum States { ... } ObjectState
Enumeration of cell states on the playing field and turns
n = 0, The case is free
x = 1, Case filled with side X
o = 2, Case filled with side O
t = 3, Denotes a draw (tie)
### Structs
- typedef struct Gamepool { ... } Gamepool
The structure of the playing field, stores 9 cells in itself and whose turn it is now
To call use (CreateXOEngine).pool
### Functions
- std::string xoEngine::replaceAll(...)
Engine stub-function to readServer(...), do not use it
- std::string xoEngine::readServer(std::string URL)
Makes a request to the server with certain parameters written in the address bar
Example: xo.readServer("http://127.0.0.1/xoengine/connect.php?someparameters")
Returns server answer (std::string)
- std::string xoEngine::stodp(Gameobject _Gameobject)
Recasting Gameobject to std::string
Returns recasted value (std::string)
- void xoEngine::drawPool()
Drawing gamepool
- void xoEngine::switchTurn(ClientTurn thisClient)
Switching game turn
If X's turn, switching it to O dna
- bool xoEngine::syncDown(ServerIP ip, char* passwd)
Downloading Gamepool struct from server
Returning true or false (bool)
If sync successfull returning true,
If sync unsuccessfull returning false
- bool xoEngine::syncUp(ServerIP ip, char* passwd)
Similar to the function above, except that it passes the Gamepool structure to the server
Returning true or false (bool)
- ClientTurn xoEngine::checkWin()
Checks for the victory of one of the teams, if yes, returns the value of the team that won. 
If the game ends in a draw, ObjectState::t is returned.
- void xoEngine::syncReset(ServerIP ip, char* passwd)
Dumps data on the game server
- bool xoEngine::connect(ServerIP _IP, const char* _Password)
If the connection to the server is successful, it returns true, if not, it returns false
- bool xoEngine::writeObject(std::string strHandle, ClientTurn _TeamHandle)
Writes to the cell