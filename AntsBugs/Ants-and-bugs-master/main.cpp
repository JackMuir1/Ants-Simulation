#include <Windows.h>
#include <iostream>
#include <ctime>    // for time
#include <conio.h> //for get char
#include "World.h"
#pragma comment(lib, "winmm.lib") //for music playing

using namespace std;

//handle used for colors and cursor
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); 

//Removes the blinking cursor from the console
void RemoveCursor()
{

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo); //Get the current cursor ifo 
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo); //sets the cursor visibility value to the cursor info
}

//Sets the cursor position for console output
void setCursorPosition(int x, int y)
{
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(out, coord);
}

//Screen that is display at the start of the game
//Contains art, title and user input 
void startScreen()
{
		//Ant art
	    SetConsoleTextAttribute(out, 12); //Color red for ant art
		cout << endl << endl;
		cout << "                                                     /\\   /\\" << endl;
		cout << "                                                       \\_/" << endl;
		cout << "                                                  __   / \\   __" << endl;
		cout << "                                                -'  `. \\_/ .'  `-" << endl;
		cout << "                                                      \\/ \\/" << endl;
		cout << "                                                 _.---(   )---._" << endl;
		cout << "                                              _.'   _.-\\_/-._   `._" << endl;
		cout << "                                                   /   /_\\   \\" << endl;
		cout << "                                                  /   /___\\   \\" << endl;
		cout << "                                                 /   |_____|   \\" << endl;
		cout << "                                              _.'    | ___ |    `._" << endl;
		cout << "                                                      \\___/" << endl;

		//Title and Name
		SetConsoleTextAttribute(out, 15); //Color white for text
		cout << "                                        Ants, Bugs, and Twin Bugs Assignment" << endl;
		cout << "                                                  By Jack Muir" << endl << endl << endl;

		//User Input Prompt
		cout << "                                             Press any key to begin" << endl;
		_getch();
}


int main()
{
		//Initialization of cursor and music
		RemoveCursor();
		PlaySound(TEXT("BugSong.wav"), NULL, SND_LOOP | SND_ASYNC); // Included file BugSong.wav plays on loop 

		//Displays the Start Screen
		startScreen();

		//Clears the Start Screen
		system("cls");

		//Creates and displays World
		World myWorld(time(0));
		myWorld.display();

		//Char used to store user input
		char ch;

		while (true) {
			//Rests screen position for changing the screen without blinking
			setCursorPosition(0,0);

			myWorld.simulateOneStep();
			myWorld.display();

			//Checks for user input
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 'q' || ch == 'Q') //Quit Game
				{
					break;
				}
				else if (ch == 'p' || ch == 'P')//pause game
				{
					//Prompts pause text and asks for user input
					cout << "\n                                          Game Paused. Press any key to resume \r";

					//User input
					_getch(); 

					//Clears pause text
					cout << "                                                                               \r";
				}
				else if (!myWorld.isFull()) //Checks to see if world is full before adding more organisms 
				{
					if (ch == 'b' || ch == 'B')
					{
						//add bug
						myWorld.createOrganisms(BUG, 1);
					}
					else if (ch == 'a' || ch == 'A')
					{
						//add ant
						myWorld.createOrganisms(ANT, 1);
					}
					else if (ch == 't' || ch == 'T')
					{
						//add twin
						myWorld.createOrganisms(TWIN, 1);
					}
				}
				
			}
			//Wait 200 miliseconds before changing screen
			Sleep(200);
		}
	

    return 0;
}

