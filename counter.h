#ifndef COUNTER_H
#define COUNTER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "blobinfo.h"

using namespace std;
using namespace cv;

class Counter
{
public:
    Counter();
    int getTotalCount();
    int getCountIn();
    int getCountOut();
    void findBlobs(Mat *);
    void setMidPoint(int, int);

private:
    int BLOB_PROXIMITY;
    int total_count;
    int midY;
    int midX;
    int count_in;
    int count_out;
    vector<BlobInfo> *blobs_old;
    vector<BlobInfo> *blobs_info;
    void initCounter();
    void resetCounter();
    void analyzeBlobs(vector<vector<Point> > *);
};

#endif // COUNTER_H
