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
	QPixmap* imagePixmap;
    QGraphicsScene* scene;
    QString imageFileName;

signals:
	

public slots:
	bool openImageFile(QString _fileName);
	bool openImage(QImage image);

private:
	void setImageFileName(QString _fileName);
	QString getImageFileName();


	

};


#endif //IMAGEVIEWER_H