/*
 * MFGeometryManager.cpp
 *
 *  Created on: 11.06.2020
 *      Author: michl
 */

#include "MFGeometryManager.h"
#include "MFBaseGeometries/MFSphere.h"
#include "MFBaseGeometries/MFBox.h"
#include "MFBaseGeometries/MFNoiseGeometry.h"
#include "MFBaseGeometries/MFAxis.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorBox.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorCapsule.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorCylinder.h"
#include <MFData/MFDataObject.h>
#include "MFBaseGeometries/MFCylinder.h"
#include "MFBaseGeometries/MFGeometryCreators/MFCreatorCone.h"
uint32_t
MFGeometryManager::indexSphere=0,
MFGeometryManager::indexAxis=1,
MFGeometryManager::indexBox=2,
MFGeometryManager::indexNoise=3,
MFGeometryManager::indexCylinder=4,
MFGeometryManager::indexCone=5,
MFGeometryManager::indexCapsule=6;
MFGeometryManager::MFGeometryManager() {
	mp_vecCreators=new std::vector<MFIGeometryCreator*>();
}

MFGeometryManager::~MFGeometryManager() {
}

void MFGeometryManager::initGeometryCreators(){
  if(initCreatorsDone)return;
  initCreatorsDone=true;
	mp_vecCreators->push_back(new MFCreatorSphere());
	mp_vecCreators->push_back(new MFCreatorAxis());
	mp_vecCreators->push_back(new MFCreatorBox());
	mp_vecCreators->push_back(new MFCreatorNoise());
  mp_vecCreators->push_back(new MFCreatorCylinder());
  mp_vecCreators->push_back(new MFCreatorCone());
  mp_vecCreators->push_back(new MFCreatorCapsule());
}

MFAbstractGeometry* MFGeometryManager::createSphere(float diameter){
	MFSphere *pGeo=new MFSphere(diameter);
	pGeo->getGeometrySetup()->clear();
	pGeo->getGeometrySetup()->addData(&indexSphere);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createBox(glm::vec3 param){
	MFBox *pGeo=new MFBox(param);
	pGeo->getGeometrySetup()->clear();
	pGeo->getGeometrySetup()->addData(&indexBox);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createAxis(glm::vec3 direction,float length){
	MFAxis *pGeo=new MFAxis(direction,length);
	pGeo->getGeometrySetup()->clear();
	pGeo->getGeometrySetup()->addData(&indexAxis);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createCylinder(float length,float radius){
  MFCylinder* pGeo=new MFCylinder(length,radius);
  pGeo->getGeometrySetup()->clear();
  pGeo->getGeometrySetup()->addData(&indexCylinder);
  pGeo->fillParameterSetup(pGeo->getGeometrySetup());
  return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createCone(float length,float radius){
  MFCone* pGeo=new MFCone(length,radius);
  pGeo->getGeometrySetup()->clear();
  pGeo->getGeometrySetup()->addData(&indexCone);
  pGeo->fillParameterSetup(pGeo->getGeometrySetup());
  return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createNoise(
		S_MFCalculationSetup *pCalcSetup,
		S_MFNoiseConfig *pNoiseConfig){
	MFNoiseGeometry *pGeo=new MFNoiseGeometry();
	pGeo->setNoiseConfig(pNoiseConfig);
	pGeo->setCalculationSetup(pCalcSetup);
	pGeo->getGeometrySetup()->clear();
	pGeo->getGeometrySetup()->addData(&indexNoise);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createCapsule(float length,float radius){
  MFCapsule *pGeo=new MFCapsule(length, radius);
  pGeo->getGeometrySetup()->clear();
  pGeo->getGeometrySetup()->addData(&indexCapsule);
  pGeo->fillParameterSetup(pGeo->getGeometrySetup());
  return pGeo;

}

MFAbstractGeometry* MFGeometryManager::createGeometry(
		MFStructurableDataSetup* pParameters){
	if(pParameters->getVecData()->size()==0){
		MFObject::printErr("MFGeometryManager::createGeometry - "
				"pParameters->getVecData()->size()==0!");
		return nullptr;
	}
	uint32_t creatorIndex=*((uint32_t*)pParameters->getVecData()->at(0)->getData());
	if(mp_vecCreators->size()<=creatorIndex){
		MFObject::printErr("MFGeometryManager::createGeometry - no creator for  "
				"index within pParameters! index="+std::to_string(creatorIndex));
		return nullptr;
	}
	MFAbstractGeometry* pGeo=mp_vecCreators->at(creatorIndex)->createGeometry(
			pParameters->getVecData()->at(1)->getData(), 0);
	MFDataObject* pData=new MFDataObject();
	pData->setData(new uint32_t());
	pData->setGuiType(E_GuiElement::GUI_TYPE_NUMBER_VIEW);
	pData->setDataType(E_DataType::DATA_TYPE_UINT32);
	pData->writeData(&creatorIndex, sizeof(uint32_t));
	pGeo->getGeometrySetup()->addData(pData);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

MFAbstractGeometry* MFGeometryManager::createGeometry(
		void* pParameters){
	if(pParameters==nullptr){
		MFObject::printErr("MFGeometryManager::createGeometry - "
				"pParameters->getVecData()->size()==0!");
		return nullptr;
	}
	uint32_t creatorIndex=*((uint32_t*)pParameters);
	if(mp_vecCreators->size()<=creatorIndex){
		MFObject::printErr("MFGeometryManager::createGeometry - no creator for  "
				"index within pParameters! index="+std::to_string(creatorIndex));
		return nullptr;
	}
	MFObject::printInfo("MFGeometryManager::createGeometry - creating geo with index "
			""+std::to_string(creatorIndex));
	MFAbstractGeometry* pGeo=mp_vecCreators->at(creatorIndex)->createGeometry(
			pParameters, sizeof(uint32_t));
	MFDataObject* pData=new MFDataObject();
	pData->setData(new uint32_t());
	pData->setGuiType(E_GuiElement::GUI_TYPE_NUMBER_VIEW);
	pData->setDataType(E_DataType::DATA_TYPE_UINT32);
	pData->writeData(&creatorIndex, sizeof(uint32_t));
	pGeo->getGeometrySetup()->addData(pData);
	pGeo->fillParameterSetup(pGeo->getGeometrySetup());
	return pGeo;
}

uint32_t MFGeometryManager::getIndexGeometry(MFAbstractGeometry* pGeo){
  MFStructurableDataSetup *pD=pGeo->getGeometrySetup();
  if(pD==nullptr)
    return 0xFFFFFFFF;
  if(pD->getVecData()->size()==0)
    return 0xFFFFFFFF;
  uint32_t index=*((uint32_t*)pD->getVecData()->at(0)->getData());
  return index;
}













