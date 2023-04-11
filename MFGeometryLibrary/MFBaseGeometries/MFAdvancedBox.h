/*
 * MFAdvancedBox.h
 *
 *  Created on: 08.01.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFADVANCEDBOX_H_
#define MFBASEGEOMETRIES_MFADVANCEDBOX_H_
#include "MFAbstractGeometry.h"
class MFAdvancedBox:MFAbstractGeometry{
public:
	MFAdvancedBox(
			glm::vec3 upperLeft,
			glm::vec3 lowerLeft,
			glm::vec3 lowerRight,
			glm::vec3 upperRight,
			float depth);
	MFAdvancedBox(
				glm::vec3 frontUpperLeft,
				glm::vec3 frontLowerLeft,
				glm::vec3 frontLowerRight,
				glm::vec3 frontUpperRight,
				glm::vec3 backUpperLeft,
				glm::vec3 backLowerLeft,
				glm::vec3 backLowerRight,
				glm::vec3 backUpperRight);
	virtual ~MFAdvancedBox();
};

#endif /* MFBASEGEOMETRIES_MFADVANCEDBOX_H_ */
