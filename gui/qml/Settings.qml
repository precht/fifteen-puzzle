import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
  id: settings;
  height: 500;
  width: 400;
  property int spaceSize: 30
  signal solved(bool isSolved);
  signal blockBoard();
  signal releaseBoard();

  // ------------------------- Functions -------------------------

  function updateBoxes() {
    if (algorithmBox.currentIndex < 3) {
      orderRow.visible = true;
      heuristic_row.visible = false;
    } else {
      orderRow.visible = false;
      heuristic_row.visible = true;
    }
  }

  function solve() {
    blockBoard();
    algorithmBox.enabled = false;
    orderBox.enabled = false;
    heuristicBox.enabled = false;

    if (!boardModel.solve(algorithmBox.currentText, orderBox.currentText, heuristicBox.currentIndex)) {
      updateResults(false);
    }
    else {
      indicator.visible = true;
      solveButton.visible = false;
      cancelButton.visible = true;
    }
  }

  function updateResults(isSolved) {
    if (boardModel.wasInterrupted())
      return;
    resultRectangle.visible = true;
    resultArea.text = boardModel.resultText();
    if (isSolved === true) {
      checkedRow.children[0].visible = true;
      checkedRow.children[2].visible = true;
      checkedLabel.text = boardModel.checkedStates();
      lengthRow.children[0].visible = true;
      lengthRow.children[2].visible = true;
      lengthLabel.text = boardModel.resultLength();
    }
    finishSolving();
  }

  function finishSolving() {
    indicator.visible = false;
    solveButton.visible = true;
    cancelButton.visible = false;
    algorithmBox.enabled = true;
    orderBox.enabled = true;
    heuristicBox.enabled = true;
    releaseBoard();
  }

  Connections {
    target: boardModel;
    onSolved: updateResults(isSolved);
  }

  function cleanLastResult() {
    resultRectangle.visible = false;
    checkedRow.children[0].visible = false;
    checkedRow.children[2].visible = false;
    lengthRow.children[0].visible = false;
    lengthRow.children[2].visible = false;
  }

  Component.onCompleted: {
    orderBox.currentIndex = 6;
  }

  // ------------------------- Layout -------------------------

  Column {
    Item { height: 25; width: 1; } // Top space
    Row { // Row for choosing algorithm
      height: 50;

      Item {
        width: settings.width / 2 - spaceSize;
        height: parent.height;

        Label {
          text: "Algorithm:";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.right: parent.right;
        }
      }
      Item { height: parent.height; width: spaceSize; }
      Item {
        width: settings.width / 2;
        height: parent.height;

        ComboBox {
          id: algorithmBox
          width: 160
          anchors.verticalCenter: parent.verticalCenter;
          anchors.left: parent.left;
          model: ["BFS", "DFS", "IDFS", "Best-First", "A*", "SMA*"];
          onActivated: updateBoxes();
        }
      }
    }
    Row { // Row for choosing directions order
      id: orderRow
      height: 50;

      Item {
        width: settings.width / 2 - spaceSize;
        height: parent.height;

        Label {
          text: "Directions order:";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.right: parent.right;
        }
      }
      Item { height: parent.height; width: spaceSize; }
      Item {
        width: settings.width / 2;
        height: parent.height;

        ComboBox {
          id: orderBox;
          width: 160
          anchors.verticalCenter: parent.verticalCenter;
          anchors.left: parent.left;
          model: ["RAND", "DLRU", "DLUR", "DRLU", "DRUL", "DULR", "DURL", "LDRU", "LDUR",
            "LRDU", "LRUD", "LUDR", "LURD", "RDLU", "RDUL", "RLDU", "RLUD",
            "RUDL", "RULD", "UDLR", "UDRL", "ULDR", "ULRD", "URDL", "URLD"];
        }
      }
    }
    Row { // Row for choosing heuristics
      id: heuristic_row
      height: 50;
      visible: false;

      Item {
        width: settings.width / 2 - spaceSize;
        height: parent.height;

        Label {
          text: "Heuristic:";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.right: parent.right;
        }
      }
      Item { height: parent.height; width: spaceSize; }
      Item {
        width: settings.width / 2;
        height: parent.height;

        ComboBox {
          id: heuristicBox;
          width: 160
          anchors.verticalCenter: parent.verticalCenter;
          anchors.left: parent.left;
          model: ["All Taxicab", "Zero Taxicab", "Wrong Count"];
        }
      }
    }
    Item { // Solve button
      height: 80;
      width: settings.width - 30;
      Button {
        id: solveButton;
        text: "Solve";
        anchors.centerIn: parent;
        onPressed: cleanLastResult();
        onReleased: solve();
      }
      Button {
        id: cancelButton;
        text: "Cancel";
        visible: false;
        anchors.centerIn: parent;
        onReleased: {
          boardModel.cancelSolving();
          finishSolving();
        }
      }
    }
    Row { // Checked states row
      id: checkedRow
      height: 30;

      Item {
        width: settings.width / 2 - spaceSize;
        height: parent.height;
        visible: false;

        Label {
          text: "Checked states:";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.right: parent.right;
        }
      }
      Item { height: parent.height; width: spaceSize; }
      Item {
        width: settings.width / 2;
        height: parent.height;

        Label {
          id: checkedLabel;
          text: "";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.left: parent.left;
        }
      }
    }
    Row { // Length row
      id: lengthRow
      height: 30;

      Item {
        width: settings.width / 2 - spaceSize;
        height: parent.height;
        visible: false;

        Label {
          text: "Result length:";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.right: parent.right;
        }
      }
      Item { height: parent.height; width: spaceSize; }
      Item {
        width: settings.width / 2;
        height: parent.height;

        Label {
          id: lengthLabel
          text: "";
          anchors.verticalCenter: parent.verticalCenter;
          anchors.left: parent.left;
        }
      }
    }
    Item { height: 14; width: 1 } // space after stats
    Rectangle {
      id: resultRectangle
      width: settings.width - 20;
      height: 170;
      border.width: 1;
      border.color: "lightgrey";
      visible: false;

      ScrollView {
        anchors.fill: parent;

        TextArea {
          id: resultArea;
          wrapMode: TextEdit.WrapAnywhere;
          readOnly: true;
        }
      }
    }
    BusyIndicator {
      id: indicator
      width: settings.width - 30;
      height: 100;
      visible: false;
    }
  }
}
