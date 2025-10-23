#include "ChessBoardWidget.h"

ChessBoardWidget::ChessBoardWidget(Board* b, QWidget* parent)
    : QWidget(parent), board(b), selectedSquare(-1, -1) {
    setFixedSize(400, 400); // 8x8 клеток по 50 пикселей
}

void ChessBoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            painter.fillRect(col * 50, (7 - row) * 50, 50, 50,
                (row + col) % 2 ? Qt::lightGray : Qt::white);
            if (Piece* p = board->getPiece(row, col)) {
                QPixmap pixmap(p->getImagePath());
                painter.drawPixmap(col * 50, (7 - row) * 50, 50, 50, pixmap);
            }
        }
    }
}

void ChessBoardWidget::mousePressEvent(QMouseEvent* event) {
    int col = event->x() / 50;
    int row = 7 - (event->y() / 50);
    if (selectedSquare == QPoint(-1, -1)) {
        if (board->getPiece(row, col)) {
            selectedSquare = QPoint(row, col);
            update(); // ѕерерисовать дл€ подсветки
        }
    }
    else {
        emit moveSelected(selectedSquare.x(), selectedSquare.y(), row, col);
        selectedSquare = QPoint(-1, -1);
        update();
    }
}