import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
  id: appWindow;
  title: qsTr("Fifteen Puzzle");
  width: 800;
  height: 480;
  visible: true;

  signal blockBoard();
  signal releaseBoard();

  Row {
    Board {
      id: board;
      height: 480;
      width: 400;
    }
    Settings {
      id: settings;
      width: 400;
      height: 480;
      onBlockBoard: board.blockBoard();
      onReleaseBoard: board.releaseBoard();
    }
  }
}
