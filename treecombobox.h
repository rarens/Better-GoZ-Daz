#include "dzinclude.h"

#ifndef GP_TREE_COMBOBOX
#define GP_TREE_COMBOBOX
class TreeComboBox : public QComboBox {
    Q_OBJECT
public:
    TreeComboBox(QWidget* parent = 0) : QComboBox(parent), skipNextHide(false) {
                    mTreeView=new QTreeView(this);
    	mTreeView->setMinimumHeight(300);
    	mModel=new DzPathItemModel(mTreeView);
    	//mTreeView->setRootIsDecorated(false);
    	
    	setModel(mModel);
    	mTreeView->viewport()->installEventFilter(this);
    	setView(mTreeView);
			mTreeView->setHeaderHidden(true);
    	    
         DzConnect(view()->selectionModel(),SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),this,SLOT(updateModelIndex(const QModelIndex &)));
    	//DzConnect(mModel,SIGNAL(dataChanged(const QModelIndex & , const QModelIndex & )),this,SLOT(updateComboString()));
        //DzConnect(mModel,SIGNAL(rowsRemoved(const QModelIndex & , int , int )),this,SLOT(updateComboString()));
        //DzConnect(mModel,SIGNAL(rowsInserted(const QModelIndex &, int , int )),this,SLOT(updateComboString()));
        //DzConnect(mModel,SIGNAL(rowsMoved(const QModelIndex &, int , int, const QModelIndex &, int)),this,SLOT(updateComboString()));
    }
	public slots:
    QString getFullPath() {
        DzHierarchyPath path = mModel->pathFromIndex(view()->currentIndex());
        const QString fullPath = path.getTextPath(true);
        return fullPath;
    }
	
      virtual void paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);
        QStylePainter painter(this);
        painter.setPen(palette().color(QPalette::Text));

        QStyleOptionComboBox opt;
        initStyleOption(&opt);
        opt.currentText = mPath;
        
        painter.drawComplexControl(QStyle::CC_ComboBox, opt);
        painter.drawControl(QStyle::CE_ComboBoxLabel, opt);
    }
    bool eventFilter(QObject* object, QEvent* event) {
        if (event->type() == QEvent::MouseButtonPress && object == view()->viewport()) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QModelIndex index = view()->indexAt(mouseEvent->pos());
            if (!view()->visualRect(index).contains(mouseEvent->pos()))
                skipNextHide = true;
        }
        return false;
    }
   	void updateModelIndex(const QModelIndex& idx){
    	mDebug()<<"TreeCombo updateModelIndex()";
        if(idx.isValid()){
            mIndex=idx;
        	//setCurrentIndex(mIndex.row());
        	}
    	//updateComboString();
    }
   void updateComboString(){
		mDebug()<<"UpdateComboString()"      <<getFullPath();
		//setCurrentIndex(mIndex.row());
          mPath=getFullPath();
    	setCurrentText(mPath);
    }
	void updatePath(DzNode* node, QString path) {
    	mDebug()<<"TreeCombo updatePath() "<<path;
    	
    	QStringList list=node->getPropertyGroups()->getAllPaths();
    	if(!list.contains(path))list<<path;
        mModel->clearPaths();
    	setRootModelIndex(QModelIndex());
    	
    	mModel->setPaths(list);
    	mIndex=mModel->getIndexForPath(path);
		mPath=path;
    	mTreeView->setCurrentIndex(mIndex);
    	setEditText(mPath);
    	
    	updateComboString();
    	update();
    }
    virtual void showPopup() {
    	mDebug()<<"TreeCombo->Show Popup() "<<mTreeView->x()<<", "<<mTreeView->y();
        setRootModelIndex(QModelIndex());
        QComboBox::showPopup();
                                                        
    	QFrame* popup =(QFrame*)this->findChild<QFrame*>();
    	
		popup->move(popup->x(),popup->y()+height());
    }
	
    virtual void hidePopup()
    {
    	mDebug()<<"TreeCombo hidePopup()";
        setRootModelIndex(QModelIndex());
        DzPathItemModel* mModel = (DzPathItemModel*)model();
        DzHierarchyPath path = mModel->pathFromIndex(view()->currentIndex());
        mPath = path.getTextPath(false);
				        
        
        if (skipNextHide)
            skipNextHide = false;
        else
            QComboBox::hidePopup();
    }

private:
    bool skipNextHide;
	DzPathItemModel* mModel;
	QTreeView* mTreeView;
	QString mPath="/";
	QModelIndex mIndex;
};
#endif