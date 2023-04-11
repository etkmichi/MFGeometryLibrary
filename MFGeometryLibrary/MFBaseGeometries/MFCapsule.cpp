/*
 * MFCapsule.cpp
 *
 *  Created on: 27.11.2020
 *      Author: michl
 */

#include "MFCapsule.h"
#include <btBulletDynamicsCommon.h>

MFCapsule::MFCapsule(float length,float radius) :
MFAbstractGeometry("capsule"){
  m_radius=radius;
  m_length=length;
}

MFCapsule::~MFCapsule() {
}

void* MFCapsule::createCollisionShape(){
  btCapsuleShapeZ *pCone=new btCapsuleShapeZ(m_radius,m_length);
  return pCone;
}

bool MFCapsule::calculateGeometryData(
    std::vector<glm::vec3> &vertices,
    std::vector<uint32_t> &indices){
  float polarInc = M_PI/(m_stepsPolarAngle);
  float azimutInc = 2*M_PI/m_stepsAzimutAngle;
//  MFBox *pBox=new MFBox(glm::vec3(m_diameter,m_diameter,m_diameter));
//  pBox->createGeometry();
//  pBox->calculateGeometryData(vertices,indices);
//  return true;
  glm::vec3 vertexFirst={0.0f,0.0f,-m_length/2.0f-m_radius};
  vertices.push_back(vertexFirst);

  uint32_t countPolarSteps=0;
  uint32_t countAzimutSteps=0;
  for(float anglePolar=M_PI-polarInc;anglePolar>0;anglePolar-=polarInc){
    //z stays the same for each point of the azimut angles
    countPolarSteps++;
    countAzimutSteps=0;
    float zCoord=cos(anglePolar)*m_radius;//anglePolar
    float radiusAzimut=sin(anglePolar)*m_radius;//anglePolar
    for(float angleAzimut = 0; angleAzimut<2*M_PI; angleAzimut+=azimutInc){//circles around the sphere at each polar angle
      float xCoord=radiusAzimut*cos(angleAzimut);//angleAzimut
      float yCoord=radiusAzimut*sin(angleAzimut);//angleAzimut
      glm::vec3 vertex;
      if(zCoord<=0){
        vertex={xCoord,yCoord,zCoord-m_length/2};
      }else{
        vertex={xCoord,yCoord,zCoord+m_length/2};
      }
      vertices.push_back(vertex);
      countAzimutSteps++;
    }
  }

  //last vertex (top pole)
  glm::vec3 vertexLast={0.0f,0.0f,m_length/2.0f+m_radius};
  vertices.push_back(vertexLast);
  while((vertices.size()%16) != 0)
  {
    vertices.push_back(glm::vec3(.0f,.0f,m_length/2.0f));
  }
  //first indices
  for(uint32_t i = 1; i<=countAzimutSteps;i++){
    indices.push_back(0);
    indices.push_back(i);
    if(i==1)
      indices.push_back(countAzimutSteps);
    else
      indices.push_back(i-1);
  }

  for(uint32_t j = 0; j<countPolarSteps;j++){
    for(uint32_t i = 1; i<=countAzimutSteps;i++){
      if(
        ((j+1)*countAzimutSteps)+countAzimutSteps > vertices.size() ||
        ((j+1)*countAzimutSteps) + 1 > vertices.size()){
  //        MFObject::printErr("MFSphere::calculateGeometryData -"
  //            "Sphere index out of bounds!!!");
        continue;
      }
      if(i==1){

        indices.push_back((j*countAzimutSteps)+1);//+i
        indices.push_back((j*countAzimutSteps)+2);//+i+1
        indices.push_back(((j+1)*countAzimutSteps)+1);//First point of next circle

        indices.push_back((j*countAzimutSteps)+1);//+i
        indices.push_back(((j+1)*countAzimutSteps)+1);//First point of next circle
        indices.push_back(((j+1)*countAzimutSteps)+countAzimutSteps);//Last point of next circle
      }
      if(i>1 && i<countAzimutSteps){
        indices.push_back((j*countAzimutSteps)+i);//+i
        indices.push_back((j*countAzimutSteps)+i+1);//+i+1
        indices.push_back(((j+1)*countAzimutSteps)+i);//Parallel point of next circle

        indices.push_back((j*countAzimutSteps)+i);//+i
        indices.push_back(((j+1)*countAzimutSteps)+i);//Parallel point of next circle
        indices.push_back(((j+1)*countAzimutSteps)+i-1);//Parallel point of next circle -1
      }
      if(i==countAzimutSteps){
        indices.push_back((j*countAzimutSteps)+countAzimutSteps);//+i
        indices.push_back(((j+1)*countAzimutSteps)+countAzimutSteps);//Parallel point of next circle
        indices.push_back(((j+1)*countAzimutSteps)+countAzimutSteps-1);//Parallel point of next circle -1
      }
    }
  }

  //last indices
  uint32_t lastPointIndex=countAzimutSteps*countPolarSteps+1;
  for(uint32_t i = lastPointIndex-1; i>=lastPointIndex-1-countAzimutSteps;i--){
    indices.push_back(i);
    indices.push_back(lastPointIndex);
    if(i==lastPointIndex-1-countAzimutSteps)
      indices.push_back(lastPointIndex-1);
    else
      indices.push_back(i-1);
  }
  int counter=1;
  while((indices.size()%(16*3)) != 0)
  {
    if(counter%3==0){
//      indices[indices.size()-1]=vertices.size()-1-(counter+3);
//      indices[indices.size()-2]=vertices.size()-2-(counter+3);
//      indices[indices.size()-3]=vertices.size()-3-(counter+3);
    }
    counter++;
    indices.push_back(3);
  }
  return true;
}
