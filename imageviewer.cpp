#include <imageviewer.h>

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
{}

bool ImageViewer::showImage( cv::Mat image )
{
    switch (image.type()) {
    case CV_8UC1:
        cvtColor(image, _tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cvtColor(image, _tmp, CV_BGR2RGB);
        break;
    }

    //    assert(_tmp.isContinuous());
    _qimage = QImage(_tmp.data, _tmp.cols, _tmp.rows, _tmp.cols*3, QImage::Format_RGB888);

    this->setFixedSize(image.cols, image.rows);

    repaint();
    return true;
}

void ImageViewer::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), _qimage);
    painter.end();
}
