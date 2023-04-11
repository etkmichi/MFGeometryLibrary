/*
 * MFCreatorSphere.cpp
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#include "MFCreatorSphere.h"
#include "../MFSphere.h"

MFCreatorSphere::MFCreatorSphere() :
MFIGeometryCreator("Sphere"){
	// TODO Auto-generated constructor stub

}

MFCreatorSphere::~MFCreatorSphere() {
	// TODO Auto-generated destructor stub
}

MFAbstractGeometry* MFCreatorSphere::createGeometry(
		void* pDataSetup,
		uint32_t byteOffset){
	MFObject::printInfo("MFCreatorSphere::createGeometry");
	uint8_t* pData=(uint8_t*)pDataSetup;
	pData+=byteOffset;
	float diameter=*((float*)pData);
	MFSphere *pS=new MFSphere(diameter);
	return pS;
}
