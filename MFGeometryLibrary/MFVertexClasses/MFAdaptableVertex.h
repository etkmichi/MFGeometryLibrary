/*
 * MFAdaptableVertex.h
 *
 *  Created on: 10.12.2019
 *      Author: michl
 */

#ifndef MFVERTEXCLASSES_MFADAPTABLEVERTEX_H_
#define MFVERTEXCLASSES_MFADAPTABLEVERTEX_H_

#include <MFData/MFDataObject.h>
#include <MFData/MFDataObjectBuffer.h>
#include <MFData/MFStructurableData.h>

/**
 * The adaptable vertex can be used to define a data structure for vertices. For example
 * it can be set up with a position (glm::vec3), a color (uint32_t), a normal (glm::vec3)
 * and a texture coordinate (glm::vec2) which may be needed in a renderer. The adaptable
 * vertex must be set up with the meta data of the needed data structure. For a definition
 * of a specific data element (i.e. glm::vec3) the class provides functions.
 * The complex vertex is a defineable vertex structure. It can be used
 * to match specific formats.
 */
class MFAdaptableVertex : public MFStructurableData{
public:
	MFAdaptableVertex();
	virtual ~MFAdaptableVertex();
	std::string toString();
	void printVertexData();
};

#endif /* MFVERTEXCLASSES_MFADAPTABLEVERTEX_H_ */
