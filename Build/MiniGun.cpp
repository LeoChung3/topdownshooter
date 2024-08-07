#include "MiniGun.h"

void MiniGun::craftItem()
{
	for (int i = 0; i < matmanager->returnMaterials().size(); i++)
	{
		for (auto it = craftingRequirements.rbegin(); it != craftingRequirements.rend(); it++)
		{
			if (matmanager->returnMaterials()[i].getName() == it->first)
			{
				if (matmanager->returnMaterials()[i].numPickedUp >= it->second)
				{
					matmanager->MiniGunEnough(i);
					//matmanager->returnMaterials()[i].craftMiniGum = true;
					cout << "madetrue" << endl;
				}
				else
				{
					matmanager->MinigunNotEnough(i);
					cout << "madefalse" << endl;
				}
			}
		}
	}
	canCraft = true;
	for (int i = 0; i < matmanager->returnMaterials().size(); i++)
	{
		if (matmanager->returnMaterials()[i].craftMiniGum == false)
		{
			cout << matmanager->returnMaterials()[i].getName() << endl;
			canCraft = false;
			break;
		}

	}

	if (canCraft == false) 
	{
		cout << "cannot make minigun" << endl;
	}
	if(canCraft == true)
	{
		if (!inInventory)
		{
			cout << "can make minigun" << endl;
			inInventory = true;
			for (int i = 0; i < matmanager->returnMaterials().size(); i++)
			{
				for (auto it = craftingRequirements.rbegin(); it != craftingRequirements.rend(); it++)
				{
					if (matmanager->returnMaterials()[i].getName() == it->first)
					{
						matmanager->removeMaterials(i, it->second);
					}
				}
			}
		}
	}
		/*if (matmanager->returnMaterials()[i].getName() == "metalTube")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 2)
			{

				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}
		if (matmanager->returnMaterials()[i].getName() == "baseGun")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 1)
			{
				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}
		if (matmanager->returnMaterials()[i].getName() == "Welder")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 1)
			{
				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}
		if (matmanager->returnMaterials()[i].getName() == "metalChair")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 1)
			{
				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}
		if (matmanager->returnMaterials()[i].getName() == "drill")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 1)
			{
				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}
		if (matmanager->returnMaterials()[i].getName() == "largeBoreAmmo")
		{
			if (matmanager->returnMaterials()[i].numPickedUp >= 5)
			{
				matmanager->returnMaterials()[i].craftMiniGum = true;
			}
		}*/

	

		/*if (largeBoreAmmo.craftMiniGum && drill.craftMiniGum && metalChair.craftMiniGum && Welder.craftMiniGum && baseGun.craftMiniGum && metalTube.craftMiniGum)
		{
			cout << "mini gun craftable" << endl;
		}
		else {
			cout << "mini gun not craftable" << endl;
		}*/
	
}

bool MiniGun::checkInInventory()
{
	return inInventory;
}
