#include "Game.h"

Game::Game() : isWhiteTurn(true), gameStatus("���� ������") {
    startGame();
}

Game::~Game() {}

void Game::startGame() {
    board.initializeBoard();
    isWhiteTurn = true;
    gameStatus = "��� �����";
}

void Game::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (board.movePiece(fromRow, fromCol, toRow, toCol, isWhiteTurn)) {
        isWhiteTurn = !isWhiteTurn;
        gameStatus = isWhiteTurn ? "��� �����" : "��� ������";
    }
    else {
        gameStatus = "������������ ���";
    }
}

void Game::undoMove() {
    board.undoLastMove();
    isWhiteTurn = !isWhiteTurn;
    gameStatus = isWhiteTurn ? "��� �����" : "��� ������";
}

QString Game::getStatus() const {
    return gameStatus;
}