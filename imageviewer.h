#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QImage>
#include "serializator.h"
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

class QLabel;
class QScrollArea;
class QScrollBar;

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    ImageViewer(QScrollArea* scrollArea);
    bool loadFile(const QString &);

public slots:
    void updateImage();
    void zoomIn();
    void zoomOut();
    void normalSize();

private:
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif
};

#endif
