#ifndef IMAGEPROCESSINGTOOL_H
#define IMAGEPROCESSINGTOOL_H

#include <QtWidgets>
#include <QtGui>
#include <QAction>

#include "ImageViewer.h"

class ImageProcessingTool : public QMainWindow
{
	Q_OBJECT

public:
	ImageProcessingTool(QWidget *parent = 0);
	~ImageProcessingTool();


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
	void openRecentFile();
    bool save();
    void about();
    void isModified();
    void newFile();
    bool saveAs();

private:
	static const int maxRecentFiles = 5;

    void createWidgets();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

	
    QAction* openAction;
    QAction* saveAction;
    QAction* exitAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* aboutAction;
    QAction* newAction;
    QAction* saveAsAction;
    QAction* copyAction;
	QAction* recentFileActions[maxRecentFiles];
	

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;
    
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    
    // Widgets and variables
	ImageViewer* imageViewer;
    QString currFile;
	QString currDir;
	QStringList recentFileList;
	

    // Supporting methods
	
    bool okToContinue();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
	void setCurrentDir(const QString &dirName);
	void addFileToRecentFileList(QString fileName);
	void removeFileFromRecentFileList(QString fileName);
	void updateRecentFileList();
	
};

#endif // IMAGEPROCESSINGTOOL_H
