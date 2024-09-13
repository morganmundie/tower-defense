/**
 * \file Dialogue.h
 *
 * \author Jacob Frank
 *
 *
 * The parent class of all dialogue buttons.
 * Similar to the Tile or the Entity classes
 */

#pragma once
#include "Item.h"

/// Framework for all dialogue buttons
class CDialogue : public CItem
{
public:

    CDialogue(CTowersGame* game);

    ///  Default constructor (disabled)
    CDialogue() = delete;

    void CDialogue::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    ///  Copy constructor (disabled)
    CDialogue(const CDialogue&) = delete;

    //virtual bool HitTest(int x, int y) override { return false; }

    ~CDialogue();

private:
};