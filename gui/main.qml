import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
  id: appWindow;
  title: qsTr("Fifteen Puzzle");
  width: 800;
  height: 500;
  visible: true;

  signal blockBoard();
  signal releaseBoard();

  menuBar: MenuBar {
    Menu {
      title: qsTr("&Menu")
      MenuItem {
        text: qsTr("New &3x3 board")
        onTriggered: {
          board.createGrid(3, 3);
          settings.cleanLastResult();
        }
      }
      MenuItem {
        text: qsTr("New &4x4 board")
        onTriggered:  {
          board.createGrid(4, 4);
          settings.cleanLastResult();
        }
      }
      MenuItem {
        text: qsTr("&Exit")
        onTriggered: Qt.quit();
      }
    }
  }

  Row {
    Board {
      id: board;
      height: 460;
      width: 400;
    }
    Settings {
      id: settings;
      width: 400;
      height: 460;
      onBlockBoard: board.blockBoard();
      onReleaseBoard: board.releaseBoard();
    }
  }
}
