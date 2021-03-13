#pragma once

class Path;

class ChunkManager;

class PathManager {
public:
    // May edit the current point to ensure there are no collisions
    void processCurrentPoint(Path * path);
private:
    ChunkManager * chunkManager;
};




