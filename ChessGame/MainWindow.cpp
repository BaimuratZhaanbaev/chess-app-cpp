#include "MainWindow.h"
#include ".\x64\Debug\qt\uic\ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Шахматы");
    game = new Game();
    ui->chessBoardWidget->setBoard(&game->getBoard());
    connect(ui->chessBoardWidget, &ChessBoardWidget::moveSelected, game, &Game::makeMove);
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::onNewGame);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExit);
}

MainWindow::~MainWindow() {
    delete game;
    delete ui;
}

void MainWindow::onNewGame() {
    game->startGame();
    ui->chessBoardWidget->update();
    ui->statusLabel->setText(game->getStatus());
}

void MainWindow::onUndo() {
    game->undoMove();
    ui->chessBoardWidget->update();
    ui->statusLabel->setText(game->getStatus());
}

void MainWindow::onExit() {
    close();
}