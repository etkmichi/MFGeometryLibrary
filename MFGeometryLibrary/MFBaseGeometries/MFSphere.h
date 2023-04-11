/*
 * MFSphere.h
 *
 *  Created on: 01.10.2019
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFSPHERE_H_
#define MFBASEGEOMETRIES_MFSPHERE_H_

#include <stdint.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include "MFAbstractGeometry.h"

class MFSphere : public MFAbstractGeometry{
private:
  float
  m_diameter=1.0f;

  void*
  mp_buffer=nullptr;

  uint32_t
  m_byteSize=0,
  m_stepsPolarAngle=15,
  m_stepsAzimutAngle=15;

public:/*virtual functions MFAbstractGeometry:*/
  /**
   * returns a void* which must be a btCollisionShape*.
   */
  virtual void* createCollisionShape();


  virtual bool calculateGeometryData(
      std::vector<glm::vec3> &vertices,
      std::vector<uint32_t> &indices);

  virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
    pSetup->addData(&m_diameter);
  }

public:
  MFSphere(float diameter);
  virtual ~MFSphere();
  void setDiameter(float diameter);
  void setPolarAngleSteps(uint32_t steps);
  void setAzimutAngleSteps(uint32_t steps);
  uint32_t getPolarAngleSteps();
  uint32_t getAzimutAngleSteps();
  float getDiameter();
};

#endif /* MFBASEGEOMETRIES_MFSPHERE_H_ */
