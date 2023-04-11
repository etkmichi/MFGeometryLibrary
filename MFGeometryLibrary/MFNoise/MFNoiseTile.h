/*
 * MFNoiseTile.h
 *
 *  Created on: 10.02.2020
 *      Author: michl
 */

#ifndef MFNOISE_MFNOISETILE_H_
#define MFNOISE_MFNOISETILE_H_

#include <vector>
#include <noise.h>
#include <glm/glm.hpp>

#include "../MFVertexClasses/MFVertexDataCollection.h"
#include "MFNoiseSetup.h"
#include "MFNoiseStructs.h"
//TODO MFColorizedNoiseTile MFNoiseTileGeometry:MFAbstractGeometry
class MFNoiseTile {
private:
	S_MFCalculationSetup
		*mp_calcSetup,
		*mp_internalCalcSetup;
	MFNoiseSetup
		*mp_noiseSetup,
		*mp_internalNoiseSetup;

	std::vector<glm::vec3>
		*mp_trianglePoints;
	std::vector<uint32_t>
		*mp_indices;
	glm::vec3
		m_surroundingBox;
public:
	MFNoiseTile();
	virtual ~MFNoiseTile();

	/**
	 * returns the noise value for the specified parameters. if useZ=false the z
	 * value for noise calculation depends on the noise calculation setup
	 * which can be changes/set by get/setCalculationSetup functions.
	 * @param x
	 * @param y
	 * @param z
	 * @param useZ
	 * @return
	 */
	float getNoiseValue(float x, float y, float z=0.0f,bool useZ=false);

  /**
   * returns the noise value for the specified parameters. if useZ=false the z
   * value for noise calculation depends on the noise calculation setup
   * which can be changes/set by get/setCalculationSetup functions.
   * @param x
   * @param y
   * @param z
   * @param useZ
   * @return
   */
  float getNoiseValue(double x, double y, double z=0.0f,bool useZ=false);

	void setCalculationSetup(S_MFCalculationSetup* pSetup){mp_calcSetup=pSetup;};
  MFNoiseSetup* getNoiseSetup(){return mp_noiseSetup;};


	void setNoiseSetup(MFNoiseSetup* pSetup){mp_noiseSetup=pSetup;};
	virtual bool calculateTile(
			std::vector<glm::vec3>* pTrianglePoints,
			std::vector<uint32_t>* pIndices);
	/**
	 * This function calculates extra data depending on the setup.
	 * @param pTrianglePoints
	 * @param pIndices
	 * @param pVertexColors - not implemented yet - color for each vertex
	 * @param pVertexNormals - normal for each vertex, weighened by surrounding triangles
	 * @return
	 */
	virtual bool calculateTile(
			std::vector<glm::vec3>* pTrianglePoints,
			std::vector<uint32_t>* pIndices,
			std::vector<uint32_t> *pVertexColors,
			std::vector<glm::vec3> *pVertexNormals);
	virtual bool calculateTile(MFVertexDataCollection* pDataCollection);
	virtual bool calculateIndices(std::vector<uint32_t> *pVecIndices);

	/**
	 * calculates the indices for a surface with xSteps*ySteps size
	 * @param pIndices
	 * @param xSteps
	 * @param ySteps
	 */
  void calculateIndices(
      std::vector<uint32_t> *pIndices,
      uint32_t xSteps,
      uint32_t ySteps);
	virtual bool calculateVertices(MFVertexDataCollection* pDataCollection);

	bool updateTile(MFVertexDataCollection* pDataCollection);
	//TODO virtual bool calculateColors; setColor
	/**
	 *
	 * @return the surrounding box.
	 */
	glm::vec3 getSurroundingBox(){return m_surroundingBox;};
	glm::vec3 getMinAABB(){return mp_calcSetup->startPosition;};
	glm::vec3 getMaxAABB(){return (mp_calcSetup->startPosition+getSurroundingBox());};
	S_MFCalculationSetup* getCalculationSetup(){return mp_calcSetup;};

	/**
	 * Calculates the vertex normal depending on the position. Creates surrounding
	 * vertices depending on the calculation setup and calculates the triangle normals.
	 * With the triangle normals the point normal is created.
	 * @param position
	 * @return
	 */
	glm::vec3 calcPointNormal(glm::vec3 &position);
	bool checkCalculationSetup();
};

#endif /* MFNOISE_MFNOISETILE_H_ */
