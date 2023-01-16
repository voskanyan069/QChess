#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardwidget.h"

#include <QMainWindow>
#include <QPlainTextEdit>

#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUi();
    void addBoard();
    void addPreviousMovesDialog();

private:
    Ui::MainWindow* m_ui;
    BoardWidget* m_board;
    QPlainTextEdit* m_previousMoves;
};
#endif // MAINWINDOW_H
