/*
 * MFComplexConstruct.h
 *
 *  Created on: 28.12.2019
 *      Author: michl
 */

#ifndef MFCOMPLEXCONSTRUCTS_MFCOMPLEXCONSTRUCT_H_
#define MFCOMPLEXCONSTRUCTS_MFCOMPLEXCONSTRUCT_H_
#include <vector>

#include "MFComplexSegment.h"
#include "../MFDockingSystem/MFDockingPoint.h"
struct S_SubElement{
	MFAbstractGeometry* pGeo=nullptr;
	MFComplexSegment* parentSegment=nullptr;
	glm::vec3 localTransformation;
	MFAbstractGeometry* getGeometry(){return pGeo;};
};
class MFComplexConstruct {
private:
	std::vector<S_SubElement*>
		*mp_vecSubElements;
	std::vector<MFComplexSegment*>
		*mp_vecSegments;
	std::vector<MFDockingPoint*>
		*mp_vecDockingPoints;

public:
	MFComplexConstruct();
	virtual ~MFComplexConstruct();
	/**
	 * This function will call all neccessary functions to create the construct.
	 * @return
	 */
	bool createConstruct();

	/**/
	virtual bool createSubElements(std::vector<S_SubElement*>* pVecElements){
		return false;
	};

	/**
	 * This function adds the created geometries to segments.
	 * The segments are needed to split the construct into smaller parts, which can
	 * be handled more fast. F.e. if a sphere hits a wall, segments can be used to create
	 * the physics objects arround the hit point.
	 * @return
	 */
	virtual bool createSegments(std::vector<MFComplexSegment*>* pVecSegs){
		return false;
	};

	/**/
	virtual bool createDockingPoints(std::vector<MFDockingPoint*>* pVecSegs){
		return false;
	};

	std::vector<S_SubElement*>* getVecElements(){return mp_vecSubElements;};
	std::vector<MFComplexSegment*>* getVecSegments(){return mp_vecSegments;};
	std::vector<MFDockingPoint*>* getVecDockingPoints(){return mp_vecDockingPoints;};
	//TODO get simple physics body and get segment release energy (if energy is
	//surpassed, the segment will be added to physics simulation, if segment energy is
	//surpassed, the segment will split up into ist sub components).
	//

};

#endif /* MFCOMPLEXCONSTRUCTS_MFCOMPLEXCONSTRUCT_H_ */
