#pragma once

class Humanoid;

class SurfaceEffect;

class Prop;

class Beast;

class Player;

class EntityVisitor {
public:
	virtual void visit(SurfaceEffect* surfaceEffect);
	virtual void visit(Beast* beast);
	virtual void visit(Humanoid* humanoid);
	virtual void visit(Prop* prop);
};
