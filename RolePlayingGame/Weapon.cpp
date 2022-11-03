#include "pch.h"
#include "Weapon.h"

Weapon::Weapon(int id):baseItem(id)
{
	SetPos(1140, 660);
	prop.SetWidth(50);
	prop.SetHeight(50);
	prop.SetMaxHP(-1);
	sprite.SetImages("weapon",1);

	sprite.SetStatOffset({ -125,-125,-120,-100 });
	sprite.Set_px({ 5,5,5,0 });
}
