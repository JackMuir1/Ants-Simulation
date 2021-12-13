//
//  Rock.cpp
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Jack Muir on 1/28/21
//

#include "Rock.h"
#include "Organism.h"
#include "World.h"
using namespace std;

Rock::Rock(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{

}

// Returns the type of this organism.
OrganismType Rock::getType() const
{
	return ROCK;
}

// The character representation of this organism.
char Rock::representation() const
{
	return 'R';
}

// The size of this organism.
int Rock::size() const
{

	return 10;
}

//returns if the parameters are in range of the organisms position
bool Rock::in_range(int xx, int yy)
{
	return (xx >= 0) && (xx < WORLDSIZE_X) && (yy >= 0) && (yy < WORLDSIZE_Y);
}

//Unused overwritten methods. Rock does not move or breed, just occupies space
void Rock::breed()
{}
void Rock::generateOffspring(int x, int y)
{} 
void Rock::move()
{
}
