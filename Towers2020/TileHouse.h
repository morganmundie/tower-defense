/**
 * \file TileHouse.h
 *
 * \author Jacob Frank
 * \author
 *
 *  Declares the House tile and its behvior
 */

#pragma once
#include "Tile.h"

 /**
  *  Implements a simple tile with tiles we can manipulate
  */
class CTileHouse : public CTile
{
public:

    CTileHouse(CTowersGame* game);

    ///  Default constructor (disabled)
    CTileHouse() = delete;

    ///  Copy constructor (disabled)
    CTileHouse(const CTileHouse&) = delete;

    ~CTileHouse();

    //virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** 
     * Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileHouse(this); }

    /**
     * Method Disabled (no entities are drawn on trees)
     * @param graphics The graphics object
     */
    virtual void RenderEntities(Gdiplus::Graphics* graphics) {};
};

