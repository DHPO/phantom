#include <opencv2/opencv.hpp>
using namespace cv;

void imgResize(Mat& img1, Mat& img2, int width, int height)
{
    resize(img1, img1, Size(width, height));
    resize(img2, img2, Size(width, height));
}

void calculate(uchar whitePx, uchar blackPx, uchar *grayscale, uchar *alpha)
{
    whitePx = whitePx / 2 + 128;
    blackPx = blackPx / 2;
    double alpha_f = 1 - double(whitePx - blackPx)/255;
    *grayscale = blackPx / alpha_f;
    *alpha = uchar(alpha_f * 255);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return -1;

    int width = 400;
    int height = 300;

    Mat img1 = imread(argv[1], 0);
    Mat img2 = imread(argv[2], 0);
    Mat dst = Mat(height, width, CV_8UC4);


    imgResize(img1, img2, width, height);

    for ( int r = 0; r < height; r++) {
        uchar *ptr1 = img1.ptr<uchar>(r);
        uchar *ptr2 = img2.ptr<uchar>(r);
        uchar *ptrd = dst.ptr<uchar>(r);
        for (int c = 0; c < width; c++) {
            uchar grayscale, alpha;
            calculate(ptr1[c], ptr2[c], &grayscale, &alpha);
            ptrd[4 * c + 0] = grayscale;
            ptrd[4 * c + 1] = grayscale;
            ptrd[4 * c + 2] = grayscale;
            ptrd[4 * c + 3] = alpha;
        }
    }

    //imwrite("output.jpg", dst);

    std::vector<int> compression_params;  
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  
    compression_params.push_back(9);  
  
    imwrite("output.png", dst, compression_params);  

    return 0;
}