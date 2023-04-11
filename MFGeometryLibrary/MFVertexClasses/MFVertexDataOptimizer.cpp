/*
 * MFVertexDataOptimizer.cpp
 *
 *  Created on: 03.12.2019
 *      Author: michl
 */

#include "MFVertexDataOptimizer.h"
#include <MFObjects/MFObject.h>
#include <map>
#define GLM_ENABLE_EXPERIMENTAL
#include <math.h>
#include <glm/gtx/hash.hpp>

//namespace std {
//	template<> struct hash<VertexData>{
//		size_t operator()(VertexData const& vertex) const {
//			return (
//				((hash<glm::vec3>()(vertex.vertex)^(hash<glm::vec3>))
//			);
//		}
//	}
//}
std::mutex MFVertexDataOptimizer::lockVec256NormalsWrite;
std::mutex MFVertexDataOptimizer::lockVec256Normals;
struct TriangleData{
	std::vector<glm::vec3> vertices;
	glm::vec3 normal;
	bool calculateNormal(){
		if(vertices.size()!=3){
			return false;
		}
		/*TODO calculate normal*/
		glm::vec3 v1=vertices.at(1)-vertices.at(0);
		glm::vec3 v2=vertices.at(2)-vertices.at(0);
		normal=glm::cross(v1,v2);
		normal=glm::normalize(normal);
		if(glm::length(normal)==0){
			normal=glm::vec3(0,0,1);
			return false;
		}
		return true;
	}
};
/**
 * VertexData contains data of vertex. The index of the vertex must be lower than
 * 0xFFFFFFFF. If index is 0xFFFFFFFF, thand index will not be used. The lower operator
 * returns compares the indices if used else it compares the length of the vectors
 */
struct VertexData{
	glm::vec3 vertex;
	uint32_t index=0xFFFFFFFF;
	std::vector<TriangleData> corneringTriangles;
	glm::vec3 vertexNormal;
	bool calculateNormal(){
		if(corneringTriangles.size()==0){
			MFObject::printWarning("TriangleData::calculateNormal() - "
									"no cornering triangle!");
			return false;
		}
		vertexNormal=glm::vec3(0,0,0);
		for(TriangleData trigl:corneringTriangles){
			if(!trigl.calculateNormal()){
				MFObject::printWarning("TriangleData::calculateNormal() - "
						"0,0,0 normal, shouldnt exist!");
				continue;
			}
			vertexNormal+=trigl.normal;
		}
		vertexNormal=glm::normalize(vertexNormal);
		if(glm::length(vertexNormal)==0.0f){
			MFObject::printWarning("VertexData::calculateNormal() - "
					"normalLength==0, setting normal to 0,0,1");
			vertexNormal=glm::vec3(0,0,1);
			return false;
		}
		/*TODO calculate median normal*/
		return true;
	}
	bool operator==(const VertexData& other) const{
		if(index!=0xFFFFFFFF && other.index!=0xFFFFFFFF){
			return index==other.index;
		}
		return vertex==other.vertex;
	}
	bool operator<(const VertexData& other) const{
		if(index!=0xFFFFFFFF && other.index!=0xFFFFFFFF){
			return index<other.index;
		}
		return (glm::dot(vertex,vertex)<(glm::dot(other.vertex,other.vertex)));
	}
};
std::vector<glm::vec3>* MFVertexDataOptimizer::ms_vec256Normals=
		new std::vector<glm::vec3>();
MFVertexDataOptimizer::MFVertexDataOptimizer() {
}

MFVertexDataOptimizer::~MFVertexDataOptimizer() {
	// TODO Auto-generated destructor stub
}

std::vector<uint8_t >* MFVertexDataOptimizer::calc8BitIndexedNormals (
		std::vector<glm::vec3>* pNormals){
	std::vector<uint8_t>* pIndices=new std::vector<uint8_t>();
	for(glm::vec3 vec : *pNormals){
		pIndices->push_back(get8BitNormalIndex(vec));
	}
	MFObject::printInfo("MFVertexDataOptimizer::calc8BitIndexedNormals - "
			"calculated normal indices count: "+std::to_string(pIndices->size()));
	return pIndices;
}

void MFVertexDataOptimizer::print256NormalsVector(){
	create256NormalsVector();
	int counter=0;
	std::string info="256 sphere normals:("+std::to_string(ms_vec256Normals->size())
	+")\n";
	for(glm::vec3 normal:*ms_vec256Normals){
//		if(index<100){
//			if(index<10)
//				info+="  ";
//			else
//				info+=" ";
//		}
		counter++;
		if(normal.x>=0)
			info+=" vec3(";
		else
			info+="vec3(";
		info+=std::to_string(normal.x)+",";
		if(normal.y>=0)
			info+=" ";
		info+=std::to_string(normal.y)+",";
		if(normal.z>=0)
			info+=" ";
		info+=std::to_string(normal.z)+"), ";
		if(counter%3==0){
			info+="\n";
			counter=0;
		}
	}
	MFObject::printInfo(info);
}
bool MFVertexDataOptimizer::create256NormalsVector(){
	lockVec256NormalsWrite.lock();
	if(ms_vec256Normals->size()!=0){
		if(ms_vec256Normals->size()==256){
			lockVec256NormalsWrite.unlock();
			return true;
		}
		MFObject::printWarning("MFVertexDataOptimizer::create256NormalsVector() -"
				"clearing normals(256) vector because size missmatch!");
		ms_vec256Normals->clear();
	}
	/*the vectors (0,0,1) and (0,0,-1) will be excluded*/
	float
		polarStepSize=M_PI/18.0f,
		azimutStepSize=M_PI*2/16.0f,
		azimutAngle=0.0f,
		polarAngle=0.0f;
	uint32_t debugCounter=0;
	for(int polarCounter=1;polarCounter<=16;polarCounter++){
		polarAngle=-M_PI_2+polarStepSize*polarCounter;/*first circle at polarStepSize*/
		float
			zCoord=sin(polarAngle),/*interval: (-1.0,+1.0) = ]-1.0,1.0[*/
			currentRadius=sqrt(1-(zCoord*zCoord));
		for(int azimutCounter=0;azimutCounter<16;azimutCounter++){
			azimutAngle=azimutCounter*azimutStepSize;/*[0,2*PI[*/
			float
				xCoord=sin(azimutAngle)*currentRadius,
				yCoord=cos(azimutAngle)*currentRadius;
			ms_vec256Normals->push_back(glm::vec3(xCoord,yCoord,zCoord));
			debugCounter++;
			if(debugCounter>256){
				MFObject::printErr("MFVertexDataOptimizer::create256NormalsVector - "
						"more than 256 points!!!!!!!!!\\/°_°\\/!");
			}
		}
	}
	std::string info="\n calculated normal count: "+std::to_string(debugCounter);
	MFObject::printInfo("MFVertexDataOptimizer::create256NormalsVector() -"
			"calculating 256 normals vector!"+info);
	lockVec256NormalsWrite.unlock();
	return true;
}

uint32_t MFVertexDataOptimizer::getCloseLowerIndexFor256Normals(float zCoordinate){
//TODO
	MFObject::printInfo("MFVertexDataOptimizer::getCloseLowerIndexFor256Normals - "
			"ni!");
	return 0;
}
//TODO create algorithm and data stucture for deriving data like normal index by
// a function f(vec3)
//	-> better thand seraching index
//	-> can be calculated by shader (f(vec3)=index on cpu -> f(index)=vec3 on gpu)
//	-> for 8,16,32 bit data
//	-> create indexed coordinates
//		->1x32bit = (3x8Bit)+8Bit = (vec3)+vec3 = (point coords) + (point normal)
//		->extra 32bit for color...

uint8_t MFVertexDataOptimizer::get8BitNormalIndex(glm::vec3 normal){
	MFVertexDataOptimizer::create256NormalsVector();
	glm::vec3 n1=glm::normalize(normal);
	float closestDistance=10.0f;
	uint8_t closestIndex=0;

	uint32_t stopCounter=0;
	for(uint8_t i=0;i<ms_vec256Normals->size();i++){
		glm::vec3 distance=n1-ms_vec256Normals->at(i);
		float difference=glm::dot(distance,distance);
		if(difference<closestDistance){
			closestDistance=difference;
			stopCounter=0;
			closestIndex=i;
		}else{
			stopCounter++;
			if(stopCounter>33){
				/*All following points are farther away, so
			the correct index was found already!*/
				return closestIndex;
			}
		}
	}
	return closestIndex;
}
std::vector<uint16_t>* MFVertexDataOptimizer::calc16BitIndexedNormals(
		std::vector<glm::vec3>* pNormals){
	MFObject::printErr("MFVertexDataOptimizer::calc16BitIndexedNormals - not impl.");
	return nullptr;
}

std::vector<uint32_t>* MFVertexDataOptimizer::calc32BitIndexedNormals(
		std::vector<glm::vec3>* pNormals){
	//TODO do not use new here!
	std::vector<uint32_t>* pIndices=new std::vector<uint32_t>();
	pIndices->resize(pNormals->size());
	uint32_t counter=0;
	for(glm::vec3 vec : *pNormals){
		pIndices->at(counter)=0+get8BitNormalIndex(vec);
		counter++;
	}
//	MFObject::printInfo("MFVertexDataOptimizer::calc32BitIndexedNormals - "
//			"calculated normal indices count: "+std::to_string(pIndices->size()));
	return pIndices;
}

typedef std::map<VertexData,VertexData> MapType;
bool MFVertexDataOptimizer::calcVertexNormals(
		const std::vector<glm::vec3>* pVertices,
		const std::vector<uint32_t>* pIndices,
		std::vector<glm::vec3>* pVecVertexNormals){
	MapType mapVertexNormal = {};
//	MFObject::printInfo("MFVertexDataOptimizer::calcVertexNormals - "
//			"Indices count: "+std::to_string(pIndices->size()));
	if((pIndices->size()%3)!=0){
		MFObject::printWarning("MFVertexDataOptimizer::calcVertexNormals - "
				"Indices count % 3 != 0!!! this function calculates"
				"normals for triangles!");
	}
	uint32_t highestIndex=0;
	for(uint32_t i=0;i<pIndices->size();i+=3){
		if( ((i+2)>pIndices->size()) ){
			MFObject::printWarning("MFVertexDataOptimizer::calcVertexNormals - "
					"Index out of bounce");
			continue;
		}

		VertexData vertex1={},vertex2={},vertex3={};
		vertex1.index=pIndices->at(i);
		vertex1.vertex=pVertices->at(vertex1.index);
		vertex2.index=pIndices->at(i+1);
		vertex2.vertex=pVertices->at(vertex2.index);
		vertex3.index=pIndices->at(i+2);
		vertex3.vertex=pVertices->at(vertex3.index);
		if(pIndices->at(i)>highestIndex)
			highestIndex=pIndices->at(i);
		if(pIndices->at(i+1)>highestIndex)
			highestIndex=pIndices->at(i+1);
		if(pIndices->at(i+2)>highestIndex)
			highestIndex=pIndices->at(i+2);

		TriangleData triangle;
		triangle.vertices.push_back(vertex1.vertex);
		triangle.vertices.push_back(vertex2.vertex);
		triangle.vertices.push_back(vertex3.vertex);

		if(mapVertexNormal.count(vertex1)==0){
			vertex1.corneringTriangles.push_back(triangle);
			mapVertexNormal.insert(mapVertexNormal.end(),{vertex1,vertex1});
		}else{
			mapVertexNormal[vertex1].corneringTriangles.push_back(triangle);
		}

		if(mapVertexNormal.count(vertex2)==0){
			vertex2.corneringTriangles.push_back(triangle);
			mapVertexNormal.insert(mapVertexNormal.end(),{vertex2,vertex2});
		}else{
			mapVertexNormal[vertex2].corneringTriangles.push_back(triangle);
		}

		if(mapVertexNormal.count(vertex3)==0){
			vertex3.corneringTriangles.push_back(triangle);
			mapVertexNormal.insert(mapVertexNormal.end(),{vertex3,vertex3});
		}else{
			mapVertexNormal[vertex3].corneringTriangles.push_back(triangle);
		}
	}

	uint32_t counter=0;
	for(MapType::iterator it = mapVertexNormal.begin();it!=mapVertexNormal.end();++it){
		it->second.calculateNormal();
		pVecVertexNormals->push_back(it->second.vertexNormal);
		counter++;
	}
	if(pVecVertexNormals->size()!=pVertices->size()){
		MFObject::printWarning("MFVertexDataOptimizer::calcVertexNormals - "
				"normals count != vertex count - norm_c/vert_c/highestIndex: "+
				std::to_string(pVecVertexNormals->size())+"/"+
				std::to_string(pVertices->size())+"/"+
				std::to_string(highestIndex));
		if(highestIndex<pVertices->size()){
			MFObject::printWarning("MFVertexDataOptimizer::calcVertexNormals - missing "
					"index for vertex! Filling normal vector with dummy data (results "
					"in incorrect normal calculations!)");
			while(pVecVertexNormals->size()<pVertices->size()){
				pVecVertexNormals->push_back(pVecVertexNormals->at(pVecVertexNormals->size()-1));
				highestIndex++;
			}
		}
	}
	return (pVecVertexNormals->size()>=3);
}

