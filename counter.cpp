#include "counter.h"
#include <QTextStream>
#include "mergesort.h"

Counter::Counter()
{
    total_count = 0;
    blobs = new vector<vector<Point> >();
}

void Counter::initCounter()
{
    count_in = 0;
    count_out = 0;
}

void Counter::resetCounter()
{
    this->initCounter();
}

void Counter::findBlobs(Mat *binary)
{
    blobs->clear();
    Mat label_image;
    binary->convertTo(label_image, CV_32SC1);

    int label_count = 0;

    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 255) {
                continue;
            }

            Rect rect;
            floodFill(label_image, Point(x,y), label_count, &rect, 0, 0, 4);

            vector <Point> blob;
            int cnt = 0;
            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }
                    cnt++;
                    blob.push_back(Point(j,i));
                }
            }

            if(cnt>500){
                blobs->push_back(blob);
                label_count++;
            }
        }
    }
    total_count = label_count;
}

void Counter::analyzeBlobs()
{
    blobs->iterator;
}
