/*
 * MFIGeometryCreator.h
 *
 *  Created on: 13.06.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFINTERFACESGEOMETRIES_MFIGEOMETRYCREATOR_H_
#define MFBASEGEOMETRIES_MFINTERFACESGEOMETRIES_MFIGEOMETRYCREATOR_H_
#include <MFData/MFStructurableDataSetup.h>
#include "../MFAbstractGeometry.h"
class MFIGeometryCreator {
public:
  std::string m_geometryName="";
public:/*virtual functions MFIGeometryCreator*/
  /**
   * Creates a geometry with data from pDataSetup
   * @param pDataSetup data setup which contains all necessary parameter as a
   * subsequence.
   * @param byteOffset index of first parameter within pDataSetup (if
   * parameters are a subsequence of pDataSetup)
   * @return
   */
  virtual MFAbstractGeometry* createGeometry(
      void* pDataSetup,
      uint32_t byteOffset=0){
    MFObject::printErr("MFIGeometryCreator::createGeometry - not impl.!");
    return nullptr;
  }
  /**
   * Creates a geometry with data from pDataSetup
   * @param pDataSetup data setup which contains all necessary parameter as a
   * subsequence.
   * @param parameterStartIndex index of first parameter within pDataSetup (if
   * parameters are a subsequence of pDataSetup)
   * @return
   */
  virtual MFAbstractGeometry* createGeometry(
      MFStructurableDataSetup* pDataSetup,
      uint32_t dataIndexOffset=0){
    MFObject::printErr("MFIGeometryCreator::createGeometry - not impl.!");
    return nullptr;
  }

public:
	MFIGeometryCreator(std::string geometryName){m_geometryName=geometryName;};
	virtual ~MFIGeometryCreator(){};
};

#endif /* MFBASEGEOMETRIES_MFINTERFACESGEOMETRIES_MFIGEOMETRYCREATOR_H_ */
