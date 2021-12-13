//
//  Twin.h
//  INHERITANCE_AND_POLYMORPHISM
//
//  Created by Jack Muir on 1/28/21
//

#include <iostream>

#include "World.h"
#include "Organism.h"

class Twin : public Organism
{
public:

	Twin(World* aWorld, int xcoord, int ycoord);

	// In the given world moves this organism.
	void move();

	// Makes this organism breed.
	void breed();

	// Returns the type of this organism.
	OrganismType getType() const;

	// The character representation of this organism.
	char representation() const;

	// The size of this organism.
	int size() const;

	//returns if the parameters are in range of the organisms position
	bool in_range(int xx, int yy);

private:

	//Creates an offspring of the same organism type at the parameters
	void generateOffspring(int whereX, int whereY);

	//Resets the spaces in all directions around the organism, including its own space
	void explode(int x, int y);
};
