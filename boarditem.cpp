#include "boarditem.h"
#include "colors.h"

#include <chess/Board.hxx>
#include <pieces/EmptyPiece.hxx>

#include <QPixmap>

#include <iostream>

BoardItem::BoardItem(BoardWidget* widget)
    : QPushButton(widget)
    , m_isHittable(false)
    , m_boardWidget(widget)
    , m_piece(nullptr)
    , m_pixmap(nullptr)
    , m_backgroundColor()
{
    connectSlots();
}

BoardItem::~BoardItem()
{
}

void BoardItem::connectSlots()
{
    connect(this, SIGNAL(clicked()), SLOT(onClick()));
}

void BoardItem::initPiece(const Pieces::Position& pos)
{
    m_piece = Chess::Board::GetInstance()->GetPiece(pos);
}

std::string BoardItem::constructFilename()
{
    if ( nullptr == m_piece )
    {
        return "";
    }
    std::string sImagePath = ":/images/pieces/";
    Pieces::PieceColor color = m_piece->GetColor();
    if (Pieces::PieceColor::WHITE == color) sImagePath += "W";
    else if (Pieces::PieceColor::BLACK == color) sImagePath += "B";
    sImagePath += m_piece->GetPieceName();
    sImagePath += ".png";
    return sImagePath;
}

void BoardItem::constructCell(bool isDark)
{
    m_backgroundColor = ( isDark ) ? PIECE_DARK_BACKGROUND : PIECE_LIGHT_BACKGROUND;
}

void BoardItem::cleanCell()
{
    if (nullptr != m_pixmap)
    {
        delete m_pixmap;
        m_pixmap = nullptr;
    }
    if (nullptr != m_piece)
    {
        m_piece = nullptr;
    }
}

void BoardItem::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect rect(0, 0, width(), height());
    if ( m_isHittable )
        painter.setBrush(PIECE_HITTABLE_BACKGROUND);
    else
        painter.setBrush(m_backgroundColor);
    painter.drawRect(rect);
    if (nullptr == m_piece)
    {
        return;
    }
    m_pixmap = new QPixmap(constructFilename().c_str());
    m_pixmap = new QPixmap(m_pixmap->scaled(QSize(40, 40), Qt::KeepAspectRatio));
    painter.drawPixmap(5, 5, *m_pixmap);
}

void BoardItem::markAsAvailable(const Pieces::Position& pos)
{
    m_piece = new Pieces::EmptyPiece(pos);
}

void BoardItem::removeAvailableMoveMark()
{
    if ( nullptr != m_piece && Pieces::PieceColor::UNDEF == m_piece->GetColor() )
    {
        cleanCell();
    }
}

void BoardItem::setHittable(bool isHittable)
{
    m_isHittable = isHittable;
}

void BoardItem::onAvailableMoveClick()
{
    Pieces::Position pos = m_piece->GetPosition();
    m_boardWidget->movePiece(pos);
}

void BoardItem::onPieceClick()
{
    if ( m_isHittable )
    {
        m_boardWidget->movePiece(m_piece->GetPosition());
        return;
    }
    if ( m_boardWidget->getPlayerTurn() != m_piece->GetColor() )
    {
        return;
    }
    Pieces::Positions positions;
    m_piece->GetAvailableMoves(positions);
    m_boardWidget->cleanAvailableMoves();
    m_boardWidget->addAvailableMoves(m_piece, positions);
}

void BoardItem::onClick()
{
    if (nullptr == m_piece)
    {
        return;
    }
    Pieces::PieceColor color = m_piece->GetColor();
    if ( Pieces::PieceColor::UNDEF == color )
    {
        onAvailableMoveClick();
    }
    else
    {
        onPieceClick();
    }
}
