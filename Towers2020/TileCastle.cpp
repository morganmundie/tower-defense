/**
 * \file TileCastle.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TileCastle.h"

using namespace std;

/** 
 * Constructor
 * @param item The Towers game 
 */
CTileCastle::CTileCastle(CTowersGame* item) : CTile(item)
{
}

///  Default destructor
CTileCastle::~CTileCastle()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTileCastle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing any castleTile-specific attributes

    CTile::XmlLoad(node);
}