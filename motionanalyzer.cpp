#include "motionanalyzer.h"
#include "counter.h"
#include "mergesort.h"

MotionAnalyzer::MotionAnalyzer()
{
    BG_FRAMES_REQ = 10;
    bgframe_ev_count = 0;
    curr_frame = new Mat();
    prev_frame = new Mat();
    motion_frame = new Mat();
    foreground_frame = new Mat();
    background_frame = new Mat();
    tracker_img = new Mat();
    hasBackground = false;
    counter = new Counter();
}

void MotionAnalyzer::resetBackground()
{
    bgframe_ev_count = 0;
    hasBackground = false;
}

void MotionAnalyzer::evaluateForeground()
{
    Mat *tmp_img = new Mat();
    getForeground(curr_frame, foreground_frame);
    //    adaptiveThreshold(*motion_frame, *tmp_img, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 11, 2);
    threshold(*foreground_frame, *tmp_img, 50, 255, CV_THRESH_BINARY);
    erode(*tmp_img, *tmp_img, Mat(), Point(-1, -1), 3, BORDER_REPLICATE, morphologyDefaultBorderValue());
    //    dilate(*tmp_img, *tmp_img, Mat(), Point(-1,-1), 3, BORDER_REPLICATE, morphologyDefaultBorderValue());
    tmp_img->copyTo(*tracker_img);
    counter->findBlobs(tmp_img);
}

void MotionAnalyzer::initBackground()
{
    calc_frame[bgframe_ev_count] = new Mat(curr_frame->rows, curr_frame->cols, CV_8UC1);
    curr_frame->copyTo(*calc_frame[bgframe_ev_count]);

    if(bgframe_ev_count == BG_FRAMES_REQ){
        MergeSort *sorter = new MergeSort();
        int pixels[10];

        for(int i=0; i<curr_frame->rows; i++){
            for(int j=0; j<curr_frame->cols; j++){
                for(int k=0; k<BG_FRAMES_REQ; k++){
                    pixels[k] = calc_frame[k]->at<uchar>(i, j);
                }
                sorter->mergesort(pixels, 0, 9);
            }
        }

        calc_frame[BG_FRAMES_REQ/2]->copyTo(*background_frame);
        hasBackground = true;

        for(int i=0; i<BG_FRAMES_REQ; i++){
            calc_frame[i]->release();
        }
    }

    bgframe_ev_count++;
}

void MotionAnalyzer::updateBackground()
{
    addWeighted(*curr_frame, 0.5, *prev_frame, 0.5, 0, *background_frame, -1);
}

void MotionAnalyzer::evaluateMotion()
{
    getMotion(curr_frame, motion_frame);
    if(countNonZero(*motion_frame) > 50){
        evaluateForeground();
    }
    else{
        updateBackground();
    }
}

void MotionAnalyzer::getForeground(Mat *frame_in, Mat *frame_out)
{
    absdiff(*frame_in, *background_frame, *frame_out);
}

void MotionAnalyzer::getMotion(Mat *frame_in, Mat *frame_out)
{
    if(prev_frame->empty()){
        curr_frame->copyTo(*prev_frame);
    }
    absdiff(*frame_in, *prev_frame, *frame_out);
    threshold(*frame_out, *frame_out, 50, 255, CV_THRESH_BINARY);
}

void MotionAnalyzer::processFrame(Mat captureImg)
{
    cvtColor(captureImg, *curr_frame, CV_BGR2GRAY, 1);

    if(hasBackground){
        initBackground();
    }else{
        evaluateMotion();
    }

    curr_frame->copyTo(*prev_frame);
}
