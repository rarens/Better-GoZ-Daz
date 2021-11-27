#include "betterGozDlg.h"

#include <functional>

#include "dzapp.h"
#include "dzpanemgr.h"
#include "qmetaobject.h"
#include "qmath.h"
#include "QtUiTools/quiloader.h"
#include "generated/dzmorphloader.h"
#include "gpCommon.h"


 //QString BetterGoZDialog::mStyleSheet = "QLineEdit {border: 0px solid gray; ;background: #282C34;background-color: #282C34; color:white;selection-background-color: white;font-size: 15px;font-family: 'helvetica';}" \
			" QSpinBox {border: 1px solid gray; ;background: #282C34;background-color: #282C34; color:white;selection-background-color: white;font-size: 12px;font-family: 'helvetica';}" \
			" QDoubleSpinBox {border: 0px solid gray; ;background: #282C34;background-color: #282C34; color:white;selection-background-color: white;font-size: 12px;font-family: 'helvetica';}" \
			" QMenu {color:white;font-size: 14px;font-family: 'Helvetica';}" \
			" QLabel {color:white;font-size: 12px;font-family: 'Helvetica';}" \
			" DzMainWindow {color:white;font-size: 12px;font-family: 'Helvetica';}" \
			"QComboBox{border: 2px solid gray;selection-background-color:#262A32;background-color: #262A32;color:white;font-size: 15px;font-family: 'helvetica';}"\
			"QComboBox:editable {border:0px white;selection-background-color:#262A32;alternate-background: #262A32;background: #262A32;background-color: #262A32;}"\
			"QToolButton:border: 0px;"\
			"QMenu::item {color:blue;font-size: 14px;font-family: 'Helvetica';}";
void BetterGoZDialog::setupUi(QWidget* Form) {

	//setStyleSheet(mStyleSheet);
	setAttribute(Qt::WA_DeleteOnClose);
	QFile file(":/ui/bettergoz.ui");
	file.open(QIODevice::ReadOnly);
	QUiLoader loader;
	topWidget=	 loader.load(&file, Form);
	QWidget* w = topWidget;
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(w);
	setLayout(layout);
	file.close();
	spSubDLev = w->findChild<QSpinBox*>("spSubD");
	cbMirror = w->findChild<QCheckBox*>("cbMirror");
	cbOE = w->findChild<QCheckBox*>("cbOE");
	pathLayout = w->findChild<QHBoxLayout*>("layoutPathCombo");
	cbReverse = w->findChild<QCheckBox*>("cbReverse");
	cbApplyToGrafts = w->findChild<QCheckBox*>("cbApplyToGrafts");
	btnAddPath = w->findChild<QToolButton*>("btnAddPath");
	cbSubD = w->findChild<QComboBox*>("cbSubD");
	cbMorphLoadType = w->findChild<QComboBox*>("cbMorphLoadType");
	tvNumFacesCached = w->findChild<QLabel*>("tvNumFacesCached");
	tvNumFacesBase = w->findChild<QLabel*>("tvNumFacesBase");
	tvNumFacesGoZ = w->findChild<QLabel*>("tvNumFacesGoZ");
	tvFigureName = w->findChild<QLabel*>("tvFigureName");
	btnCreate = w->findChild<QPushButton*>("btnCreate");
	textBrowser = w->findChild<QTextBrowser*>("textBrowser");


	cmbName = w->findChild<QComboBox*>("cmbName");
	btnUseSelected = w->findChild<QToolButton*>("btnUseSelected");
	btnImportNew = w->findChild<QPushButton*>("btnImportNew");
	cbApplyMorph = w->findChild<QCheckBox*>("cbApplyWhenComplete");
	cbUseLimits = w->findChild<QCheckBox*>("cbLimits");;
	spMin = w->findChild<QDoubleSpinBox*>("spMin");
	spMax = w->findChild<QDoubleSpinBox*>("spMax");
	spScale = w->findChild<QDoubleSpinBox*>("spScale");
	etName = new QLineEdit(NULL);
	//QMetaObject::connectSlotsByName(Form);
} // setupUi





void BetterGoZDialog::setupUiAddl() {
	Qt::WindowFlags flags = windowFlags();
	setWindowFlags(Qt::Dialog|Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_DeleteOnClose);
	int mwHeight = dzApp->getInterface()->height();
	int popupH = .7 * (float)mwHeight;

	lvNames = new QListView();
	lvNames->viewport()->installEventFilter(cmbName);
	cmbName->setView(lvNames);
	
	cmbPath = new TreeComboBox(this);
	
	//cmbPath->setEditable(true);
	
	pathLayout->add(cmbPath);
	cmbName->setLineEdit(etName);
	btnImportNew->setVisible(false);
	//	cmbName->setStyleSheet("selection-background-color:#262A32;");
	etName->setStyleSheet("border:0px; background:#262A32;");



	//cmbPath->setStyleSheet("selection-background-color:#262A32;");

	cbSubD->addItem("Catamark", DzMorphLoader::SubdMapping::Catamark);
	cbSubD->addItem("Facet Order", DzMorphLoader::SubdMapping::FacetOrder);
	cbSubD->addItem("Zbrush Cage", DzMorphLoader::SubdMapping::ZbrushCage);
	cbSubD->addItem("Mudbox Cage", DzMorphLoader::SubdMapping::MudboxCage);

	cbMorphLoadType->addItem("Entire Figure", DzMorphLoader::LoadMode::EntireFigure);
	cbMorphLoadType->addItem("Selected Nodes", DzMorphLoader::LoadMode::SelectedNodes);
	cbMorphLoadType->addItem("Primary Node", DzMorphLoader::LoadMode::PrimaryNode);
	cbMorphLoadType->addItem("Single Skin Figure", DzMorphLoader::LoadMode::SingleSkinFigure);
	cbMorphLoadType->addItem("Single Skin Figure From Graft", DzMorphLoader::LoadMode::SingleSkinFigureFromGraft);

	cbMorphLoadType->setCurrentIndex(3);
	DzConnect(btnUseSelected, SIGNAL(clicked()), this, SLOT(updateMorphName()));
	DzConnect(btnCreate, SIGNAL(clicked()), this, SLOT(createMorph()));
	DzConnect(btnAddPath, SIGNAL(clicked()), this, SLOT(addNewPath()));
	DzConnect(btnImportNew, SIGNAL(clicked()), this, SLOT(importAsNew()));
	DzConnect(dzScene, SIGNAL(primarySelectionChanged(DzNode*)), this, SLOT(selectionChanged(DzNode*)));
	cmbName->addItems(mOptions.nameHistory);
	cmbName->setCurrentIndex(0);
}
void BetterGoZDialog::postLoadMesh() {
	mOptions.setOptionsFromSettings();
	cbMorphLoadType->setCurrentIndex(mOptions.getLoadMode());
	cbSubD->setCurrentIndex(mOptions.mSubDCage);
	cbOE->setChecked(mOptions.mOE);
	cbReverse->setChecked(mOptions.getRevD());
	cbApplyToGrafts->setChecked(mOptions.mApplyToGrafts);
	cbApplyMorph->setChecked(mOptions.applyMoprh);
	cbUseLimits->setChecked(mOptions.useLimits);
	spMin->setValue(mOptions.limMin);
	spMax->setValue(mOptions.limMax);
	cbMirror->setChecked(mOptions.mMirror);
	
	cmbPath->setEditText(mOptions.mPath);
	
	spScale->setValue(mOptions.mScale);
	if (cbApplyToGrafts->isChecked()) {
		cbMorphLoadType->setCurrentIndex(4);
		cbMorphLoadType->setEnabled(false);
	}


	DzNode* node = GET_NODE();
	if (node) {
		cmbName->addItems(mOptions.nameHistory);
		cmbName->setCurrentIndex(0);
		selectionChanged(node);
		updatePath(node, mOptions.mPath);
	} else {
		qDebug() << "post load mesh No node";
	}
	//dump(cmbPath);
	mDebug() << "CmbPath Height " << cmbPath->height();
	//dump(this);
}

void BetterGoZDialog::show()
{
	getMainWindow()->setWindowState((getMainWindow()->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
	getMainWindow()->activateWindow();
	QWidget::show();
}


void BetterGoZDialog::importAsNew() {


	DzFacetShape* shape = new DzFacetShape();
	shape->setName("Default");
	shape->setLabel("Default");
	DzFacetMesh* mMesh=mOptions.mMesh;
	int n = mMesh->getNumMaterialGroups();
	for (int i = 0; i < n; i++) {
		DzMaterial* mat = new DzDefaultMaterial();
		mat->setName(mMesh->getMaterialGroup(i)->getName());
		shape->addMaterial(mat);
		//mesh->selectFacets(mMesh->getMaterialGroup(i));
		//mesh->addSelectedFacetsToMaterialGroup(i);
		//mesh->deselectAllFacets();
	}
	DzFacetMeshPtr mesh = mMesh->buildWorkingMeshForShape(shape, 0);

	//mesh->finishEdit();*/
	shape->setFacetMesh(mesh);
	DzNode* node = new DzNode();
	node->setName(mMesh->getName());
	node->setLabel("Goz_" + mMesh->getName());
	DzObject* obj = new DzObject();
	obj->setName("Goz_" + mMesh->getName() + "obj");
	obj->addShape(shape);
	node->setObject(obj);
	mMesh->unref();

	////////////newObj->finalize(*newNode,false);
	//mShape->finalize(*newNode,*mMesh,false);

	DzPresentation* pres = node->getPresentation();

	// If the node did not have a presentation,
	// create one and assign it to the node
	if (!pres){
		pres = new DzPresentation();
		node->setPresentation(pres);
	}
	pres->setType("Prop");
	dzScene->addNode(node);
	obj->forceCacheUpdate(node, true);
	node->finalize(true, true);

	//	mShape->deleteLater();

}

void BetterGoZDialog::addNewPath() {
	DzBasicDialog dlg(this, "addPath");
	QLineEdit* le = new QLineEdit(NULL, "etAddPath");
	dlg.addWidget(le, 1, Qt::AlignHCenter);
	le->setText(cmbPath->getFullPath());
	le->setMinimumWidth(400);
	le->setStyleSheet("border: 2px solid gray;\nbackground: #262A32;\ncolor:white;\nselection-background-color: white;\nfont-size: 12px;\nfont-family: 'helvetica';\n");
	le->setFocus();
	dlg.exec();
	QString newPath = le->text();
	updatePath(dzScene->getPrimarySelection(), newPath);

}
void BetterGoZDialog::updatePath(DzNode* node, QString path, bool fromSelected) {
	if (!node)return;
	cmbPath->updatePath(node,path);
	
	
	//mDebug()<<"updatePath() currentPath:"<<currentPath<<" path in:"<<path;





}
void BetterGoZDialog::selectionChanged(DzNode* node) {
	if (!node)return;
	tvFigureName->setText(node->getLabel());
	if (!node->getObject())return;
	DzFacetMesh* cachedMesh = (DzFacetMesh*)node->getObject()->getCachedGeom();
	DzFacetMesh* baseGeom = (DzFacetMesh*)node->getObject()->getCurrentShape()->getGeometry();
	DzShape* shape = node->getObject()->getCurrentShape();
	DzGraftingFigureShape* gfShape = qobject_cast<DzGraftingFigureShape*>(shape);
	if (gfShape) {
		DzFigure* figure = (DzFigure*)node;
		if (figure->isGraftFollowing())figure = (DzFigure*)figure->getFollowTarget();
		gfShape = (DzGraftingFigureShape*)figure->getObject()->getCurrentShape();
		DzFacetMesh* assyGeom = (DzFacetMesh*)gfShape->getAssemblyGeometry();
		mSubDLev = calcSubdLev(cachedMesh, assyGeom);
	} else {
		mSubDLev = calcSubdLev(mOptions.mMesh, baseGeom);

	}
	qDebug() << "GoZDlg mSubDLev:" << mSubDLev;
	spSubDLev->setValue(mSubDLev);

	tvNumFacesBase->setText(QString::number(baseGeom->getNumFacets()));
	tvNumFacesGoZ->setText(QString::number(mOptions.mMesh->getNumFacets()));
	tvNumFacesCached->setText(QString::number(cachedMesh ? cachedMesh->getNumFacets() : 0));
	DzProperty* prop = findNodePropertyByLabel(node, cmbName->currentText());
	if (prop){
		updatePath(node, prop->getPath());
	}else {
		updatePath(node,mOptions.getPath());
	}

}
int BetterGoZDialog::calcSubdLev(DzFacetMesh* subDMesh, DzFacetMesh* baseMesh)
{
	float faces = (float)subDMesh->getNumFacets();
	float target = baseMesh->getNumFacets() * 1.02;
	int lev = 0;
	while (faces > target){
		faces /= 4.0;
		lev++;
	}
	return lev;
}
class DzParametersPane;

void BetterGoZDialog::updateMorphName() {
	DzNode* node = dzScene->getPrimarySelection();
	if (!node)return;
	DzPane* pane = dzApp->getInterface()->getPaneMgr()->findPane("DzParametersPane");
	const QString nodeEditorName("ParametersWgt");
	QObject* ne = pane->findChild<QObject*>(nodeEditorName);
	int idx = ne->metaObject()->indexOfMethod("getPrimaryPropertySelection()");
	QObjectList props;
	ne->metaObject()->invokeMethod(ne, "getPropertySelections", Qt::DirectConnection, Q_RETURN_ARG(QObjectList, props));
	if (props.length() > 0){
		DzFloatProperty* prop = (DzFloatProperty*)props.at(0);
		qDebug() << prop->getLabel();
		qDebug() << prop->getName();
		QString path = prop->getPath();
		updatePath(node, path, true);
		cmbName->setCurrentText(prop->getLabel());
	} else {
		updatePath(node, mOptions.mPath, false);
	}


}
void BetterGoZDialog::print(QString s) {
	textBrowser->append(s);
	QCoreApplication::processEvents();
}

void BetterGoZDialog::hideEvent(QHideEvent* event1){
	mDebug() << "Goz Dlg, Hide Event Mesh Ref Count" <<mOptions.mMesh->getRefCount() ;
	while(mOptions.mMesh->getRefCount()>0)mOptions.mMesh->unref();
	//mOptions.setMesh(NULL);


}

void BetterGoZDialog::createMorph() {
	mDebug() << "Create Morph()";

	DzNodeList nodes;

	mOptions.mApplyToGrafts = cbApplyToGrafts->isChecked();
	mOptions.mMirror = cbMirror->isChecked();
	mOptions.mRevDef = cbReverse->isChecked();
	mOptions.mSubDCage = (DzMorphLoader::SubdMapping)cbSubD->currentItem();
	mOptions.mMorphName = cmbName->currentText();
	mOptions.mPath = cmbPath->getFullPath();
	mOptions.mOE = cbOE->isChecked();
	mOptions.mSubDLev = spSubDLev->value();
	mOptions.loadMode = (DzMorphLoader::LoadMode)cbMorphLoadType->currentIndex();
	mOptions.applyMoprh = cbApplyMorph->isChecked();
	mOptions.useLimits = cbUseLimits->isChecked();
	mOptions.limMin = spMin->value();
	mOptions.limMax = spMax->value();
	mOptions.mScale=spScale->value();
	mOptions.writeOptionsToSettings();
	DzNode* node = GET_NODE();
	if (node==NULL){
		textBrowser->append("No Node Selected.");
		return;
	}
	DzFigure* figure = (DzFigure*)node;

	if (node->inherits("DzFigure")) {
		if (mOptions.mApplyToGrafts){

			int numGrafts = figure->getNumGraftFigures();
			for (int i = 0; i < numGrafts; i++) {
				DzFigure* graft = figure->getGraftFigure(i);
				nodes.append(graft);
				doGraftMorph(graft);
			}
		}
		
	}
	doGraftMorph(node);
	nodes.append(node);
}

bool BetterGoZDialog::doGraftMorph(DzNode* node) {
	DzMorphLoader* ml = (DzMorphLoader*)dzApp->findClassFactory("DzMorphLoader")->createInstance();
	QString optOut;

	optOut += "\nCreating Morph With Options on: ";
	optOut += node->getLabel();
	optOut += " \nOptions:" + mOptions.toString();
	mDebug() << optOut;
	textBrowser->append(optOut);
	ml->setMorphMirroring(mOptions.mMirror ? DzMorphLoader::MirroringType::XSwap : DzMorphLoader::MirroringType::DoNotMirror);
	ml->setReverseDeformations(mOptions.mRevDef);
	ml->setSubdivisionMapping(mOptions.mSubDCage);
	ml->setSubdivisionBuiltResolution(mOptions.mSubDLev);
	ml->setPropertyGroupPath(mOptions.mPath);
	ml->setMorphName(mOptions.mMorphName);

	ml->setMorphSubdivision(mOptions.mSubDLev > 0);
	ml->setOverwriteExisting(mOptions.mOE ? DzMorphLoader::OverwriteMode::DeltasOnly : DzMorphLoader::OverwriteMode::MakeUnique);
	ml->setLoadMode(mOptions.loadMode, node);
	DzFacetMesh* morphMesh=mOptions.getScaledMesh();
	QString out = ml->createMorphFromMesh(morphMesh, node, false, false);
	out += " " + node->getLabel(); +" " + mOptions.mMorphName;
	textBrowser->insertHtml(out);
	ml->deleteLater();
	bool success=out.contains("successfully");
	QString sucS=success?"Success":"Failure";
	textBrowser->append("Morph Creation "+sucS);
	if (success){
		dzScene->update();
		processEvents();
		DzMorph* mod = (DzMorph*)node->getObject()->findModifier(mOptions.getMorphName());
		DzFloatProperty* prop = qobject_cast<DzFloatProperty*>(findNodePropertyByLabel(node, mOptions.mMorphName));
		if (prop) {

			if (cbApplyMorph->isChecked())prop->setValue(1.0);
			if (cbUseLimits->isChecked()) {
				prop->beginEdit();
				prop->setMinMax(spMin->value(), spMax->value());
				prop->finishEdit();

			} else {
				prop->setIsClamped(false);
			}
			node->update(true);
		} else {
			mDebug() << "NO PROPERTY FOUND";
			textBrowser->insert("No Property Found on Node");
		}
	}
	return out.contains("Successfully");
}



#include "betterGozDlg_moc.cpp"