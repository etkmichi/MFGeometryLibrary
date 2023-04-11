/*
 * MFGeoAxis.h
 *
 *  Created on: 03.01.2020
 *      Author: michl
 */

#ifndef MFGEOCLASSES_MFGEOAXIS_H_
#define MFGEOCLASSES_MFGEOAXIS_H_
#include <glm/glm.hpp>
class MFGeoAxis {
	MFGeoAxis
		*mp_parent,
		*mp_child;
	bool
		m_isTranslationAxis;
public:
	MFGeoAxis(glm::vec3 axis, bool isTranslationAxis);
	virtual ~MFGeoAxis();
	MFGeoAxis* getParent(){return mp_parent;};
	void setParent(MFGeoAxis* parent){mp_parent=parent;};
	MFGeoAxis* getChild(){return mp_child;};
	void setChild(MFGeoAxis* child){mp_child=child;};
	bool isRotationAxis(){return !m_isTranslationAxis;};
	bool isTranslationAxis(){return m_isTranslationAxis;};
};

#endif /* MFGEOCLASSES_MFGEOAXIS_H_ */
