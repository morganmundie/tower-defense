/**
 * \file TileCastle.h
 *
 * \author Jacob Frank
 * \author
 *
 *  Declares the Castle tile and its behvior
 */

#pragma once
#include "Tile.h"

 /**
  *  Implements a simple tile with tiles we can manipulate
  */
class CTileCastle : public CTile
{
public:

    CTileCastle(CTowersGame* game);

    ///  Default constructor (disabled)
    CTileCastle() = delete;

    ///  Copy constructor (disabled)
    CTileCastle(const CTileCastle&) = delete;

    ~CTileCastle();

    //virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept a visitor
    * @param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTileCastle(this); }

private:
};

