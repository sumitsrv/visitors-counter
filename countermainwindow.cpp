#include "countermainwindow.h"
#include "ui_countermainwindow.h"

using namespace std;

CounterMainWindow::CounterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CounterMainWindow)
{
    ui->setupUi(this);
    track = false;
}

CounterMainWindow::~CounterMainWindow()
{
    delete ui;
}

void CounterMainWindow::timerEvent(QTimerEvent *event)
{
    Mat captureImg;
    mCapture >> captureImg;
//    ui->imageViewer->showImage(captureImg);
    if(track) {
        motion_analyzer->processFrame(captureImg);
    }
    ui->imageViewer->showImage(*motion_analyzer->tracker_img);
//    ui->lcdNumber->showCount(motion_analyzer->total_count);
}

void CounterMainWindow::on_actionStartCamera_triggered()
{
    if( !mCapture.isOpened() )
    {
        mCapture.set(CV_CAP_PROP_FPS, 30.0);
        mCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 480.0);
        mCapture.set(CV_CAP_PROP_FRAME_WIDTH, 640.0);
        motion_analyzer = new MotionAnalyzer();

        if( !mCapture.open( 1 ) )
        {
            return;
        }
        else
        {
            timerId = startTimer(10);
        }
    }

    if(ui->imageViewer->isHidden()){
        ui->imageViewer->show();
    }
}

void CounterMainWindow::on_actionStopCamera_triggered()
{
    mCapture.release();
    killTimer(timerId);
    ui->imageViewer->hide();
}

void CounterMainWindow::on_actionStartTrack_triggered()
{
    track = true;
}

void CounterMainWindow::on_actionStopTrack_triggered()
{
    track = false;
}

void CounterMainWindow::on_actionReset_triggered()
{
    motion_analyzer->resetBackground();
}
