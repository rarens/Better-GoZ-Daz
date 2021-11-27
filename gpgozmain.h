#pragma once
#ifndef GP_BETTER_GOZ
#define GP_BETTER_GOZ
#define NOMINMAX
#include "QtCore/qobject.h"
#include "QtCore/qtimer.h"
#include "QtCore/qsharedmemory.h"
#include "dzplugin.h"
#include "dzfacetmesh.h"
#include "qvector3d.h"
#include "dzfacetmesh.h"
#include "gozfilereader.h"
#include "dzvec3.h"
#include <iostream>
#include <fstream>
#include <gpCommon.h>

#define SHARED_KEY "daz3d.dazstudio64.goz.notify"


QString operator + (QString s, quint32 i) {
	return s + QString::number(i);

}
template <typename T>
T swap_endian(T u)
{
	static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

	union
	{
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (size_t k = 0; k < sizeof(T); k++)
		dest.u8[k] = source.u8[sizeof(T) - k - 1];

	return dest.u;
}
class BetterGoZExportAction:public DzEditAction {
	Q_OBJECT
public:
	BetterGoZExportAction():DzEditAction("Better GoZ Export","Better GoZ Export") {
		setIcon(":ui/better GoZ icon.png");
	}

	QString getActionGroup() const override {
		return "Bridges";
		
	}
	QString getDefaultMenuPath() const override{return "File";}
	void executeAction() {
		DzNode* node=GET_NODE();
		if(!node)return;
		GoZFileReader reader(this);
		reader.writeGoZ(node);
		
	}
};

class GpBetterGoZ:public DzPlugin {
	Q_OBJECT
		
public:
	GpBetterGoZ();
	GpBetterGoZ(const QString& name,
		const QString& author = QString::null,
		const QString& description = QString::null,
		unsigned short  	major = 0,
		unsigned short  	minor = 0,
		unsigned short  	rev = 0,
		unsigned short  	build = 0);
	



public slots:
	void checkStatus();
	void onMesh(DzFacetMeshPtr shape);
	void dialogVisChanged(bool vis);
protected:
	virtual void startup();
private:
	QTimer qtimer;
	bool running;
	QSharedMemory* mSharedMemory;
	int getDetectedSubDLevel(DzFacetMesh* importedMesh, DzNode*);
	bool isPotentialMorphTarget(DzFacetMesh*, DzNode*);
	BetterGoZDialog* dialog;

};
#endif