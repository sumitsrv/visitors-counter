#include "counterviewer.h"

CounterViewer::CounterViewer(QWidget *parent) :
    QLCDNumber(parent)
{
}

void CounterViewer::showCount(int count)
{
    this->display(count);
    this->repaint();
}
