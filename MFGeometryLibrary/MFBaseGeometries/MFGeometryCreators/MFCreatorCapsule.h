/*
 * MFCreatorCapsule.h
 *
 *  Created on: 30.11.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCAPSULE_H_
#define MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCAPSULE_H_
#include "../MFInterfacesGeometries/MFIGeometryCreator.h"
#include "../MFCapsule.h"
class MFCreatorCapsule: public MFIGeometryCreator {
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
    MFObject::printInfo("MFCreatorCapsule::createGeometry");
    uint8_t* pData=(uint8_t*)pDataSetup;
    pData+=byteOffset;
    float radius=*((float*)pData);
    pData+=4;
    float length=*((float*)pData);
    MFCapsule *pS=new MFCapsule(length,radius);
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
    MFObject::printErr("MFCreatorCapsule::createGeometry - not impl.!");
    return nullptr;
  }
public:
  MFCreatorCapsule():MFIGeometryCreator("Capsule"){};
  virtual ~MFCreatorCapsule(){};
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORCAPSULE_H_ */
