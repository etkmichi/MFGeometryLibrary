/*
 * MFConeCreator.h
 *
 *  Created on: 27.11.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCONE_H_
#define MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCONE_H_

#include "../MFInterfacesGeometries/MFIGeometryCreator.h"
#include "../MFCone.h"

class MFCreatorCone: public MFIGeometryCreator {
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
    MFObject::printInfo("MFCreatorCone::createGeometry");
    uint8_t* pData=(uint8_t*)pDataSetup;
    pData+=byteOffset;
    float radius=*((float*)pData);
    pData+=4;
    float length=*((float*)pData);
    MFCone *pS=new MFCone(length,radius);
    return pS;
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
  MFCreatorCone():MFIGeometryCreator("Cone"){};
  virtual ~MFCreatorCone(){};
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCONE_H_ */

