#include<opencv2/opencv.hpp>


using namespace cv;
#include<iostream>
#include<vector>
using namespace std;


int main(int argc, char** argv){
  VideoCapture mov(argv[1]);
  mov.set(CV_CAP_PROP_FRAME_WIDTH,640);
  mov.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  if(!mov.isOpened()){
    cout<<"File open failed."<<endl;
    return -1;
  }
  namedWindow("MOVIE",CV_WINDOW_AUTOSIZE|CV_WINDOW_KEEPRATIO|CV_GUI_EXPANDED);
  while(1){
    Mat frame,gray;
    /*get new frame*/
    mov>>frame;
    /*check new frame*/
    if(frame.empty())break;
    /*copy to gray*/
    cvtColor(frame,gray,CV_BGR2GRAY);
    normalize(gray,gray,0,255,NORM_MINMAX);
    /*descripter*/
    vector<KeyPoint> keypoints;
    vector<KeyPoint>::iterator itk;
    /*SHIFT*/
    FastFeatureDetector detector(70,false);
    Scalar color(50,50,155);
    detector.detect(gray,keypoints);
    for(itk = keypoints.begin(); itk!=keypoints.end(); ++itk) {
      cv::circle(frame, itk->pt, 1, color, -1);
      cv::circle(frame, itk->pt, itk->size, color, 1, CV_AA);
      if(itk->angle>=0) {
        cv::Point pt2(itk->pt.x + cos(itk->angle)*itk->size, itk->pt.y + sin(itk->angle)*itk->size);
        cv::line(frame, itk->pt, pt2, color, 1, CV_AA);
      }
    }

    /*show new frame*/
    imshow("MOVIE",frame);
    /*key interrupt*/
    if(waitKey(30)>=0)break;
  }
}
