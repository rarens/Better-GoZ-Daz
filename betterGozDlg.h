#pragma once
#ifndef BETTER_GOZ_DLG
#define BETTER_GOZ_DLG

#include <functional>

#include "dzScene.h"
#include "dzpathitemmodel.h"
#include "dzpropertygroup.h"
#include "dzinclude.h"
#include "gpCommon.h"
#include "GpMorphOptions.h"
#include "generated/dzcomboedit.h"
#include "treecombobox.h"
class BetterGoZDialog : public QWidget
{
	Q_OBJECT
public:
	BetterGoZDialog(DzFacetMeshPtr mesh) :QWidget(),mOptions(this){
		
		mOptions.setMesh(mesh);
		setupUi(this); setupUiAddl();
		postLoadMesh();
}
	BetterGoZDialog(QWidget* parent, DzFacetMeshPtr mesh) :QWidget(parent),mOptions(this) {
		mOptions.setMesh(mesh);
		mDebug()<<"Dialog Constructor, Mesh Ref count:"<<mesh->getRefCount();
		setupUi(this); setupUiAddl();
		postLoadMesh();
	}

	TreeComboBox* cmbPath;
	QCheckBox* cbMirror;
	QCheckBox* cbReverse;
	QCheckBox* cbOE;
	QCheckBox* cbApplyToGrafts;
	QCheckBox* cbApplyMorph;
	QCheckBox* cbUseLimits;
	QDoubleSpinBox* spMin;
	QDoubleSpinBox* spMax;
	QToolButton* btnAddPath;
	QComboBox* cbSubD;
	QComboBox* cbMorphLoadType;
	QSpinBox* spSubDLev;
	QLabel* tvFigureName;
	QPushButton* btnCreate;
	QTextBrowser* textBrowser;
	QHBoxLayout* pathLayout;
	QToolButton* btnUseSelected;
	QPushButton* btnImportNew;
	QLabel* tvNumFacesBase;
	QLabel* tvNumFacesGoZ;
	QLabel* tvNumFacesCached;
	QComboBox* cmbName;
	QLineEdit* etName;
	QDoubleSpinBox* spScale;
	QListView* lvNames;
	QWidget* topWidget;
	int mSubDLev;
	void setupUi(QWidget* Form);
	void setupUiAddl();
	DzAppSettings mSettings;
	void retranslateUi(QWidget* Form);
	QString mMeshName;
	QFrame* framePath;
public slots:
	void selectionChanged(DzNode* node);
	void updateMorphName();
	void createMorph();
	void print(QString s);
	void updatePath(DzNode*, QString, bool fromSelected = false);
	void addNewPath();
	void importAsNew();
	void postLoadMesh();

	void show();
	bool doGraftMorph(DzNode* dst);
	int calcSubdLev(DzFacetMesh* subDMesh, DzFacetMesh* baseMesh);
	virtual void hideEvent(QHideEvent*);
private:
	GpMorphOptions mOptions;
	//static QString mStyleSheet;
};




#endif // BETTERGOZP26984_H
