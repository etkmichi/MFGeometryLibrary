/*
 * MFAdvancedBox.cpp
 *
 *  Created on: 08.01.2020
 *      Author: michl
 */

#include "MFAdvancedBox.h"

MFAdvancedBox::MFAdvancedBox(
		glm::vec3 upperLeft,
		glm::vec3 lowerLeft,
		glm::vec3 lowerRight,
		glm::vec3 upperRight,
		float depth) :
		MFAbstractGeometry("advanced box"){
	// TODO Auto-generated constructor stub

}
MFAdvancedBox::MFAdvancedBox(
		glm::vec3 frontUpperLeft,
		glm::vec3 frontLowerLeft,
		glm::vec3 frontLowerRight,
		glm::vec3 frontUpperRight,
		glm::vec3 backUpperLeft,
		glm::vec3 backLowerLeft,
		glm::vec3 backLowerRight,
		glm::vec3 backUpperRight) {
	// TODO Auto-generated constructor stub

}

MFAdvancedBox::~MFAdvancedBox() {
	// TODO Auto-generated destructor stub
}

//virtual bool calculateGeometryData(
//		std::vector<glm::vec3> &vertices,
//		std::vector<uint32_t> &indices){return false;};
///**
// * returns a void* which must be a btCollisionShape*.
// */
//virtual void* createCollisionShape(){return nullptr;};
//virtual void* getBulletCollisionShape(){return nullptr;};
