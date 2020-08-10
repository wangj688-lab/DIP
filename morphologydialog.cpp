#include "morphologydialog.h"
#include <QDebug>

MorphologyDialog::MorphologyDialog(QImage inputImage)
{
    srcImage = inputImage;
    erosionImage = erodingImage(srcImage);
    dilationImage = dilatingImage(srcImage);
    openImage = openingImge(srcImage);
    closeImage = closingImage(srcImage);
    //contourImage = contourExtraction(srcImage);  //效果不好，删掉了

    //erosionImage = inputImage;
    //qDebug()<<"wangjie is cute";

     iniUI();

    srcImageLabel->setPixmap(QPixmap::fromImage(srcImage).scaled(srcImageLabel->width(), srcImageLabel->height()));
    erosionImageLabel->setPixmap(QPixmap::fromImage(erosionImage).scaled(erosionImageLabel->width(), erosionImageLabel->height()));
    dilationImageLabel->setPixmap(QPixmap::fromImage(dilationImage).scaled(dilationImageLabel->width(), dilationImageLabel->height()));
    openImageLabel->setPixmap(QPixmap::fromImage(openImage).scaled(openImageLabel->width(), openImageLabel->height()));
    closeImageLabel->setPixmap(QPixmap::fromImage(closeImage).scaled(closeImageLabel->width(), closeImageLabel->height()));
    //contourImageLabel->setPixmap(QPixmap::fromImage(contourImage).scaled(contourImageLabel->width(), contourImageLabel->height()));



}

//图像腐蚀
QImage MorphologyDialog:: erodingImage(QImage &image)
{

    //设定7X7的卷积核
    QImage newImage(image.width(), image.height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;

    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            Rcolor = QColor(image.pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image.pixel(x + i, y + j));
                    // 求局部最小值
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    return newImage;
}


QImage  MorphologyDialog::dilatingImage(QImage& image)
{
    QImage dilationImage(image.width(), image.height(), QImage::Format_ARGB32);
    //设定7X7的卷积核
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;

    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            Rcolor = QColor(image.pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image.pixel(x + i, y + j));
                    //求解局部最大值
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            dilationImage.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    return dilationImage;
}

//开运算：先腐蚀后膨胀
QImage MorphologyDialog::openingImge(QImage& image)
{
    QImage newImage(image.width(), image.height(), QImage::Format_ARGB32);
    QImage newImage1(image.width(), image.height(), QImage::Format_ARGB32);

    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    /*腐蚀操作*/
    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image.pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    /*膨胀操作*/
    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage.pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    return newImage1;
}

QImage  MorphologyDialog::closingImage(QImage& image)
{
    QImage newImage(image.width(), image.height(), QImage::Format_ARGB32);
    QImage newImage1(image.width(), image.height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;

    /*膨胀操作*/
    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image.pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    /*腐蚀操作*/
    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage.pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }



    return newImage1;
}


//提取图像轮廓
QImage MorphologyDialog::contourExtraction(QImage& image)
{
    QImage newImage(image.width(), image.height(), QImage::Format_ARGB32);
    QImage newImage1(image.width(), image.height(), QImage::Format_ARGB32);

    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor newcolor;
    int r = 0;
    int g = 0;
    int b = 0;
    /*膨胀操作*/
    for (int y = sizeKernel / 2; y < image.height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image.width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image.pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage.setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    /*end*/
    for (int y = 0; y<image.height(); y++)
    {
        for (int x = 0; x<image.width(); x++)
        {
            color = QColor(image.pixel(x, y));
            newcolor = QColor(newImage.pixel(x, y));
            if (color.red() != newcolor.red())
            {
                r = 255;
            }
            else
            {
                r = 0;
            }
            if (color.green() != newcolor.green())
            {
                g = 255;
            }
            else
            {
                g = 0;
            }
            if (color.blue() != newcolor.blue())
            {
                b = 255;
            }
            else
            {
                b = 0;
            }
            newImage.setPixel(x, y, qRgb(r, g, b));
        }
    }
    return newImage;
}

//形态学滤波对话框界面设计
void MorphologyDialog::iniUI()
{
    // five image labels
    srcImageLabel = new QLabel();
    srcImageLabel->setAlignment(Qt::AlignCenter);

    erosionImageLabel = new QLabel();
    erosionImageLabel->setAlignment(Qt::AlignCenter);

    dilationImageLabel = new QLabel();
    dilationImageLabel->setAlignment(Qt::AlignCenter);

    openImageLabel = new QLabel();
    openImageLabel->setAlignment(Qt::AlignCenter);

    closeImageLabel = new QLabel();
    closeImageLabel->setAlignment(Qt::AlignCenter);

    contourImageLabel = new QLabel();
    contourImageLabel->setAlignment(Qt::AlignCenter);

     //qDebug()<<"wangj cool: ";



    // five images names
    srcLabel = new QLabel(tr("Original"));
    srcLabel->setAlignment(Qt::AlignCenter);
    erosionLabel = new QLabel(tr("Erosion"));
    erosionLabel->setAlignment(Qt::AlignCenter);
    dilationLabel = new QLabel(tr("Dilation"));
    dilationLabel->setAlignment(Qt::AlignCenter);

    openLabel = new QLabel(tr("Open"));
    openLabel->setAlignment(Qt::AlignCenter);

    closeLabel = new QLabel(tr("Close"));
    closeLabel->setAlignment(Qt::AlignCenter);

//    contourLabel = new QLabel(tr("Contour"));
//    contourLabel->setAlignment(Qt::AlignCenter);

    // three buttons
    btnOK = new QPushButton(tr("OK"));
    btnCancel = new QPushButton(tr("Cancel"));
    btnClose = new QPushButton(tr("Exit"));

    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(srcImageLabel);
    layout1->addWidget(erosionImageLabel);
    layout1->addWidget(dilationImageLabel);


    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(srcLabel);
    layout2->addWidget(erosionLabel);
    layout2->addWidget(dilationLabel);


    QHBoxLayout *layout3 = new QHBoxLayout;

    layout3->addWidget(openImageLabel);
    layout3->addWidget(closeImageLabel);
    // layout3->addWidget(contourImageLabel);

    QHBoxLayout *layout4 = new QHBoxLayout;

    layout4->addWidget(openLabel);
    layout4->addWidget(closeLabel);
//    layout4->addWidget(contourLabel);

    QHBoxLayout *layout8 = new QHBoxLayout;
    layout8->addStretch();
    layout8->addWidget(btnOK);
    layout8->addWidget(btnCancel);
    layout8->addStretch();
    layout8->addWidget(btnClose);

    // main layout
    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->addLayout(layout1);
    mainlayout->addLayout(layout2);
    mainlayout->addLayout(layout3);
    mainlayout->addLayout(layout4);
    mainlayout->addLayout(layout8);


    setLayout(mainlayout);
}

void MorphologyDialog::setImage(QImage image, QLabel *label)
{
    QPixmap pix;
    pix.fromImage(image);
    label->setPixmap(pix);
}
