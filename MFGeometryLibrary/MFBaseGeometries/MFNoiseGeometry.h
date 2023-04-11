/*
 * MFNoiseGeometry.h
 *
 *  Created on: 11.02.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFNOISEGEOMETRY_H_
#define MFBASEGEOMETRIES_MFNOISEGEOMETRY_H_

#include "../MFNoise/MFNoiseSetup.h"
#include "MFAbstractGeometry.h"
#include "../MFNoise/MFNoiseTile.h"
#include "../MFNoise/MFNoiseStructs.h"

class MFNoiseGeometry: public MFAbstractGeometry {
private:
	MFNoiseTile
		*mp_noiseTile,
		*mp_innerNoiseTile;
	void*
		mp_stridingMesh=nullptr;
	void*
		mp_heightData=nullptr;
public:
	MFNoiseGeometry();
	MFNoiseGeometry(MFNoiseTile* pNoiseTile);
	virtual ~MFNoiseGeometry();

	virtual bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices);
	virtual bool calculateGeometryData(
		std::vector<glm::vec3> &vertices,
		std::vector<uint32_t> &indices,
		std::vector<uint32_t> *pVertexColors,
		std::vector<glm::vec3> *pVertexNormals);
	virtual bool calculateGeometryData(MFVertexDataCollection* pDataCollection);
	virtual void* createCollisionShape();
	virtual void* createCollisionShape(MFVertexDataCollection* pDataCollection);
	bool updateData(
			std::vector<glm::vec3> &vertices,
			std::vector<uint32_t> &indices,
			std::vector<uint32_t> *pVertexColors,
			std::vector<glm::vec3> *pVertexNormals);
	virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
		pSetup->addNBitValue(sizeof(S_MFCalculationSetup),
				mp_noiseTile->getCalculationSetup());
	}
	bool updateData();
	void setNoiseConfig(S_MFNoiseConfig* pConfig);
	void setCalculationSetup(S_MFCalculationSetup* pCalcSetup);
	MFNoiseTile* getNoiseTile(){return mp_noiseTile;}

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
  float getNoiseValue(float x, float y, float z=0.0f,bool useZ=false){
    return mp_noiseTile->getNoiseValue(x,y,z,useZ);
  }
  float getNoiseValue(double x, double y, double z=0.0f,bool useZ=false){
    return mp_noiseTile->getNoiseValue(x,y,z,useZ);
  }
};

#endif /* MFBASEGEOMETRIES_MFNOISEGEOMETRY_H_ */
