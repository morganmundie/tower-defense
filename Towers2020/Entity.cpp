/**
 * \file Entity.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Entity.h"

using namespace std;
using namespace Gdiplus;

/// Maximum speed in the X direction in pixels per second 
const double MaxSpeedX = 50;

/** Constructor
 * @param game The game this is a member of
 */
CEntity::CEntity(CTowersGame* game) : CItem(game)
{
    mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
}

/// Default destructor
CEntity::~CEntity()
{
}

/**
* Load function DISABLED
*/
//void CEntity::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
//{
//    CItem::XmlLoad(node);
//   mSpeedX = node->GetAttributeDoubleValue(L"xSpeed", 0);
//   mSpeedY = node->GetAttributeDoubleValue(L"ySpeed", 0);
//}

/** Set the speed of this balloon from some range
 *
 * @param minX Minimum X value
 * @param maxX Maximum X value
 */
void CEntity::SetSpeed(double minX, double maxX)
{
    mSpeedX = minX + ((double)rand() / RAND_MAX) * (maxX - minX);
}