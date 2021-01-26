# open-world-rpg

A continuous work in progress; early prototype.

Written in C++ using lightweight multimedia library SFML.

**Demos**
- Latest from Jan 2020, showing world generation: https://www.youtube.com/watch?v=lamWDDJ_wLc
- Old version from May 2020, showing very basic gameplay interactions: https://www.youtube.com/watch?v=0c8xLTAbcqw

A WIP 2D game engine, intending to help create procedurally generated games. I've spent most of my time on the world generation and animation system, which supports a variety of animation types. The world is generated procedurally as the player moves, thanks to a worker thread that offloads the expensive generation computation from the main thread, which handles everything else. Each world 'chunk' is generated using a pipeline of algorithms that allocate environments, tiles, and entities. Perlin noise and hash functions are used throughout for the procedural aspects.

Effort has been put into making the terrain look less blocky, as the ground is represented by square tiles. This notably involved the development of an algorithm that allocates special border tiles when two environments collide (eg. water and dirt), to make the landscape more seamless. 

I'm currently working on a collision system and improving the prop generation. 
