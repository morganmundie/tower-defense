/**
 * \file TileRoad.h
 *
 * \author Jacob Frank
 * \author
 *
 *  Declares the Trees tile and its behvior
 */

#pragma once
#include "Tile.h"

 /**
  *  Implements a simple tile we can manipulate
  */
class CTileTrees : public CTile
{
public:

    CTileTrees(CTowersGame* game);

    ///  Default constructor (disabled)
    CTileTrees() = delete;

    ///  Copy constructor (disabled)
    CTileTrees(const CTileTrees&) = delete;

    ~CTileTrees();

    //virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** 
     * Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileTrees(this); }

    /**
     * Method Disabled (no entities are drawn on trees)
     * @param graphics The graphics object
     */
    virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

};

