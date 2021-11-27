#pragma once
#ifndef GOZ_FILE_READER
#define GOZ_FILE_READER

#include "dzinclude.h"
class GoZFileReader : public QObject {
	Q_OBJECT
public:

	GoZFileReader(QObject* parent) :QObject(parent) {  }
	
	QString mMeshName;
public slots:
	DzFacetMeshPtr readGoZ();
	 
	void writeGoZ(DzNode* node);
private:
	

	void writeGoZFile(
		QString& GoZBinFilename,
		QString& meshName,
		const std::vector<std::vector<float>>& V,
		const std::vector<std::vector<int>>& F,
		const std::vector<std::vector<std::pair<float, float>>>& UV,
		const std::vector<std::vector<float>>& VC,
		const std::vector<float>& M,
		const std::vector<int>& G);

	void writeGoZFile(
		QString& GoZBinFilename,
		QString& meshName,
		const std::vector<std::vector<float>>& V,
		const std::vector<std::vector<int>>& F);

};
#endif