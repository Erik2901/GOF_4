#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
protected:
	House* h;
public:
	~House() { delete h; }
	bool __fastcall isInside(double x1, double x2) const override;
	inline uint16_t GetScore() const override { return score; }
	virtual void createhome() {}
	virtual void createHouse() {}
	virtual void buildch() {}
	virtual void buildwallL() {}
	virtual void buildwallR() {}
	virtual void buildroof() {}
	virtual void buildfloor() {}
	virtual void buildwindow() {}
	virtual void buildpipe() {}
	virtual House* getHouse() { return h; }
	void Draw() const override;
	friend class HouseBuilderA;
	friend class HouseBuilderB;
private:
	char look[7][14];
	const uint16_t score = 40;
};

class HouseBuilderA : public House {
public:
	void createhome() { h = new House; };
	void buildch();
	void buildwallL();
	void buildwallR();
	void buildroof();
	void buildfloor();
};

class HouseBuilderB : public House {
public:
	void createhome() { h = new House; };
	void buildch();
	void buildwallL();
	void buildwallR();
	void buildroof();
	void buildfloor();
	void buildwindow();
	void buildpipe();
};

class HouseDirector {
public:
	House* createHouse(House& house);
};