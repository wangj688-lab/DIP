#ifndef MORPHOLOGYDIALOG_H
#define MORPHOLOGYDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QImage>
#include <QComboBox>
#include "imageprocess.h"
#include "padding.h"
#include "floatslider.h"
#include <QApplication>
#include <QDesktopWidget>


QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSlider;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QBoxLayout;
class QHBoxLayout;
class QVBoxLayout;
class QComboBox;
QT_END_NAMESPACE

class MorphologyDialog : public QDialog
{
    Q_OBJECT
public:
    MorphologyDialog(QImage inputImage);
    ~MorphologyDialog()
    {
        if (rgb)
            delete [] rgb;
        if (rgbPadded)
            delete [] rgbPadded;
        if (rgbFilteredX)
            delete [] rgbFilteredX;
        if (filterKernelX)
            delete [] filterKernelX;
    }
    QImage getImage() {return dstImage;}
    //void showEvent(QShowEvent *event);
private:
    void iniUI();
    QImage erodingImage(QImage &image);
    QImage dilatingImage(QImage& image);
    QImage openingImge(QImage& image);
    QImage closingImage(QImage& image);
    QImage contourExtraction(QImage& image);
    QImage srcImage;
    QImage erosionImage;
    QImage dilationImage;
    QImage openImage;
    QImage closeImage;
    QImage dstImage;
    QImage contourImage;

    uchar *rgb = nullptr;
    uchar *rgbPadded = nullptr;
    uchar *rgbFilteredX = nullptr;
    uchar *rgbFilteredY = nullptr;
    float *filterKernelX = nullptr;
    float *filterKernelY = nullptr;


    QLabel *srcImageLabel;
    QLabel *erosionImageLabel;
    QLabel *dilationImageLabel;
    QLabel *openImageLabel;
    QLabel *closeImageLabel;
    QLabel *contourImageLabel;


    QLabel *srcLabel;
    QLabel *erosionLabel;
    QLabel *dilationLabel;
    QLabel *openLabel;
    QLabel *closeLabel;
    QLabel *contourLabel;

    int borderType = 0;
    QLabel *borderTypeLabel;
    QComboBox *borderTypeComboBox;

    int filterType = 0;
    QLabel *filterTypeLabel;
    QComboBox *filterTypeComboBox;

    QPushButton     *btnOK;
    QPushButton     *btnCancel;
    QPushButton     *btnClose;
private slots:
    void setImage(QImage image, QLabel *label);
};
#endif // MORPHOLOGYDIALOG_H
