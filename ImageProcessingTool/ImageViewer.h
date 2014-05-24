/*

	A widget to view one image.

*/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtWidgets>

class ImageViewer: public QGraphicsView
{
	Q_OBJECT
public:
	ImageViewer(QWidget* parent=0);
	~ImageViewer();

protected:
	QImage image;
	QGraphicsPixmapItem* imagePixmap;
    QGraphicsScene* scene;
    QString imageFileName;

	//for zooming
	double scaleFactor; //How much % to zoom each time the wheel is scrolled.
	double minScale;
	double maxScale;

	void wheelEvent(QWheelEvent* event);
	void mouseReleaseEvent(QMouseEvent *event);

	inline qreal getScale() const {return transform().m11();}//Current scale
	void scaleBy(qreal sFactor);
	void setZoom(float percentZoom);

	//TODO: replace hardcoded minmax scale
	void calcAndSetMinMaxScale();

signals:
	

public slots:
	bool openImageFile(QString _fileName);
	bool openImage(QImage image);
	void clearScene();
	void saveImage(QString dstFile);

private:
	void setImageFileName(QString _fileName);
	QString getImageFileName();


	

};


#endif //IMAGEVIEWER_H