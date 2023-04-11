/*
 * MFDynCompoundGeometry.cpp
 *
 *  Created on: 23.04.2021
 *      Author: michl
 */

#include "MFDynCompoundGeometry.h"
#include <MFBasicDefines.h>

MFDynCompoundGeometry::MFDynCompoundGeometry() {
  pVecGeometries=new std::vector<MFAbstractGeometry*>();
  pVecChildParts=new std::vector<S_SubStructure*>();
  pCompoundShape=new btCompoundShape(true,0);
  pPhysicsGeometry=new MFAbstractGeometry("physics compound geometry");
  pPhysicsGeometry->setBulletShape(pCompoundShape);
}

MFDynCompoundGeometry::~MFDynCompoundGeometry() {
  // TODO Auto-generated destructor stub
}

bool MFDynCompoundGeometry::initGeometries() {
  bool ret=true;
  if(!initChildStructures()){
    ret=false;
    P_ERR("failed to init child sturctures!");
  }
  for(MFAbstractGeometry* pGeo:*pVecGeometries){
    if(!pGeo->initGeometry()){
      ret=false;
      P_ERR("failed to create child geometry! Geometry name: "+pGeo->getGeometryName());
    }
  }
  return ret;
}

const btTransform& MFDynCompoundGeometry::getChildTransform(uint32_t index){
  return pCompoundShape->getChildTransform(index);
}
S_SubStructure* MFDynCompoundGeometry::addChildGeometry(
    const glm::mat4x4 &localTransform,
    MFAbstractGeometry* pGeometry)
{
  if(pGeometry==nullptr){
    P_ERR("geometry is nullptr!");
    return nullptr;
  }

  pVecGeometries->push_back(pGeometry);
  if(!pGeometry->initBulletShape()){
    P_WRN("failed to init bullet shape! This geometry will only be added for rendering purpose!");
    return nullptr;
  }

  btCollisionShape* pCS=static_cast<btCollisionShape*>(pGeometry->getBulletCollisionShape());
  S_SubStructure* pBS=new S_SubStructure();
  pBS->pGeo=pGeometry;
  pBS->pGeoShape=pCS;
  pBS->index=pCompoundShape->getNumChildShapes();

  btTransform trans = btTransform();
  trans.setFromOpenGLMatrix((btScalar*)(&localTransform));

  pCompoundShape->addChildShape(trans, pBS->pGeoShape);
  pVecChildParts->push_back(pBS);
  pCompoundShape->updateChildTransform (
      pBS->index,trans,true);
//  pBS->pChild=&pCompoundShape->getChildList()[pBS->index];
//  pBS->pTransform=&pCompoundShape->getChildTransform(pBS->index);
  return pBS;
}

void MFDynCompoundGeometry::updateChildTransform(uint32_t index,const btTransform& localTransform){
  pCompoundShape->updateChildTransform(index, localTransform, true);
}
