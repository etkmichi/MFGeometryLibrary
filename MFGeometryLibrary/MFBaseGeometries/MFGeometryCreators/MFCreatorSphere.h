/*
 * MFCreatorSphere.h
 *
 *  Created on: 16.06.2020
 *      Author: michl
 */

#ifndef MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORSPHERE_H_
#define MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORSPHERE_H_
#include <vector>
#include <MFData/MFDataObject.h>
#include <MFData/MFStructurableDataSetup.h>
#include "../MFInterfacesGeometries/MFIGeometryCreator.h"
#include "../MFAbstractGeometry.h"

class MFCreatorSphere: public MFIGeometryCreator {
public:
	MFCreatorSphere();
	virtual ~MFCreatorSphere();
	MFAbstractGeometry* createGeometry(
			void* pDataSetup,
			uint32_t byteOffset=0);
};

#endif /* MFBASEGEOMETRIES_MFGEOMETRYCREATORS_MFCREATORSPHERE_H_ */
