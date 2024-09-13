/**
 * \file DiagTimer.h
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 *
 *
 * A class which represents the timer object that
   is made on level creation starts the level
 *
 */

#pragma once
#include "Dialogue.h"

/// Represents the timer object dialogue box
class CDiagTimer : public CDialogue
{
public:

    CDiagTimer(CTowersGame* game);

    ///  Default constructor (disabled)
    CDiagTimer() = delete;

    ///  Copy constructor (disabled)
    CDiagTimer(const CDiagTimer&) = delete;

    ~CDiagTimer();

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** 
     * Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitDiagTimer(this); }

    void SetLevelNumber(int num);

    /** Method Disabled (no entities are drawn on ship entities)
     * @param graphics The graphics 
     */
    virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

private:

    /// The current level number
    int mLevelNum = 0; 
};