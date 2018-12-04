import QtQuick 2.0

Item {
  id: cell
  property int value: 0;
  property int index: 0;
  property string clickedColor: "lightblue";
  width: Props.cellSize;
  height: Props.cellSize;

  function resetColor() {
    rect.color = "transparent";
  }

  function blockCell() {
    mouseArea.visible = false;
  }

  function releaseCell() {
    mouseArea.visible = true;
  }

  Rectangle {
    id: rect;
    color: "transparent";
    border.color: "black";
    border.width: 1;
    width: parent.width - 1;
    height: parent.height - 1;
    anchors.centerIn: parent;

    MouseArea {
      id: mouseArea;
      anchors.fill: parent;
      onPressed: parent.color = (Qt.colorEqual(parent.color, clickedColor) ? "transparent" : clickedColor);
      onReleased: cell.parent.changed(cell.index); // NOTE: grid containing cells must define signal
    }
  }

  Text {
    text: value;
    font.pixelSize: 20;
    anchors.centerIn: parent;
  }

}
