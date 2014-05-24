// Webcam.h

#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include <QTime>
#include <QEvent>
#include <QPainter>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Webcam: public QWidget
{
	Q_OBJECT
public:
	Webcam(int dev, int fps);
	~Webcam();
protected:
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
	void timerEvent(QTimerEvent* event);
	void paintEvent(QPaintEvent* event);
private:
	CvCapture* capture;
	int timerId;
	int frameRate; // input frame rate
	QPixmap pixmap;
	int nframes; // used to calculate actual frame rate
	QTime time; // used to calculate actual frame rate
	// convert image format
	QImage IplImage2QImage(const IplImage *iplImage);
};
#endif