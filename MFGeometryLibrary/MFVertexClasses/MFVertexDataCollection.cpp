/*
 * MFVertexDataCollection.cpp
 *
 *  Created on: 16.12.2019
 *      Author: michl
 */

#include "MFVertexDataCollection.h"
#include <MFObjects/MFObject.h>

MFVertexDataCollection::MFVertexDataCollection() {
	mp_sharedDataBuffer=nullptr;
	mp_vecVertices=nullptr;
	mp_vecNormals=nullptr;
	mp_vecIndices=nullptr;
	mp_vec8BitNormalIndices=nullptr;
	mp_vec16BitNormalIndices=nullptr;
	mp_vec32BitNormalIndices=nullptr;

	mp_vertexOperator = new MFVertexDataOptimizer();
	mp_vecComplexVertices = new std::vector<MFAdaptableVertex*>();
	m_dummyData=glm::mat4x4(0.0);
	mp_dummyVertex=new MFAdaptableVertex();
}
MFVertexDataCollection::MFVertexDataCollection(MFGeometryData* pGeoData) {
	mp_sharedDataBuffer=nullptr;
	setGeometryData(pGeoData);
	mp_vec16BitNormalIndices=nullptr;
	mp_vec32BitNormalIndices=nullptr;

	mp_vertexOperator = new MFVertexDataOptimizer();
	mp_vecComplexVertices = new std::vector<MFAdaptableVertex*>();
	m_dummyData=glm::mat4x4(0.0);
	mp_dummyVertex=new MFAdaptableVertex();
}

MFVertexDataCollection::~MFVertexDataCollection() {
	delete mp_vertexOperator;
	delete mp_vecComplexVertices;
}

bool MFVertexDataCollection::initNormals(){
	//TODO init normals must not be called if normals are already available...
	if(mp_vecVertices==nullptr || mp_vecNormals==nullptr || mp_vecIndices==nullptr){
		MFObject::printErr("MFVertexDataCollection::initNormals() - "
				"mp_vecVertices==nullptr || mp_vecNormals==nullptr "
				"|| mp_vecIndices==nullptr");
		return false;
	}
	if(mp_vecNormals->size()>2){
		return true;
	}else{
		if(!mp_vertexOperator->calcVertexNormals(
				mp_vecVertices,
				mp_vecIndices,
				mp_vecNormals
				)){
			MFObject::printErr("MFVertexDataCollection::initNormals() - "
										"failed to calculate normals!!");
			return false;
		}
	}
	if(mp_vecVertices->size()!=mp_vecNormals->size()){
		MFObject::printWarning("MFVertexDataCollection::initNormals - "
				"mp_vecVertices->size()!=mp_vecNormals->size()");
	}
//	MFObject::printInfo("MFVertexDataCollection::initNormals() - normals initialiced!"
//			" n_count/v_count: "+
//			std::to_string(mp_vecNormals->size())+"/"+
//			std::to_string(mp_vecVertices->size()));
	return true;
}

void MFVertexDataCollection::setGeometryData(MFGeometryData* pGeoData){
	mp_geometryData=pGeoData;
	if(pGeoData!=nullptr){
		mp_vecVertices=&mp_geometryData->m_vecVertices;
		mp_vecNormals=&mp_geometryData->m_vecVertexNormals;
		mp_vecIndices=&mp_geometryData->m_vecIndices;
		mp_sharedDataBuffer=pGeoData->mp_sharedObjectBuffer;
		m_vertexCount=mp_vecVertices->size();
	}
}

bool MFVertexDataCollection::createCollection(){
	if(m_isCreated){
		return true;
	}
	if(mp_geometryData!=nullptr &&
			mp_geometryData->m_creationFlag!=E_CREATE_BY_DEFAULT){
		MFObject::printInfo("MFVertexDataCollection::createCollection() - "
				"function will only create data if "
				"mp_geometryData->m_creationFlag==E_CREATE_BY_DEFAULT!");
		return true;
	}
	if(mp_vertexOperator==nullptr){
		mp_vertexOperator=new MFVertexDataOptimizer();
	}

	if(m_use8BitIndexedNormals){
		if(!create8BitNormals())return false;
	}

	if(m_use16BitIndexedNormals){
		if(!create16BitNormals())return false;
	}

	if(m_use32BitIndexedNormals){
		if(!create32BitNormals())return false;
	}

	m_isCreated=true;

	return true;
}

bool MFVertexDataCollection::create8BitNormals(){
	MFObject::printInfo("MFVertexDataCollection::create8BitNormals() - "
			"creating 8 bit normal indices");

	if(!initNormals()){
		MFObject::printErr("MFVertexDataCollection::create8BitNormals() - "
						"initNormals() failed!");
		return false;
	}

	mp_vec8BitNormalIndices = mp_vertexOperator->calc8BitIndexedNormals(mp_vecNormals);

	return (3<=mp_vec8BitNormalIndices->size());
}

bool MFVertexDataCollection::create16BitNormals(){
	if(!initNormals()){
		MFObject::printErr("MFVertexDataCollection::create8BitNormals() - "
						"initNormals() failed!");
		return false;
	}

	mp_vec16BitNormalIndices=mp_vertexOperator->calc16BitIndexedNormals(mp_vecNormals);

	return (3<=mp_vec16BitNormalIndices->size());
}

bool MFVertexDataCollection::create32BitNormals(){
	if(!initNormals()){
		MFObject::printErr("MFVertexDataCollection::create32BitNormals() - "
						"initNormals() failed!");
		return false;
	}

	mp_vec32BitNormalIndices=
			mp_vertexOperator->calc32BitIndexedNormals(mp_vecNormals);
	return (3<=mp_vec32BitNormalIndices->size());
}

MFAdaptableVertex* MFVertexDataCollection::getNextComplexVertex(){
	MFAdaptableVertex* pCompVert=createNewVertex();
	if(pCompVert==nullptr){
		pCompVert=new MFAdaptableVertex();
	}
	//mp_sharedDataBuffer must be initialized!
	setupComplexVertex(pCompVert);
	return pCompVert;
}

MFAdaptableVertex* MFVertexDataCollection::createComplexVertex(uint32_t dataIndex){
	if(!m_isCreated)createCollection();
	if(dataIndex > mp_vecVertices->size()-1){
		MFObject::printErr("MFVertexDataCollection::createComplexVertex("
				"uint32_t dataIndex)- "
				"index out of bounce, returning nullptr!");
		return nullptr;
	}
	MFAdaptableVertex* pCompVert=createNewVertex();
	if(pCompVert==nullptr){
		pCompVert=new MFAdaptableVertex();
	}
	pCompVert->add3DVec(&mp_vecVertices->at(dataIndex));
	if(m_use8BitIndexedNormals){
		if(dataIndex > mp_vec8BitNormalIndices->size()-1){
			MFObject::printErr("MFVertexDataCollection::createComplexVertex("
					"uint32_t dataIndex)- "
					"dataIndex > mp_vec8BitNormalIndices->size()-1, adding dummy!");
			pCompVert->addData((uint8_t*)(&m_dummyData));
		}else{
			pCompVert->addData(&mp_vec8BitNormalIndices->at(dataIndex));
		}
	}
	if(m_use16BitIndexedNormals){
		if(dataIndex > mp_vec16BitNormalIndices->size()-1){
			MFObject::printErr("MFVertexDataCollection::createComplexVertex(uint32_t dataIndex)- "
							"dataIndex > mp_vec16BitNormalIndices->size()-1, adding dummy!");
			pCompVert->addData((uint16_t*)(&m_dummyData));
		}else{
			pCompVert->addData(&mp_vec16BitNormalIndices->at(dataIndex));
		}
	}
	if(m_use32BitIndexedNormals){
		if(dataIndex > mp_vec32BitNormalIndices->size()-1){
			MFObject::printErr("MFVertexDataCollection::createComplexVertex(uint32_t dataIndex)- "
							"dataIndex > mp_vec32BitNormalIndices->size()-1, adding dummy!");
			pCompVert->addData((uint32_t*)(&m_dummyData));
		}else{
			pCompVert->addData(&mp_vec32BitNormalIndices->at(dataIndex));
		}
	}
	if(m_use3DNormals){
		if(dataIndex > mp_vecNormals->size()-1){
			MFObject::printErr("MFVertexDataCollection::createComplexVertex(uint32_t dataIndex)- "
							"dataIndex > mp_vecNormals->size()-1, adding dummy!");
			pCompVert->add3DVec(&m_dummyData);
		}else{
			pCompVert->add3DVec(&mp_vecNormals->at(dataIndex));
		}
	}
	return pCompVert;
}

void MFVertexDataCollection::setupComplexVertex(MFAdaptableVertex* pCompVert){
	pCompVert->clear();
	if(mp_sharedDataBuffer!=nullptr && pCompVert!=mp_dummyVertex){
		pCompVert->useSharedBuffer(mp_sharedDataBuffer);
	}
	//TODO use indexed Vertex coordinates
	pCompVert->add3DVec(&m_dummyData);
	if(m_use8BitIndexedNormals){
		pCompVert->addData((uint8_t*)(&m_dummyData));
	}
	if(m_use16BitIndexedNormals){
		pCompVert->addData((uint16_t*)(&m_dummyData));
	}
	if(m_use32BitIndexedNormals){
		pCompVert->addData((uint32_t*)(&m_dummyData));
	}
	if(m_use3DNormals){
		pCompVert->add3DVec(&m_dummyData);
	}

}

MFAdaptableVertex* MFVertexDataCollection::createComplexVertex(){
	MFAdaptableVertex* pCompVert=createNewVertex();
	if(pCompVert==nullptr){
		pCompVert=new MFAdaptableVertex();
	}
	setupComplexVertex(pCompVert);
	return pCompVert;
}

MFAdaptableVertex* MFVertexDataCollection::getDummyVertex(){
	mp_dummyVertex->useSharedBuffer(nullptr);
	setupComplexVertex(mp_dummyVertex);
	return mp_dummyVertex;
}

void MFVertexDataCollection::setupComplexVertices(){
	MFAdaptableVertex *pNextVertex=nullptr;
	m_vertexByteSize=getDummyVertex()->calculateStructureSize();
	if(mp_sharedDataBuffer != nullptr){
		mp_sharedDataBuffer->setBufferByteSize(m_vertexCount*m_vertexByteSize);
		mp_sharedDataBuffer->createBuffer();
	}
	if(mp_geometryData==nullptr ||
			(mp_geometryData!=nullptr &&
			 mp_geometryData->m_creationFlag==E_CREATE_BY_DEFAULT)){
		createCollection();
		//TODO separate internal creation from external
		mp_vecComplexVertices->resize(mp_vecVertices->size());
		for(uint32_t index=0;index<mp_vecVertices->size();index++){
			pNextVertex=createComplexVertex(index);
			mp_vecComplexVertices->at(index)=pNextVertex;
		}
	}
	if(mp_geometryData!=nullptr &&
			mp_geometryData->m_creationFlag==E_CREATE_BY_COLLECTION){
		mp_vecComplexVertices->resize(m_vertexCount);
		for(uint32_t index=0;index<m_vertexCount;index++){
			if(mp_vecComplexVertices->at(index)==nullptr){
				pNextVertex=createComplexVertex();
				mp_vecComplexVertices->at(index)=pNextVertex;
			}
		}
	}
}

void MFVertexDataCollection::printCollectionInfo(){
	std::string info="Vertex data collection info:";
	if(mp_vecVertices!=nullptr){
		info+="\n vertices size(): "+std::to_string(mp_vecVertices->size());
	}
	if(mp_vecIndices!=nullptr){
		info+="\n vertex indices size(): "+std::to_string(
				mp_vecIndices->size());
	}
	if(mp_vecNormals!=nullptr){
		info+="\n normals size(): "+std::to_string(mp_vecNormals->size());
	}
	if(mp_vec8BitNormalIndices!=nullptr){
		info+="\n 8bit index normals size(): "+std::to_string(
				mp_vec8BitNormalIndices->size());
	}
	if(mp_vec16BitNormalIndices!=nullptr){
		info+="\n 16bit index normals size(): "+std::to_string(
				mp_vec16BitNormalIndices->size());
	}
	if(mp_vec32BitNormalIndices!=nullptr){
		info+="\n 32bit index normals size(): "+std::to_string(
				mp_vec32BitNormalIndices->size());
	}
	MFObject::printInfo("MFVertexDataCollection - "+info);
}

void MFVertexDataCollection::testDataCollection(){
	MFObject::printWarning("MFVertexDataCollection::testDataCollection() -"
			"code out of date!");
	MFObject::printInfo("MFVertexDataCollection::testDataCollection() -"
			"creating sphere");
	MFVertexDataCollection* pSphereCollection=new MFVertexDataCollection();
	pSphereCollection->use8BitIndexedNormals(true);

	MFObject::printInfo("MFVertexDataCollection::testDataCollection() - "
			"creating collection (8Bit indexed normals)");
	if(pSphereCollection->createCollection()){
		MFObject::printInfo("MFVertexDataCollection::testDataCollection() - "
				"Creation done!");
	}else{
		MFObject::printErr("MFVertexDataCollection::testDataCollection() - "
				"Creation failed!");
	}
	pSphereCollection->printCollectionInfo();
	pSphereCollection->printVerticesWithIndexedNormals();
}

void MFVertexDataCollection::printNormals(){
	std::string info="Normals: | x,y,z | \n";
	if(mp_vecNormals!=nullptr){
		int counter=0;
		for(glm::vec3 normal:*mp_vecNormals){
			counter++;
			if(normal.x>0)
				info+=" ";
			info+="vec3("+std::to_string(normal.x)+",";
			if(normal.y>0)
				info+=" ";
			info+=std::to_string(normal.y)+",";
			if(normal.z>0)
				info+=" ";
			info+=std::to_string(normal.z)+") ";
			if(counter%3==0){
				info+="\n";
				counter=0;
			}
		}
	}
	MFObject::printInfo(info);
}

void MFVertexDataCollection::printIndexedNormals(){
	std::string info="Normals: |index: x,y,z | \n";
	if(mp_vec8BitNormalIndices!=nullptr){
		int counter=0;
		for(uint32_t index:*mp_vec32BitNormalIndices){
			glm::vec3 normal=mp_vertexOperator->get256NormalsVector()->at(index);
			if(index<100){
				if(index<10)
					info+="  ";
				else
					info+=" ";
			}
			info+=std::to_string(index);
			info+=": ";
			counter++;
			if(normal.x>=0)
				info+="vec3(";
			info+=std::to_string(normal.x)+",";
			if(normal.y>=0)
				info+=" ";
			info+=std::to_string(normal.y)+",";
			if(normal.z>=0)
				info+=" ";
			info+=std::to_string(normal.z)+") ";
			if(counter%3==0){
				info+="\n";
				counter=0;
			}
		}
	}
	MFObject::printInfo(info);
}

void MFVertexDataCollection::printVerticesWithIndexedNormals(){
	std::string info="Vertex + Normals: | vertex : \nn_ind: normal | \n";
	if(mp_vec8BitNormalIndices!=nullptr){
		int counter=0;
		uint32_t vertexCounter=0;
		for(uint8_t index:*mp_vec8BitNormalIndices){
			std::string vertex="";
			if(vertexCounter>mp_vecVertices->size()-1){
				vertex+=" - :";
			}else{
				glm::vec3 vec=mp_vecVertices->at(vertexCounter);
				vertexCounter++;
				if(vec.x>=0)
					info+=" ";
				vertex+=std::to_string(vec.x)+",";
				if(vec.y>=0)
					info+=" ";
				vertex+=std::to_string(vec.y)+",";
				if(vec.z>=0)
					vertex+=" ";
				vertex+=std::to_string(vec.z);
				vertex+=" :\n";
			}
			info+=vertex;
			glm::vec3 normal=mp_vertexOperator->get256NormalsVector()->at(index);
			if(index<100){
				if(index<10)
					info+="  ";
				else
					info+=" ";
			}
			info+=std::to_string(index);
			info+=": ";
			counter++;
			if(normal.x>=0)
				info+=" ";
			info+=std::to_string(normal.x)+",";
			if(normal.y>=0)
				info+=" ";
			info+=std::to_string(normal.y)+",";
			if(normal.z>=0)
				info+=" ";
			info+=std::to_string(normal.z)+" |\n";
			if(counter%1==0){
				info+="\n";
				counter=0;
			}
		}
	}
	MFObject::printInfo(info);
}
