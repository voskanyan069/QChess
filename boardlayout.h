#ifndef BOARDLAYOUT_H
#define BOARDLAYOUT_H

#include <QWidget>
#include <QGridLayout>

class BoardLayout : public QGridLayout
{
    Q_OBJECT

public:
    BoardLayout(QWidget* parent = nullptr);
    ~BoardLayout();
};

#endif // BOARDLAYOUT_H
