import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
  id: board;
  width: 4 * Props.cellSize;
  height: 4 * Props.cellSize;
//  focus: true;
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
      object.value = boardModel.valueAt(iChild / columns, iChild % columns);
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
      grid.children[index1].value = boardModel.valueAt(row1, column1);
      grid.children[index2].value = boardModel.valueAt(row2, column2);
    }
    pressedCells = [];
    resetColors();
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
//    focus: false;
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
    boardModel.setValueAt(0, 0, 5);   grid.children[0].value = 5;
    boardModel.setValueAt(0, 1, 1);   grid.children[1].value = 1;
    boardModel.setValueAt(0, 2, 2);   grid.children[2].value = 2;
    boardModel.setValueAt(0, 3, 3);   grid.children[3].value = 3;

    boardModel.setValueAt(1, 0, 9);   grid.children[4].value = 9;
    boardModel.setValueAt(1, 1, 10);  grid.children[5].value = 10;
    boardModel.setValueAt(1, 2, 6);   grid.children[6].value = 6;
    boardModel.setValueAt(1, 3, 4);   grid.children[7].value = 4;

    boardModel.setValueAt(2, 0, 13);  grid.children[8].value = 13;
    boardModel.setValueAt(2, 1, 0);   grid.children[9].value = 0;
    boardModel.setValueAt(2, 2, 7);   grid.children[10].value = 7;
    boardModel.setValueAt(2, 3, 8);   grid.children[11].value = 8;

    boardModel.setValueAt(3, 0, 14);  grid.children[12].value = 14;
    boardModel.setValueAt(3, 1, 15);  grid.children[13].value = 15;
    boardModel.setValueAt(3, 2, 11);  grid.children[14].value = 11;
    boardModel.setValueAt(3, 3, 12);  grid.children[15].value = 12;
  }
}
