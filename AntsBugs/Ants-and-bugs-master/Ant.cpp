//
//  Ant.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Kristjan Thorsteinsson on 01/04/14.
//  Copyright (c) 2014 Kristjan Thorsteinsson. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"
using namespace std;

Ant::Ant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
	
}

// In the given world moves this organism.
void Ant::move()
{
	//Increase breedTicks until they reach breeding constant
    breedTicks++;

	//Increase moveTick, switches its divisibility by 2
	moveTicks++;

	//Moves only on odd values of moveTicks - Can move once every two ticks
	if (moveTicks % 2 == 1)
	{
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

// Makes this organism breed if breedTick reaches the constant set by the world.
void Ant::breed()
{
    if(breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}

//Creates an offspring of the same organism type at the parameters
void Ant::generateOffspring(int whereX, int whereY)
{
    new Ant(this->world, whereX, whereY);
    breedTicks = 0;
}

// Returns the type of this organism.
OrganismType Ant::getType() const
{
    return ANT;
}

// The character representation of this organism.
char Ant::representation() const
{
    return char(2); //A smile face
}

// The size of this organism.
int Ant::size() const
{
	
    return 10;
}

//Returns true if the xx and yy parameters are in the world coordinates
bool Ant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE_X) && (yy >= 0) && (yy < WORLDSIZE_Y);
}
