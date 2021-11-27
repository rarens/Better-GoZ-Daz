#ifndef GP_MORPH_OPTIONS
#define GP_MORPH_OPTIONS
#include <generated/dzmorphloader.h>

#include "dzinclude.h"

class GpMorphOptions: public QObject{
    Q_OBJECT
    //Q_PROPERTY(int subDLev MEMBER mSubDLev)
	//Q_PROPERTY(DzMorphLoader::SubdMapping mSubDCage)
	
   
public:


    GpMorphOptions() :mSubDLev(0),mSubDCage(DzMorphLoader::SubdMapping::Catamark),mMorphName(""),mApplyToGrafts(true),mOE(true),mRevDef(true),mPath(""),loadMode(DzMorphLoader::LoadMode::SingleSkinFigure), QObject(NULL),mScaledMesh(NULL) {};
    GpMorphOptions(QObject* parent) :mSubDLev(0), mSubDCage(DzMorphLoader::SubdMapping::Catamark), mMorphName(""), mApplyToGrafts(true), mOE(true), mRevDef(true), mPath(""),loadMode(DzMorphLoader::LoadMode::SingleSkinFigure), QObject(parent),mScaledMesh(NULL) {}
	int mSubDLev;
    DzMorphLoader::SubdMapping mSubDCage;
    QString mMorphName;
    bool mApplyToGrafts;
    bool mOE;
    bool mRevDef;
    bool mMirror;
	DzMorphLoader::LoadMode loadMode;
    QString mPath;
    DzFacetMeshPtr mMesh;
	DzFacetMeshPtr mScaledMesh;
	bool applyMoprh;
	bool useLimits;
	float limMax,limMin;
	float mScale;
	QStringList nameHistory;
public slots:
    inline int getSubDLev() { return mSubDLev; }
    QString toString();
    inline DzMorphLoader::SubdMapping getSubDCage() { return mSubDCage; }
    inline QString getMorphName() { return mMorphName; }
    inline bool getAG() { return mApplyToGrafts; }
    inline bool getOE() { return mOE; }
    inline bool getRevD() { return mRevDef; }
    inline bool getMirror() { return mMirror; }
    inline QString getPath() { return mPath; }
    inline DzFacetMesh* getMesh() { return mMesh; }
	inline DzMorphLoader::LoadMode getLoadMode(){return loadMode;}
	inline QString toJsonString(){return "";}
    void setOptionsFromSettings();
    void writeOptionsToSettings();
	DzFacetMesh* getScaledMesh();
    QStringList getNameHistory() {
	    return QStringList(nameHistory);
    }

    void setMesh(DzFacetMeshPtr mesh);
};

#endif