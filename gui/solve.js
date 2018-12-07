WorkerScript.onMessage = function(message) {
  var isSolvable = message.boardModel.solve()

  WorkerScript.sendMessage({ 'boardModel': message.boardModel, 'isSolvable' : isSolvable });
}
