#include "imageprocessingtool.h"





// Constructor

ImageProcessingTool::ImageProcessingTool(QWidget *parent) : QMainWindow(parent)
{
	createWidgets();
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	this->move(10,10);
}

ImageProcessingTool::~ImageProcessingTool()
{

}


// Protected methods

void ImageProcessingTool::closeEvent(QCloseEvent *event)
{
	if (okToContinue())
		event->accept();
	else
		event->ignore();
}


// Create widgets, actions, menus, toolbars, status bar.

void ImageProcessingTool::createWidgets()
{
	QSplitter* mainWidget = new QSplitter();
	
	imageViewer = new ImageViewer();
	imageViewer->openImageFile("test.jpg");
	imageViewer->saveImage("test-out.jpg");

	setWindowIcon(QIcon(":/images/ImageProcessingTool.png"));
	setGeometry(0, 0, 550, 650);
	setCurrentFile("");
	setCurrentDir(".");

	toolsPanel = new ToolsPanel();

	mainWidget->addWidget(toolsPanel);
	mainWidget->addWidget(imageViewer);

	this->setCentralWidget(mainWidget);
}

void ImageProcessingTool::createActions()
{   
	newAction = new QAction(tr("&New"), this);
	newAction->setIcon(QIcon(":/images/new.png"));
	newAction->setShortcut(tr("Ctrl+N"));
	newAction->setStatusTip(tr("Create a new file"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

	openAction = new QAction(tr("&Open"), this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(tr("Ctrl+O"));
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    
	saveAction = new QAction(tr("&Save"), this);
	saveAction->setIcon(QIcon(":/images/save.png"));
	saveAction->setShortcut(tr("Ctrl+S"));
	saveAction->setStatusTip(tr("Save the document to a file"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAction = new QAction(tr("S&ave As"), this);
	saveAsAction->setIcon(QIcon(":/images/saveas.png"));
	saveAsAction->setShortcut(tr("Ctrl+Alt+S"));
	saveAsAction->setStatusTip(tr("Save the document to a specified file"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    
	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit ImageProcessingTool"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    
	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setStatusTip(tr("Show information about ImageProcessingTool"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	//Recent files actions
	for(int i=0 ; i<maxRecentFiles ; i++){
		recentFileActions[i] = new QAction(tr(""), this);
		recentFileActions[i]->setVisible(false);
		recentFileActions[i]->setStatusTip(tr("Opens recent file"));
		connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
	}

}


void ImageProcessingTool::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	for(int i=0 ; i<maxRecentFiles ; i++){
		fileMenu->addAction(recentFileActions[i]);	
	}
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
}


void ImageProcessingTool::createToolBars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);
	fileToolBar->addAction(saveAsAction);

	editToolBar = addToolBar(tr("Edit"));
}


void ImageProcessingTool::createStatusBar()
{
	statusBar()->showMessage(tr(""));
}


//Slot functions
void ImageProcessingTool::newFile(){
	if(okToContinue()){
		imageViewer->clearScene();
		setCurrentFile("");
	}
}

bool ImageProcessingTool::saveAs(){
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As..."),
							"",
                            tr("All files (*.*)\n"
							"JPEG (*.jpg; *.jpeg)\n"
							"PNG (*.png)"));
	if (!fileName.isEmpty()) {
		return saveFile(fileName);
	} else {
		return false;
	}
}


void ImageProcessingTool::open()
{
	if (okToContinue()) {
		QString fileName = QFileDialog::getOpenFileName(this,
										tr("Open image file"),
										currDir,
										tr("All files (*.*)\n"
										"JPEG (*.jpg; *.jpeg)\n"
										"PNG (*.png)"));
            
		if (!fileName.isEmpty()){
			loadFile(fileName);
		}
	}
}

void ImageProcessingTool::openRecentFile()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if(action != NULL){
		if (okToContinue()) {
			QString fileName = action->data().toString();
			loadFile(fileName);
		}
	}
}

bool ImageProcessingTool::save()
{   
	if (currFile.isEmpty()){
		return saveAs();
	}
	return saveFile(currFile);
}


void ImageProcessingTool::about()
{
	QMessageBox::about(this, tr("About ImageProcessingTool"),
	tr("This is a simple image processing tool used to "
	   "visualize image processing operations.\n"));
}


void ImageProcessingTool::isModified()
{
	//TODO: implement this.
	//setWindowModified(textEdit->document()->isModified());
}


// Supporting methods

bool ImageProcessingTool::okToContinue()
{
	//TODO: check if image is modified.
	if (true)
		return true;
    
	int code = QMessageBox::warning(this, tr("ImageProcessingTool"),
	tr("The document has been modified.\n"
		"Do you want to save the changes?"),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape);

	if (code == QMessageBox::Yes)
		return save();
	else if (code == QMessageBox::Cancel)
		return false;
    
	return true;
}


void ImageProcessingTool::loadFile(const QString &fileName)
{
	if(fileName.isEmpty()){
		statusBar()->showMessage(tr("No file specified to load"), 2000);
		return;
	}

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::critical(this, tr("ImageProcessingTool"),
									tr("Cannot read file \"%1\":\n%2.")
									.arg(fileName).arg(file.errorString()));
		statusBar()->showMessage(tr("File not loaded"), 2000);
		removeFileFromRecentFileList(fileName);
		return;
	}

	// Read file content into textEdit widget.
	QApplication::setOverrideCursor(Qt::WaitCursor);
	imageViewer->openImageFile(fileName);
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	setCurrentDir(QFileInfo(fileName).absolutePath());
	statusBar()->showMessage(tr("File loaded"), 2000);
}


bool ImageProcessingTool::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::critical(this, tr("ImageProcessingTool"),
		tr("Cannot write file %1:\n%2.")
		.arg(fileName).arg(file.errorString()));
		return false;
	}

	// Write contents in textEdit widget into file.
	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	//out << textEdit->toPlainText();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	setCurrentDir(QFileInfo(fileName).absolutePath());
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}


void ImageProcessingTool::setCurrentFile(const QString &fileName)
{
	currFile = fileName;
	//textEdit->document()->setModified(false);
	setWindowModified(false);

	// * is displayed in window title if isWindowModified() == true.
	QString shownName = "ImageProcessingTool - [*] " + currFile;
	if (currFile.isEmpty()){
		shownName = "ImageProcessingTool - [*] untitled";
	}
	setWindowTitle(shownName);

	if(!currFile.isEmpty()){
		addFileToRecentFileList(fileName);
	}	
}

void ImageProcessingTool::setCurrentDir(const QString &dirName){
	currDir = dirName;
}

void ImageProcessingTool::addFileToRecentFileList(QString fileName){
	recentFileList.removeOne(fileName);
	recentFileList.push_front(fileName);
	if(recentFileList.size() > maxRecentFiles){
		recentFileList.pop_back();
	}
	updateRecentFileList();
}

void ImageProcessingTool::removeFileFromRecentFileList(QString fileName){
	recentFileList.removeAll(fileName);
	updateRecentFileList();
}

void ImageProcessingTool::updateRecentFileList(){
	for(int i=0 ; i<maxRecentFiles ; i++){
		recentFileActions[i]->setVisible(false);
	}
	for(int i=0 ; i<recentFileList.size() ; i++){
		if(!recentFileList.at(i).isEmpty()){
			recentFileActions[i]->setVisible(true);

			recentFileActions[i]->setText( QString::number(i+1) + ". " + recentFileList.at(i).split("/").back());
			recentFileActions[i]->setData(recentFileList.at(i));
		}
	}
}

