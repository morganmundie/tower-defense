/**
 * \file TileTrees.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TileTrees.h"

using namespace std;

/** 
 * Constructor
 * @param item The Towers game 
 */
CTileTrees::CTileTrees(CTowersGame* item) : CTile(item)
{
}

/// Destructor
CTileTrees::~CTileTrees()
{
}

/**
 * @brief Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void CTileTrees::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // For storing any tree-specific attributes

    CTile::XmlLoad(node);
}