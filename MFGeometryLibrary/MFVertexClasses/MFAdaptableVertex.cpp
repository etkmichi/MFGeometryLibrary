/*
 * MFAdaptableVertex.cpp
 *
 *  Created on: 10.12.2019
 *      Author: michl
 */

#include "MFAdaptableVertex.h"
#include <MFObjects/MFObject.h>
#include <string.h>

MFAdaptableVertex::MFAdaptableVertex() {
}

MFAdaptableVertex::~MFAdaptableVertex() {
}

void MFAdaptableVertex::printVertexData(){
	std::string info="";
	for(MFDataObject* pData:*getVecData()){
		info+=pData->toString()+"\n";
	}
	MFObject::printInfo("Vertex data:\n"+info);
}
std::string MFAdaptableVertex::toString(){
	std::string ret="MFAdaptableVertex::toString() ";
	for(MFDataObject* pData:*getVecData()){
		ret+=pData->toString();
	}
	return ret;
}
