#include "QtTestRestFulDemo.h"
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

QtTestRestFulDemo::QtTestRestFulDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_GET, SIGNAL(clicked()), this, SLOT(OnGETSlot()));
	connect(ui.pushButton_POST, SIGNAL(clicked()), this, SLOT(OnPOSTSlot()));
}

void QtTestRestFulDemo::SendAndGetText(QString strUrl, MyMethod thod, QString strInput, QString &strMessage,QString &strResult)
{

	QNetworkRequest oNetRequest;
	oNetRequest.setUrl(QUrl(strUrl));
	oNetRequest.setRawHeader("Content-Type", "application/octet-stream");
	//oNetRequest.setRawHeader("Content-Type", "application/json");
	//oNetRequest.setRawHeader("Content-Type", "application/xml");
	//oNetRequest.setRawHeader("Content-Type", "application/octet-stream");

	//oNetRequest.setRawHeader("Authorization", "Bearer global-0b9ad652-9671-4cd8-86e9-e1b288dfe1da"); //token时用
	oNetRequest.setRawHeader("CLIENTVERSION", ("V1"));
	//oNetReply = oNetAccessManager.put(oNetRequest, *request.getRequestData());
	//oNetReply = oNetAccessManager.post(oNetRequest, *request.getRequestData());
	//oNetReply = oNetAccessManager.get(oNetRequest);
	//oNetReply = oNetAccessManager.deleteResource(oNetRequest);

	QNetworkAccessManager oNetAccessManager;
	QNetworkReply* oNetReply = NULL;
	QByteArray inputTmp;
	if (thod == POST)
	{
		oNetReply = oNetAccessManager.post(oNetRequest, strInput.toLocal8Bit());
	}
	else if (thod == GET )
	{
		oNetReply = oNetAccessManager.get(oNetRequest);
	}

	QEventLoop loop;
	connect(oNetReply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	//记录httpCode
	int httpsCode = oNetReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	
	QNetworkReply::NetworkError e = oNetReply->error();
	strResult = oNetReply->readAll();
	if (e)
	{
		strMessage = oNetReply->errorString();
	}
}

void QtTestRestFulDemo::OnPOSTSlot()
{
	//传Json时可以用下列操作
	/*
	QJsonObject oSendObject;
	oSendObject.insert("id1", 1);
	oSendObject.insert("name1", "a");

	QJsonObject oSendObject2;
	oSendObject2.insert("id2", 2);
	oSendObject2.insert("name2", "b");

	int Tmp1 = oSendObject.value("id1").toInt();

	oSendObject.insert("second", oSendObject2);
	int Tmp2 = oSendObject.value("second").toObject().value("id2").toInt();

	if ( oSendObject.contains("name1") )
	{
		int h = 1;
	}

	QJsonDocument doc;
	doc.setObject(oSendObject);
	QByteArray body = doc.toJson();
	QString str = body;
	*/

	QString strMessage;
	QString strResult;
	QString strUrl;
	QString strInput = ui.textEdit_input->toPlainText();
	strUrl += "http://" + ui.lineEdit_Url->text();
	SendAndGetText(strUrl, POST, strInput,strMessage,strResult);
	ui.textEdit_errorMessage->setText(strMessage);
	ui.textEdit_Result->setText(strResult);
}

void QtTestRestFulDemo::OnGETSlot()
{
	QString strMessage;
	QString strResult;
	QString strUrl;
	QString strInput = ui.textEdit_input->toPlainText();
	strUrl += "http://" + ui.lineEdit_Url->text();
	SendAndGetText(strUrl, GET, strInput, strMessage, strResult);
	ui.textEdit_errorMessage->setText(strMessage);
	ui.textEdit_Result->setText(strResult);
}
