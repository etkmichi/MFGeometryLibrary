/*
 * MFStaticCompountGeometry.cpp
 *
 *  Created on: 23.04.2021
 *      Author: michl
 */
#include "MFStaticCompountGeometry.h"
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <MFBasicDefines.h>

MFStaticCompountGeometry::MFStaticCompountGeometry() :
MFAbstractGeometry("static compound"){
  pSubGeometries=new std::vector<S_ChildSetup*>();
}

MFStaticCompountGeometry::~MFStaticCompountGeometry() {
  // TODO Auto-generated destructor stub
}

void* MFStaticCompountGeometry::createCollisionShape(){
  btCompoundShape* pCS=new btCompoundShape();
  for(S_ChildSetup* pChild:*pSubGeometries){
    if(!pChild->pGeo->initBulletShape())continue;
    btTransform transform=btTransform();
    transform.setFromOpenGLMatrix((btScalar*)(&pChild->transform));
    pCS->addChildShape(
        transform,
        static_cast<btCollisionShape*>(pChild->pGeo->getBulletCollisionShape())
        );
  }
  return pCS;
}

bool MFStaticCompountGeometry::calculateGeometryData(
    std::vector<glm::vec3> &vertices,
    std::vector<uint32_t> &indices,
    std::vector<uint32_t> *pVertexColors,
    std::vector<glm::vec3> *pVertexNormals){
  return calculateGeometryData(vertices,indices);
}

bool MFStaticCompountGeometry::calculateGeometryData(
    std::vector<glm::vec3> &vertices,
    std::vector<uint32_t> &indices){
  bool ret=true;
  for(S_ChildSetup* pChild:*pSubGeometries){
    //parts shall be movable -> vertices must be separeated by parts
    uint32_t startIndex=vertices.size();
    if(!pChild->pGeo->calculateGeometryData(vertices, indices)){
      P_ERR("failed to create geometry!");
      ret=false;
    }

    /*iterate over vertices and transform them to given position*/
    uint32_t stopIndex=vertices.size();
    for(;startIndex<stopIndex;startIndex+=1){
      glm::mat3x3 transform=(glm::mat3x3)pChild->transform;
      vertices.data()[startIndex]=vertices.data()[startIndex]*transform;
    }

  }
  return ret;
}

bool MFStaticCompountGeometry::calculateGeometryData(MFVertexDataCollection* pDataCollection){
  P_ERR("no impl.!");
  return false;
}

void MFStaticCompountGeometry::fillParameterSetup(MFStructurableDataSetup* pSetup){
  if(mp_geometrySetup!=nullptr){
    pSetup->appendDataStructure(mp_geometrySetup);
  }
  for(S_ChildSetup* pBS:*pSubGeometries){
    pBS->pGeo->fillParameterSetup(pSetup);
  }
}
