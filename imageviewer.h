#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);

public slots:
    bool showImage( cv::Mat image ); /// Used to set the image to be viewed

protected:
    void paintEvent(QPaintEvent*);

private:
    QImage _qimage;
    cv::Mat _tmp;
};

#endif // IMAGEVIEWER_H
