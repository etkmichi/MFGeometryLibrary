/*
 * MFNoiseVoxel.h
 *
 *  Created on: 02.03.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFVOXELGEOMETRIES_MFNOISEVOXEL_H_
#define MFBASEGEOMETRIES_MFVOXELGEOMETRIES_MFNOISEVOXEL_H_
#include "../MFNoiseGeometry.h"
class MFNoiseVoxel : public MFNoiseGeometry
{
public:
	MFNoiseVoxel();
	virtual ~MFNoiseVoxel();
	virtual bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices){
		MFObject::printWarning("MFNoiseVoxel::calculateGeometryData - dont use this "
				"function, use calculateGeometryData(MFVertexDataCollection*)!");
		return calculateGeometryData(&m_vertexDataCollection);
	};
	virtual bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices,
		std::vector<uint32_t> *pVertexColors,
		std::vector<glm::vec3> *pVertexNormals){
		MFObject::printWarning("MFNoiseVoxel::calculateGeometryData - dont use this"
				" function, use calculateGeometryData(MFVertexDataCollection*)!");
		return calculateGeometryData(&m_vertexDataCollection);
	}
	virtual bool calculateGeometryData(MFVertexDataCollection* pDataCollection){
		return false;
	};
	virtual void* createCollisionShape(MFVertexDataCollection* pDataCollection){
		return nullptr;
	};
	bool updateData(){return false;};
};

#endif /* MFBASEGEOMETRIES_MFVOXELGEOMETRIES_MFNOISEVOXEL_H_ */
