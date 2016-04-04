#pragma once
#include "base/ComPtr.h"
#include "../Polyline/Polyline_h.h"

class PolylineTest
{
public:
	PolylineTest();
	~PolylineTest();
	int testCompoundFile();
	int writePersistFile();
	int readPersistFile();
	int writeFileMoniker();
	int readFileMoniker();

private:
	void outputPoints(ComPtr<IPolyline>& pl);
	int writeCompoundFile();
	int readCompundFile();
};

