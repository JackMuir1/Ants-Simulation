//
//  Twin.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Jack Muir on 1/28/21
//

#include "Twin.h"
#include "Organism.h"
using namespace std;

Twin::Twin(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
}

// In the given world moves this organism.
void Twin::move()
{
	//Death_tik ommitted. Twin bug does not starve

	//Checking in all directions for other Twin Bug. If there is one, explode
	if (world->getAt(x, y + 1) != NULL)
	{
		if (world->getAt(x, y + 1)->getType() == TWIN)
		{
			explode(x, y + 1);
			return;
		}
	}

	if (world->getAt(x, y - 1) != NULL)
	{
		if (world->getAt(x, y - 1)->getType() == TWIN)
		{
			explode(x, y - 1);
			return;
		}
	}

	if (world->getAt(x - 1, y) != NULL)
	{
		if (world->getAt(x - 1, y)->getType() == TWIN)
		{
			explode(x - 1, y);
			return;
		}
	}
	if (world->getAt(x + 1, y) != NULL)
	{
		if (world->getAt(x + 1, y)->getType() == TWIN)
		{
			explode(x +1, y);
			return;
		}
	}

	//Movement
	Move mover = world->randomMove();
	switch (mover) {
	case UP:
		if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
		{
			movesTo(x, y + 1);
		}
		break;
	case DOWN:
		if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
		{
			movesTo(x, y - 1);
		}
		break;
	case LEFT:
		if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
		{
			movesTo(x - 1, y);
		}
		break;
	case RIGHT:
		if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
		{
			movesTo(x + 1, y);
		}
		break;
	default:
		break;
	}
}

// Returns the type of this organism.
OrganismType Twin::getType() const
{
	return TWIN;
}

// The character representation of this organism.
char Twin::representation()const
{
	return char(220); //A square
}

// The size of this organism.
int Twin::size() const
{
	return 30;
}

//returns if the parameters are in range of the organisms position
bool Twin::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE_X) && (yy >= 0) && (yy < WORLDSIZE_Y);
}

//Function to destroy the spaces one space apart in all directions from the object, including the object's space
void Twin::explode(int x, int y)
{
	//Checking of bounds is handled by the setAt function
		world->setAt(x - 1, y + 1, NULL); //All spaces above the object
		world->setAt(x, y + 1, NULL);
		world->setAt(x + 1, y + 1, NULL);

		world->setAt(x - 1, y - 1, NULL); //All spaces below the object
		world->setAt(x, y - 1, NULL);
		world->setAt(x + 1, y - 1, NULL);

		world->setAt(x - 1, y, NULL); //All spaces in line with the object
		world->setAt(x + 1, y, NULL);
		world->setAt(x, y, NULL);
}

//Unused overwritten methods. Twin Bugs do not breed
void Twin::breed()
{}
void Twin::generateOffspring(int x, int y)
{}
