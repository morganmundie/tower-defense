/**
 * \file Tile.h
 * 
 * \author Jacob Frank
 * \author
 * 
 *  Class that holds methods only for the the collection of Tiles
 */


#pragma once
#include "Item.h"

 /**
  *  Implements a simple tile with tiles we can manipulate
  */
class CTile : public CItem
{
public:

    CTile(CTowersGame* game);

    ///  Default constructor (disabled)
    CTile() = delete;

    void CTile::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    ///  Copy constructor (disabled)
    CTile(const CTile&) = delete;

    ~CTile();

private: 
};

