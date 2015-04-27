#ifndef MOTIONANALYZER_H
#define MOTIONANALYZER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "counter.h"

using namespace cv;
using namespace std;

class MotionAnalyzer
{
public:
    MotionAnalyzer();
    Mat *tracker_img;
    Mat *background_frame;
    void processFrame(Mat);
    void resetBackground();
    Counter* getCounter();

private:
    short BG_FRAMES_REQ;
    bool hasBackground;
    Mat *calc_frame[10];
    Mat *curr_frame;
    Mat *prev_frame;
    Mat *motion_frame;
    Mat *foreground_frame;
    Counter *counter;
    int bgframe_ev_count;
    void evaluateMotion();
    void initBackground();
    void updateBackground();
    void evaluateForeground();
    void getMotion(Mat*, Mat*);
    void getForeground(Mat*, Mat*);

};

#endif // MOTIONANALYZER_H
