/*
 * MFNoiseGeometry.cpp
 *
 *  Created on: 11.02.2020
 *      Author: michl
 */

#include "MFNoiseGeometry.h"
#include <MFObjects/MFObject.h>
#include <btBulletDynamicsCommon.h>
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

MFNoiseGeometry::MFNoiseGeometry() :
MFAbstractGeometry("noise"){
	mp_innerNoiseTile=new MFNoiseTile();
	mp_noiseTile=mp_innerNoiseTile;
}

MFNoiseGeometry::MFNoiseGeometry(MFNoiseTile* pNoiseTile) {
	mp_innerNoiseTile=new MFNoiseTile();
	mp_noiseTile=pNoiseTile;
}

MFNoiseGeometry::~MFNoiseGeometry() {
	delete mp_innerNoiseTile;
	if(mp_stridingMesh!=nullptr){
		btTriangleIndexVertexArray *pSM=(btTriangleIndexVertexArray*)mp_stridingMesh;
		delete pSM;
	}
}

bool MFNoiseGeometry::updateData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices,
		std::vector<uint32_t> *pVertexColors,
		std::vector<glm::vec3> *pVertexNormals){
	return calculateGeometryData(vertices,indices,pVertexColors,pVertexNormals);
}

void MFNoiseGeometry::setNoiseConfig(S_MFNoiseConfig* pConfig){
	mp_noiseTile->getNoiseSetup()->setNoiseConfig(pConfig);
}
void MFNoiseGeometry::setCalculationSetup(S_MFCalculationSetup* pConfig){
	mp_noiseTile->setCalculationSetup(pConfig);
}
bool MFNoiseGeometry::updateData(){
	bool ret=true;
//	m_vertexDataCollection.setGeometryData(&m_geometryData);
	ret&=mp_noiseTile->updateTile(&m_vertexDataCollection);
	//ret&=(nullptr!=createCollisionShape());TODO what happens with bullet col shape?
	return ret;
}
glm::vec3 counter=glm::vec3(0,0,0);

//void* MFNoiseGeometry::createCollisionShape(MFVertexDataCollection* pDataCollection){
//	if(m_geometryData.m_vecIndices.size()<3){
//		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
//				"m_vecIndices->size()<3");
//		return nullptr;
//	}
//	if(pDataCollection->getComplexVertices()->size()<3){
//		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
//				"pDataCollection->getComplexVertices()->size()<3");
//		return nullptr;
//	}
//	if(mp_heightData==nullptr){
//		mp_heightData=malloc(pDataCollection->getVertexCount()*sizeof(float));
//	}
//	for(uint32_t i=0;i<pDataCollection->getVertexCount();i++){
//		MFDataObject* pO=pDataCollection->getComplexVertices()->at(i)->getVecData()->at(0);
//		glm::vec3* pVec=(glm::vec3*)pO->getData();
//		float* pDst=(float*)(mp_heightData);
//		pDst[i]=(pVec->z);
//	}
//	btHeightfieldTerrainShape* pHF=new btHeightfieldTerrainShape (
//			10,
//			10,
//			mp_heightData,
//			1,
//			-1,
//			1,
//			3,
//			PHY_FLOAT,
//			false);
//	btAssert(pHF && "null heightfield");
//	pHF->buildAccelerator(10);
////	btVector3 minAB=btVector3(mp_noiseTile->getMinAABB().x,
////			mp_noiseTile->getMinAABB().y,
////			mp_noiseTile->getMinAABB().z);
////	btVector3 maxAB=btVector3(mp_noiseTile->getMaxAABB().x,
////			mp_noiseTile->getMaxAABB().y,
////			mp_noiseTile->getMaxAABB().z);
////	pHF->processAllTriangles(nullptr,minAB,maxAB);
//	mp_bulletCollisionShape=pHF;
//
////	btBoxShape *pBoxShape;
////	btVector3 boxSize=btVector3(
////			mp_noiseTile->getSurroundingBox().x,
////			mp_noiseTile->getSurroundingBox().y,
////			mp_noiseTile->getSurroundingBox().z);
////	pBoxShape=new btBoxShape(boxSize);
////	mp_bulletCollisionShape=pBoxShape;
//
////	MFObject::printVec3(glm::vec3(
////			pTriMesh->getLocalAabbMax().x(),
////			pTriMesh->getLocalAabbMax().y(),
////			pTriMesh->getLocalAabbMax().z()));
////	MFObject::printVec3(glm::vec3(
////			pTriMesh->getLocalAabbMin().x(),
////			pTriMesh->getLocalAabbMin().y(),
////			pTriMesh->getLocalAabbMin().z()));
////	counter.x++;
////	counter.y=counter.x/125.0f;
////	MFObject::printVec3(counter);
//	return mp_bulletCollisionShape;
//}
void* MFNoiseGeometry::createCollisionShape(MFVertexDataCollection* pDataCollection){
	if(m_geometryData.m_vecIndices.size()<3){
		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
				"m_vecIndices->size()<3");
		return nullptr;
	}
	if(pDataCollection->getComplexVertices()->size()<3){
		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
				"pDataCollection->getComplexVertices()->size()<3");
		return nullptr;
	}
	int triangleCount=m_geometryData.m_vecIndices.size()/3;
	int* pIndexData=(int*)m_geometryData.m_vecIndices.data();
	int indexStride=(3*sizeof(uint32_t));
	int verticesCount=pDataCollection->getComplexVertices()->size();
	btScalar* pVertices=(btScalar*)
		((pDataCollection->getComplexVertices()->at(0)->getVecData()->at(0)->getData()));
	int vertexStride=pDataCollection->getComplexVertices()->at(0)->calculateStructureSize();
	btTriangleIndexVertexArray *pSM=nullptr;
//	glm::vec3 triSu=glm::vec3(triangleCount,verticesCount,indexStride);
//	MFObject::printVec3(triSu);
	if(mp_stridingMesh==nullptr){
		pSM=new btTriangleIndexVertexArray(
				triangleCount,
				pIndexData,
				indexStride,
				verticesCount,
				pVertices,
				vertexStride
				);
		mp_stridingMesh=pSM;
	}else{
		pSM=(btTriangleIndexVertexArray*)mp_stridingMesh;
		pSM->getIndexedMeshArray()[0].m_numTriangles=triangleCount;
		pSM->getIndexedMeshArray()[0].m_numVertices=verticesCount;
		pSM->getIndexedMeshArray()[0].m_triangleIndexBase=(unsigned char*)pIndexData;
		pSM->getIndexedMeshArray()[0].m_triangleIndexStride=indexStride;
		pSM->getIndexedMeshArray()[0].m_vertexStride=vertexStride;
		pSM->getIndexedMeshArray()[0].m_vertexBase=(unsigned char*)pVertices;
	}
//	btVector3 minAB=btVector3(mp_noiseTile->getMinAABB().x,
//			mp_noiseTile->getMinAABB().y,
//			mp_noiseTile->getMinAABB().z);
//	btVector3 maxAB=btVector3(mp_noiseTile->getMaxAABB().x,
//			mp_noiseTile->getMaxAABB().y,
//			mp_noiseTile->getMaxAABB().z);
//	pSM->setPremadeAabb(minAB, maxAB);

	btBvhTriangleMeshShape *pTriMesh;
  pTriMesh=new btBvhTriangleMeshShape(
    pSM,
    true
    );
  pTriMesh->buildOptimizedBvh();


//	MFObject::printVec3(glm::vec3(
//			pTriMesh->getLocalAabbMax().x(),
//			pTriMesh->getLocalAabbMax().y(),
//			pTriMesh->getLocalAabbMax().z()));
//	MFObject::printVec3(glm::vec3(
//			pTriMesh->getLocalAabbMin().x(),
//			pTriMesh->getLocalAabbMin().y(),
//			pTriMesh->getLocalAabbMin().z()));
	counter.x++;
	counter.y=counter.x/125.0f;
//	MFObject::printVec3(counter);
	return pTriMesh;
}
void* MFNoiseGeometry::createCollisionShape(){
	if(m_geometryData.m_creationFlag==E_CREATE_BY_COLLECTION){
		return createCollisionShape(&m_vertexDataCollection);
	}
	if(m_geometryData.m_vecIndices.size()<3){
		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
				"m_vecIndices->size()<3");
		return nullptr;
	}
	if(m_geometryData.m_vecVertices.size()<3){
		MFObject::printErr("MFNoiseGeometry::createCollisionShape() - failed, "
				"m_vecVertices->size()<3");
		return nullptr;
	}
	int triangleCount=m_geometryData.m_vecIndices.size()/3;
	int* pIndexData=(int*)m_geometryData.m_vecIndices.data();
	int indexStride=(3*sizeof(uint32_t));
	int verticesCount=m_geometryData.m_vecVertices.size();
	btScalar* pVertices=(btScalar*)(&(m_geometryData.m_vecVertices.at(0)[0]));
	int vertexStride=sizeof(glm::vec3);
	btTriangleIndexVertexArray *pSM=new btTriangleIndexVertexArray(
			triangleCount,
			pIndexData,
			indexStride,
			verticesCount,
			pVertices,
			vertexStride
			);
	btBvhTriangleMeshShape *pTriMesh=new btBvhTriangleMeshShape(
			pSM,
			true
			);
	mp_stridingMesh=pSM;
	return pTriMesh;
}

bool MFNoiseGeometry::calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices){
	return mp_noiseTile->calculateTile(&vertices, &indices);
}

bool MFNoiseGeometry::calculateGeometryData(MFVertexDataCollection* pDataCollection){
	return mp_noiseTile->calculateTile(pDataCollection);
};

bool MFNoiseGeometry::calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices,
		std::vector<uint32_t> *pVertexColors,
		std::vector<glm::vec3> *pVertexNormals){
	return mp_noiseTile->calculateTile(&vertices, &indices,pVertexColors,pVertexNormals);
}
