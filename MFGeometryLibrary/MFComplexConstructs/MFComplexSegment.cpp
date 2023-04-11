/*
 * MFComplexSegment.cpp
 *
 *  Created on: 03.01.2020
 *      Author: michl
 */

#include "MFComplexSegment.h"

MFComplexSegment::MFComplexSegment() {
	mp_vecGeometries=new std::vector<MFAbstractGeometry*>();
	mp_vecBulletCollisionShapes=new std::vector<void*>();
}

MFComplexSegment::~MFComplexSegment() {
	delete mp_vecGeometries;
}

