
#include "GpMorphOptions.h"
QString GpMorphOptions::toString() {
    QString output("Morph Options\n");
    output.append("\tsubDLev: " + QString::number(mSubDLev) + "\n");
    output.append("\tapply_to_grafts: " + QString::number(mApplyToGrafts) + "\n");
    output.append("\tmesh: ""\n");
    output.append("\t\tnumFaces: " + QString::number(mSubDLev) + "\n");
    output.append("\t\tnumVerts: " + QString::number(mMesh->getNumFacets()) + "\n");
    output.append("\tmirror: " + QString::number(mMesh->getNumVertices()) + "\n");
    output.append("\treverse_deformations: " + QString::number(mRevDef) + "\n");
    output.append("\tsubDCage: " + QString::number(mSubDCage) + "\n");
    output.append("\tmorph_name: " + mMorphName + "\n");
    output.append("\tpath: " + mPath + "\n");
    output.append("\toverrride_existing: " + QString::number(mOE) + "\n");
    return output;
}

void GpMorphOptions::setOptionsFromSettings() {
	DzAppSettings settings("BetterGoZ");
	mSubDCage = (DzMorphLoader::SubdMapping)settings.getIntValue("subDMapping", 0);
	mMorphName = settings.getStringValue("morphName", "Better GoZ Morph");
	mApplyToGrafts = settings.getBoolValue("applyToGrafts", true);
	mOE = settings.getBoolValue("overrideExisting", true);
	mRevDef = settings.getBoolValue("revDef", true);
	mMirror = settings.getBoolValue("mirror", false);
	mPath = settings.getStringValue("path", "/MyMorphs");
	loadMode = (DzMorphLoader::LoadMode)settings.getIntValue("loadMode", DzMorphLoader::LoadMode::SingleSkinFigure);
	useLimits = settings.getBoolValue("useLimits", true);
	limMax = settings.getFloatValue("limMax", 1.0);
	limMin = settings.getFloatValue("limMin", 0);
	mScale=settings.getFloatValue("scale",1.0);
	applyMoprh = settings.getBoolValue("applyMorph", true);
	QString hist=settings.getStringValue("nameHist","Better GoZ Morph");
	if(!hist.contains(","))nameHistory.append(hist);
	else
	nameHistory.append(hist.split(",",QString::SkipEmptyParts));
}

void GpMorphOptions::writeOptionsToSettings() {
	DzAppSettings settings("BetterGoZ");
	settings.setIntValue("subDMapping", mSubDCage);
	settings.setStringValue("morphName", mMorphName);
	settings.setBoolValue("applyToGrafts", mApplyToGrafts);
	settings.setBoolValue("overrideExisting", mOE);
	settings.setBoolValue("revDef", mRevDef);
	settings.setBoolValue("mirror", mMirror);
	settings.setStringValue("path", mPath);
	settings.setIntValue("loadMode", loadMode);
	settings.setBoolValue("useLimits", useLimits);
	settings.setFloatValue("limMax", limMax);
	settings.setFloatValue("limMin", limMin);
	settings.setFloatValue("scale",mScale);
	settings.setBoolValue("applyMorph", applyMoprh);
	QString hist;
	nameHistory.remove(mMorphName);
	nameHistory.push_front(mMorphName);
	for(int i=0;i<nameHistory.length();i++) {
		hist+=nameHistory[i];
		if(i<nameHistory.length()-1)hist+=",";
	}
	settings.setStringValue("nameHist",hist);
}

DzFacetMesh* GpMorphOptions::getScaledMesh() {
	mDebug()<<"getScaledMesh() mMesh Ref Count"<<mMesh->getRefCount();
	if(mScale==1)return	mMesh;
	while(mScaledMesh!=NULL && mScaledMesh->getRefCount()>0)mScaledMesh->unref();
	
	mScaledMesh =  DzFacetMeshPtr((DzFacetMesh*)mMesh->makeCopy(false,false));
	int n=mScaledMesh->getNumVertices();
	DzVec3 scaleVec(mScale,mScale,mScale);
	for(int i=0;i<n;i++) {
		DzVec3 vert=mScaledMesh->getVertex(i);
		vert*=scaleVec;
		mScaledMesh->setVertex(i,vert);
	}
	return mScaledMesh;
}

void GpMorphOptions::setMesh(DzFacetMeshPtr mesh) {
	while (!mesh && mMesh && mMesh->getRefCount()>0)mMesh->unref();
	mMesh = mesh;
	if (mesh) {
		mMesh->ref();
		mDebug() << "Morph Options mesh ref count" << mMesh->getRefCount();
	}
}

#include "GpMorphOptions_moc.cpp";
