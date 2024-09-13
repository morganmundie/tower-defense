/**
 * \file TowerRings.h
 *
 * \author  Jacob Frank
 * \author 
 *
 *  Class that holds ring towers
 */

#pragma once
#include <math.h>
#include "Tower.h"


using namespace Gdiplus;

 /**
  *  Implements a simple tower we can manipulate
  */
class CTowerRings : public CTower
{
public:

    CTowerRings(CTowersGame* game);

    ///  Default constructor (disabled)
    CTowerRings() = delete;

    ///  Copy constructor (disabled)
    CTowerRings(const CTowerRings&) = delete;

    ~CTowerRings();

    void Update(double elapsed) override;

    /** Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerRings(this); }

    virtual void Draw(Gdiplus::Graphics* graphics);

    virtual void Attack() override;

    /** 
     * Function that controls/initiates the attack sequence of a tower. 
     * \return the radius of the ring
     */
    int GetRadius() const { return mCircleDiameter; }

    /**
     * Indicates if the tower is currently in its attack phase
     * @returns True if attacking, False if not.
     */
    bool GetAttacking() const { return mAttacking; }

    virtual void RenderEntities(Gdiplus::Graphics* graphics) override;


private:
    /// Time between fires
    double mTimeTofire = 5; 

    /// Offset of tower x,y to circle
    int mOffset = 5;   

    /// X of the upper left corner
    int mCircleX = 5;  

    /// Y of the upper left corner
    int mCircleY = 5;  

    /// Radius of circle
    int mCircleDiameter = 10;  

    /// Bool if drawing circle
    bool mDrawCircle = true;  

    /// Bool if attack is initiated
    bool mAttacking = false; 

    /// To save the elapsed val
    double mElapsed = 0;  

};

