#define NOMINMAX
#include "gozfilereader.h"

#include <functional>

#include "dzplugin.h"
#include "dzapp.h"
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
#include "dzscript.h"
#include "dzfigure.h"
#include "dzfacetshape.h"
#include "qdatetime.h"
#include "GoZ_Mesh.h"
#include "dzfacetshape.h"
#include "dzface.h"
#include "dzfacegroup.h"
#include "generated/dzuvsetbuilder.h"
#define GROUPS_MATERIAL 0
#define GROUPS_EXISTING 1
#define GROUPS_REGION 2
#define GROUPS_SELECTION_SETS 3
using namespace std;



DzFacetMeshPtr GoZFileReader::readGoZ() {
	QFile obListFile("C:/Users/Public/Pixologic/GoZBrush/GoZ_ObjectList.txt");
	obListFile.open(QIODevice::ReadOnly);
	QString line(obListFile.readAll());
	QString gozPath = line.trimmed().append(".goz");
	qDebug() << "GoZPath: " << gozPath;
	
	mDebug() << "Read of GoZ Start:";
	qint64 startTime = QDateTime::currentMSecsSinceEpoch();
	
	GoZ_Mesh gozMesh;
	gozMesh.readMesh(gozPath);
	  

					
	QSet<short>groups;
	for(int i=0;i<gozMesh.m_faceCount;i++)groups.insert(gozMesh.m_groups[i]);
	QList<short>groupList=groups.toList();
	qSort(groupList);
	QStringList matList;
	
	QMap<short,DzFaceGroupPtr>mMatMap;
	DzFacetMeshPtr mMesh(new DzFacetMesh());
	//mMesh->ref();
	mMesh->setName(gozMesh.m_name);
	mMesh->beginEdit(false);
	for(int i=0;i<groups.size();i++) {
		QString matName= "Mat_"+QString::number(groupList[i]);
		matList<<matName;
		DzFaceGroupPtr ptr(new DzFaceGroup(matName));
		mMatMap.insert(groupList[i],ptr);
		int matnum=mMesh->createMaterialGroup(matName);
		
		//mDebug()<<"Created material group< "	<<matName<<" matnum "<<matnum<<" numMatGroups: "<<mMesh->getNumMaterialGroups();//<< "num shape mats: "<<shape->getNumMaterials();
	}
	if(groupList.size()==0)groupList.append(0);
	qint64 endTime = QDateTime::currentMSecsSinceEpoch() - startTime;
	qint64 startMeshTime = QDateTime::currentMSecsSinceEpoch();
	mDebug() << "Read Of File Complete in " << endTime << "MS";
	mMesh->activateMaterial(matList[0]);
	DzUVSet* map =new DzUVSet();
	mMesh->preSizeVertexArray(gozMesh.m_vertexCount);
	mMesh->preSizeFacets(gozMesh.m_faceCount);
	float* Vs = gozMesh.m_vertices;
	for (int i = 0; i < gozMesh.m_vertexCount; i++) {
		mMesh->addVertex(Vs[i * 3]*10, Vs[i * 3 + 1]*-10, Vs[i * 3 + 2]*-10);
	}

	
	map->preSize(gozMesh.m_faceCount * 8);
	
		int count = 0;
		float* gUVS = gozMesh.m_uvs;
		for (int i = 0; i < gozMesh.m_faceCount; i++) {
			DzPnt2 pt0 = { gUVS[i * 8],gUVS[i * 8 + 1] };
			DzPnt2 pt1 = { gUVS[i * 8 + 2],gUVS[i * 8 + 3] };
			DzPnt2 pt2 = { gUVS[i * 8 + 4],gUVS[i * 8 + 5] };
			DzPnt2 pt3 = { gUVS[i * 8 + 6],gUVS[i * 8 + 7] };

			map->appendPnt2Value(pt0);
			map->appendPnt2Value(pt1);
			map->appendPnt2Value(pt2);
			map->appendPnt2Value(pt3);
			
		}
	
	mDebug() << "Adding Vertices Complete in" << QDateTime::currentMSecsSinceEpoch() - startMeshTime;
	mMesh->setUVList(map);
	qDebug() << "GoZReader: mesh verts:" << gozMesh.m_vertices;
	qDebug() << "GoZReader: mesh faces:" << gozMesh.m_faceCount;
	
	
	int* fIdx = gozMesh.m_vertexIndices;
	DzMaterial* mat;
	for (int i = 0; i < gozMesh.m_faceCount; i++) {
			int vs[4];
			vs[0]= fIdx[i * 4]; vs[1] = fIdx[i * 4 + 1]; vs[2] = fIdx[i * 4 + 2]; vs[3] = fIdx[i * 4 + 3];
			int uvs[4]={i*4,i*4+1,i*4+2,i*4+3};
			int idx = groupList.indexOf(gozMesh.m_groups[i]);
			mMesh->activateMaterial(groupList.indexOf(gozMesh.m_groups[i]));
			mMesh->addFacet(vs, uvs);
			/*DzFaceGroup* matG=mMatMap.value(gozMesh.m_groups[i]);
			matG->addIndex(i);			*/
			
		
		
	}
	mMesh->deactivateMaterialGroup();
	mDebug()<<"Adding faces complete";
	/*for(int i=0;i<mMatMap.count();i++) {
		DzFaceGroupPtr ptr=mMatMap.value(mMatMap.keys()[i]);
		mMesh->createMaterialGroup(ptr->getName());
		mMesh->deselectAllFacets();
		mMesh->selectFacets(ptr);
		mMesh->addSelectedFacetsToMaterialGroup(i);
		mMesh->deselectAllFacets();
	}*/
	mMesh->finishEdit();
	qint64 finishMeshTime = QDateTime::currentMSecsSinceEpoch() -startMeshTime;
	qint64 totalTime = finishMeshTime + endTime;
	mDebug() << "Read GoZ complete in " << totalTime << " ms " << "read of goZ " << endTime << " creation of mesh " << finishMeshTime<<" mesh ref count:"<<mMesh->getRefCount();
	return mMesh;

}


	 void GoZFileReader::writeGoZ(DzNode* node) {

	DzFigure* figure = qobject_cast<DzFigure*>(node);
	DzBasicDialog dlg(NULL, "Export Options");
	QCheckBox* cbGrafts = new QCheckBox(&dlg);
	dlg.addWidget(cbGrafts);
	dlg.setMinimumWidth(250);
	cbGrafts->setChecked(true);
	cbGrafts->setText("Export with Grafts Attached");
	cbGrafts->setMinimumHeight(30);
	QCheckBox* cbRes = new QCheckBox();

	cbRes->setText("Export at Current resolution");
	cbRes->setChecked(true);
	cbRes->setMinimumHeight(30);
	dlg.addWidget(cbRes);
	QComboBox* cbGroups = new QComboBox(&dlg);
	cbGroups->addItem("Use Material Groups");
	cbGroups->addItem("Use Existing Face Groups");
	if (figure) {
		cbGroups->addItem("Use Regions as Groups");
	}
	cbGroups->addItem("No Groups");
	dlg.addWidget(cbGroups);
	DzViewportMgr* vpm = dzApp->getInterface()->getViewportMgr();
	DzObject* object = node->getObject();
	dlg.setCaption("Export Options");

	if (!dlg.exec())return;
	long startTime = QDateTime::currentMSecsSinceEpoch();
	bool useGrafts = cbGrafts->isChecked();
	bool allowGraftDrawing = vpm->allowGraftDrawing();
	int groupsType = cbGroups->currentIndex();
	vpm->setAllowGraftDrawing(useGrafts);
	object->update(*node, false);
	object->finalize(*node, false, true);

	QCoreApplication::processEvents();
	dzScene->update();
	QCoreApplication::processEvents();

	DzFacetMesh* mesh = (DzFacetMesh*)object->getCachedGeom();

	DzUVSet* uvSet = (DzUVSet*)mesh->getUVs();
	QString meshName(node->getLabel());
	std::vector<std::vector<float>> V, VC;
	std::vector<float> M;
	std::vector<int> G(mesh->getNumFacets());
	std::vector<std::vector<int>> F;
	std::vector<std::vector<std::pair<float, float>>> UV;

	int numVerts = mesh->getNumVertices();
	for (int i = 0; i < numVerts; i++) {
		DzVec3 inVert = mesh->getVertex(i);
		std::vector<float> outVert(3);
		outVert[0] = inVert.m_x * .1;
		outVert[1] = inVert.m_y * -.1;
		outVert[2] = inVert.m_z * -.1;
		V.push_back(outVert);
	}
	int numFaces = mesh->getNumFacets();


	for (int i = 0; i < numFaces; i++) {
		std::vector<int>outFace(4);
		DzFacet face = mesh->getFacet(i);


		outFace[0] = face.m_vertIdx[0];
		outFace[1] = face.m_vertIdx[1];
		outFace[2] = face.m_vertIdx[2];
		outFace[3] = face.m_vertIdx[3];
		F.push_back(outFace);

		if (uvSet) {
			std::vector<std::pair<float, float>>outUV;
			for (int j = 0; j < 4; j++) {
				DzVec3 uvPoint = uvSet->getPnt2Vec(face.m_uvwIdx[j]);
				outUV.push_back(std::pair<float, float>(uvPoint.m_x, uvPoint.m_y));
			}


			UV.push_back(outUV);
		}
	}
	QFile obPathFile("C:/Users/Public/Pixologic/GoZBrush/GoZ_ObjectPath.txt");
	obPathFile.remove();
	obPathFile.open(QIODevice::WriteOnly);
	QString Ob(meshName);
	obPathFile.write(Ob);
	obPathFile.close();
	if (groupsType == GROUPS_EXISTING) {
		int numGroups = mesh->getNumFaceGroups();
		for (int i = 0; i < numGroups; i++) {
			DzFaceGroup* fg = mesh->getFaceGroup(i);
			int numIdx = fg->count();
			for (int j = 0; j < numIdx; j++) {
				G[fg->getIndex(j)] = i * 1000;
			}
		}
	} else if (groupsType == GROUPS_MATERIAL) {
		int numMats = mesh->getNumMaterialGroups();
		for (int i = 0; i < numMats; i++) {
			DzFaceGroup* fg = mesh->getMaterialGroup(i);
			int numIdx = fg->count();
			for (int j = 0; j < numIdx; j++) {
				G[fg->getIndex(j)] = i * 1000;
			}
		}
	} else if (groupsType == GROUPS_REGION) {

	}
	QProcess::startDetached("C:/Users/Public/Pixologic/GoZBrush/GoZMakeObjectPath.exe");
	Sleep(100);
	QFile obPathFile2("C:/Users/Public/Pixologic/GoZBrush/GoZ_ObjectPath.txt");
	obPathFile2.open(QIODevice::ReadOnly);
	QString objectPath(obPathFile2.readLine());
	//objectPath=objectPath.trimmed();
	obPathFile2.close();





	QFile obListFile("C:/Users/Public/Pixologic/GoZBrush/GoZ_ObjectList.txt");
	obListFile.remove();
	obListFile.open(QIODevice::WriteOnly);
	obListFile.write(objectPath);
	obListFile.close();

	QString gozPath(objectPath + ".goz");
	qDebug() << "objectPath=" << objectPath;
	qDebug() << "gozPath  = " << gozPath;
	QFile appFile("C:/Users/Public/Pixologic/GoZBrush/GoZ_Application.txt");
	appFile.remove();
	appFile.open(QIODevice::WriteOnly);
	appFile.write("dazStudio64");
	appFile.close();
	writeGoZFile(gozPath, meshName, V, F, UV, VC, M, G);
	QProcess::startDetached("C:/Users/Public/Pixologic/GoZBrush/GoZBrushFromApp.exe");
	vpm->setAllowGraftDrawing(allowGraftDrawing);
	vpm->setAllowGraftDrawing(useGrafts);
	object->update(*node, false);
	object->finalize(*node, false, true);

	QCoreApplication::processEvents();
	dzScene->update();
	QCoreApplication::processEvents();
	delete(cbRes);
	delete(cbGrafts);
	delete(cbGroups);
	long cTime = QDateTime::currentMSecsSinceEpoch() - startTime;
	mDebug() << "Write of goZ file finished in " << cTime << "ms";
}
void GoZFileReader::writeGoZFile(
	QString& GoZBinFilename,
	QString& meshName,
	const std::vector<std::vector<float>>& V,
	const std::vector<std::vector<int>>& F)
{
	std::vector<std::vector<std::pair<float, float>>> UV;
	std::vector<std::vector<float>> VC;
	std::vector<float> M;
	std::vector<int> G;

	writeGoZFile(GoZBinFilename, meshName, V, F, UV, VC, M, G);
}


void GoZFileReader::writeGoZFile(
	QString& GoZBinFilename,
	QString& meshName,
	const std::vector<std::vector<float>>& V,
	const std::vector<std::vector<int>>& F,
	const std::vector<std::vector<std::pair<float, float>>>& UV,
	const std::vector<std::vector<float>>& VC,
	const std::vector<float>& M,
	const std::vector<int>& G)
{
	// union data structures for conversion
	union uint32_char
	{
		quint32 i;
		char c[4];
		unsigned char uc[4];
	};
	union uint64_char
	{
		quint64 i;
		char c[8];
	};
	union float_char
	{
		float f;
		char c[4];
	};

	// GoZ binary file uses littele endian
	bool isThisSystemLittleEndian = false;
	{
		uint32_char tmp = { 0x01020304 };
		isThisSystemLittleEndian = (tmp.c[0] == 4);
	}
	qDebug() << GoZBinFilename;
	QFile GoZFile(GoZBinFilename);
	GoZFile.open(QIODevice::WriteOnly);
	QDataStream out(&GoZFile);

	// Header
	{
		std::string buf("GoZb 1.0 ZBrush GoZ Binary");
		out.writeRawData(buf.c_str(), buf.size());
		for (int i = 0; i < 6; ++i)
		{
			out << static_cast<unsigned char>(0x2E);

		}
	}
	{
		uint32_char tmp;
		tmp.i = quint32(1);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);

		tmp.i = meshName.size() + 24;
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);
	}
	{
		uint64_char tmp;
		tmp.i = quint64(1);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[7]);
			std::swap(tmp.c[1], tmp.c[6]);
			std::swap(tmp.c[2], tmp.c[5]);
			std::swap(tmp.c[3], tmp.c[4]);
		}
		out.writeRawData(tmp.c, 8);
	}

	// Mesh name
	{
		QString buf("GoZMesh_");
		buf += meshName;

		out.writeRawData(buf.toLocal8Bit(), buf.size());
		char c7[4] = { 0x89,0x13,0,0 };

		out.writeRawData(c7, 4);
	}
	{
		uint32_char tmp;
		tmp.i = quint32(20);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);
	}
	{
		uint64_char tmp;
		tmp.i = quint64(1);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[7]);
			std::swap(tmp.c[1], tmp.c[6]);
			std::swap(tmp.c[2], tmp.c[5]);
			std::swap(tmp.c[3], tmp.c[4]);
		}
		out.writeRawData(tmp.c, 8);
	}
	{
		uint32_char tmp;
		tmp.i = quint32(0);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);
	}

	// Vertices
	{
		char cc[4] = { 0x11,0x27,0,0 };
		out.writeRawData(cc, 4);

	}
	{
		uint32_char tmp;
		tmp.i = quint32(V.size() * 3 * 4 + 16);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);
	}
	{
		uint64_char tmp;
		tmp.i = quint64(V.size());
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[7]);
			std::swap(tmp.c[1], tmp.c[6]);
			std::swap(tmp.c[2], tmp.c[5]);
			std::swap(tmp.c[3], tmp.c[4]);
		}
		out.writeRawData(tmp.c, 8);
	}
	for (int vnum = 0; vnum < V.size(); vnum++){
		const vector<float>& vertex = V[vnum];
		for (int xyzNum = 0; xyzNum < vertex.size(); xyzNum++){
			const float& xyz = vertex[xyzNum];
			float_char tmp;
			tmp.f = static_cast<float>(xyz);
			if (!isThisSystemLittleEndian){
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
	}

	// Faces
	{
		char fff[4] = { 0x21,0x4E,0,0 };
		out.writeRawBytes(fff, 4);
	}
	{
		uint32_char tmp;
		tmp.i = quint32(F.size() * 4 * 4 + 16);
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[3]);
			std::swap(tmp.c[1], tmp.c[2]);
		}
		out.writeRawData(tmp.c, 4);
	}
	{
		uint64_char tmp;
		tmp.i = quint64(F.size());
		if (!isThisSystemLittleEndian)
		{
			std::swap(tmp.c[0], tmp.c[7]);
			std::swap(tmp.c[1], tmp.c[6]);
			std::swap(tmp.c[2], tmp.c[5]);
			std::swap(tmp.c[3], tmp.c[4]);
		}
		out.writeRawData(tmp.c, 8);
	}
	for (int i = 0; i < F.size(); i++){
		const vector<int>& face = F[i];

		for (int j = 0; j < face.size(); j++){
			const int& fv = face[j];
			uint32_char tmp;
			tmp.i = static_cast<quint32>(fv);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
		for (int j = face.size(); j < 4; ++j)
		{
			out << static_cast<unsigned char>(0xff);
			out << static_cast<unsigned char>(0xff);
			out << static_cast<unsigned char>(0xff);
			out << static_cast<unsigned char>(0xff);
		}
	}

	// UVs
	if (UV.size() == F.size())
	{
		{
			out << static_cast<unsigned char>(0xA9);
			out << static_cast<unsigned char>(0x61);
			out << static_cast<unsigned char>(0x00);
			out << static_cast<unsigned char>(0x00);
		}
		{
			uint32_char tmp;
			tmp.i = quint32(UV.size() * 4 * 2 * 4 + 16);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
		{
			uint64_char tmp;
			tmp.i = quint64(UV.size());
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[7]);
				std::swap(tmp.c[1], tmp.c[6]);
				std::swap(tmp.c[2], tmp.c[5]);
				std::swap(tmp.c[3], tmp.c[4]);
			}
			out.writeRawData(tmp.c, 8);
		}
		for (int q = 0; q < UV.size(); q++){
			const vector<pair<float, float>>& faceUV = UV[q];
			for (int f = 0; f < faceUV.size(); f++){
				const pair<float, float>& uv = faceUV[f];
				float_char tmp;
				tmp.f = static_cast<float>(uv.first);
				if (!isThisSystemLittleEndian)
				{
					std::swap(tmp.c[0], tmp.c[3]);
					std::swap(tmp.c[1], tmp.c[2]);
				}
				out.writeRawData(tmp.c, 4);
				tmp.f = static_cast<float>(uv.second);
				if (!isThisSystemLittleEndian)
				{
					std::swap(tmp.c[0], tmp.c[3]);
					std::swap(tmp.c[1], tmp.c[2]);
				}
				out.writeRawData(tmp.c, 4);
			}
			for (int i = faceUV.size(); i < 4; ++i)
			{
				float_char tmp;
				tmp.f = 0.0f;
				if (!isThisSystemLittleEndian)
				{
					std::swap(tmp.c[0], tmp.c[3]);
					std::swap(tmp.c[1], tmp.c[2]);
				}
				out.writeRawData(tmp.c, 4);
				tmp.f = 1.0f;
				if (!isThisSystemLittleEndian)
				{
					std::swap(tmp.c[0], tmp.c[3]);
					std::swap(tmp.c[1], tmp.c[2]);
				}
				out.writeRawData(tmp.c, 4);
			}
		}
	}

	// Polypaints
	if (VC.size() == V.size())
	{
		{
			out << static_cast<unsigned char>(0xB9);
			out << static_cast<unsigned char>(0x88);
			out << static_cast<unsigned char>(0x00);
			out << static_cast<unsigned char>(0x00);
		}
		{
			uint32_char tmp;
			tmp.i = quint32(V.size() * 4 + 16);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
		{
			uint64_char tmp;
			tmp.i = quint64(V.size());
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[7]);
				std::swap(tmp.c[1], tmp.c[6]);
				std::swap(tmp.c[2], tmp.c[5]);
				std::swap(tmp.c[3], tmp.c[4]);
			}
			out.writeRawData(tmp.c, 8);
		}
		for (int k = 0; k < VC.size(); k++){
			const vector<float>& vc = VC[k];
			uint32_char tmp;
			tmp.uc[0] = static_cast<unsigned char>(qRound(vc.at(2) * 255.0));
			tmp.uc[1] = static_cast<unsigned char>(qRound(vc.at(1) * 255.0));
			tmp.uc[2] = static_cast<unsigned char>(qRound(vc.at(0) * 255.0));
			tmp.uc[3] = static_cast<unsigned char>(qRound(vc.at(3) * 255.0));

			out.writeRawData(tmp.c, 4);
		}
	}

	// Mask
	if (M.size() == V.size())
	{
		{
			out << static_cast<unsigned char>(0x32);
			out << static_cast<unsigned char>(0x75);
			out << static_cast<unsigned char>(0x00);
			out << static_cast<unsigned char>(0x00);
		}
		{
			uint32_char tmp;
			tmp.i = quint32(V.size() * 2 + 16);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
		{
			uint64_char tmp;
			tmp.i = quint64(V.size());
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[7]);
				std::swap(tmp.c[1], tmp.c[6]);
				std::swap(tmp.c[2], tmp.c[5]);
				std::swap(tmp.c[3], tmp.c[4]);
			}
			out.writeRawData(tmp.c, 8);
		}
		for (int mm = 0; mm < M.size(); mm++){
			const float& m = M[mm];
			uint32_char tmp;
			tmp.i = static_cast<quint32>(qRound(m * std::numeric_limits<quint16>::max()));
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 2);
		}
	}

	// Polygroups
	if (G.size() == F.size())
	{
		{
			out << static_cast<unsigned char>(0x41);
			out << static_cast<unsigned char>(0x9C);
			out << static_cast<unsigned char>(0x00);
			out << static_cast<unsigned char>(0x00);
		}
		{
			uint32_char tmp;
			tmp.i = quint32(G.size() * 2 + 16);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 4);
		}
		{
			uint64_char tmp;
			tmp.i = quint64(G.size());
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[7]);
				std::swap(tmp.c[1], tmp.c[6]);
				std::swap(tmp.c[2], tmp.c[5]);
				std::swap(tmp.c[3], tmp.c[4]);
			}
			out.writeRawData(tmp.c, 8);
		}
		for (int gi = 0; gi < G.size(); gi++){
			const int& g = G[gi];
			uint32_char tmp;
			tmp.i = static_cast<quint32>(g);
			if (!isThisSystemLittleEndian)
			{
				std::swap(tmp.c[0], tmp.c[3]);
				std::swap(tmp.c[1], tmp.c[2]);
			}
			out.writeRawData(tmp.c, 2);
		}
	}

	// End
	{
		out << static_cast<unsigned char>(0x00);
		out << static_cast<unsigned char>(0x00);
		out << static_cast<unsigned char>(0x00);
		out << static_cast<unsigned char>(0x00);
	}

	GoZFile.close();
}



#include "gozfilereader_moc.cpp"
