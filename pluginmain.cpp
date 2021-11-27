/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ Studio SDK.

	This file may be used only in accordance with the DAZ Studio SDK 
	license provided with the DAZ Studio SDK.

	The contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D, Inc or for more 
	information about the DAZ Studio SDK.
**********************************************************************/
#define NOMINMAX 
/*****************************
   Include files
*****************************/
#include "dzplugin.h"
#include "dzapp.h"

#include "version.h"
#include "gpgozmain.h"
#include "QtCore/qdebug.h"
#include "dzscene.h"
#include "dzfacetmeshbc.h"
#include "dzfacetmesh.h"
#include "dzgraftingfigureshape.h"
#include "dznode.h"
#include "qbytearray.h"
#include "qendian.h"
#include "dzface.h"
#include "dzinfile.h"
#include "dzobject.h"
#include "dzshape.h"
#include <iostream>     // std::cout
#include <fstream> 
#include <climits>
#include "dzscript.h"
#include "qvariant.h"
#include "QtScript/qscriptvalue.h"
#include "betterGozDlg.h"
#include "GpMorphOptions.h"
#include <iostream>

#include "GpGozWorker.h"

/*****************************
   Plugin Definition
*****************************/

/**
	This macro creates the plugin definition, and the functions that are needed
	for DAZ Studio to load our plugin.
**/
DZ_CUSTOM_PLUGIN_DEFINITION(GpBetterGoZ);
//DZ_PLUGIN_CLASS_GUID(GoZFileReader, 299A67B3 - 0332 - 6Ad0 - 7231 - F675799D7574);
//DZ_PLUGIN_CLASS_GUID(BetterGoZDialog, AAAA67B3 - 7232 - 6AE0 - B231 - F6757A9D7574);
DZ_PLUGIN_CLASS_GUID(BetterGoZExportAction, BBBB69B3 - 7232 - 6AE0 - A731 - F6757A9D7575)
DZ_PLUGIN_CLASS_GUID(GpMorphOptions, AAAA69B3 - 7232 - 6AE0 - B731 - F6757A9D7575)
GpBetterGoZ::GpBetterGoZ():DzPlugin("Better GoZ", "Gamplod", "A better GoZ Plugin", 1, 1, 1, 1) {
	
}

void GpBetterGoZ::startup() {
	running = true;
	

	mSharedMemory=new QSharedMemory("daz3d.dazstudio64.goz.notify");
	if (mSharedMemory->attach()) {
		if (mSharedMemory->size() == 1024) {
			qDebug() << "Share Mem exists with size 4096";
			mSharedMemory->unlock();
			mSharedMemory->detach();
		
			checkStatus();
			
		}
	}
	else {
		qDebug() << "Creating new shared memory";
		mSharedMemory->setKey("daz3d.dazstudio64.goz.notify");
		if (mSharedMemory->create(1024)) {
			mSharedMemory->unlock();
			QTimer::singleShot(1000, this, SLOT(checkStatus()));
		}
		else {
			qDebug() << "FML couldn't create shared mem";
			qDebug() << mSharedMemory->errorString();
		}
	}

}
void GpBetterGoZ::onMesh(DzFacetMeshPtr mesh) {
			  
				dialog=new BetterGoZDialog(getMainWindow(),mesh);
				//DzConnect(dialog,SIGNAL(visibilityChanged(bool)),this,SLOT(dialogVisChanged(bool)))			 ;
				dialog->show();
}
void GpBetterGoZ::dialogVisChanged(bool vis) {
	
}
void GpBetterGoZ::checkStatus() {
			  bool triggered=false;
	//if (mSharedMemory->attach()) {
		if (mSharedMemory->lock()) {
			char* c = (char*)mSharedMemory->data();
		//	qDebug() << "Check Status " + QString::number(c[0]);
			if (c[0] == 1) {
				qDebug() << "GoZ Triggered";
				*c = 0;
				triggered=true;
				
			}
		}
		else {
			qDebug() << "Failed To Lock SM";
			qDebug() << mSharedMemory->errorString();
		}
	mSharedMemory->unlock();
	if(triggered) {
				
		    QString scriptPath=dzApp->getContentMgr()->findFile("Scripts/newgoz.dsa");
			GoZFileReader reader(this);
			DzFacetMeshPtr ptr=reader.readGoZ();
			//GpGozWorker* worker=new GpGozWorker(this);
			//QThreadPool::globalInstance()->start(worker);
		onMesh(ptr);
	}
	
	QTimer::singleShot(1000, this, SLOT(checkStatus()));
}

#include "gpgozmain_moc.cpp"