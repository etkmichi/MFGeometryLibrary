/*
 * MFGeometryData.h
 *
 *  Created on: 21.02.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYDATA_H_
#define MFBASEGEOMETRIES_MFGEOMETRYDATA_H_

#include <vector>
#include <glm/glm.hpp>
#include <MFData/MFDataObjectBuffer.h>
#include <MFData/MFDataObject.h>
#include "../MFVertexClasses/MFAdaptableVertex.h"

enum E_CreateGeometryFlag{
	E_CREATE_BY_COLLECTION,
	E_CREATE_BY_DEFAULT
};
/**
 * This class provides data for geometries.
 */
class MFGeometryData {
public:
	std::vector<glm::vec3>
		m_vecVertices,
		m_vecVertexNormals;
	std::vector<uint32_t>
		m_vecIndices,
		m_vecVertexColors;
	std::vector<MFAdaptableVertex*>
		m_vecAdaptableVertex;
	MFDataObjectBuffer
		*mp_sharedObjectBuffer=nullptr;
	E_CreateGeometryFlag
		m_creationFlag=E_CREATE_BY_DEFAULT;

	MFGeometryData();
	virtual ~MFGeometryData();
	void clear(){
	  m_vecAdaptableVertex.clear();
	  m_vecVertices.clear();
	  m_vecVertexNormals.clear();
    m_vecIndices.clear();
    m_vecVertexColors.clear();
	}
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYDATA_H_ */
