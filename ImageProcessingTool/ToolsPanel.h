/*
	Tools Panel
*/

#ifndef TOOLSPANEL_H
#define TOOLSPANEL_H

#include <QtWidgets>
#include <QLayout>

class ToolsPanel : public QWidget
{
	Q_OBJECT
public:
	ToolsPanel(QWidget* parent=0);
	~ToolsPanel();

protected:
	void createWidgets();
	QWidget* createOperationsSelector();
	QWidget* createOperationsList();
	QWidget* createHistogram();


signals:


public slots:

	
private:
	


};

#endif