#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    Mat src, src_gray;
    Mat src2;
    Mat grad;
    char* window_name = "Sobel Demo - Simple Edge Detector";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;


    int c;

    /// Load an image
    src = imread( argv[1] );
    src2 = imread(argv[2]);


    if( !src.data )
    { return -1; }

    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );


    /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Generate grad_x and grad_y
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    Mat res;
    imshow( window_name, grad );
    bitwise_or(src,src,res,grad);
    //bitwise_or(src,src,res,src2); не могу применить методы bitwise между рисунками 2.jpg и lena.jpg
    imshow("OR",res);
    bitwise_and(src,src,res,grad);
    imshow("AND",res);
    bitwise_xor(src,src,res,grad);
    imshow("XOR",res);



    waitKey(0);

}