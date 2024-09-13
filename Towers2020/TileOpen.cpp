/**
 * \file TileOpen.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TileOpen.h"

using namespace std;

/** 
 * Constructor
 * @param item The Towers game 
 */
CTileOpen::CTileOpen(CTowersGame* item) : CTile(item)
{
}

///  Default destructor
CTileOpen::~CTileOpen()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTileOpen::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing any openTile-specific attributes

    CTile::XmlLoad(node);
}
