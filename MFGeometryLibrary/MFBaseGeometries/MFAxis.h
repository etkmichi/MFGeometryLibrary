/*
 * MFXAxis.h
 *
 *  Created on: 14.10.2019
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFAXIS_H_
#define MFBASEGEOMETRIES_MFAXIS_H_
#include <stdint.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "MFAbstractGeometry.h"

class MFAxis :public MFAbstractGeometry
{
	glm::vec3
		m_axe;
	float
		m_length;

public:
	/**
	 *
	 * @param axis - a vector which will be normalized and multiplied with length. The axis will
	 * align to this vector.
	 * @param length
	 */
	MFAxis(glm::vec3 axis,float length);
	virtual ~MFAxis();
	bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices);
	virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
		pSetup->add3DVec(&m_axe);
		pSetup->addData(&m_length);
	}
};

#endif /* MFBASEGEOMETRIES_MFAXIS_H_ */
