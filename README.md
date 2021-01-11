# open-world-rpg

A continuous WIP; early prototype.

Written in C++ using the lightweight multimedia library SFML (provides simple abstractions for handling windows, sound, and some graphics).

**Demos**

Most recent demo (Jan 2021) featuring world generation system w/ a couple of sample props and environments (I need really need to add more assets): https://www.youtube.com/watch?v=lamWDDJ_wLc&

Old demo from May 2020 featuring very basic item/enemy gameplay interactions: https://www.youtube.com/watch?v=0c8xLTAbcqw

**Details**

Notable engine features include a world generation system that creates a near-infinite open world and an extensible animation system supporting a variety of animation types. World chunks are generated around the player using a worker thread (and mostly wait-free synchronization) to offload world generation/loading-related computation from the main thread that handles everything else. 

The world gen handled by this worker thread is multi-layered: 
1. A matrix of temporary environmental cells (eg. dirt, water) is filled using the improved perlin noise algo [+ extra hashing for tile variety within environments]
2. This matrix is processed by an algorithm that selects special border units for cells that collide with a different environment type than its own - this is critical in enabling smooth/natural transitions between different environments. This algorithm was quite tricky, as chunks of the world are generated separate from one another, so corner cells followed by cells that are on the boundary sides of the matrix are processed first to create smooth transitions between chunks.
3. Lastly these temporary cells are converted to tiles with sprites based on another intermediate representation contained in the previous version of the cell [this is to support  generation of tile sprites that are drawn to take up multiple tiles (to make the world look less blocky), but are eventually represented as a single tile]
4. Now, a tile matrix is complete and it's passed to the prop generator, which has an algorithm that generates props based on sequences of hash fn calls around the tile map.
The nice thing about these systems is that they're designed to scale w/ a flexible number of assets, so I just have to create them; their addition to the program doesn't require too much code, whether it's a new environment tile type, props, or animations [this is ofc also facilitated thanks to the limited interactivity of the world]

Currently working on improving the prop generation algorithm to be smarter and overhauling the chunk management system to use an LRU cache and a dynamic spatial partition for optimized rendering and collision detection.
