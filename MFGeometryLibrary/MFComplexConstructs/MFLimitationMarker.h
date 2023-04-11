/*
 * MFLimitationMarker.h
 *
 *  Created on: 03.01.2020
 *      Author: michl
 */

#ifndef MFCOMPLEXCONSTRUCTS_MFLIMITATIONMARKER_H_
#define MFCOMPLEXCONSTRUCTS_MFLIMITATIONMARKER_H_

/**
 * This class provides limit markers for complex constructs (for example
 * MFComplexConstruct). If an object of this class is added to an constructs docking
 * point, it provides the necessary information for the construct which docks at this
 * point.
 * Example:
 * 	A House construct provides an opening for a door with a specific width/height and
 * 	a docking point.
 * 	To add a door construct, the door needs the width and height, that it can setup
 * 	its geometries. The constraints are given by the MFLimitationMarker class.
 *
 */
class MFLimitationMarker {
public:
	MFLimitationMarker();
	virtual ~MFLimitationMarker();
};

#endif /* MFCOMPLEXCONSTRUCTS_MFLIMITATIONMARKER_H_ */
