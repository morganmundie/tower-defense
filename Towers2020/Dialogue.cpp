/**
 * \file Dialogue.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Dialogue.h"

/** 
 * Constructor
 * @param game The game 
 */
CDialogue::CDialogue(CTowersGame* game) : CItem(game)
{
}

/** 
 * Method to load xml
 * @param node The node 
 */
void CDialogue::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
}

/// Destructor
CDialogue::~CDialogue()
{
}
