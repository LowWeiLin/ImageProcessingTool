/*
Abstract Base Class for image operations.
*/

#ifndef OPERATION_H
#define OPERATION_H

#include <QtWidgets>

class Operation {
public:
	QString operationName;
	bool enabled;

	virtual bool applyOperation()=0;
	virtual QWidget* operationOptionsPanel()=0;

};

#endif