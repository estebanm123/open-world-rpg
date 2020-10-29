# open-world-rpg

A continuous work in progress; early prototype.

Written in C++ using the lightweight SFML framework.

Currently features an infinite procedurally generated world. Chunks are generated around the player using one worker thread (and mostly wait-free synchronization) to offload computation from the main thread that handles everything else currently. 

Right now, I'm working on overhauling the tile generation system to add support for more complex tile groups and, most importantly, to allow for the introduction of a noise algorithm/ hash function, which will make make different tile types appear more natural.

Here's a demo from May 2020: https://www.youtube.com/watch?v=0c8xLTAbcqw
