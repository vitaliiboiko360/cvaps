#ifndef UTIL_H
#define UTIL_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

void print_video_stats(cv::VideoCapture& cap) 
{
    std::cout<<"video frame count= "<<static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT))<<"\n";
    std::cout<<"video frame width= "<<static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH))<<"\n";
    std::cout<<"video frame height= "<<static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))<<"\n";
}

void drawContours(cv::Mat& img) 
{ 
  std::vector< std::vector<float> > output; 
  std::vector<std::vector<cv::Point> > contours; 
   
  std::vector<cv::Vec4i> hierarchy; 
  cv::findContours(img, contours, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE); 

  for(auto i=0; i<contours.size(); i++)
  { 
    cv::Mat mask= cv::Mat::zeros(img.rows, img.cols, CV_32SC1); 
    cv::drawContours(mask, contours, i, cv::Scalar(1), cv::LineTypes::FILLED, cv::LineTypes::LINE_8, hierarchy, 1); 
  } 
} 

#endif // UTIL_H