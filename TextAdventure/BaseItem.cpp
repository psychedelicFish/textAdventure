#include "BaseItem.h"

BaseItem::BaseItem() 
{

}

BaseItem::BaseItem(std::string name, ItemType type)
{
	itemType = type;
	Name = name;
}
std::string BaseItem::GetName() 
{
	return Name;
}