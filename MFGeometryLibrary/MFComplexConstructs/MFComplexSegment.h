/*
 * MFComplexSegment.h
 *
 *  Created on: 03.01.2020
 *      Author: michl
 */

#ifndef MFCOMPLEXCONSTRUCTS_MFCOMPLEXSEGMENT_H_
#define MFCOMPLEXCONSTRUCTS_MFCOMPLEXSEGMENT_H_

#include <vector>

#include "../MFBaseGeometries/MFAbstractGeometry.h"

struct SubComponent{
	MFAbstractGeometry* pSubGeometry;
	glm::vec3 localPosition;
	glm::vec3 rotationAxis;
	float	rotationAngle;
	glm::vec3 scales;
};
class MFComplexSegment {
private:
	std::vector<MFAbstractGeometry*>
		*mp_vecGeometries;
	std::vector<void*>
		*mp_vecBulletCollisionShapes;
public:
	MFComplexSegment();
	virtual ~MFComplexSegment();
	std::vector<void*> getVecBulletCollisionShapes();
	std::vector<void*> createVecBulletCollisionShapes();
	std::vector<MFAbstractGeometry*>* getVecSubComponents();
};

#endif /* MFCOMPLEXCONSTRUCTS_MFCOMPLEXSEGMENT_H_ */
