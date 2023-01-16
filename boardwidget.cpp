#include "boardwidget.h"
#include "boarditem.h"

#include <chess/Board.hxx>
#include <utils/Exception.hxx>

#include <QMessageBox>

#include <iostream>
#include <sstream>
#include <iomanip>

BoardWidget::BoardWidget(QWidget* parent, QPlainTextEdit* logWindow)
    : QWidget(parent)
    , m_logWindow(logWindow)
    , m_layout(new BoardLayout(this))
    , m_playerTurn(Pieces::PieceColor::WHITE)
    , m_board(Chess::Board::GetInstance())
    , m_selectedPiece(nullptr)
{
    init();
}

void BoardWidget::init()
{
    initCells();
}

void BoardWidget::initCells()
{
    m_layout->setSizeConstraint(QLayout::SetFixedSize);
    m_layout->setSpacing(0);
    BoardItem* boardItem;
    bool isDark = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        isDark = !isDark;
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            isDark = !isDark;
            boardItem = new BoardItem(this);
            boardItem->constructCell(isDark);
            boardItem->setFixedWidth(50);
            boardItem->setFixedHeight(50);
            m_layout->addWidget(boardItem, i, j);
        }
    }
}

void BoardWidget::setLogWindow(QPlainTextEdit* logWindow)
{
    m_logWindow = logWindow;
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
    repaintBoard();
}

void BoardWidget::repaintBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            BoardItem* item = (BoardItem*)(m_layout->itemAtPosition(i, j)->widget());
            if ( !m_board->IsFree(Pieces::Position(i, j)) )
            {
                item->initPiece(Pieces::Position(i, j));
            }
        }
    }
}

void BoardWidget::addAvailableMoves(Pieces::BasePiece* clicked, const Pieces::Positions& positions)
{
    m_selectedPiece = clicked;
    BoardItem* item = nullptr;
    for (const auto& pos : positions)
    {
        item = (BoardItem*)(m_layout->itemAtPosition(pos.x, pos.y)->widget());
        Pieces::BasePiece* piece = m_board->GetPiece(pos);
        if ( nullptr == piece )
        {
            item->markAsAvailable(pos);
            m_layout->addWidget(item, pos.x, pos.y);
        }
        else
        {
            if ( clicked->GetColor() == piece->GetColor() )
            {
                continue;
            }
            item->markAsAvailable(pos);
            item->setHittable(true);
            m_layout->addWidget(item, pos.x, pos.y);
        }
    }
    repaint();
}

void BoardWidget::cleanAvailableMoves()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            BoardItem* item = (BoardItem*)(m_layout->itemAtPosition(i, j)->widget());
            item->removeAvailableMoveMark();
            item->setHittable(false);
        }
    }
}

void BoardWidget::swapPlayerOrder()
{
    if ( Pieces::PieceColor::WHITE == m_playerTurn )
        m_playerTurn = Pieces::PieceColor::BLACK;
    else if ( Pieces::PieceColor::BLACK == m_playerTurn )
        m_playerTurn = Pieces::PieceColor::WHITE;
}

Pieces::PieceColor BoardWidget::getPlayerTurn()
{
    return m_playerTurn;
}

std::string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(localtime(&time_now), "%T");
    return ss.str();
}

void BoardWidget::printInMovesWindow(const Pieces::Position& from, const Pieces::Position& to)
{
    Pieces::BasePiece* piece = m_board->GetPiece(to);
    if ( nullptr == m_logWindow || nullptr == piece )
    {
        std::cout << "a" <<std::endl;
        return;
    }
    int oldX = from.x + 1;
    char oldY = from.y + 65;
    int newX = to.x + 1;
    char newY = to.y + 65;
    std::stringstream ss;
    ss << piece->GetPieceChar() << " from " << oldY << oldX << " to " << newY << newX << " | " << getCurrentTime();
    m_logWindow->appendPlainText(ss.str().c_str());
}

void BoardWidget::movePiece(const Pieces::Position& pos)
{
    Pieces::Position selectedPos = m_selectedPiece->GetPosition();
    BoardItem* selectedItem = (BoardItem*)(m_layout->itemAtPosition(selectedPos.x, selectedPos.y)->widget());
    Pieces::BasePiece* piece = m_board->GetPiece(selectedPos);
    try
    {
        piece->Move(pos);
    }
    catch ( const Utils::Exception& e )
    {
        QMessageBox msg(this);
        msg.setModal(true);
        msg.critical(0, "Error", e.what());
        return;
    }
    BoardItem* newItem = (BoardItem*)(m_layout->itemAtPosition(pos.x, pos.y)->widget());
    selectedItem->cleanCell();
    newItem->initPiece(pos);
    cleanAvailableMoves();
    swapPlayerOrder();
    printInMovesWindow(selectedPos, pos);
    repaint();
}

BoardWidget::~BoardWidget()
{
    if (nullptr != m_layout)
    {
        delete m_layout;
    }
}
