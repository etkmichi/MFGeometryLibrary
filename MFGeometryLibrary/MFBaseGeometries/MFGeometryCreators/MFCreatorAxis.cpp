/*
 * MFCreateAxis.cpp
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#include "MFCreatorAxis.h"
#include "../MFAxis.h"

MFCreatorAxis::MFCreatorAxis() :
MFIGeometryCreator("Axis"){
}

MFCreatorAxis::~MFCreatorAxis() {
	// TODO Auto-generated destructor stub
}

MFAbstractGeometry* MFCreatorAxis::createGeometry(
		void* pDataSetup,
		uint32_t byteOffset){
	MFObject::printInfo("MFCreatorAxis::createGeometry");
	uint8_t* pData=(uint8_t*)pDataSetup;
	pData+=byteOffset;
	glm::vec3 param1=*((glm::vec3*)pData);
	pData+=sizeof(glm::vec3);
	float param2=*((float*)pData);
	MFAxis *pGeo=new MFAxis(param1,param2);
	return pGeo;
}
