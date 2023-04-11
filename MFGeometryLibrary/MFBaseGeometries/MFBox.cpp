/*
 * MFBox.cpp
 *
 *  Created on: 28.10.2019
 *      Author: michl
 */

#include "MFBox.h"
#include "btBulletDynamicsCommon.h"
#include "MFObjects/MFObject.h"
#include <BulletCollision/CollisionShapes/btBoxShape.h>


MFBox::MFBox(glm::vec3 extent) :
MFAbstractGeometry("box"){
	m_boxExtents=extent;
	m_offset=glm::vec3(.0f,.0f,.0f);
}

MFBox::~MFBox() {
}

bool MFBox::calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices){
	glm::vec3 firstPoint;
	glm::vec3 nextPoint;
	firstPoint.x=m_boxExtents.x;
	firstPoint.y=m_boxExtents.y;
	firstPoint.z=m_boxExtents.z;

	nextPoint=firstPoint+m_offset;
	vertices.push_back(nextPoint);//Top point 0

	nextPoint=firstPoint*glm::vec3(1,1,-1)+m_offset;//Top point 1
	vertices.push_back(nextPoint);

	nextPoint=firstPoint*glm::vec3(-1,1,-1)+m_offset;//Top point 2
	vertices.push_back(nextPoint);

	indices.push_back(0);/*first triangle on top*/
	indices.push_back(1);
	indices.push_back(2);

	nextPoint=firstPoint*glm::vec3(-1,1,1)+m_offset;//Top point 3
	vertices.push_back(nextPoint);

	indices.push_back(0);/*second top triangle*/
	indices.push_back(2);
	indices.push_back(3);

	/*bottom points (same as top just -y)*/
	nextPoint=firstPoint*glm::vec3(1,-1,1)+m_offset;
	vertices.push_back(nextPoint);//Top point 0

	nextPoint=firstPoint*glm::vec3(1,-1,-1)+m_offset;//Bottom point 1
	vertices.push_back(nextPoint);

	nextPoint=firstPoint*glm::vec3(-1,-1,-1)+m_offset;//Bottom point 2
	vertices.push_back(nextPoint);

	nextPoint=firstPoint*glm::vec3(-1,-1,1)+m_offset;//Bottom point 3
	vertices.push_back(nextPoint);

	/*Bottom triangles:*/
	indices.push_back(4);/*first bot triangle*/
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(4);/*second bot triangle*/
	indices.push_back(6);
	indices.push_back(7);

	/*sides*/
	indices.push_back(0);/*first bot triangle*/
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(4);/*second bot triangle*/
	indices.push_back(3);
	indices.push_back(7);

	indices.push_back(0);/*first bot triangle*/
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(0);/*second bot triangle*/
	indices.push_back(5);
	indices.push_back(1);

	indices.push_back(1);/*first bot triangle*/
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(1);/*second bot triangle*/
	indices.push_back(6);
	indices.push_back(2);

	indices.push_back(2);/*first bot triangle*/
	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(2);/*second bot triangle*/
	indices.push_back(7);
	indices.push_back(3);

	return true;
};

void* MFBox::createCollisionShape(){
  btBoxShape* pBox=new btBoxShape(btVector3(
      m_boxExtents.x,m_boxExtents.y,m_boxExtents.z));
	pBox->setMargin(0.3f);
	return pBox;
}


