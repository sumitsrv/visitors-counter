#include "blobinfo.h"

BlobInfo::BlobInfo()
{
    radius = 0;
    direction = 0;
    center = Point2f(0,0);
    blob = new vector<Point>();
}

void BlobInfo::setBlob(vector<Point> blob)
{
    this->blob = &blob;
}

void BlobInfo::setRadius(float radius)
{
    this->radius = radius;
}

void BlobInfo::setCenter(Point2f center)
{
    this->center = center;
}

void BlobInfo::setDirection(short)
{
    this->direction = direction;
}

void BlobInfo::setMark(bool marked)
{
    this->marked = marked;
}

vector<Point>* BlobInfo::getBlob()
{
    return this->blob;
}

float BlobInfo::getRadius()
{
    return radius;
}

Point2f BlobInfo::getCenter()
{
    return center;
}

short BlobInfo::getDirection()
{
    return direction;
}

bool BlobInfo::isMarked()
{
    return this->marked;
}
