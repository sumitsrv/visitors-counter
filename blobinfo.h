#ifndef BLOBINFO_H
#define BLOBINFO_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class BlobInfo
{
public:
    BlobInfo();
    short direction;
    float radius;
    bool marked;
    Point2f center;
    vector<Point> *blob;

    void setBlob(vector<Point>);
    void setRadius(float);
    void setCenter(Point2f);
    void setDirection(short);
    void setMark(bool);

    vector<Point> *getBlob();
    float getRadius();
    Point2f getCenter();
    short getDirection();
    bool isMarked();

};

#endif // BLOBINFO_H
