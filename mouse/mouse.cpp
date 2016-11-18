#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void onMouse( int event, int x, int y, int flag, void* )
{
  std::string desc;

  // マウスイベントを取得
  switch(event) {
  case cv::EVENT_MOUSEMOVE:
    desc += "MOUSE_MOVE";
    break;
  case cv::EVENT_LBUTTONDOWN:
    desc += "LBUTTON_DOWN";
    break;
  case cv::EVENT_RBUTTONDOWN:
    desc += "RBUTTON_DOWN";
    break;
  case cv::EVENT_MBUTTONDOWN:
    desc += "MBUTTON_DOWN";
    break;
  case cv::EVENT_LBUTTONUP:
    desc += "LBUTTON_UP";
    break;
  case cv::EVENT_RBUTTONUP:
    desc += "RBUTTON_UP";
    break;
  case cv::EVENT_MBUTTONUP:
    desc += "MBUTTON_UP";
    break;
  case cv::EVENT_LBUTTONDBLCLK:
    desc += "LBUTTON_DBLCLK";
    break;
  case cv::EVENT_RBUTTONDBLCLK:
    desc += "RBUTTON_DBLCLK";
    break;
  case cv::EVENT_MBUTTONDBLCLK:
    desc += "MBUTTON_DBLCLK";
    break;
  }

  // マウスボタン，及び修飾キーを取得
  if(flag & cv::EVENT_FLAG_LBUTTON)
    desc += " + LBUTTON";
  if(flag & cv::EVENT_FLAG_RBUTTON)
    desc += " + RBUTTON";
  if(flag & cv::EVENT_FLAG_MBUTTON)
    desc += " + MBUTTON";
  if(flag & cv::EVENT_FLAG_CTRLKEY)
    desc += " + CTRL";
  if(flag & cv::EVENT_FLAG_SHIFTKEY)
    desc += " + SHIFT";
  if(flag & cv::EVENT_FLAG_ALTKEY)
    desc += " + ALT";

  std::cout << desc << " (" << x << ", " << y << ")" << std::endl;
}
int
main(int argc, char *argv[])
{
  cv::Mat black_img = cv::Mat::zeros(cv::Size(800, 500), CV_8UC3); 
  
  cv::namedWindow("mouse event demo", 0 );
  cv::setMouseCallback("mouse event demo", onMouse, 0);
  imshow("mouse event demo", black_img);
  
  int key;
  while(1) {
    key = cv::waitKey(0);
    if(key=='q') break;
  }
}
