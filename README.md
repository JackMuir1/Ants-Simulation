# Ants-Simulation
This project runs a 2D simulation of a predator and prey relationship over time in a console, with the addition of some fun elements. 

In this simulation, the prey are ants, and the predators are bugs. They live in a world composed of a 60×20 character grid of cells where only one organism may occupy a cell at a time. The grid is enclosed, so a organisms is not allowed to move off the edges of the grid. Time is simulated in discrete steps. Each critter performs some action every time step. 

If a predator comes in contact with an ant, it will eat it and take it's space. Predators and prey will reproduce at a constant rate. The world size, number of starting organisms, and breeding rates can be edited in the World class.

In addition, there are two other occupants of the world, the rock and the twin bug. The rock is an immovable part of the environment that cannot die, and serves the purpose of taking up space. When two twin bugs make contact with each other, they explode and kill everything one space away from them in all directions, including rocks. 

Users can add organisms through key presses explained in the console window with the simulation.

*Note: There is the capability to play a song during the simulatin under the file "BugSong.mp3", which was too large to be uploaded.
