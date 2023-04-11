/*
 * MFCylinder.h
 *
 *  Created on: 28.10.2019
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFCYLINDER_H_
#define MFBASEGEOMETRIES_MFCYLINDER_H_

#include "MFAbstractGeometry.h"

class MFCylinder: public MFAbstractGeometry {
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
	MFCylinder(float length=1.0f,float radius=1.0f);
	virtual ~MFCylinder();
};

#endif /* MFBASEGEOMETRIES_MFCYLINDER_H_ */
