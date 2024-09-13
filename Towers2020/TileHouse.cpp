/**
 * \file TileHouse.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TileHouse.h"

using namespace std;

/** 
 * Constructor
 * @param item The Towers game 
 */
CTileHouse::CTileHouse(CTowersGame* item) : CTile(item)
{
}

///  Default desstructor
CTileHouse::~CTileHouse()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTileHouse::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing any houseTile-specific attributes

    CTile::XmlLoad(node);
}