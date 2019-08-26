#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtTestRestFulDemo.h"

enum MyMethod
{
	GET,
	POST
};

class QtTestRestFulDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtTestRestFulDemo(QWidget *parent = Q_NULLPTR);

	void SendAndGetText(QString strUrl, MyMethod thod,QString strInput, QString &strMessage, QString &strResult);

public slots:
	void OnGETSlot();
	void OnPOSTSlot();

private:
	Ui::QtTestRestFulDemoClass ui;
};
