//============================================
// Name        : Mgr.h 
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#ifndef MGR_H_
#define MGR_H_

class Engine;

class Mgr {
public:
	Engine *engine;

	Mgr(Engine *eng);
	virtual ~Mgr();

	virtual void tick(float dt);
	virtual void init();
	virtual void load_level();
	virtual void stop();
};



#endif /* MGR_H_ */