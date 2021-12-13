#include <iostream>
#include <string>
#include <cstdlib> // for rand
#include <Windows.h> //for color text
#include <iomanip> //For text padding
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "Twin.h"
#include "Rock.h"
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE_X; i++) {
        for (int j = 0; j < WORLDSIZE_Y; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 30
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 60
    createOrganisms(BUG, INITIAL_BUGS);
	//creates the twins = 12
	createOrganisms(TWIN, INITIAL_TWINS);
	//creates the rocks = 15
	createOrganisms(ROCK, INITIAL_ROCKS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE_X; i++) {
        for (int j = 0; j < WORLDSIZE_Y; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE_X) && (y >= 0) && (y < WORLDSIZE_Y)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE_X) && (y >= 0) && (y < WORLDSIZE_Y)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const {
    int numAnts = 0;
    int numBugs = 0;
	int numTwins = 0;
	int numRocks = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //For coloring of Text

	 //Top line of border
	cout << "                              --------------------------------------------------------------" << endl;

	//Printing World
    for (int j = 0; j < WORLDSIZE_Y; j++) {
		SetConsoleTextAttribute(h, 15);
		cout << "                              |"; //Text Centering and vertical line of border
        for (int i = 0; i < WORLDSIZE_X; i++) {
            if (grid[i][j] == NULL) {
                cout << " ";
            } else {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
					SetConsoleTextAttribute(h, 12);
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
					SetConsoleTextAttribute(h, 5);
                }
				else if (grid[i][j]->getType() == TWIN) {
					numTwins++;
					SetConsoleTextAttribute(h, 14);

				}
				else if (grid[i][j]->getType() == ROCK) {
					numRocks++;
					SetConsoleTextAttribute(h, 10);

				}
                cout << grid[i][j]->representation();
            }
        }
		SetConsoleTextAttribute(h, 15);
        cout << "|" << endl; //right vertical side of border
    }

	//Bottom line of border
	cout << "                              -------------------------------------------------------------" << endl;

	//Printing of the number of organisms. 
	//Includes text centering, color change, organism symbol, organism name, and padded number of organism

	//Ants
	cout << "                                                        "; //For text centering
	SetConsoleTextAttribute(h, 12);                                     //Color to red
	cout << char(2) << " Ants: " << setw(4) << numAnts << endl;         //Symbol, name, and number (padded to 4 digits)

	//Bugs
	cout << "                                                       "; //For text centering
	SetConsoleTextAttribute(h, 5);                                     //Color to purple
	cout << " % Bugs: " << setw(4) << numBugs << endl;                 //Symbol, name, and number (padded to 4 digits)

	//Twins
	cout << "                                                        "; //For text centering
	SetConsoleTextAttribute(h, 14);                                     //Color to yellow
	cout << char(220) << " Twins:" << setw(4) << numTwins << endl;      //Symbol, name, and number (padded to 4 digits)

	//Rocks
	cout << "                                                       "; //For text centering
	SetConsoleTextAttribute(h, 10);                                    //Color to green
	cout << " R Rocks:" << setw(4) << numRocks << " (Rocks cannot be moved but can be blown up)" << endl;//Symbol, name, number, and description

	//Instruction line
	SetConsoleTextAttribute(h, 15);                                     //Color to white
	cout << "          Press 'a' to add ants, 'b' to add bugs, 't' to add twin bugs, 'p' to pause the game, and 'q' to quit"; //Instructions
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
	// 3. move twins
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);
	
	//Move the Twins
	moveOrganism(TWIN);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE_X;
    p.y = rand() % WORLDSIZE_Y;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
			else if (orgType == TWIN)
			{
				new Twin(this, p.x, p.y);   // Create a Twin and put it into the world
			}
			else if (orgType == ROCK)
			{
				new Rock(this, p.x, p.y);   // Create a Rock and put it into the world
			}
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE_X; i++)
    {
        for (int j = 0; j < WORLDSIZE_Y; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE_X; i++)
    {
        for(int j = 0; j < WORLDSIZE_Y; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE_X; i++) {
        for (int j = 0; j < WORLDSIZE_Y; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE_X; i++)
    {
        for(int j = 0; j < WORLDSIZE_Y; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}

//Checks world to see if all spaces are occupied
bool World::isFull() {

	for (int j = 0; j < WORLDSIZE_Y; j++) {
		for (int i = 0; i < WORLDSIZE_X; i++) {
			if (grid[i][j] == NULL)
				return false;
		}
	}
	return true;
}
