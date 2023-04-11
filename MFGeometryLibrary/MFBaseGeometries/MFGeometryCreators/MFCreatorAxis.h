/*
 * MFCreateAxis.h
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORAXIS_H_
#define MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORAXIS_H_
#include <vector>
#include <MFData/MFDataObject.h>
#include <MFData/MFStructurableDataSetup.h>
#include "../MFInterfacesGeometries/MFIGeometryCreator.h"
#include "../MFAbstractGeometry.h"
class MFCreatorAxis: public MFIGeometryCreator {
public:
	MFCreatorAxis();
	virtual ~MFCreatorAxis();
	MFAbstractGeometry* createGeometry(
			void* pDataSetup,
			uint32_t byteOffset=0);
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORAXIS_H_ */
