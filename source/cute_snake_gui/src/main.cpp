#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "board_model.h"
#include "snake_game.h"
#include <thread>
#include "qt_renderer.h"
#include "qt_controller.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	board state{ 30, 15 };
	auto model =  std::make_unique<board_model>( &state );
	auto view = std::make_unique<qt_renderer>();
	auto controller = std::make_unique<qt_controller>();

	auto game = snake_game(*controller, state, *view);

	QObject::connect(view.get(), &qt_renderer::render, model.get(), &board_model::draw, Qt::QueuedConnection);
	QObject::connect(view.get(), &qt_renderer::finish, model.get(), &board_model::game_over, Qt::QueuedConnection);

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("gameState", QVariant::fromValue(model.get()));
	engine.rootContext()->setContextProperty("gameController", QVariant::fromValue(controller.get()));
	engine.load(QUrl(QStringLiteral("qrc:/main_window.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	auto update_thread = std::thread(
		[&]()
	{
		game.run();
	});
	update_thread.detach();

	return app.exec();
}
