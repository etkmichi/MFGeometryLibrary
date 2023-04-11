/*
 * MFComplexConstruct.cpp
 *
 *  Created on: 28.12.2019
 *      Author: michl
 */
#include <MFObjects/MFObject.h>
#include "MFComplexConstruct.h"


MFComplexConstruct::MFComplexConstruct() {
	mp_vecSubElements = new std::vector<S_SubElement*>();
	mp_vecSegments = new std::vector<MFComplexSegment*>();
	mp_vecDockingPoints = new std::vector<MFDockingPoint*>();
}

MFComplexConstruct::~MFComplexConstruct() {
	if(mp_vecSubElements!=nullptr){
		delete mp_vecSubElements;
	}

	if(mp_vecSegments!=nullptr){
		delete mp_vecSegments;
	}

	if(mp_vecDockingPoints!=nullptr){
		delete mp_vecDockingPoints;
	}
}

bool MFComplexConstruct::createConstruct(){
	if(!createSubElements(mp_vecSubElements)){
		MFObject::printErr("MFComplexConstruct::createGeometries() - failed!");
		return false;
	}
	if(!createSegments(mp_vecSegments)){
		MFObject::printErr("MFComplexConstruct::createConstruct() - failed!");
		return false;
	}
	if(!createDockingPoints(mp_vecDockingPoints)){
		MFObject::printErr("MFComplexConstruct::createDockingPoints() - failed!");
		return false;
	}
	return true;
}
