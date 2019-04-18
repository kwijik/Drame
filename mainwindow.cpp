#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <functional>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace cv;

void drawTriangle(Mat image, Point p1, Point p2, Point p3, Scalar sc, int width){
    line( image, p1, p2, sc, width, 8 );
    line( image, p1, p3, sc, width, 8 );
    line( image, p2, p3, sc, width, 8 );
}

QImage generator( std::string text){

    const int line_width = 2;

    int size_pic = 400;

    //std::string test = "tttt";

    std::size_t h = std::hash <std::string>{}(text); // hash

    std::cout << "h: " << h << std::endl;

    int img_size = 400;

    Mat image ( 400, 400, CV_8UC3, Scalar(255,255,0) ); // unsigned double


    //int test1 = 10 >>2;
    //std::cout << "test1 is " << test1 <<  std::endl;

    int fig = h & 3; // 3 это 11; берем 2 бита
    std::cout << "fig is " << fig <<  std::endl;

    h >>= 2; // смещаем вправо на 2 бита
    std::cout << "h is " << h <<  std::endl;

    int col = h & 3; // 3 это 11
    std::cout << "col is " << col <<  std::endl;

    h >>= 2; // смещаем вправо на 2 бита

//
    for (int i=0; i < 4; i++){
        for (int j=0; j<4; j++){
            int fig = h & 3; // 3 это 11

            Scalar sc; // цвет
            h >>= 2; // смещаем вправо на 2 бита

            int col = h & 3; // 3 это 11

            h >>= 2; // смещаем вправо на 2 бита

            switch(col){
                case 0:
                    sc = Scalar(255, 255, 255);
                    break;
                case 1:
                    sc = Scalar(0, 0, 0);
                    break;
                case 2:
                    sc = Scalar(255, 0, 0);
                    break;
                case 3:
                    sc = Scalar(0, 0, 255);
                    break;
            }

            switch(fig){
                case 0:
                    circle( image, Point( i * 100 + 50, j * 100 + 50 ), 32.0, sc, line_width, LINE_8 );
                    break;
                case 1:
                    line( image, Point( i * 100, j * 100 ), Point( i * 100 +100, j * 100 +100), sc, line_width, LINE_8 );
                    break;
                case 2:
                    line( image, Point( i*100, j * 100 + 100 ), Point( i * 100 +100, j * 100), sc, line_width, LINE_8 );
                    break;
                case 3:
                    drawTriangle( image, Point( i*100, j * 100), Point( i * 100 +100, j * 100), Point(i * 100 +50, j * 100 + 100), sc, line_width);
                    break;
            }

            // std::cout << "color is " << col << "; fig is " << fig <<  std::endl;
        }
    }



   // imshow("Image",image);

    // waitKey(0);
//QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    return QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("/Users/denisbolshakov/Documents/cpp/DrawMe/2019-02-03 02.45.44.jpg");
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("lineEdit");
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateImage(const QString &)));

}

MainWindow::~MainWindow()
{
     delete ui;
}

void MainWindow::updateImage(const QString &str)
{
   // QString str = ui->lineEdit->text();
    //std::cout << str << std::endl;
    // generator(str.toUtf8().constData()).save("test_image.png");
    std::cout << "string is: " << str.toUtf8().constData() << std::endl;
    QPixmap pix(QPixmap::fromImage(generator(str.toUtf8().constData())));

    int w = ui->labelPic->width();
    int h = ui->labelPic->height();
    std::cout << "setPixmap goes here..." << std::endl;

    ui->labelPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    std::cout << "update goes here..." << std::endl;
     QWidget::update();
    // QWidget::repaint();
     std::cout << "after update goes here..." << std::endl;

     //
}
