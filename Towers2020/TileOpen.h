/**
 * \file TileOpen.h
 *
 * \author Jacob Frank
 * \author
 *
 *  Class that holds open tiles
 */

#pragma once
#include "Tile.h"

 /**
  *  Implements a simple tile with tiles we can manipulate
  */
class CTileOpen : public CTile
{
public:

    CTileOpen(CTowersGame* game);

    ///  Default constructor (disabled)
    CTileOpen() = delete;

    ///  Copy constructor (disabled)
    CTileOpen(const CTileOpen&) = delete;

    ~CTileOpen();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    
    /** Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileOpen(this); }

    /**
     * Method Disabled (no entities are drawn on trees)
     * @param graphics The graphics object
     */
    virtual void RenderEntities(Gdiplus::Graphics* graphics) {};
};

