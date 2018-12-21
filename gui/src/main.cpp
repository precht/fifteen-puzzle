#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "boardmodel.h"

int main(int argc, char *argv[])
{
  QQuickStyle::setFallbackStyle("Default");
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);
  QQmlApplicationEngine engine;

  BoardModel boardModel;
  engine.rootContext()->setContextProperty("boardModel", &boardModel);

  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
