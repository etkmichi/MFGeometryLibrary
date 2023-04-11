/*
 * MFCreatorNoise.cpp
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#include "MFCreatorNoise.h"
#include "../MFNoiseGeometry.h"
#include "../../MFNoise/MFNoiseSetup.h"
#include "../../MFNoise/MFNoiseStructs.h"

MFCreatorNoise::MFCreatorNoise() :
MFIGeometryCreator("Noise"){
	// TODO Auto-generated constructor stub

}

MFCreatorNoise::~MFCreatorNoise() {
	// TODO Auto-generated destructor stub
}

MFAbstractGeometry* MFCreatorNoise::createGeometry(
		void* pDataSetup,
		uint32_t byteOffset){
	MFObject::printInfo("MFCreatorNoise::createGeometry");
	uint8_t* pData=(uint8_t*)pDataSetup;
	pData+=byteOffset;

	S_MFNoiseConfig *pS=new S_MFNoiseConfig();
	*pS=*((S_MFNoiseConfig*)pData);

	MFNoiseGeometry *pGeo=new MFNoiseGeometry();
	pGeo->setNoiseConfig(pS);
	return pGeo;
}
