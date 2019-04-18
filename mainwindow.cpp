#include "mainwindow.h"
#include "ui_mainwindow.h"
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    std::cout << "button clicked" << std::endl;
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("lineEdit");
    std::cout << "input " << lineEditstr.toUtf8().constData() << std::endl;

}

void drawTriangle(Mat image, Point p1, Point p2, Point p3, Scalar sc, int width){
    line( image, p1, p2, sc, width, 8 );
    line( image, p1, p3, sc, width, 8 );
    line( image, p2, p3, sc, width, 8 );
}

QImage generator(){

	const int line_width = 2; 

	int size_pic = 400;

	std::string test = "tttt";

	std::size_t h = std::hash <std::string>{}(test); 

	std::cout << "h: " << h << std::endl;

	int img_size = 400;

	Mat image ( 400, 400, CV_8UC3, Scalar(255,255,0) ); 



	int fig = h & 3; 
	std::cout << "fig is " << fig <<  std::endl;

 	h >>= 2; 
	std::cout << "h is " << h <<  std::endl;

 	int col = h & 3; 
	std::cout << "col is " << col <<  std::endl;

 	h >>= 2; 

// 
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

			// std::cout << "color is " << col << "; fig is " << fig <<  std::endl;


		}

	    return QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);

	}