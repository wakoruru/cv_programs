/*--- INCLUDE ---*/
#include<opencv2/opencv.hpp>
using namespace cv;
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
/*--- DEFINE ---*/
#define ROW 10
#define COL 7
/*--- MAIN ---*/
int main(int argc,char** argv){
/*--- VALUABLE ---*/
  int past_key=0;
  int file_count=0;
  bool ret = false;
/*--- CAPTURE SETTING ---*/
  Mat frame,capture;
  VideoCapture cap(0);
  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  namedWindow("CAPTURE",CV_WINDOW_AUTOSIZE);
  namedWindow("CHESS",CV_WINDOW_AUTOSIZE);
/*--- CORNER ---*/
  Size patSize(ROW,COL);
  vector<Point2f> corner;
  vector<Point3f> obj;
  vector< vector<Point3f> > objectPoints;
  vector< vector<Point2f> > imagePoints;
  for(int i=0;i<ROW*COL;i++){
    obj.push_back(Point3f(i/ROW,i%ROW,0.0f));
  }
/*--- LOOP ---*/
  while(1){
    /*--- NEW FRAME ---*/
    cap >> capture;
    capture.copyTo(frame);
    cvtColor(frame,frame,CV_BGR2GRAY);
    /*--- DETECT CHESS ---*/
    Mat chess;
    ret = findChessboardCorners(frame,patSize,corner,CV_CALIB_CB_ADAPTIVE_THRESH);
    drawChessboardCorners(frame,patSize,(Mat)corner,ret);
    /*--- IMAGE SHOW ---*/
    imshow("CAPTURE",frame);
    /*--- KEY INTERRUPT ---*/
    int key = waitKey(1);
    if(key == 'q')break;
    if(key == 's' && key != past_key){
      /*--- IMAGE SHOW ---*/
      imshow("CHESS",frame);
      /*--- SAVE IMAGE ---*/
      ostringstream file_name;
      file_name <<"./image/chess/chess_img_"<< ++file_count<<".png";
      cout<<file_name.str()<<endl;
      imwrite(file_name.str(),capture);
      /*--- SAVE CORNER ---*/
      cornerSubPix(frame,corner,Size(11,11),Size(-1,-1),TermCriteria(TermCriteria::EPS+TermCriteria::COUNT,30,0.1));
      objectPoints.push_back(obj);
      imagePoints.push_back(corner);
    }
    past_key = key;
  }
  /*--- CALIBRATION ---*/
  vector<Mat> rvecs,tvecs;
  Mat mtx(3,3,CV_64F);
  Mat dist(8,1,CV_64F);
  calibrateCamera(objectPoints,imagePoints,Size(480,640),mtx,dist,rvecs,tvecs);
  FileStorage fs("bluecam.xml",FileStorage::WRITE);
  fs<<"mtx"<<mtx;
  fs<<"dist"<<dist;
  return 0;
}
/*---END OF FILE---*/
