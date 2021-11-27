#ifndef GpGozWorker_GUARD
#define GpGozWorker_GUARD
#include "dzinclude.h"
#include "gozfilereader.h"
class GpGozWorker: public QObject,public QRunnable
{
Q_OBJECT
public:
	GpGozWorker(QObject* parent):QRunnable() {
		DzConnect(this,SIGNAL(finished(DzFacetMeshPtr)),parent,SLOT(onMesh(DzFacetMeshPtr)));
	}
	  void run() {
			GoZFileReader* mReader=new GoZFileReader(this);
			DzFacetMesh* mesh=mReader->readGoZ();
			emit finished(mesh);
	  }

signals:
	void finished(DzFacetMeshPtr);
private:
	
};
#endif
