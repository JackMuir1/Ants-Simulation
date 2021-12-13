#ifndef ORGANISM_H
#define ORGANISM_H


//Enumerator for the 4 different types of derived organisms
enum OrganismType {ANT, BUG, TWIN, ROCK};

// forward declaration
class World;

class Organism {
    public:
        // Create an organism at the given coordinates.
        Organism(World* aWorld, int xcoord, int ycoord);
        virtual ~Organism() { }

        // In the given world moves this organism.
        virtual void move() = 0;

        // Makes this organism breed.
        virtual void breed() = 0;

        // Returns the type of this organism.
        virtual OrganismType getType() const = 0;

        // Flags this organism as moved or not.
        void setMoved(bool hasMoved);

        // The character representation of this organism.
        virtual char representation() const = 0;

        // The size of this organism.
        virtual int size() const = 0;

        // Has this organism moved in this time slot or not?
        bool hasMoved() const;

        // Returns true if organism is dead, false otherwise.
        virtual bool isDead() const;
    
		//Returns true if the xx and yy parameters are in the world coordinates
        bool in_range(int xx, int yy);
    
    protected:
        // Generates an offspring at the given position.
        virtual void generateOffspring(int whereX, int whereY) = 0;

        // Moves this organism from coordinates (x,y) to (xNew,yNew).
        void movesTo(int xNew, int yNew);

        // Breeds a new organism at an adjacent cell. Tries to produce one new
        // organism in UP, DOWN, LEFT, or RIGHT cell (in that order).  Makes
        // sure not to breed off the grid.
        void breedAtAdjacentCell();

        // This organism's x position in the world.
        int x;

        // This organism's y position in the world.
        int y;

        // Has moved this turn?
        bool moved;

        // Number of ticks since breeding.
        int breedTicks;

        // A pointer to the world in which this organism lives.
        World* world;

		//Number of ticks counting the organsims moves
		int moveTicks;
    private:
};

#endif // ORGANISM_H
