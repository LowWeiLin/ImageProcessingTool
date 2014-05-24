#include "imageprocessingtool.h"
#include <QtWidgets/QApplication>
#include "WebCam.h"

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	ImageProcessingTool w;
	w.show();
	return a.exec();
	

	/*
	//Webcam example
	QApplication app(argc, argv);
	int dev = 0; // default device
	int fps = 25; // 25 frames per second
	if (argc > 1)
		sscanf(argv[1], "%d", &dev);
	if (argc > 2)
		sscanf(argv[2], "%d", &fps);
	Webcam *view = new Webcam(dev, fps);
	view->show();
	return app.exec();
	*/
}
