/*
 * MFCreatorBox.cpp
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#include "MFCreatorBox.h"
#include "../MFBox.h"
#include <glm/glm.hpp>

MFCreatorBox::MFCreatorBox():
MFIGeometryCreator("Box") {
	// TODO Auto-generated constructor stub

}

MFCreatorBox::~MFCreatorBox() {
	// TODO Auto-generated destructor stub
}

MFAbstractGeometry* MFCreatorBox::createGeometry(
		void* pDataSetup,
		uint32_t byteOffset){
	MFObject::printInfo("MFCreatorBox::createGeometry");
	uint8_t* pData=(uint8_t*)pDataSetup;
	pData+=byteOffset;
	glm::vec3 param1=*((glm::vec3*)pData);
	pData+=sizeof(glm::vec3);
	MFBox *pGeo=new MFBox(param1);
	return pGeo;
}

MFAbstractGeometry* MFCreatorBox::createGeometry(
		MFStructurableDataSetup* pDataSetup,
		uint32_t dataIndexOffset){
	MFObject::printInfo("MFCreatorBox::createGeometry");
	uint8_t* pData=(uint8_t*)pDataSetup->getVecData()->at(dataIndexOffset)->getData();
	glm::vec3 param1=*((glm::vec3*)pData);
	pData+=sizeof(glm::vec3);
	MFBox *pGeo=new MFBox(param1);
	return pGeo;
}
