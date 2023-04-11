/*
 * MFVertexDataCollection.h
 *
 *  Created on: 16.12.2019
 *      Author: michl
 */

#ifndef MFVERTEXCLASSES_MFVERTEXDATACOLLECTION_H_
#define MFVERTEXCLASSES_MFVERTEXDATACOLLECTION_H_

#include <vector>
#include <glm/glm.hpp>
#include <MFData/MFDataObjectBuffer.h>

#include "../MFBaseGeometries/MFGeometryData.h"
#include "MFVertexDataOptimizer.h"
#include "MFAdaptableVertex.h"

/**
 * This class provides functionality for automatically creating data. The automation
 * can be specified by the use functions.
 */
class MFVertexDataCollection {
private:
protected:
	glm::mat4x4
		m_dummyData;
	MFVertexDataOptimizer
		*mp_vertexOperator;
	uint32_t
		m_vertexCount=0,
		m_vertexByteSize=0;

	MFGeometryData
		*mp_geometryData=nullptr;
	MFDataObjectBuffer
		*mp_sharedDataBuffer;
	std::vector<glm::vec3>
		*mp_vecVertices,
		*mp_vecNormals;

	std::vector<uint8_t>
		*mp_vec8BitNormalIndices;

	std::vector<uint16_t>
		*mp_vec16BitNormalIndices;

	std::vector<uint32_t>
		*mp_vec32BitNormalIndices,
		*mp_vecIndices;

	bool
		m_deleteNormals=false,
		m_use8BitIndexedNormals=false,
		m_use16BitIndexedNormals=false,
		m_use32BitIndexedNormals=false,
		m_use3DNormals=false,
		m_useSharedBuffer=true,//Not used!
		m_isCreated=false;

	std::vector<MFAdaptableVertex*>
		*mp_vecComplexVertices;
	MFAdaptableVertex
		*mp_dummyVertex;

public:
	MFVertexDataCollection();
	MFVertexDataCollection(MFGeometryData* pGeoData);
	virtual ~MFVertexDataCollection();

	/**
	 * If no normals are available, this function uses the
	 * vertex operator to calculate normals.
	 * Its possible that the normal calculation fails and this function returns false.
	 * If false is returned, further usage should be canceled!
	 * @return true if normals were calculated, false if sth failed. If false is returned,
	 * further usage of the data should be canceled!
	 */
	bool initNormals();
	void use8BitIndexedNormals(bool enable){m_use8BitIndexedNormals=enable;};
	void use16BitIndexedNormals(bool enable){m_use16BitIndexedNormals=enable;};
	void use32BitIndexedNormals(bool enable){m_use32BitIndexedNormals=enable;};
	void use3DVecNormals(bool enable){m_use3DNormals=enable;};
	//TODO useVertexIndices function - automatically create indices!
	bool createCollection();//TODO set use... and iterate over vec<AdaptableVert>
	bool create8BitNormals();
	bool create16BitNormals();
	bool create32BitNormals();
	void setVertexCount(uint32_t vertCount){m_vertexCount=vertCount;};
	uint32_t getVertexCount(){return m_vertexCount;};
	void setSharedBuffer(MFDataObjectBuffer* buffer){mp_sharedDataBuffer=buffer;};
	MFDataObjectBuffer* getSharedBuffer(){return mp_sharedDataBuffer;};

	std::vector<glm::vec3>* getVertices(){return mp_vecVertices;};
	std::vector<uint32_t>* getVertexIndices(){return mp_vecIndices;};
	std::vector<glm::vec3>* get3DVecNormals(){return mp_vecNormals;};
	std::vector<uint8_t>* get8BitNormalIndices(){return mp_vec8BitNormalIndices;};
	std::vector<uint16_t>* get16BitNormalIndices(){return mp_vec16BitNormalIndices;};
	std::vector<uint32_t>* get32BitNormalIndices(){return mp_vec32BitNormalIndices;};

	MFVertexDataOptimizer* getVertexOperator(){return mp_vertexOperator;};

	void setupComplexVertex(MFAdaptableVertex* pComplexVertex);
	void setupComplexVertices();
	void setGeometryData(MFGeometryData* pGeoData);

	std::vector<MFAdaptableVertex*>* getComplexVertices(){return mp_vecComplexVertices;};
	MFAdaptableVertex* getNextComplexVertex();
	MFAdaptableVertex* getDummyVertex();



	/**
	 * This function uses the given setup of this object to create the
	 * base MFAdaptableVertex object. The create object will be filled with
	 * data at dataIndex (uses the data from vertex related vectors -> vertices
	 * normals, normal indices, maybe color...).
	 */
	MFAdaptableVertex* createComplexVertex(uint32_t dataIndex);

	/**
	 * This function uses the given setup of this object to create the
	 * base MFAdaptableVertex object. The return object doesn't hold any valid data.
	 * The data of the adaptable vertex will be written to the MFDataObjectBuffer if
	 * set.
	 */
	MFAdaptableVertex* createComplexVertex();

	/**
	 * If derived from a subclass an advanced MFAdaptableVertex can be returned.
	 * This function is used by this class for creating vertices.
	 * @return
	 */
	virtual MFAdaptableVertex* createNewVertex(){return new MFAdaptableVertex();};

	void testDataCollection();
	void printCollectionInfo();
	void printNormals();
	void printIndexedNormals();
	void printVerticesWithIndexedNormals();
};

#endif /* MFVERTEXCLASSES_MFVERTEXDATACOLLECTION_H_ */
