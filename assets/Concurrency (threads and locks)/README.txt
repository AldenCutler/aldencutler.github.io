Project 2: Synchronization and Concurrency 
=========================================
This is the work of Alden Cutler and Nia Junod 

Our task for this project was to develop a multi-threaded simulator for Worcester Gompei Park. 
The park is used by various sports teams including baseball, football, and rugby. 
The primary objective was to ensure that all teams could use the park simultaneously while ensuring fair performance opportunities for everyone. 
The main challenge was to maximize parallelism without compromising on fairness.


To build the project, run the 'make' command in the terminal:
make

To run the project you can use the following command:
./project2

The simulation creates threads for each sport, coordinating their games based on specific guidelines. 

The main.c file has the main function and core of the simulation, while the seed.h file has the function to 
generate and read the random seed for the simulation. The sports.h file includes the constants, the function prototypes, and the data 
structures. 

=========================================
Issues: 

1. We ran into a few issues while implementing the rugby threads. 
    - Our first hurdle was ensuring that rugby players could join ongoing games.
        - Since rugby players join in pairs, we tried a few different ways to let them join that would cause some form of deadlock.
        - The threads would either be waiting for each other to signal to join, or they would be waiting for someone to start a game that never would.
        - We eventually solved this using a mutex and a condition variable to signal when a game was starting.
    - The second issue we ran into was ensuring that the rugby players would not join a game that was already full.
        - The check that we implemented seemed logically sound, but it would either cause a deadlock or allow more players to join than the game could handle.
        - We eventually solved this by making sure the signaling thread was the only one that could change the game state.
    - After these two issues, we ran into an issue where the rugby players would somehow affect the field state in other games.
        - This was probably the most confusing issue we ran into, as we could not figure out how the rugby players were affecting the other games.
        - We eventually solved this by switching the order that the threads would get the locks and signals, and that seemed to fix the issue.
    - The last issue we ran into was that we didn't know how to get the rugby players to leave in pairs as they joined.
        - We weren't sure how we could somehow pass a sleep time to each thread, so the solution we implemented is similar to what baseball and football do,
          where the thread that starts the game chooses a random game time, then once that time is up, the thread signals to end the game, removing all 
          the players from the field.
        - This solution isn't ideal but we couldn't figure out an easier way to do it.

2. You also might notice that this is very different from our checkpoint. We were running into issue after issue with all the different players, which eventually
led us to think about our code logically. We noticed a few very large logic issues that had to to with the way we implemented the system. Fixing these issues would
have involved such a major refactor that we decided that it would probably take us less time to learn from our mistakes and start over than to try and fix the 
issues we were running into. I think this was overall very beneficial to us, as we were able to implement a much better system in the end that is much more
understandable and less prone to issues.

