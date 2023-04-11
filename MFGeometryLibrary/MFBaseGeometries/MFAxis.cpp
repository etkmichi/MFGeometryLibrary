/*
 * MFAxis.cpp
 *
 *  Created on: 14.10.2019
 *      Author: michl
 */

#include "MFAxis.h"

MFAxis::MFAxis(glm::vec3 axis,float length) :
MFAbstractGeometry("axis"){
	m_length=length;
	m_axe=glm::normalize(axis);
}

MFAxis::~MFAxis() {
	// TODO Auto-generated destructor stub
}

bool MFAxis::calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices){
	float rotation=0;
	uint32_t indexCounter=0;
	for(float currentPos=0.0f;currentPos<m_length;currentPos+=(m_length/20.0f)){
		glm::vec3 posV1,posV2,posV3,posV4,cros;
		cros=m_axe+glm::vec3(1.0f,3.0f,7.0f);
		cros=glm::normalize(cros);
		cros=glm::rotate(cros,rotation,m_axe);
		cros=glm::cross(cros,m_axe);
		rotation+=0.9f;
		posV1=m_axe*currentPos;
		posV2=m_axe*(currentPos+(m_length/20.0f));
		posV3=posV1+0.01f*m_length*cros;

		cros=m_axe+glm::vec3(1.0f,3.0f,7.0f);
		cros=glm::normalize(cros);
		cros=glm::rotate(cros,rotation+3.14f,m_axe);
		cros=glm::cross(cros,m_axe);
		posV4=posV1+0.01f*m_length*cros;
		vertices.push_back(posV1);
		vertices.push_back(posV2);
		vertices.push_back(posV3);
		vertices.push_back(posV4);
		indices.push_back(indexCounter);
		indices.push_back(indexCounter+1);
		indices.push_back(indexCounter+2);
		indices.push_back(indexCounter);
		indices.push_back(indexCounter+3);
		indices.push_back(indexCounter+1);
		indexCounter+=4;
	}

	return true;
}
