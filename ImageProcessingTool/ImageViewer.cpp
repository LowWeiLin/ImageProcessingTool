#include "ImageViewer.h"

ImageViewer::ImageViewer(QWidget* parent) : QGraphicsView(parent)
{

	//this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setDragMode(ScrollHandDrag);
	viewport()->setCursor(Qt::ArrowCursor);

	scene = new QGraphicsScene();

	//Hardcoded for now.
	scaleFactor = 1.15;
	minScale = 1;
	maxScale = 5;
	//this->setZoom(minScale*100);

	this->setScene(scene);
	this->show();
}

ImageViewer::~ImageViewer(){
}

bool ImageViewer::openImageFile(QString _fileName){
	image.load(_fileName);
	if(image.isNull()){
		QMessageBox::about(this, tr(std::string("Loading failed").c_str()),
								"The image \""+_fileName+"\" has failed to load.\n\n"
								"" );
        return false;
	} else {
		clearScene();
		imagePixmap = new QGraphicsPixmapItem(QPixmap::fromImage(image));
		imagePixmap->setPos(0,0);
		scene->setSceneRect(0,0,image.width(),image.height());
		scene->addItem(imagePixmap);
		setImageFileName(_fileName);
		return true;
	}
	
	
	image.invertPixels();
	

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

void ImageViewer::clearScene(){
	scene->clear();
}


void ImageViewer::saveImage(QString dstFile){
	image.save(dstFile);
	
}


void ImageViewer::wheelEvent(QWheelEvent* event) {
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	// Scale the view / do the zoom
	if(event->delta() > 0) {
		// Zoom in
		scaleBy(scaleFactor);
	} else {
		// Zooming out
		scaleBy(1.0 / scaleFactor);
	}
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event) {
     QGraphicsView::mouseReleaseEvent(event);
	 viewport()->setCursor(Qt::ArrowCursor);
}


void ImageViewer::scaleBy(qreal sFactor)
{
	qreal curScaleFactor = transform().m11();
	if (((curScaleFactor == minScale) && (sFactor < 1.0)) ||
		((curScaleFactor == maxScale) && (sFactor > 1.0))){
			return;
	}

	qreal sc = sFactor;
	if ((curScaleFactor * sc < minScale)&&(sc < 1.0)){
		sc = minScale / curScaleFactor;
	} else {
		if ((curScaleFactor * sc > maxScale)&&(sc > 1.0)){
			sc = maxScale / curScaleFactor;
		}
	}
	scale(sc, sc);
}

void ImageViewer::setZoom(float percentZoom)
{
	qreal targetScale = (qreal)percentZoom / 100.0;
	qreal scaleFactor = targetScale / transform().m11();
	scaleBy(scaleFactor);
}

void ImageViewer::calcAndSetMinMaxScale(){
	QSize widgetSize = this->size();
	QSize imgSize = image.size();


	minScale = 1;
}