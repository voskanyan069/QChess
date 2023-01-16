#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include "boardlayout.h"

#include <chess/Board.hxx>

#include <QWidget>
#include <QPlainTextEdit>

#define BOARD_SIZE 8

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    BoardWidget(QWidget* parent = nullptr, QPlainTextEdit* logWindow = nullptr);
    ~BoardWidget();

public:
    void setLogWindow(QPlainTextEdit* logWindow);
    void addAvailableMoves(Pieces::BasePiece* clicked, const Pieces::Positions& positions);
    void cleanAvailableMoves();
    void movePiece(const Pieces::Position& pos);
    Pieces::PieceColor getPlayerTurn();

private:
    void init();
    void initCells();
    void swapPlayerOrder();
    void printInMovesWindow(const Pieces::Position& from, const Pieces::Position& to);
    void repaintBoard();
    void paintEvent(QPaintEvent* event);

private:
    QPlainTextEdit* m_logWindow;
    BoardLayout* m_layout;

private:
    Pieces::PieceColor m_playerTurn;
    Chess::Board* m_board;
    Pieces::BasePiece* m_selectedPiece;
};

#endif // BOARDWIDGET_H
