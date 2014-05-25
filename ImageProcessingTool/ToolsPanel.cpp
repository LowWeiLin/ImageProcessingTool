#include "ToolsPanel.h"

ToolsPanel::ToolsPanel(QWidget* parent) : QWidget(parent)
{
	createWidgets();
}

ToolsPanel::~ToolsPanel(){
	
}

void ToolsPanel::createWidgets(){
	//Create the ToolsPanel 

	QVBoxLayout* layout = new QVBoxLayout();
	QWidget* operationsSelector = createOperationsSelector();
	QWidget* operationsList = createOperationsList();
	QWidget* histogramWidget = createHistogram();


	layout->addWidget(operationsSelector);
	layout->addStretch(1);

	this->setLayout(layout);
}

QWidget* ToolsPanel::createOperationsSelector(){
	QWidget* operationsSelector = new QWidget();

	//QLabel* operationsLabel = new QLabel("Operation: ");
	QComboBox* operationsCombo = new QComboBox();
	QPushButton* operationsAddButton = new QPushButton("+");

	//TODO: Add stuff into the combo box
	//TODO: Add Connections

	QHBoxLayout* hLayout = new QHBoxLayout();
	//hLayout->addWidget(operationsLabel,0);
	hLayout->addWidget(operationsCombo,1);
	hLayout->addWidget(operationsAddButton,0);

	operationsSelector->setLayout(hLayout);

	return operationsSelector;
}

QWidget* ToolsPanel::createOperationsList(){
	return NULL;
}

QWidget* ToolsPanel::createHistogram(){
	return NULL;
}