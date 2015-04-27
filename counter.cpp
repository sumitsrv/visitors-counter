#include "counter.h"
#include <QTextStream>
#include "mergesort.h"
#include <QDebug>

Counter::Counter()
{
    BLOB_PROXIMITY = 30;
    total_count = 0;
    midX = 0;
    midY = 0;
    blobs_info = new vector<BlobInfo>();
    blobs_old = new vector<BlobInfo>();
}

int Counter::getTotalCount()
{
    return this->total_count;
}

int Counter::getCountIn()
{
    return this->count_in;
}

int Counter::getCountOut()
{
    return this->count_out;
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

void Counter::setMidPoint(int midX, int midY)
{
    this->midX = midX;
    this->midY = midY;
}

void Counter::findBlobs(Mat *binary)
{
    vector<vector<Point> > *blobs = new vector<vector<Point> >();

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
    analyzeBlobs(blobs);
}

void Counter::analyzeBlobs(vector<vector<Point> > *blobs)
{
    blobs_info->clear();
    short direction = 0;
    for(vector< vector< Point> >::iterator bl = blobs->begin(); bl != blobs->end(); bl++){
        BlobInfo *blob_info = new BlobInfo();
        minEnclosingCircle(*bl, blob_info->center, blob_info->radius);
        blobs_info->push_back(*blob_info);

        for(vector<BlobInfo>::iterator it = blobs_old->begin(); it != blobs_old->end(); it++){
            direction = 0;
            int diff = blob_info->center.y - (*it).center.y;

            if(diff%BLOB_PROXIMITY >= BLOB_PROXIMITY-1){
                total_count++;
            }else{
                blob_info->setMark((*it).marked);

                if(blob_info->isMarked()){
                    break;
                }

                if(blob_info->center.y > (*it).center.y){
                    direction = 1;
                }else{
                    direction = -1;
                }
                blob_info->setDirection(direction);

                if(blob_info->getCenter().y > this->midY && direction == 1) {
                    blob_info->setMark(true);
                    this->count_in++;
                } else if(blob_info->getCenter().y < this->midY && direction == -1) {
                    blob_info->setMark(true);
                    this->count_out++;
                }
            }

//            qDebug() << blob_info->getCenter().y << "\t" << (*it).center.y << "\t" << midY << "\t" << direction << "\n";
        }
    }
    blobs_old->clear();
    blobs_old = new vector<BlobInfo>(*blobs_info);
}
