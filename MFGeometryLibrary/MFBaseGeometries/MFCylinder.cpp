/*
 * MFCylinder.cpp
 *
 *  Created on: 28.10.2019
 *      Author: michl
 */

#include "MFCylinder.h"
#include "btBulletDynamicsCommon.h"

MFCylinder::MFCylinder(float length,float radius) :
MFAbstractGeometry("cylinder"){
  m_radius=radius;
  m_length=length;
}

MFCylinder::~MFCylinder() {
	// TODO Auto-generated destructor stub
}

void* MFCylinder::createCollisionShape(){
  btCylinderShapeZ *pCylinder=new btCylinderShapeZ(
      btVector3(m_radius,m_radius,m_length/2));
  return pCylinder;
}

bool MFCylinder::calculateGeometryData(
    std::vector<glm::vec3> &vertices,
    std::vector<uint32_t> &indices){
  float azimutInc = 2*M_PI/m_stepsAzimutAngle;
  uint32_t countAzimutSteps=0;
  //circle for bottom
  for(float angleAzimut = 0; angleAzimut<2*M_PI; angleAzimut+=azimutInc){
    float xCoord=m_radius*cos(angleAzimut);//angleAzimut
    float yCoord=m_radius*sin(angleAzimut);//angleAzimut
    glm::vec3 vertex={xCoord,yCoord,-m_length/2};
    vertices.push_back(vertex);
    countAzimutSteps++;
  }
  //circle for top
  for(uint32_t i=0;i<countAzimutSteps;i++){
    glm::vec3 vertex=vertices.at(i);
    vertex.z=m_length/2;
    vertices.push_back(vertex);
  }

  indices.clear();
  /*triangles for wall*/
  /*triangle indices from two points bottom, one on top*/
  for(uint32_t i = 0; i<countAzimutSteps;i++){
    indices.push_back(i);

    if(i+1!=countAzimutSteps)
      indices.push_back(i+1);
    else
      indices.push_back(0);

    indices.push_back(i+countAzimutSteps);
  }
  /*triangle indices from two points top, one bottom*/
  for(uint32_t i = 0; i<(countAzimutSteps-1);i++){
    indices.push_back(i+1);/*one bottom*/
    indices.push_back(i+1+countAzimutSteps);/*top*/
    indices.push_back(i+countAzimutSteps);/*top-1*/
  }

  /*triangles for top cyrcle*/
  for(uint32_t i = 1; i<(countAzimutSteps)-1;i+=1){
    indices.push_back(0);/*one bottom*/
    indices.push_back(i);/*top*/
    indices.push_back(i+1);/*top-1*/
  }

  /*triangles for bottom cyrcle*/
  for(uint32_t i = countAzimutSteps; i<(2*countAzimutSteps)-1;i+=1){
    indices.push_back(0);/*one bottom*/
    indices.push_back(i);/*top*/
    indices.push_back(i+1);/*top-1*/
  }
  return true;
}
