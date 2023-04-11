/*
 * MFCreatorBox.h
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORBOX_H_
#define MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORBOX_H_
#include <vector>
#include <MFData/MFDataObject.h>
#include <MFData/MFStructurableDataSetup.h>
#include "../MFInterfacesGeometries/MFIGeometryCreator.h"
#include "../MFAbstractGeometry.h"

class MFCreatorBox: public MFIGeometryCreator {
public:
	MFCreatorBox();
	virtual ~MFCreatorBox();
	MFAbstractGeometry* createGeometry(
			void* pDataSetup,
			uint32_t byteOffset=0);
	MFAbstractGeometry* createGeometry(
			MFStructurableDataSetup* pDataSetup,
			uint32_t dataIndexOffset=0);
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORBOX_H_ */
