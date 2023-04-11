/*
 * MFBox.h
 *
 *  Created on: 28.10.2019
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFBOX_H_
#define MFBASEGEOMETRIES_MFBOX_H_

#include "MFAbstractGeometry.h"

class MFBox: public MFAbstractGeometry {
protected:
	glm::vec3
		m_boxExtents;
public:
	MFBox(glm::vec3 extent);
	virtual ~MFBox();
	bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices);
	void* createCollisionShape();

	virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
		pSetup->add3DVec(&m_boxExtents);
	}
	float getHeight(){return m_boxExtents.y;};
	float getDepth(){return m_boxExtents.z;};
	float getWidth(){return m_boxExtents.x;};
	glm::vec3 getExtents(){return m_boxExtents;};
};

#endif /* MFBASEGEOMETRIES_MFBOX_H_ */
