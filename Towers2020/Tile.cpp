/**
 * \file Tile.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Tile.h"

using namespace std;
using namespace Gdiplus;

/** 
 * Constructor
 * @param game The Towers game 
 */
CTile::CTile(CTowersGame* game) : CItem(game)
{
}

/// Default destructor
CTile::~CTile()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing attributes in the node pertaining to all tiles

    CItem::XmlLoad(node);
}