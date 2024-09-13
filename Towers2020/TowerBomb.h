/**
 * \file TowerBomb.h
 *
 * \author
 * \author
 *
 *  Class that holds bomb towers
 */

#pragma once
#include "Tower.h"
#include "BombCounter.h"
#include "TowersGame.h"

 /**
  *  Implements a simple tower we can manipulate
  */
class CTowerBomb : public CTower
{
public:

	CTowerBomb(CTowersGame* game);

	///  Default constructor (disabled)
	CTowerBomb() = delete;

    ///  Copy constructor (disabled)
    CTowerBomb(const CTowerBomb&) = delete;

    ~CTowerBomb();

    virtual void Attack() override;

    void Update(double elapsed) override;

    /** 
     * Accept a visitor
     * @param visitor The visitor we accept 
     */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitTowerBomb(this); }

    virtual void Draw(Gdiplus::Graphics* graphics);

    /**
     * Method to set the time to explode
     * @param time The time to explode 
     */
    void SetTimeToExplode(int time) { mTimeToExplode = time;  }

    /**
     * Method to return status of mBlownUp
     * @return bool of mBlownUp 
     */
    bool GetBlownUp() { return mBlownUp;  }

    virtual void RenderEntities(Gdiplus::Graphics* graphics) override;


private:
    /// The time count down to explosion
	double mTimeToExplode = 0;  

    /// Offset of tower x,y to circle
	int mOffset = 5;

    /// X of the upper left corner
	int mCircleX = 5;  

    /// Y of the upper left corner
	int mCircleY = 5; 

    /// Radius of circle
	int mBombDiameter = 10;  

    /// The explosion duration of the bomb
	double mExplosionDuration = .25;

    /// Bool if drawing circle
	bool mDrawCircle = true;  

    /// Bool if bomb is blown up or not
	bool mBlownUp = false;    

	/// Determines if the bomb explosion should be shown or not
	bool mShow = false;
};
