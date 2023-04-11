/*
 * MFBrickGeometry.h
 *
 *  Created on: 06.01.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFBRICKGEOMETRY_H_
#define MFBASEGEOMETRIES_MFBRICKGEOMETRY_H_

#include "MFBox.h"
//TODO create geometry of boxes for the Ger:Mörtel (Extra boxes with color gray on
//predefined sides. The gray boxes represent the glue which is sticking other bricks
//to this one. Implement as MFDockingPoint with area setup. Setup physics to handle all
//bricks as one if the min energy of the glue is not surpassed...
class MFBrickGeometry : public MFBox {
public:
	MFBrickGeometry(glm::vec3 extent);
	virtual ~MFBrickGeometry();
	float getLowestZValue(){return -m_boxExtents.z/2.0f;};
	float getLowestYValue(){return -m_boxExtents.y/2.0f;};
	float getLowestXValue(){return -m_boxExtents.x/2.0f;};
};

#endif /* MFBASEGEOMETRIES_MFBRICKGEOMETRY_H_ */
