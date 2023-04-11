/*
 * MFBrickWall.cpp
 *
 *  Created on: 05.01.2020
 *      Author: michl
 */

#include "MFBrickWall.h"
#include <glm/glm.hpp>

MFBrickWall::MFBrickWall() {
	mp_baseBrickGeometry=nullptr;
	startBrickRow1=nullptr;
	startBrickRow2=nullptr;
	endBrickRow1=nullptr;
	endBrickRow2=nullptr;


}

MFBrickWall::~MFBrickWall() {
	if(startBrickRow1!=nullptr)
		delete startBrickRow1;
	if(startBrickRow2!=nullptr && startBrickRow2!=mp_baseBrickGeometry){
		delete startBrickRow2;
	}//TODO
	if(endBrickRow1!=nullptr && endBrickRow1!=mp_baseBrickGeometry){
		delete endBrickRow1;
	}
	if(endBrickRow2!=nullptr && endBrickRow2!=startBrickRow1){
		delete endBrickRow2;
	}
	if(mp_baseBrickGeometry!=nullptr)delete mp_baseBrickGeometry;
}

/*Implementation of virtual funcs*/
bool MFBrickWall::createSubElements(std::vector<S_SubElement*>* pVecElements){
	//TODO dimensions check for wall... if...  print err... return false
	mp_baseBrickGeometry=new MFBrickGeometry(
			glm::vec3(m_brickLength,m_brickDepth,m_brickHeight));
	float bricksPRow=(m_length/m_brickLength);
	float baseBricksPRow=glm::floor((m_length/m_brickLength));
	float smallBrickLength=(bricksPRow-baseBricksPRow)*m_brickLength;
	if(smallBrickLength<m_minBrickDistance){
		baseBricksPRow-=1.0f;
		smallBrickLength+=(m_brickLength/2.0f);
//		endBrickRow1=new MFBrickGeometry(
//				glm::vec3(m_brickLength/2.0f,m_brickDepth,m_brickHeight));
		endBrickRow1=mp_baseBrickGeometry;
		startBrickRow1=new MFBrickGeometry(
				glm::vec3(smallBrickLength,m_brickDepth,m_brickHeight));
		startBrickRow2=mp_baseBrickGeometry;
	} else {//TODO if smallBrickLength>m_brickLength-m_minBrickDistance
		startBrickRow1=new MFBrickGeometry(
				glm::vec3(smallBrickLength,m_brickDepth,m_brickHeight));
		endBrickRow1=mp_baseBrickGeometry;
		startBrickRow2=mp_baseBrickGeometry;
	}
	endBrickRow2=startBrickRow1;

	bool modFirst=true;
	glm::vec3 currentPosition=glm::vec3(0.0f,.0f,.0f);
	for(float crtHeight=0.0f;crtHeight<=m_height;crtHeight+=2*m_brickHeight){
		currentPosition.z=crtHeight;
		S_SubElement* pStartBrick=new S_SubElement();
		if(modFirst){
			pStartBrick->localTransformation=currentPosition;
			pStartBrick->pGeo=startBrickRow1;
			currentPosition.x+=startBrickRow1->getWidth()+mp_baseBrickGeometry->getWidth();
		} else {
			currentPosition.x+=
					(startBrickRow2->getWidth()-startBrickRow1->getWidth());
			pStartBrick->localTransformation=currentPosition;
			pStartBrick->pGeo=startBrickRow2;
			currentPosition.x+=
					startBrickRow2->getWidth()+mp_baseBrickGeometry->getWidth();
		}
		pVecElements->push_back(pStartBrick);
		for(float bc=baseBricksPRow;bc>0.0f;bc-=1.0f){
			S_SubElement* pBrick=new S_SubElement();
			pBrick->pGeo=mp_baseBrickGeometry;
			pBrick->localTransformation=currentPosition;
			currentPosition.x+=mp_baseBrickGeometry->getWidth()*2;
			pVecElements->push_back(pBrick);
		}

		S_SubElement* pEndBrick=new S_SubElement();
		if(modFirst){
			pEndBrick->pGeo=endBrickRow1;
			pEndBrick->localTransformation=currentPosition;
			pEndBrick->localTransformation.x+=endBrickRow1->getWidth()-
					mp_baseBrickGeometry->getWidth();
		} else {
			pEndBrick->pGeo=endBrickRow2;
			pEndBrick->localTransformation=currentPosition;
			pEndBrick->localTransformation.x+=endBrickRow2->getWidth()-
					mp_baseBrickGeometry->getWidth();
		}

		currentPosition.x=0.0f;
		pVecElements->push_back(pEndBrick);
		modFirst=(!modFirst);
	}
	return true;
}

bool MFBrickWall::createSegments(std::vector<MFComplexSegment*>* pVecSegs){
	return true;
}

bool MFBrickWall::createDockingPoints(std::vector<MFDockingPoint*>* pVecSegs){
	return true;
}
