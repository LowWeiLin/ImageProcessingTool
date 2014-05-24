#include "Webcam.h"

Webcam::Webcam(int dev, int fps)
{
	timerId = 0;
	frameRate = fps;
	capture = cvCaptureFromCAM(dev);
	int width = 640;
	int height = 480;
	cvSetCaptureProperty(capture,
		CV_CAP_PROP_FRAME_WIDTH, width);
	cvSetCaptureProperty(capture,
		CV_CAP_PROP_FRAME_HEIGHT, height);
	setFixedSize(width, height);
}

Webcam::~Webcam()
{
	cvReleaseCapture(&capture);
}

void Webcam::showEvent(QShowEvent *event)
{
	nframes = 0; // init
	timerId = startTimer(1000 / frameRate); // in msec
	time.start(); // start time
}

void Webcam::hideEvent(QHideEvent *event)
{
	killTimer(timerId);
}

void Webcam::timerEvent(QTimerEvent *event) {
	if (event->timerId() == timerId) {
		IplImage *frame = cvQueryFrame(capture);
		QImage image = IplImage2QImage(frame); // convert
		pixmap = QPixmap::fromImage(image); // convert
		repaint(); // immediate repaint
		if (++nframes == 50) {
			qDebug("frame rate: %f", // actual frame rate
				(float) nframes * 1000 / time.elapsed());
			nframes = 0;
			time.restart();
		}
	} else {
		QWidget::timerEvent(event);
	}
}

void Webcam::paintEvent(QPaintEvent *event)
{
	QRectF rect = QRectF(QPoint(), size());
	QPainter painter(this);
	painter.drawPixmap(rect, pixmap, rect);
}

// Convert OpenCV's IplImage to QImage.
QImage Webcam::IplImage2QImage(const IplImage *iplImage) 
{
	int height = iplImage->height;
	int width = iplImage->width;
	if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3) {// colour image
		const uchar *qImageBuffer = (const uchar*) iplImage->imageData;
		QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
		return img.rgbSwapped();
	} else if(iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1) {// gray image
		const uchar *qImageBuffer = (const uchar*) iplImage->imageData;
		QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);
		QVector<QRgb> colorTable; // set up colour table
		for (int i = 0; i < 256; i++) {
			colorTable.append(qRgb(i, i, i));
		}
		img.setColorTable(colorTable);
		return img;
	} else {
		qWarning() << "Image cannot be converted.";
		return QImage();
	}
}