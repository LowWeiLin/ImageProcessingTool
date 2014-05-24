#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent) : QGraphicsView()
{

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setDragMode(ScrollHandDrag);
	viewport()->setCursor(Qt::ArrowCursor);

	scene = new QGraphicsScene();

	this->setScene(scene);
	this->show();
}

ImageViewer::~ImageViewer(){
}

bool ImageViewer::openImageFile(QString _fileName){
	setImageFileName(_fileName);

	//Load image
	this->image.load(getImageFileName());
	this->imagePixmap = &QPixmap::fromImage(this->image);
	scene->addPixmap(*this->imagePixmap);

	return true;
}

bool ImageViewer::openImage(QImage image){
	return true;
}

void ImageViewer::setImageFileName(QString _fileName){
	this->imageFileName = _fileName;
}

QString ImageViewer::getImageFileName(){
	return this->imageFileName;
}