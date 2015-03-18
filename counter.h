#ifndef COUNTER_H
#define COUNTER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Counter
{
public:
    Counter();
    int total_count;
    vector<vector<Point> > *blobs;
    void findBlobs(Mat *);

private:
    int count_in;
    int count_out;
    void initCounter();
    void resetCounter();
    void analyzeBlobs();
};

#endif // COUNTER_H
