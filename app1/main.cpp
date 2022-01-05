#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "util.h"

using namespace cv;

struct cannyThresholds
{
    const int maxHigh {255};
    const int maxLow {255};
    int high{ 42 };
    int low{ 60 };
} g_CannyThresholds;

int g_MinimalArea = 450;

void onLowTrackbarSlide(int pos, void*) 
{
    g_CannyThresholds.low = pos;
}

void onHighTrackbarSlide(int pos, void*) 
{
    g_CannyThresholds.high = pos;
}

void onMinimalAreaTrackbarSlide(int pos, void*) 
{
    g_MinimalArea = pos;
}


int main(int argc, char** argv)
{
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Info", cv::WINDOW_NORMAL);
    cv::createTrackbar("Low_Thershold", "Info", &g_CannyThresholds.low, g_CannyThresholds.maxLow, onLowTrackbarSlide);
    cv::createTrackbar("High_Thershold", "Info", &g_CannyThresholds.high, g_CannyThresholds.maxHigh, onHighTrackbarSlide);
    cv::createTrackbar("Minimal Area", "Info", &g_MinimalArea, 10000, onMinimalAreaTrackbarSlide);

    cv::VideoCapture cap;
    std::string fileName = std::string(argv[1]);
    cap.open(fileName);

    if (!cap.isOpened())
	{
		std::cout << " Failed to read video file " << fileName << "\n";
		return -1;
	}

    std::cout<<"opened "<<fileName<<"\n";

    print_video_stats(cap);

    std::vector< std::vector< cv::Point > > vvContours;
    std::vector< cv::Vec4i > hierarchy;

    std::stringstream message;
    cv::Mat info;
    cv::Mat frame;
    cv::Mat imgContours;

    cv::Mat labels;
    cv::Mat stats;
    cv::Mat centroids;
    for(;;) 
    {
        cap >> frame;
        if ( frame.empty() ) 
        {
            std::cout<<"frame is empty\n";
            break;
        }
        cv::Canny(frame, imgContours, g_CannyThresholds.low, g_CannyThresholds.high);
        //cv::threshold(frame, imgContours, g_CannyThresholds.low, g_CannyThresholds.high, cv::THRESH_BINARY);
        cv::imshow("Example", imgContours);
        int numConnectedComponents = cv::connectedComponentsWithStats(imgContours, labels, stats, centroids);
        int bigContours = 0;
        for (int i=0; i<numConnectedComponents; i++) 
        {
            if(stats.at<int>(i, cv::CC_STAT_AREA) > g_MinimalArea)
            {
                bigContours++;
                stats.at<int>(i, cv::)
            }
        }

        //cv::findContours(imgContours, vvContours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        message<<"found contours= "<<bigContours<<"\n";
        std::cout<<message.str();
        //cv::putText(info, message.str(),cv::Point(1,1),cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(0,0,0),2,false);
        //cv::imshow("Info",info);
        message.clear();
        if ( cv::waitKey(67) >= 0 )
        {
            break;
        }
    }

    cv::waitKey(0);
    destroyAllWindows();
}