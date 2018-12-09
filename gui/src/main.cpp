#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "boardmodel.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  BoardModel boardModel;
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("boardModel", &boardModel);
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
