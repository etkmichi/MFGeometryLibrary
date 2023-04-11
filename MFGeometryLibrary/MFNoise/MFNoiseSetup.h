/*
 * MFNoiseSetup.h
 *
 *  Created on: 10.02.2020
 *      Author: michl
 */

#ifndef MFNOISE_MFNOISESETUP_H_
#define MFNOISE_MFNOISESETUP_H_
#include <noise.h>
#include <MFData/MFStructurableDataSetup.h>
#include "MFNoiseStructs.h"

class MFNoiseSetup : public MFStructurableDataSetup{
protected:
	void initData(){
		if(mp_internalNoiseConfig!=nullptr)
			mp_internalNoiseConfig=new S_MFNoiseConfig();
		if(mp_noiseConfig==nullptr)
			mp_noiseConfig=mp_internalNoiseConfig;
	};
	void setupDataStructure(){
		if(mp_noiseConfig==nullptr)
			mp_noiseConfigObject=addNBitValue(sizeof(S_MFNoiseConfig),
					mp_internalNoiseConfig);
		else
			mp_noiseConfigObject=addNBitValue(sizeof(S_MFNoiseConfig),
					mp_noiseConfig);
	}

private:
    noise::module::Billow       *mNoiseBillow;
    noise::module::Checkerboard *mNoiseCheckerboard;
    noise::module::Const        *mNoiseConst;
    noise::module::Cylinders    *mNoiseCylinders;
    noise::module::Perlin       *mNoisePerlin;
    noise::module::RidgedMulti  *mNoiseRidgedMulti;
    noise::module::Spheres      *mNoiseSpheres;
    noise::module::Voronoi      *mNoiseVoronoi;
    noise::module::Module		*mActiveModule;

	noise::module::Module
		*mp_noiseSource;

	S_MFNoiseConfig
		*mp_noiseConfig,
		*mp_internalNoiseConfig=nullptr;
	MFDataObject
		*mp_noiseConfigObject=nullptr;
public:
	MFNoiseSetup();
	virtual ~MFNoiseSetup();
	void initDataPointer(){
		mp_noiseConfig=(S_MFNoiseConfig*)mp_noiseConfigObject->getData();
	};
	void setNoiseConfig(S_MFNoiseConfig* pConfig){mp_noiseConfig=pConfig;};
	void updateNoiseConfigs();

	noise::module::Module* getNoiseSource(){return mActiveModule;};

  void setFrequency(double value);
  void setLacunarity(double value);
  void setPersistence(double value);
  void setOctaveCount(int value);
  void setSeed(int value);
  void setQuality(noise::NoiseQuality preDefine);
  void setConstValue(double value);
  void setDisplacement(double value);
  void setNoiseType(E_NoiseType type);
};

#endif /* MFNOISE_MFNOISESETUP_H_ */
