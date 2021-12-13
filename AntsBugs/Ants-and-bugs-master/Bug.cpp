//
//  Bug.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//

#include "Bug.h"
#include "Organism.h"
using namespace std;

Bug::Bug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}
// In the given world moves this organism.
void Bug::move()
{
	//Increase breedTicks until they reach breeding constant
    breedTicks++;

	//Increase deathTick until it reaches death constant
    death_tik++;

	//Increase moveTick, switches its divisibility by 2
	moveTicks++;

	//Moves only on odd values of moveTicks - Can move once every two ticks
	if (moveTicks % 2 == 1)
	{
		if(world->getAt(x, y + 1) != NULL)
		{
			if(world->getAt(x, y + 1)->getType() == ANT)
			{
			    death_tik = 0;
			    delete world->getAt(x, y + 1);
			    movesTo(x, y + 1);
			    return;
			}
		}
    
		if(world->getAt(x, y - 1) != NULL)
		{
			if(world->getAt(x, y - 1)->getType() == ANT)
			{
				death_tik = 0;
				delete world->getAt(x, y - 1);
				movesTo(x, y - 1);
				return;
			}
		}
    
		if(world->getAt(x - 1, y) != NULL)
		{
			if(world->getAt(x - 1, y)->getType() == ANT)
			{
				death_tik = 0;
				delete world->getAt(x - 1, y);
				movesTo(x - 1, y);
				return;
			}
		}
		if(world->getAt(x + 1, y) != NULL)
		{
			if(world->getAt(x + 1, y)->getType() == ANT)
			{
				death_tik = 0;
				delete world->getAt(x + 1, y);
				movesTo(x + 1, y);
				return;
			}
		}
	
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
}

//Creates an offspring of the same organism type at the parameters
void Bug::generateOffspring(int whereX, int whereY)
{
    new Bug(this->world, whereX, whereY);
    breedTicks = 0;
}

// Makes this organism breed.
void Bug::breed()
{
    if(breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }
    
}

// Returns true if organism is dead, false otherwise.
bool Bug::isDead() const
{
    if(death_tik >= STARVE_BUGS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns the type of this organism.
OrganismType Bug::getType() const
{
    return BUG;
}

// The character representation of this organism.
char Bug::representation()const
{
    return '%'; //Percent Sign
}

// The size of this organism.
int Bug::size() const
{
    return 30;
}

//Returns true if the xx and yy parameters are in the world coordinates
bool Bug::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE_X) && (yy >= 0) && (yy < WORLDSIZE_Y);
}
