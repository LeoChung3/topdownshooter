#pragma once
#include "MaterialManager.h"
class shelter
{
private:
	MaterialManager* matmanager;
public:
	void craftItem();

	shelter(MaterialManager* matmanage)

	{
		matmanager = matmanage;
	}
};