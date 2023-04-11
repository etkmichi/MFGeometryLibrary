/*
 * MFDynCompoundGeometry.h
 *
 *  Created on: 23.04.2021
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFDYNCOMPOUNDGEOMETRY_H_
#define MFBASEGEOMETRIES_MFDYNCOMPOUNDGEOMETRY_H_
/**
 * This class provides functionality to setup a structure out of sub geometries.
 * The class itself isn't a geometry because the underlying geometries shall be dynamic
 * (movable, removable, ...).
 * TODO take code from MFAbstractBulding
 */
#include "MFAbstractGeometry.h"
#include <BulletCollision/CollisionShapes/btCompoundShape.h>
#include <vector>

struct S_SubStructure {
  MFAbstractGeometry* pGeo=nullptr;
  btCollisionShape* pGeoShape=nullptr;
  uint32_t index=0xFFFFFFFF;
};
/**
 * This class provides functionality to create a compound geometry. Because the
 * resulting geometry shall be dynamic, this class is not a subclass of MFAbstractGeometry!
 * If the sub-geometries shall be static, MFStaticCompoundGeometries should be used.
 * TODO init physical geometry pPhysicsGeometry so that it can be serialized!
 */
class MFDynCompoundGeometry {
protected:
  MFAbstractGeometry*
  pPhysicsGeometry;
  btCompoundShape
  *pCompoundShape=nullptr;
  std::vector<S_SubStructure*>
  *pVecChildParts;
  std::vector<MFAbstractGeometry*>
  *pVecGeometries;
public:/*virtual functions of MFDynCompoundGeometry*/
  virtual bool initChildStructures() = 0;
public:
  MFDynCompoundGeometry();
  virtual ~MFDynCompoundGeometry();
  bool initGeometries();
  std::vector<MFAbstractGeometry*>* getVecSubGeometries(){return pVecGeometries;};

  S_SubStructure* addChildGeometry(
      const glm::mat4x4 &localTransform,
      MFAbstractGeometry* pGeometry);

  /**
   * this function will return a MFAbstractGeometry which only provides the physics data without
   * the geometry data for rendering!
   * @return
   */
  MFAbstractGeometry* getPhysicalGeometry(){return pPhysicsGeometry;};
  const btTransform& getChildTransform(uint32_t index);
  void updateChildTransform(uint32_t index,const btTransform& localTransform);
};

#endif /* MFBASEGEOMETRIES_MFDYNCOMPOUNDGEOMETRY_H_ */
