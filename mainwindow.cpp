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


    std::size_t h = std::hash <std::string>{}(text); 

    std::cout << "h: " << h << std::endl;

    int img_size = 400;

    Mat image ( img_size, img_size, CV_8UC3, Scalar(255,255,0) ); 



    int fig = h & 3; 
    std::cout << "fig is " << fig <<  std::endl;

    h >>= 2; 
    std::cout << "h is " << h <<  std::endl;

    int col = h & 3; 
    std::cout << "col is " << col <<  std::endl;

    h >>= 2; 

    for (int i=0; i < 4; i++){
        for (int j=0; j<4; j++){
            int fig = h & 3; 

            Scalar sc; 
            h >>= 2; 

            int col = h & 3; 

            h >>= 2; 

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

        }
    }

    return QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("lineEdit");
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateImage(const QString &)));

}

MainWindow::~MainWindow()
{
     delete ui;
}


void MainWindow::on_pushButton_clicked(){
    std::cout << "button is clicked"  << std::endl;
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("lineEdit");

    QString text = lineEdit->text();

    QString file_name = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::homePath(), ("Images (*.png *.xpm *.jpg)"));

    std::cout << "filename is: " << file_name.toStdString() << std::endl;

    if(generator(text.toStdString()).save(file_name)){
        QMessageBox::information(this, "Good news!", "File saved");
    } else {
        QMessageBox::warning(this, "Error", "Some problem occured");
    }
    std::cout << "text is: " << text.toStdString() << std::endl;

    std::cout << "something is saved..."<< std::endl;

}



void MainWindow::updateImage(const QString &str)
{
    std::cout << "string is: " << str.toUtf8().constData() << std::endl;

    if (str.isEmpty()){
        ui->labelPic->clear();
    } else {
        QPixmap pix(QPixmap::fromImage(generator(str.toUtf8().constData())));

        int w = ui->labelPic->width();
        int h = ui->labelPic->height();
        std::cout << "setPixmap goes here..." << std::endl;

        ui->labelPic->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    }
    std::cout << "update goes here..." << std::endl;
     QWidget::update();
    // QWidget::repaint();
     std::cout << "after update goes here..." << std::endl;
}
