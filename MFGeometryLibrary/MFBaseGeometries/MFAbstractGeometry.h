/*
 * MFAbstractGeometry.h
 *
 *  Created on: 23.10.2019
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFABSTRACTGEOMETRY_H_
#define MFBASEGEOMETRIES_MFABSTRACTGEOMETRY_H_
#include <vector>
#include <glm/glm.hpp>
#include <MFObjects/MFObject.h>
#include <MFData/MFDataObjectBuffer.h>
#include <MFData/MFStructurableDataSetup.h>
#include "../MFVertexClasses/MFAdaptableVertex.h"
#include "../MFVertexClasses/MFVertexDataCollection.h"
#include "MFGeometryData.h"
class MFAbstractGeometry {
protected:
  std::string
  m_geometryName="";

  MFStructurableDataSetup
  *mp_innerGeometrySetup,
  *mp_geometrySetup;

  MFGeometryData
  m_geometryData;

  MFVertexDataCollection
  m_vertexDataCollection;

  glm::vec3
  m_initPosition,
  m_offset;

  bool
  m_isCreated=false;

  void*
  mp_btShape=nullptr;

public:/*virtual functions MFAbstractGeometry:*/
  /**
   * returns a void* which must be a btCollisionShape*.
   */
  virtual void* createCollisionShape(){return nullptr;};

  void setBulletShape(void* btShape){
    mp_btShape=btShape;
  }

  virtual bool calculateGeometryData(
      std::vector<glm::vec3> &vertices,
      std::vector<uint32_t> &indices,
      std::vector<uint32_t> *pVertexColors,
      std::vector<glm::vec3> *pVertexNormals){
    return calculateGeometryData(vertices,indices);
  };

  virtual bool calculateGeometryData(
      std::vector<glm::vec3> &vertices,
      std::vector<uint32_t> &indices){
    return false;
  };

  virtual bool calculateGeometryData(MFVertexDataCollection* pDataCollection){
    return false;
  };

  /**
   * The parameter setup can be used to create the same geometry again. It must
   * provide all necessary information for recreation.
   * Appends setup parameters of this geometry to pSetup.
   * @param pSetup - setup which will be filled with the geometry setup parameters.
   */
  virtual void fillParameterSetup(MFStructurableDataSetup* pSetup){
    if(mp_geometrySetup!=nullptr){
      pSetup->appendDataStructure(mp_geometrySetup);
    }else{
      MFObject::printErr("fillParameterSetup - "
          "couldn't fill setup, function is not implemented and inner setup is "
          "nullptr!");
    }
  };

public:
  MFAbstractGeometry(std::string geometryName=""){
    m_geometryName=geometryName;
    m_initPosition=glm::vec3(0,0,0);
    mp_innerGeometrySetup=new MFStructurableDataSetup();
    mp_geometrySetup=mp_innerGeometrySetup;
    m_geometryData.clear();
  };
  virtual ~MFAbstractGeometry(){
    delete mp_innerGeometrySetup;
  };
  bool reinitGeometry(){
    m_isCreated=false;
    return initGeometry();
  };

  /**
   * @return if createCollisionShape will create a valid btCollisionShape and initBulletShape
   * was successfull, this function will return a btCollisionShape as void*.
   */
  void* getBulletCollisionShape(){return mp_btShape;};

  /*TODO at the moment this is more like initGeometry*/
  bool initGeometry();
  bool initGeometry(E_CreateGeometryFlag creationFlag);
  bool initBulletShape(){
    if(mp_btShape==nullptr)mp_btShape=createCollisionShape();
    return (mp_btShape!=nullptr);
  }
  MFVertexDataCollection& getVertexDataCollection(){return m_vertexDataCollection;};
  bool isCreated(){return m_isCreated;};
  //TODO add point offset to the parameter

  std::vector<glm::vec3>& getVecVertices(){return m_geometryData.m_vecVertices;};
  std::vector<uint32_t>& getVecIndices(){return m_geometryData.m_vecIndices;}
  std::vector<glm::vec3>& getVecVertexNormals(){return m_geometryData.m_vecVertexNormals;};
  glm::vec3 getInitPosition(){return m_initPosition;};
  MFGeometryData& getGeometryData(){return m_geometryData;};
  void setInitPosition(glm::vec3 pos){m_initPosition=pos;};

  /**
   * The local offset will be added to each point during creation of the geometry.
   * @param offset
   */
  void setLocalOffset(glm::vec3 offset){m_offset=offset;};
  glm::vec3 getLocalOffset(){return m_offset;};

  /**
   * The geometry setup is used for storing data which are needed for creation.
   * F.e. for a sphere, data may be the radius and the sphere's creation index
   * of MFGeometryManager.
   * Attation:
   * The setup may be extended externally (MFGeometryManager).
   * @return nullptr if not set.
   */
  MFStructurableDataSetup* getGeometrySetup(){return mp_geometrySetup;};

  /**
   * Serializes the geometry setup. Format: |size of geo setup | geo setup|
   * (f.e. sphere: | 4 | float32(radius)|)
   * @param copiedBytes - count of bytes which were copied to pDst
   * @param pDst - destination for geometry setup
   * @param maxSize - max count of bytes to copy to pDst. If not enough for setup,
   * this function returns false without copiing anything. If maxSize==0 the size
   * check will be ignored!
   * @return true if data was copied successfully to pDst.
   */
  bool serializeGeometrySetup(
      uint32_t &copiedBytes,
      uint8_t *pDst,
      uint32_t maxSize=0);

  void* createSerializedGeometrySetup(uint32_t &byteSize);

  uint32_t getSerializedByteSize();

  const std::string& getGeometryName(){return m_geometryName;}
  void setGeometryName(const std::string &name){m_geometryName=name;};

  /**
   * Set the geometry to provide a valid setup for the geometry.
   * @param pSetup
   */
  void setGeometrySetup(MFStructurableDataSetup* pSetup){mp_geometrySetup=pSetup;};
};



#endif /* MFBASEGEOMETRIES_MFABSTRACTGEOMETRY_H_ */
