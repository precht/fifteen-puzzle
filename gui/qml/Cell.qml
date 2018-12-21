import QtQuick 2.0

Item {
  id: cell
  property int value: 0;
  property int index: 0;
  width: Props.cellSize;
  height: Props.cellSize;

  SystemPalette { id: pallete; }

  function setValue(newValue) {
    if (newValue === 0)
      textId.text = "";
    else
      textId.text = newValue;
  }

  function resetColor() {
    rect.color = pallete.light;
  }

  function blockCell() {
    mouseArea.visible = false;
  }

  function releaseCell() {
    mouseArea.visible = true;
  }

  Rectangle {
    id: rect;
    color: "white";
    border.color: "black";
    border.width: 1;
    width: parent.width - 1;
    height: parent.height - 1;
    anchors.centerIn: parent;

    MouseArea {
      id: mouseArea;
      anchors.fill: parent;
      onPressed: parent.color = pallete.highlight;
      onReleased: cell.parent.changed(cell.index); // NOTE: grid containing cells must define signal
    }
  }

  Text {
    id: textId;
    text: "";
    font.pixelSize: 20;
    anchors.centerIn: parent;
  }

}
