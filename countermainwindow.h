#ifndef COUNTERMAINWINDOW_H
#define COUNTERMAINWINDOW_H

#include <opencv2/highgui/highgui.hpp>
#include <QMainWindow>
#include "counter.h"
#include "motionanalyzer.h"

using namespace cv;
using namespace std;

namespace Ui {
class CounterMainWindow;
}

class CounterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CounterMainWindow(QWidget *parent = 0);
    ~CounterMainWindow();

private slots:
    void on_actionStartCamera_triggered();
    void on_actionStopCamera_triggered();
    void on_actionStartTrack_triggered();
    void on_actionStopTrack_triggered();
    void on_actionReset_triggered();

private:
    Ui::CounterMainWindow *ui;
    cv::VideoCapture mCapture;
    int timerId;
    cv::Mat objectImg;
    cv::Mat sceneImg;
    bool track;
    MotionAnalyzer *motion_analyzer;

protected:
    void timerEvent(QTimerEvent *event);
    void timerEvent();
};

#endif // COUNTERMAINWINDOW_H
