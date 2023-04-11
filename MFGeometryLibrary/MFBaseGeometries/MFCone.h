/*
 * MFCone.h
 *
 *  Created on: 27.11.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFCONE_H_
#define MFBASEGEOMETRIES_MFCONE_H_

#include "MFAbstractGeometry.h"

class MFCone: public MFAbstractGeometry {
private:
  float
  m_radius,
  m_length;
  void*
  mp_btShape=nullptr;
  uint32_t
  m_stepsAzimutAngle=30;
public:/*virtual functions MFAbstractGeometry:*/
  /**
   * returns a void* which must be a btCollisionShape*.
   */
  virtual void* createCollisionShape();

  virtual bool calculateGeometryData(
    std::vector<glm::vec3> &vertices,
    std::vector<uint32_t> &indices);

  /**
   * The parameter setup can be used to create the same geometry again. It must
   * provide all necessary information for recreation.
   * Appends setup parameters of this geometry to pSetup.
   * @param pSetup - setup which will be filled with the geometry setup parameters.
   */
  virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
    pSetup->addData(&m_radius);
    pSetup->addData(&m_length);
  }
public:
  MFCone(float length=1.0f,float radius=1.0f);
  virtual ~MFCone();
};

#endif /* MFBASEGEOMETRIES_MFCONE_H_ */
