/*
 * MFGeometryManager.h
 *
 *  Created on: 11.06.2020
 *      Author: michl
 */

#ifndef MFGEOMETRYMANAGER_H_
#define MFGEOMETRYMANAGER_H_
#include <vector>
#include <MFData/MFStructurableDataSetup.h>
#include <MFData/MFDataObject.h>
#include "MFBaseGeometries/MFInterfacesGeometries/MFIGeometryCreator.h"
#include "MFBaseGeometries/MFAbstractGeometry.h"
#include "MFNoise/MFNoiseStructs.h"
/**
 * This manager provides access to geometries provided by the MFGeometryLibrary and custom
 * geometries. To make custom geometries available, a subclass of this manager must be
 * created and the custom geometries must be registered to this manager.
 */
class MFGeometryManager {

private:
  bool
  initCreatorsDone=false;
	std::vector<MFIGeometryCreator*>
		*mp_vecCreators;
	static uint32_t
		indexSphere,
		indexAxis,
		indexBox,
		indexNoise,
		indexCylinder,
		indexCone,
		indexCapsule;
public:
	MFGeometryManager();//TODO use index within data setup of abstract geometry -> force all
	//geos to use an index!
	virtual ~MFGeometryManager();
	void initGeometryCreators();
	MFAbstractGeometry* createSphere(float diameter);
	MFAbstractGeometry* createBox(glm::vec3 dimensions);
	MFAbstractGeometry* createAxis(glm::vec3 direction,float length);
	MFAbstractGeometry* createCylinder(float length,float radius);
	MFAbstractGeometry* createCone(float length,float radius);
	MFAbstractGeometry* createCapsule(float length,float radius);
	MFAbstractGeometry* createNoise(
			S_MFCalculationSetup *pCalcSetup,
			S_MFNoiseConfig *pNoiseConfig);

	MFAbstractGeometry* getStaticGeometry(uint32_t index){return nullptr;};
	//TODO implement with scaled sphere and corresponding physics object
	//scaling should be done in mfsyncobject
  MFAbstractGeometry* getStaticSphere(){return nullptr;};

	/**
	 * This will create a geometry by the given data setup. The data setup must
	 * contain a valid creator index to the managers std::vector<MFIGeometryCreator*>.
	 * The creator index must be at position 0 within pParameters.
	 * Examples: structurable data |creator index | parameters...
	 * Sphere: | 0 | radius (float)
	 * Axis: | 1 | direction (glm::vec3) | length (float)
	 * @param pParameters -
	 * @return nullptr if creation failed.
	 */
	MFAbstractGeometry* createGeometry(MFStructurableDataSetup* pParameters);

	/**
	 * This will create a geometry by the given data, which must fullfill
	 * a valid structure for creation of a geometry
	 * (structure: uint32_t creatorIndex | parameter list for creator).
	 * Examples: structurable data |creator index | parameters...
	 * Sphere: | 0 | radius (float)
	 * Axis: | 1 | direction (glm::vec3) | length (float)
	 * @param pParameters
	 * @return nullptr if creation failed.
	 */
	MFAbstractGeometry* createGeometry(void* pParameters);

	uint32_t addGeometryCreator(MFIGeometryCreator* pCreator);

	uint32_t getIndexGeometry(MFAbstractGeometry* pGeo);

  uint32_t getIndexAxis() const {
    return indexAxis;
  }

  uint32_t getIndexBox() const {
    return indexBox;
  }

  uint32_t getIndexCapsule() const {
    return indexCapsule;
  }

  uint32_t getIndexCone() const {
    return indexCone;
  }

  uint32_t getIndexCylinder() const {
    return indexCylinder;
  }

  uint32_t getIndexNoise() const {
    return indexNoise;
  }

  uint32_t getIndexSphere() const {
    return indexSphere;
  }
};

#endif /* MFGEOMETRYMANAGER_H_ */
