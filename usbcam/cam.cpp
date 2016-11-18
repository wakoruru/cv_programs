#include<iostream>
using namespace std;
#include<opencv2/opencv.hpp>
using namespace cv;

#define CAM1 0
const int width=640,height=480;
int main(int argc, const char *argv[]){
  VideoCapture cap(CAM1);
  cap.set(CV_CAP_PROP_FRAME_WIDTH,width);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,height);
  if(!cap.isOpened()){
    cout<<"CAM1 is not detected!!"<<endl;
    return -1;
  }
  else{
    int key=0;
    Mat capture,before;
    namedWindow("capture",WINDOW_AUTOSIZE);
    namedWindow("diff",WINDOW_AUTOSIZE);
    cap>>before;
    while(1){
      cap>>capture;
      absdiff(capture,before,before);
      
      cvtColor(before,before,CV_BGR2GRAY);

      imshow("capture",capture);
      imshow("diff",before);

      capture.copyTo(before);

      key = waitKey(1);
      if(key=='q'){
        break;
      }
    }
  }
  destroyAllWindows();
  return 0;
}
