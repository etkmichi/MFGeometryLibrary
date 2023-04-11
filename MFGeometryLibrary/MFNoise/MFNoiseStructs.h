/*
 * MFNoiseStructs.h
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#ifndef MFNOISE_MFNOISESTRUCTS_H_
#define MFNOISE_MFNOISESTRUCTS_H_
#include <noise.h>
#include <glm/glm.hpp>

struct S_MFCalculationSetup {
	float
		xRange=1.0f,//Positive offsets from startPoint
		yRange=1.0f,
		zValue=0.0f;
	uint32_t
		xSteps=10,
		ySteps=10;
	glm::vec3
		startPosition=glm::vec3(0,0,0);
	virtual ~S_MFCalculationSetup(){

	};
	virtual float getZ(float x,float y){
		return zValue;
	};
};

enum E_NoiseType {
	NOISE_TYPE_BILLOW=0,
	NOISE_TYPE_CHESS=1,
	NOISE_TYPE_CONST=2,
	NOISE_TYPE_CYLINDERS=3,
	NOISE_TYPE_PERLIN=4,
	NOISE_TYPE_RIDGED=5,
	NOISE_TYPE_SPHERES=6,
	NOISE_TYPE_VORONI=7
};

struct S_MFNoiseConfig {
	double
		frequency=0.1,
		lactunarity=0.0,
		constValue=1.0,
		persistence=0.5,
		displacement=0.0;
	int
		octaves=3,
		seed=0;
	noise::NoiseQuality
		noiseQualtity=noise::QUALITY_STD;
	E_NoiseType
		noiseType=NOISE_TYPE_BILLOW;
};




#endif /* MFNOISE_MFNOISESTRUCTS_H_ */
