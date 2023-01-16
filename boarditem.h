#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

#include "boardwidget.h"

#include <pieces/BasePiece.hxx>

class BoardItem : public QPushButton
{
    Q_OBJECT

public:
    BoardItem(BoardWidget* parent);
    ~BoardItem();

public:
    void initPiece(const Pieces::Position& pos);
    void markAsAvailable(const Pieces::Position& pos);
    void removeAvailableMoveMark();
    void constructCell(bool isDark);
    void cleanCell();
    void setHittable(bool isHittable);
    void paintEvent(QPaintEvent* event);

public slots:
    void onClick();

private:
    void connectSlots();
    std::string constructFilename();
    void onAvailableMoveClick();
    void onPieceClick();

private:
    bool m_isHittable;
    BoardWidget* m_boardWidget;
    Pieces::BasePiece* m_piece;
    QPixmap* m_pixmap;
    QColor m_backgroundColor;
};

#endif // BOARDITEM_H
