/*
 * MFCone.cpp
 *
 *  Created on: 27.11.2020
 *      Author: michl
 */

#include "MFCone.h"
#include "btBulletDynamicsCommon.h"

MFCone::MFCone(float length,float radius) :
MFAbstractGeometry("cone"){
  m_radius=radius;
  m_length=length;
}

MFCone::~MFCone() {
  // TODO Auto-generated destructor stub
}


void* MFCone::createCollisionShape(){
  btConeShapeZ *pCone=new btConeShapeZ(m_radius,m_length);
  return pCone;
}

bool MFCone::calculateGeometryData(
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

  //point top
  glm::vec3 vertex=glm::vec3(0,0,m_length/2);
  vertices.push_back(vertex);

  indices.clear();

  /*triangles for wall*/
  for(uint32_t i = 0; i<(countAzimutSteps-1);i++){
    indices.push_back(i);
    indices.push_back(i+1);
    indices.push_back(countAzimutSteps);/*top*/
  }

  /*triangles for bottom cyrcle*/
  for(uint32_t i = 1; i<(countAzimutSteps)-1;i+=1){
    indices.push_back(0);/*one bottom*/
    indices.push_back(i);/*top*/
    indices.push_back(i+1);/*top-1*/
  }
  return true;
}
