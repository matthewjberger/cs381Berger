//============================================
// Name        : EntityMgr.h
// Author      : Matthew J. Berger
// Email       : matthewberger@nevada.unr.edu
//============================================

#include "mgr.h"

#ifndef ENTITYMGR_H_
#define ENTITYMGR_H_

class EntityMgr : public Mgr {
public:

	EntityMgr(Engine *eng) : Mgr(eng) {}

	void tick(float dt);
	void init();
	void load_level();
	void stop();
};



#endif /* ENTITYMGR_H_ */