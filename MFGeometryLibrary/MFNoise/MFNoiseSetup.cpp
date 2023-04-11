/*
 * MFNoiseSetup.cpp
 *
 *  Created on: 10.02.2020
 *      Author: michl
 */

#include "MFNoiseSetup.h"

MFNoiseSetup::MFNoiseSetup() {
	mp_noiseSource=nullptr;
	if(mp_internalNoiseConfig==nullptr)
		mp_internalNoiseConfig=new S_MFNoiseConfig();
    mp_internalNoiseConfig->noiseType=NOISE_TYPE_BILLOW;
    mp_internalNoiseConfig->frequency=0.1;
	mp_noiseConfig=mp_internalNoiseConfig;
    mNoiseBillow=new noise::module::Billow();
    mNoiseCheckerboard=new noise::module::Checkerboard();
    mNoiseConst=new noise::module::Const();
    mNoiseCylinders=new noise::module::Cylinders();
    mNoisePerlin=new noise::module::Perlin();
    mNoiseRidgedMulti=new noise::module::RidgedMulti();
    mNoiseSpheres=new noise::module::Spheres();
    mNoiseVoronoi=new noise::module::Voronoi();
    mActiveModule=mNoiseBillow;
    updateNoiseConfigs();
}

MFNoiseSetup::~MFNoiseSetup() {
	delete mp_internalNoiseConfig;
    delete mNoiseBillow;
    delete mNoiseCheckerboard;
    delete mNoiseConst;
    delete mNoiseCylinders;
    delete mNoisePerlin;
    delete mNoiseRidgedMulti;
    delete mNoiseSpheres;
    delete mNoiseVoronoi;
}

void MFNoiseSetup::updateNoiseConfigs(){
    setFrequency(mp_noiseConfig->frequency);
    setLacunarity(mp_noiseConfig->lactunarity);
    setOctaveCount(mp_noiseConfig->octaves);
    setPersistence(mp_noiseConfig->persistence);
    setSeed(mp_noiseConfig->seed);
    setQuality(mp_noiseConfig->noiseQualtity);
    setConstValue(mp_noiseConfig->constValue);
    setDisplacement(mp_noiseConfig->displacement);
    setNoiseType(mp_noiseConfig->noiseType);
}

void MFNoiseSetup::setFrequency(double value){
    mNoiseBillow->SetFrequency(value);
    mNoisePerlin->SetFrequency(value);
    mNoiseCylinders->SetFrequency(value);
    mNoiseRidgedMulti->SetFrequency(value);
    mNoiseSpheres->SetFrequency(value);
    mNoiseVoronoi->SetFrequency(value);
    mp_noiseConfig->frequency = value;
}
//lacunarity set
void MFNoiseSetup::setLacunarity(double value){
    mNoiseBillow->SetLacunarity(value);
    mNoisePerlin->SetLacunarity(value);
    mNoiseRidgedMulti->SetLacunarity(value);
    mp_noiseConfig->lactunarity = value;
}

//octave count
void MFNoiseSetup::setOctaveCount(int value){
    mNoiseBillow->SetOctaveCount(value);
    mNoisePerlin->SetOctaveCount(value);
    mNoiseRidgedMulti->SetOctaveCount(value);
    mp_noiseConfig->octaves = value;
}

//persistence of waves
void MFNoiseSetup::setPersistence(double value){
    mNoiseBillow->SetPersistence(value);
    mNoisePerlin->SetPersistence(value);
    mp_noiseConfig->persistence = value;
}

//seed
void MFNoiseSetup::setSeed(int value){
    mNoiseBillow->SetSeed(value);
    mNoisePerlin->SetSeed(value);
    mNoiseRidgedMulti->SetSeed(value);
    mNoiseVoronoi->SetSeed(value);
    mp_noiseConfig->seed = value;
}
void MFNoiseSetup::setConstValue(double value)
{
    mNoiseConst->SetConstValue(value);
    mp_noiseConfig->constValue = value;
}

void MFNoiseSetup::setDisplacement(double value)
{
    mNoiseVoronoi->SetDisplacement(value);
    mp_noiseConfig->displacement = value;
}

void MFNoiseSetup::setQuality(noise::NoiseQuality quality)
{
	mp_noiseConfig->noiseQualtity=quality;
    mNoiseBillow->SetNoiseQuality(quality);
    mNoiseRidgedMulti->SetNoiseQuality(quality);
    mNoisePerlin->SetNoiseQuality(quality);
}
void MFNoiseSetup::setNoiseType(E_NoiseType type){
	mp_noiseConfig->noiseType=type;
	switch(type){
	case E_NoiseType::NOISE_TYPE_BILLOW:
		mActiveModule=mNoiseBillow;
		break;
	case E_NoiseType::NOISE_TYPE_CHESS:
		mActiveModule=mNoiseCheckerboard;
		break;
	case E_NoiseType::NOISE_TYPE_CONST:
		mActiveModule=mNoiseConst;
		break;
	case E_NoiseType::NOISE_TYPE_CYLINDERS:
		mActiveModule=mNoiseCylinders;
		break;
	case E_NoiseType::NOISE_TYPE_PERLIN:
		mActiveModule=mNoisePerlin;
		break;
	case E_NoiseType::NOISE_TYPE_RIDGED:
		mActiveModule=mNoiseRidgedMulti;
		break;
	case E_NoiseType::NOISE_TYPE_SPHERES:
		mActiveModule=mNoiseSpheres;
		break;
	case E_NoiseType::NOISE_TYPE_VORONI:
		mActiveModule=mNoiseVoronoi;
		break;
	default:
		mActiveModule=mNoiseBillow;
		break;
	};
}

