import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
  id: board;
  width: 4 * Props.cellSize;
  height: 4 * Props.cellSize;
  property var pressedCells: [];

  function createGrid(rows, columns) {
    grid.rows = rows;
    grid.columns = columns;
    boardModel.resetBoard(rows, columns);
    var gridSize = rows * columns;
    var cellComponent = Qt.createComponent("Cell.qml");
    grid.children = ""; // remove existing cells
    for (var iChild = 0; iChild < gridSize; iChild++) {
      var object = cellComponent.createObject(grid);
      object.setValue(boardModel.valueAt(iChild / columns, iChild % columns));
      object.index = iChild;
    }
  }

  function swapCells(index1) {
    if (index1 !== pressedCells[0]) {
      var row1 = index1 / grid.columns;
      var column1 = index1 % grid.columns;
      var index2 = pressedCells[0];
      var row2 = index2 / grid.columns;
      var column2 = index2 % grid.columns;
      var tmp = boardModel.valueAt(row1, column1);
      boardModel.setValueAt(row1, column1, boardModel.valueAt(row2, column2));
      boardModel.setValueAt(row2, column2, tmp);
      grid.children[index1].setValue(boardModel.valueAt(row1, column1));
      grid.children[index2].setValue(boardModel.valueAt(row2, column2));
    }
    pressedCells = [];
    resetColors();
  }

  function setCellValue(index, value) {
    var row = index / grid.columns;
    var column = index % grid.columns;
    boardModel.setValueAt(row, column, value);
    grid.children[index].setValue(value);
  }

  function resetColors() {
    for (var iChild = 0; iChild < grid.rows * grid.columns; iChild++)
      grid.children[iChild].resetColor();
  }

  function blockBoard() {
    for (var iChild = 0; iChild < grid.children.length; iChild++)
      grid.children[iChild].blockCell();
  }

  function releaseBoard() {
    for (var iChild = 0; iChild < grid.children.length; iChild++)
      grid.children[iChild].releaseCell();
  }

  Grid {
    signal changed(int index);
    id: grid;
    anchors.centerIn: parent;
    width: rows * Props.cellSize;
    height: columns * Props.cellSize;
  }

  Connections {
    target: grid;
    onChanged: {
      if (pressedCells.length === 0)
        pressedCells.push(index);
      else
        swapCells(index);
    }
  }

  Component.onCompleted: {
    createGrid(4, 4);
    var values = [
          5, 1, 2, 3,
          9, 10, 6, 4,
          13, 0, 7, 8,
          14, 15, 11, 12
        ];

    for (var i = 0; i < values.length; i++)
      setCellValue(i, values[i]);
  }
}
