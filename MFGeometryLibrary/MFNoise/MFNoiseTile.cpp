/*
 * MFNoiseTile.cpp
 *
 *  Created on: 10.02.2020
 *      Author: michl
 */

#include "MFNoiseTile.h"
#include <MFObjects/MFObject.h>

MFNoiseTile::MFNoiseTile() {
	mp_internalCalcSetup=new S_MFCalculationSetup();
	mp_internalNoiseSetup=new MFNoiseSetup();
	setCalculationSetup(mp_internalCalcSetup);
	setNoiseSetup(mp_internalNoiseSetup);
}

MFNoiseTile::~MFNoiseTile() {
	delete mp_internalCalcSetup;
	delete mp_internalNoiseSetup;
}

bool MFNoiseTile::checkCalculationSetup() {
	if(mp_calcSetup->xSteps==0 || mp_calcSetup->ySteps==0){
		MFObject::printErr("MFNoiseTile::checkCalculationSetup() - "
				"mp_calcSetup->xSteps==0 || mp_calcSetup->ySteps==0");
	}

	return true;
}

bool MFNoiseTile::calculateTile(
		std::vector<glm::vec3>* pTrianglePoints,
		std::vector<uint32_t>* pIndices){
	if(!checkCalculationSetup())
		return false;

//	pTrianglePoints->clear();
//	pIndices->clear();
	glm::vec3
		startPos=mp_calcSetup->startPosition,
		curPos=mp_calcSetup->startPosition;
	float
		xEnd=mp_calcSetup->xRange+curPos.x,
		yEnd=mp_calcSetup->yRange+curPos.y,
		xInc=(mp_calcSetup->xRange/ mp_calcSetup->xSteps),
		yInc=(mp_calcSetup->yRange / mp_calcSetup->ySteps);
	uint32_t
		pointCount=(mp_calcSetup->xSteps+1)*(mp_calcSetup->ySteps+1),
		oaSteps=0,
		xSteps=0;//TODO
//	MFObject::printInfo("Calculating points for [start:end]:\n[xStrt="+
//			std::to_string(startPos.x)+" : xEnd="+std::to_string(xEnd)+
//			"] [yStrt="+std::to_string(startPos.y)+" :"+" yEnd="+std::to_string(yEnd)+"]");
	pTrianglePoints->resize(pointCount);
	noise::module::Module* pSource=mp_noiseSetup->getNoiseSource();
	float
		min_z=pSource->GetValue(curPos.x, curPos.y, mp_calcSetup->getZ(curPos.x,curPos.y)),
		max_z=min_z;
	/*Calculate the points*/
	//TODO check if Inc's are rounded to next lower float, if yes,
	//there will be more points than pointCount!
	for(uint32_t yS=0 ; yS<=mp_calcSetup->ySteps; yS++){
		//TODO MFIterationSetup for sphere...
		float y=startPos.y+yS*yInc;
		xSteps=0;//TODO virtual functions iterate(.. getMax addIterationLoop
		for(uint32_t xS=0 ;xS<=mp_calcSetup->xSteps; xS++){
			float x=startPos.x+xS*xInc;
			float z=pSource->GetValue(x, y, mp_calcSetup->getZ(x,y));
			curPos=glm::vec3(x-startPos.x,y-startPos.y,z);
			if(z<min_z){
				min_z=z;
			}
			if(z>max_z){
				max_z=z;
			}
			xSteps++;
			oaSteps++;
			if(oaSteps>pointCount){
				MFObject::printWarning("MFNoiseTile::calculateTile - "
						"More points than calculated!");
				pTrianglePoints->push_back(curPos);
			}else{
				pTrianglePoints->at(oaSteps-1)=curPos;
			}
		}
	}
	if(max_z==min_z){
		max_z+=0.01;
	}
	m_surroundingBox=glm::vec3(
			xEnd-mp_calcSetup->startPosition.x,
			yEnd-mp_calcSetup->startPosition.y,
			max_z-min_z);
	/*Calculate the indices*/
	uint32_t indicesCount=mp_calcSetup->ySteps*mp_calcSetup->xSteps*6;
	pIndices->resize(indicesCount);
	uint32_t index=0;
	for(uint32_t yS=0 ; yS<=mp_calcSetup->ySteps-1; yS++){
		for(uint32_t xS=0 ;xS<=mp_calcSetup->xSteps-1; xS++){
			if((index+6) > indicesCount){
				MFObject::printErr("MFNoiseTile::calculateTile - cant setup"
						"valid indices!");
				return false;
			}
			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS);
			index++;
			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS);
			index++;

			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS);
			index++;
		}
	}
	return true;
}

float MFNoiseTile::getNoiseValue(float x, float y, float z,bool useZ){
  noise::module::Module* pSource=mp_noiseSetup->getNoiseSource();
  if(!useZ){
    return pSource->GetValue(x, y, mp_calcSetup->getZ(x,y));
  }else{
    return pSource->GetValue(x, y, z);
  }
}

float MFNoiseTile::getNoiseValue(double x, double y, double z,bool useZ){
  noise::module::Module* pSource=mp_noiseSetup->getNoiseSource();
  if(!useZ){
    return pSource->GetValue(x, y, mp_calcSetup->getZ(x,y));
  }else{
    return pSource->GetValue(x, y, z);
  }
}

bool MFNoiseTile::calculateTile(
		std::vector<glm::vec3>* pTrianglePoints,
		std::vector<uint32_t>* pIndices,
		std::vector<uint32_t> *pVertexColors,
		std::vector<glm::vec3> *pVertexNormals){
	if(!checkCalculationSetup())
		return false;
//	pTrianglePoints->clear();
//	pIndices->clear();
//	pVertexColors->clear();
//	pVertexNormals->clear();
	glm::vec3
		startPos=mp_calcSetup->startPosition,
		curPos=mp_calcSetup->startPosition;
	float
		xEnd=mp_calcSetup->xRange+curPos.x,
		yEnd=mp_calcSetup->yRange+curPos.y,
		xInc=(mp_calcSetup->xRange/ mp_calcSetup->xSteps),
		yInc=(mp_calcSetup->yRange / mp_calcSetup->ySteps);
	uint32_t
		pointCount=(mp_calcSetup->xSteps+1)*(mp_calcSetup->ySteps+1),
		oaSteps=0,
		xSteps=0;//TODO
//	MFObject::printInfo("Calculating points for [start:end]:\n[xStrt="+
//			std::to_string(startPos.x)+" : xEnd="+std::to_string(xEnd)+
//			"] [yStrt="+std::to_string(startPos.y)+" :"+" yEnd="+std::to_string(yEnd)+"]");
	pTrianglePoints->resize(pointCount);
	pVertexNormals->resize(pointCount);
	noise::module::Module* pSource=mp_noiseSetup->getNoiseSource();
	float
		min_z=getNoiseValue(curPos.x, curPos.y),
		max_z=min_z;
	/*Calculate the points*/
	//TODO check if Inc's are rounded to next lower float, if yes,
	//there will be more points than pointCount!
	for(uint32_t yS=0 ; yS<=mp_calcSetup->ySteps; yS++){
		//TODO MFIterationSetup for sphere...
		float y=startPos.y+yS*yInc;
		xSteps=0;//TODO virtual functions iterate(.. getMax addIterationLoop
		for(uint32_t xS=0 ;xS<=mp_calcSetup->xSteps; xS++){
			float x=startPos.x+xS*xInc;
			float z=pSource->GetValue(x, y, mp_calcSetup->getZ(x,y));
			curPos=glm::vec3(x-startPos.x,y-startPos.y,z);
			if(z<min_z){
				min_z=z;
			}
			if(z>max_z){
				max_z=z;
			}
			xSteps++;
			oaSteps++;
			if(oaSteps>pointCount){
				MFObject::printWarning("MFNoiseTile::calculateTile - "
						"More points than calculated!");
				pTrianglePoints->push_back(curPos);
				pVertexNormals->push_back(calcPointNormal(curPos));
			}else{
				pTrianglePoints->at(oaSteps-1)=curPos;
//				MFObject::printVec3(curPos);
				pVertexNormals->at(oaSteps-1)=calcPointNormal(curPos);
			}
		}
	}

	if(max_z==min_z){
		max_z+=0.01;
	}

	m_surroundingBox=glm::vec3(
			xEnd-mp_calcSetup->startPosition.x,
			yEnd-mp_calcSetup->startPosition.y,
			max_z-min_z);

	/*Calculate the indices*/
	calculateIndices(pIndices,mp_calcSetup->xSteps,mp_calcSetup->ySteps);

	return true;
}

void MFNoiseTile::calculateIndices(
    std::vector<uint32_t> *pIndices,
    uint32_t xSteps,
    uint32_t ySteps){
  uint32_t indicesCount=ySteps*xSteps*6;
  pIndices->resize(indicesCount);
  uint32_t index=0;
  for(uint32_t yS=0 ; yS<=ySteps-1; yS++){
    for(uint32_t xS=0 ;xS<=xSteps-1; xS++){
      if((index+6)>indicesCount){
        MFObject::printErr("MFNoiseTile::calculateTile - cant setup"
            "valid indices!");
        return;
      }
      pIndices->at(index)=(yS*(xSteps+1)+xS);
      index++;
      pIndices->at(index)=(yS*(xSteps+1)+xS+1);
      index++;
      pIndices->at(index)=((yS+1)*(xSteps+1)+xS);
      index++;

      pIndices->at(index)=(yS*(xSteps+1)+xS+1);
      index++;
      pIndices->at(index)=((yS+1)*(xSteps+1)+xS+1);
      index++;
      pIndices->at(index)=((yS+1)*(xSteps+1)+xS);
      index++;
    }
  }

}

bool MFNoiseTile::calculateTile(MFVertexDataCollection* pDataCollection){
	if(!checkCalculationSetup()){
		MFObject::printErr("MFNoiseTile::calculateTile - invalid calculation setup!");
		return false;
	}

	uint32_t
		pointCount=(mp_calcSetup->xSteps+1)*(mp_calcSetup->ySteps+1);
	pDataCollection->setVertexCount(pointCount);
	pDataCollection->use32BitIndexedNormals(true);
	pDataCollection->setupComplexVertices();
	bool ret=calculateVertices(pDataCollection);
	/*Calculate the indices*/
	std::vector<uint32_t>* pIndices=pDataCollection->getVertexIndices();
	ret&=calculateIndices(pIndices);
	return ret;
}

bool MFNoiseTile::updateTile(MFVertexDataCollection* pDataCollection){
	uint32_t
		pointCount=(mp_calcSetup->xSteps+1)*(mp_calcSetup->ySteps+1);
	if(pDataCollection->getVertexCount()!=pointCount){
		MFObject::printWarning("MFNoiseTile::updateTile - point count of collection "
				"doesn't match calculation setup, update will recreate tile!");
		MFObject::printInfo("MFNoiseTile::updateTile - setupCount/calcCount:"+
				std::to_string(pDataCollection->getVertexCount())+"/"+
				std::to_string(pointCount));
		calculateTile(pDataCollection);//TODO test°!
	}
	return calculateVertices(pDataCollection);
}
bool MFNoiseTile::calculateVertices(MFVertexDataCollection* pDataCollection){
	MFAdaptableVertex* pVertex=nullptr;
	glm::vec3
		startPos=mp_calcSetup->startPosition,
		curPos=mp_calcSetup->startPosition,
		vtxNrml=glm::vec3(1,0,0);
	float
		xEnd=mp_calcSetup->xRange+curPos.x,
		yEnd=mp_calcSetup->yRange+curPos.y,
		xInc=(mp_calcSetup->xRange/ mp_calcSetup->xSteps),
		yInc=(mp_calcSetup->yRange / mp_calcSetup->ySteps);
	std::vector<MFAdaptableVertex*>
		*pVecVertices=pDataCollection->getComplexVertices();
	noise::module::Module
		*pSource=mp_noiseSetup->getNoiseSource();
	float
		min_z=pSource->GetValue(curPos.x, curPos.y, mp_calcSetup->getZ(curPos.x,curPos.y)),
		max_z=min_z+0.01f;
	uint32_t
		pointCount=pDataCollection->getVertexCount(),
		oaSteps=0,
		xSteps=0,
		nrmlIdx=0;
	/*Calculate the points*/
	//TODO check if Inc's are rounded to next lower float, if yes,
	//there will be more points than pointCount!
	for(uint32_t yS=0 ; yS<=mp_calcSetup->ySteps; yS++){
		float y=startPos.y+yS*yInc;
		xSteps=0;//TODO virtual functions iterate(.. getMax addIterationLoop
		for(uint32_t xS=0 ;xS<=mp_calcSetup->xSteps; xS++){
			float x=startPos.x+xS*xInc;
			float z=pSource->GetValue(x, y, mp_calcSetup->getZ(x,y));
			curPos=glm::vec3(x-startPos.x,y-startPos.y,z);
			vtxNrml=calcPointNormal(curPos);
			nrmlIdx=pDataCollection->getVertexOperator()->get8BitNormalIndex(vtxNrml);
			if(z<min_z){min_z=z;}
			if(z>max_z){max_z=z;}

			if(oaSteps>pointCount){
				MFObject::printWarning("MFNoiseTile::calculateTile - "
						"More points than calculated! "
						"Most prblbly graphics will break!");
				pVertex=pDataCollection->getNextComplexVertex();
				pVecVertices->push_back(pVertex);
				//TODO this fails, data will not be
				//in shared memory -> shared memory was already shared after call
				//pDataCollection->setupComplexVertices() -> data must be somewhere else!
			}else{
				pVertex=pVecVertices->at(oaSteps);
			}
			uint32_t size=sizeof(glm::vec3);
			pVertex->getVecData()->at(0)->writeData(&curPos,size);
			size=sizeof(uint32_t);
			pVertex->getVecData()->at(1)->writeData(&nrmlIdx,size);
			xSteps++;
			oaSteps++;
		}
	}
	m_surroundingBox=glm::vec3(
			xEnd-mp_calcSetup->startPosition.x,
			yEnd-mp_calcSetup->startPosition.y,
			max_z-min_z);
	return true;
}
bool MFNoiseTile::calculateIndices(std::vector<uint32_t> *pIndices){
	uint32_t indicesCount=mp_calcSetup->ySteps*mp_calcSetup->xSteps*6;
	pIndices->resize(indicesCount);
	uint32_t index=0;
	for(uint32_t yS=0 ; yS<=mp_calcSetup->ySteps-1; yS++){
		for(uint32_t xS=0 ;xS<=mp_calcSetup->xSteps-1; xS++){
			if((index+6)>indicesCount){
				MFObject::printErr("MFNoiseTile::calculateTile - cant setup"
						"valid indices!");
				return false;
			}
			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS);
			index++;
			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS);
			index++;

			pIndices->at(index)=(yS*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS+1);
			index++;
			pIndices->at(index)=((yS+1)*(mp_calcSetup->xSteps+1)+xS);
			index++;
		}
	}
	return true;
}

glm::vec3 MFNoiseTile::calcPointNormal(glm::vec3 &pos){
	float
		xInc=(mp_calcSetup->xRange / mp_calcSetup->xSteps),
		yInc=(mp_calcSetup->yRange / mp_calcSetup->ySteps);
	glm::vec3//points of cornering triangles
		right=pos+glm::vec3(xInc,0,0),
		upper=pos+glm::vec3(0,yInc,0),
		upperLeft=pos+glm::vec3(-xInc,yInc,0),
		left=pos+glm::vec3(-xInc,0,0),
		lower=pos+glm::vec3(0,-yInc,0),
		lowerRight=pos+glm::vec3(xInc,-yInc,0);

	double x,y;
	x=right.x;y=right.y;
	right.z=getNoiseValue(x,y);
	x=upper.x;y=upper.y;
	upper.z=getNoiseValue(x,y);
	x=upperLeft.x;y=upperLeft.y;
	upperLeft.z=getNoiseValue(x,y);
	x=left.x;y=left.y;
	left.z=getNoiseValue(x,y);
	x=lower.x;y=lower.y;
	lower.z=getNoiseValue(x,y);
	x=lowerRight.x;y=lowerRight.y;
	lowerRight.z=getNoiseValue(x,y);

	glm::vec3//normals
		n1=glm::cross(right, upper),
		n2=glm::cross(upper, upperLeft),
		n3=glm::cross(upperLeft, left),
		n4=glm::cross(left, lower),
		n5=glm::cross(lower, lowerRight),
		n6=glm::cross(lowerRight, right),
		sum=(n1+n2+n3+n4+n5+n6);
	sum=sum*(1.0f/6.0f);
	//TODO check if all normals point to the same half sphere -> needed for median
	return sum;
	/*point is in the middle*/

}
