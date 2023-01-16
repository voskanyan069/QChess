#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_board(nullptr)
    , m_previousMoves(nullptr)
{
    initUi();
    addPreviousMovesDialog();
    addBoard();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::initUi()
{
    m_ui->setupUi(this);
}

void MainWindow::addBoard()
{
    m_board = new BoardWidget(m_ui->boardDock, m_previousMoves);
}

void MainWindow::addPreviousMovesDialog()
{
    QHBoxLayout* hLayout = new QHBoxLayout();
    m_previousMoves = new QPlainTextEdit();
    m_previousMoves->setReadOnly(true);
    hLayout->addWidget(m_previousMoves, 0);
    m_ui->leftDockWidgetContents->setLayout(hLayout);
}
