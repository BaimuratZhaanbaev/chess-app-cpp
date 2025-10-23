#ifndef PIECE_H
#define PIECE_H

#include <QString>

class Piece {
private:
    char type;        // ��� ������: 'P' (�����), 'R' (�����), 'N' (����), 'B' (����), 'Q' (�����), 'K' (������); ������ ������� ��� ������
    int row;          // ������ �� ����� (0-7)
    int col;          // ������� �� ����� (0-7)
    bool isWhite;     // ����: true � �����, false � ������
    QString name;     // ��� ��� ����������� (��������, "White Pawn")

    // ��������, �������� �� ���� ��� �����, ����� ��� �����
    bool isPathClear(int toRow, int toCol, const Piece* board[8][8]) const;

public:
    // ����������� �� ���������
    Piece();

    // ����������������� �����������
    Piece(char t, int r, int c, bool white);

    // ����������� �����������
    Piece(const Piece& other);

    // ����������� �����������
    Piece(Piece&& other) noexcept;

    // ����������
    ~Piece();

    // �������
    char getType() const;
    int getRow() const;
    int getCol() const;
    bool getIsWhite() const;
    QString getName() const;

    // ������ ��� �������
    void setPosition(int r, int c);

    // �������� ���������� ����
    bool isValidMove(int toRow, int toCol, const Piece* board[8][8]) const;

    // ��������� ���� � ����������� ������
    QString getImagePath() const;
};

#endif // PIECE_H