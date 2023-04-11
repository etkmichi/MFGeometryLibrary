/*
 * MFGeoAxis.cpp
 *
 *  Created on: 03.01.2020
 *      Author: michl
 */

#include "MFGeoAxis.h"

MFGeoAxis::MFGeoAxis(glm::vec3 axis, bool isTranslationAxis) {
	mp_child=nullptr;
	mp_parent=nullptr;
	m_isTranslationAxis=isTranslationAxis;
}

MFGeoAxis::~MFGeoAxis() {
	// TODO Auto-generated destructor stub
}

