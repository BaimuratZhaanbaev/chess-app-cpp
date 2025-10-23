#include "Piece.h"
#include <QDebug>
#include <cmath>

bool Piece::isPathClear(int toRow, int toCol, const Piece* board[8][8]) const {
    int dr = toRow - row;
    int dc = toCol - col;
    int steps = std::max(std::abs(dr), std::abs(dc));
    int stepRow = dr ? dr / std::abs(dr) : 0;
    int stepCol = dc ? dc / std::abs(dc) : 0;

    for (int i = 1; i < steps; ++i) {
        if (board[row + i * stepRow][col + i * stepCol] != nullptr) {
            return false;
        }
    }
    return true;
}

Piece::Piece() : type('P'), row(0), col(0), isWhite(true), name("White Pawn") {
    qDebug() << "Default constructor called for" << name;
}

Piece::Piece(char t, int r, int c, bool white)
    : type(t), row(r), col(c), isWhite(white), name(white ? "White " : "Black ") {
    switch (std::tolower(t)) {
    case 'p': name += "Pawn"; break;
    case 'r': name += "Rook"; break;
    case 'n': name += "Knight"; break;
    case 'b': name += "Bishop"; break;
    case 'q': name += "Queen"; break;
    case 'k': name += "King"; break;
    default: name += "Unknown";
    }
    qDebug() << "Parameterized constructor called for" << name << "at (" << row << "," << col << ")";
}

Piece::Piece(const Piece& other)
    : type(other.type), row(other.row), col(other.col), isWhite(other.isWhite), name(other.name + " (copy)") {
    qDebug() << "Copy constructor called for" << name;
}

Piece::Piece(Piece&& other) noexcept
    : type(other.type), row(other.row), col(other.col), isWhite(other.isWhite), name(std::move(other.name)) {
    other.type = ' ';
    other.row = -1;
    other.col = -1;
    other.isWhite = false;
    other.name = "Moved";
    qDebug() << "Move constructor called for" << name;
}

Piece::~Piece() {
    qDebug() << "Destructor called for" << name;
}

char Piece::getType() const { return type; }
int Piece::getRow() const { return row; }
int Piece::getCol() const { return col; }
bool Piece::getIsWhite() const { return isWhite; }
QString Piece::getName() const { return name; }

void Piece::setPosition(int r, int c) {
    row = r;
    col = c;
}

bool Piece::isValidMove(int toRow, int toCol, const Piece* board[8][8]) const {
    if (toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) return false;

    // ��������, ��� �������� ������ �� ������ ����� �������
    if (board[toRow][toCol] && board[toRow][toCol]->getIsWhite() == isWhite) {
        return false;
    }

    char piece = std::tolower(type);
    int dr = toRow - row;
    int dc = toCol - col;
    int absDr = std::abs(dr);
    int absDc = std::abs(dc);

    switch (piece) {
    case 'p': // �����
        if (isWhite) {
            if (dc == 0 && board[toRow][toCol] == nullptr && dr == 1) return true; // ��� �����
            if (dc == 0 && row == 1 && dr == 2 && board[toRow][toCol] == nullptr &&
                board[row + 1][col] == nullptr) return true; // ������� ���
            if (absDc == 1 && dr == 1 && board[toRow][toCol] != nullptr) return true; // ������
        }
        else {
            if (dc == 0 && board[toRow][toCol] == nullptr && dr == -1) return true;
            if (dc == 0 && row == 6 && dr == -2 && board[toRow][toCol] == nullptr &&
                board[row - 1][col] == nullptr) return true;
            if (absDc == 1 && dr == -1 && board[toRow][toCol] != nullptr) return true;
        }
        return false;

    case 'n': // ����
        return (absDr == 2 && absDc == 1) || (absDr == 1 && absDc == 2);

    case 'b': // ����
        if (absDr != absDc) return false;
        return isPathClear(toRow, toCol, board);

    case 'r': // �����
        if (dr != 0 && dc != 0) return false;
        return isPathClear(toRow, toCol, board);

    case 'q': // �����
        if (absDr != absDc && dr != 0 && dc != 0) return false;
        return isPathClear(toRow, toCol, board);

    case 'k': // ������
        return absDr <= 1 && absDc <= 1 && (dr != 0 || dc != 0);

    default:
        return false;
    }
}

QString Piece::getImagePath() const {
    QString color = isWhite ? "white" : "black";
    QString piece;
    switch (std::tolower(type)) {
    case 'p': piece = "pawn"; break;
    case 'r': piece = "rook"; break;
    case 'n': piece = "knight"; break;
    case 'b': piece = "bishop"; break;
    case 'q': piece = "queen"; break;
    case 'k': piece = "king"; break;
    default: piece = "pawn";
    }
    return QString(":/images/%1_%2.png").arg(color, piece);
}