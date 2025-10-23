#ifndef MOVE_H
#define MOVE_H

class Move {
private:
    int fromRow, fromCol, toRow, toCol;
    char pieceType;
    char capturedType;
    bool isWhite;

public:
    // ����������� �� ���������
    Move();

    // ����������������� �����������
    Move(int fr, int fc, int tr, int tc, char pt, char ct, bool w);

    // ����������� �����������
    Move(const Move& other);

    // ����������� �����������
    Move(Move&& other) noexcept;

    // ����������
    ~Move();

    // �������
    int getFromRow() const;
    int getFromCol() const;
    int getToRow() const;
    int getToCol() const;
    char getPieceType() const;
    char getCapturedType() const;
    bool getIsWhite() const;
};

#endif // MOVE_H
