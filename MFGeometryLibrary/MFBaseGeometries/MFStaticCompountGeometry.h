/*
 * MFStaticCompountGeometry.h
 *
 *  Created on: 23.04.2021
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFSTATICCOMPOUNTGEOMETRY_H_
#define MFBASEGEOMETRIES_MFSTATICCOMPOUNTGEOMETRY_H_

#include "MFAbstractGeometry.h"
/**
 * This class provides functionality to statically add sub geometries. Static means that
 * the sub geometries cant be moved or manipulated.
 * TODO take the code from MFAbstractBulding
 */
class MFStaticCompountGeometry: public MFAbstractGeometry {
public:
  struct S_ChildSetup{
    MFAbstractGeometry* pGeo;
    glm::mat4x4 transform;
  };
private:
  std::vector<S_ChildSetup*>
  *pSubGeometries;

public:/*virtual functions MFAbstractGeometry:*/
  /**
   * returns a void* which must be a btCollisionShape*.
   */
  virtual void* createCollisionShape();

  virtual bool calculateGeometryData(
      std::vector<glm::vec3> &vertices,
      std::vector<uint32_t> &indices,
      std::vector<uint32_t> *pVertexColors,
      std::vector<glm::vec3> *pVertexNormals);

  virtual bool calculateGeometryData(
      std::vector<glm::vec3> &vertices,
      std::vector<uint32_t> &indices);

  virtual bool calculateGeometryData(MFVertexDataCollection* pDataCollection);

  /**
   * The parameter setup can be used to create the same geometry again. It must
   * provide all necessary information for recreation.
   * Appends setup parameters of this geometry to pSetup.
   * @param pSetup - setup which will be filled with the geometry setup parameters.
   */
  virtual void fillParameterSetup(MFStructurableDataSetup* pSetup);
public:
  MFStaticCompountGeometry();
  virtual ~MFStaticCompountGeometry();
};

#endif /* MFBASEGEOMETRIES_MFSTATICCOMPOUNTGEOMETRY_H_ */
