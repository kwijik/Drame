#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <functional>

using namespace cv;

int main(){

	int size_pic = 400;

	std::string test = "helloo";

	std::size_t h = std::hash <std::string>{}(test); // hash

	std::cout << "h: " << h << std::endl;

		Mat image = Mat::zeros( 400, 400, CV_8UC3 );



// 
	for (int i=0; i < 4; i++){
		for (int j=0; j<4; j++){
			int fig = h & 3; // 3 это 11  

 			h >>= 2; // смещаем вправо на 2 бита

 			int col = h & 3; // 3 это 11  

 			h >>= 2; // смещаем вправо на 2 бита



			switch(fig){
				case 0: circle( image, Point( 200, 200 ), 32.0, Scalar( 110, 220, 0 ), 1, 8 );
				case 1: circle( image, Point( 200, 200 ), 32.0, Scalar( 110, 220, 0 ), 1, 8 );
				case 2: circle( image, Point( 200, 200 ), 32.0, Scalar( 110, 220, 0 ), 1, 8 );
				case 3: circle( image, Point( 200, 200 ), 32.0, Scalar( 110, 220, 0 ), 1, 8 );
			}

		std::cout << "fig is " << fig << std::endl;
		}
	}
/*
 	int fig = h & 3; // 3 это 11  == 0

 	std::cout << "fig: " << fig << std::endl; 


 	h >>= 2; // смещаем вправо на 2 бита

	std::cout << "h: " << h << std::endl;


 	 int col = h & 3; // 3 это 11  

	std::cout << "col: " << col << std::endl;

 	h >>= 2; // смещаем влево на 2 бита

 	int test1 = 4;
 	std::cout << "test1: " << test1 << std::endl;

 	test1 >>= 2;
 	std::cout << "test1: " << test1 << std::endl;

 	int test2 = 5 & 3;
 	std::cout << "test2: " << test2 << std::endl;

/*
 	switch(temp){
 		case 0: // рисуем круг
 		case 1: // рисуем цвет
 	} 

	Mat image = Mat::zeros( 400, 400, CV_8UC3 );

	line( image, Point( 15, 20 ), Point( 70, 50), Scalar( 110, 220, 0 ),  2, 8 );

	  	circle( image, Point( 200, 200 ), 32.0, Scalar( 110, 220, 0 ), 1, 8 );


 	*/



	imshow("Image",image);

	waitKey(0);

	return 0;
}