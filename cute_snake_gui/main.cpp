#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "board_model.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	board state{ 30, 15 };
	board_model view{ state };


	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("gameState", &view);
	engine.load(QUrl(QStringLiteral("qrc:/main_window.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
