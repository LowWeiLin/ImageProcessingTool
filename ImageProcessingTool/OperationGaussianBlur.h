

#ifndef OPERATIONGAUSSIANBLUR_H
#define OPERATIONGAUSSIANBLUR_H

#include "Operation.h"
#include <opencv2/core/core.hpp>

class OperationGaussianBlur : public Operation {
public:

	virtual bool applyOperation();
	virtual QWidget* operationOptionsPanel();

};



#endif
