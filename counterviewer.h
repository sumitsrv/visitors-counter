#ifndef COUNTERVIEWER_H
#define COUNTERVIEWER_H

#include <QObject>
#include <QLCDNumber>

class CounterViewer : public QLCDNumber
{
    Q_OBJECT
public:
    explicit CounterViewer(QWidget *parent = 0);

public slots:
    void showCount(int count);

};

#endif // COUNTERVIEWER_H
