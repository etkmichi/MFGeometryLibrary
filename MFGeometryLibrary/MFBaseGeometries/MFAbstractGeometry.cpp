/*
 * MFAbstractGeometry.cpp
 *
 *  Created on: 26.02.2020
 *      Author: michl
 */
#include <MFObjects/MFObject.h>
#include <cstring>
#include "MFAbstractGeometry.h"

bool MFAbstractGeometry::initGeometry(){
	if(m_isCreated)return true;
	if(calculateGeometryData(
			m_geometryData.m_vecVertices,
			m_geometryData.m_vecIndices,
			&m_geometryData.m_vecVertexColors,
			&m_geometryData.m_vecVertexNormals)){
		m_isCreated=true;
		return true;
	}
	MFObject::printErr("MFAbstractGeometry::createGeometry - "
			"failed to create geometry!");
	m_isCreated=false;
	return false;
}

bool MFAbstractGeometry::initGeometry(E_CreateGeometryFlag creationFlag){
	if(m_isCreated)return true;
	m_geometryData.m_creationFlag=creationFlag;
	switch(creationFlag){
	case E_CREATE_BY_COLLECTION:
		m_geometryData.mp_sharedObjectBuffer=new MFDataObjectBuffer();
		m_vertexDataCollection.setGeometryData(&m_geometryData);
		if(calculateGeometryData(&m_vertexDataCollection)){
			m_isCreated=true;
			return true;
		}
		MFObject::printErr("MFAbstractGeometry::createGeometry("
				"E_CREATE_BY_COLLECTION) - failed!");
		break;
	default:
		if(calculateGeometryData(
				m_geometryData.m_vecVertices,
				m_geometryData.m_vecIndices,
				&m_geometryData.m_vecVertexColors,
				&m_geometryData.m_vecVertexNormals)){
			m_isCreated=true;
			return true;
		}
		MFObject::printErr("MFAbstractGeometry::createGeometry - switch default "
				"failed to create geometry!");
	}

	m_isCreated=false;
	return false;
}

bool MFAbstractGeometry::serializeGeometrySetup(
		uint32_t &copiedBytes,
		uint8_t *pDst,
		uint32_t maxSize){
	MFStructurableDataSetup* pParamSetup=getGeometrySetup();
	uint32_t setupSize=pParamSetup->getStructureSize();
	if(maxSize < (setupSize+4) && maxSize!=0){
		MFObject::printErr("MFAbstractGeometry::serializeGeometrySetup - not"
				" enough space for copiing data!");
		copiedBytes=0;
		return false;
	}
	memcpy(pDst,&setupSize,sizeof(uint32_t));
	pDst+=sizeof(uint32_t);/*size of setup*/
	copiedBytes=sizeof(uint32_t);
	if(!pParamSetup->copyDataFromStructure(pDst,0)){
		MFObject::printErr("MFNetClientConnectDispatchTask::sendObjectSetup - "
				"failed to copy object init data!");
		setupSize=0;
		pDst-=sizeof(uint32_t);
		memcpy(pDst,&setupSize,sizeof(uint32_t));
		pDst+=sizeof(uint32_t);
		return false;
	}else{
		copiedBytes+=setupSize;
	}
	return true;
}

void* MFAbstractGeometry::createSerializedGeometrySetup(uint32_t &byteSize){
  uint32_t bufferSize=getSerializedByteSize();
  byteSize=bufferSize;
  void *data=malloc(bufferSize);
  uint32_t ignore=0;
  if(!serializeGeometrySetup(ignore,(uint8_t*)data,bufferSize)){
    free(data);
    MFObject::printErr("MFAbstractGeometry::createSerializedGeometrySetup - failed!");
    return nullptr;
  }
  return data;
}

uint32_t MFAbstractGeometry::getSerializedByteSize(){
  return getGeometrySetup()->getStructureSize()+4;
}
