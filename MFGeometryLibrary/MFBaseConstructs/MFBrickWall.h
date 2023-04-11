/*
 * MFBrickWall.h
 *
 *  Created on: 05.01.2020
 *      Author: michl
 */

#ifndef MFBASECONSTRUCTS_MFBRICKWALL_H_
#define MFBASECONSTRUCTS_MFBRICKWALL_H_
#include <glm/glm.hpp>

#include "../MFComplexConstructs/MFComplexConstruct.h"
#include "../MFBaseGeometries/MFBrickGeometry.h"

class MFBrickWall: public MFComplexConstruct {
private:
	float
		m_length=10.0f,
		m_height=5.3f,
		m_brickHeight=0.6f,
		m_brickLength=0.9f,
		m_brickDepth=1.10f,
		m_minBrickDistance=0.2f;

	MFBrickGeometry
		*mp_baseBrickGeometry,
		*startBrickRow1,
		*startBrickRow2,
		*endBrickRow1,
		*endBrickRow2;

public:
	MFBrickWall();
	virtual ~MFBrickWall();
	void setBrickDimensions(float length,float heigth,float depth);
	void setWallDimensions(float length,float height);

	/*Implementation of virtual funcs*/
	bool createSubElements(std::vector<S_SubElement*>* pVecElements);

	/**
	 * This function adds the created geometries to segments.
	 * The segments are needed to split the construct into smaller parts, which can
	 * be handled more fast. F.e. if a sphere hits a wall, segments can be used to create
	 * the physics objects arround the hit point.
	 * @return
	 */
	bool createSegments(std::vector<MFComplexSegment*>* pVecSegs);

	/**/
	bool createDockingPoints(std::vector<MFDockingPoint*>* pVecSegs);


};

#endif /* MFBASECONSTRUCTS_MFBRICKWALL_H_ */
