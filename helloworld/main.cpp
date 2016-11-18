#include<opencv2/opencv.hpp>
int main(int argc,const char *argv[]){
  
  cv::Mat src = cv::imread(argv[1],cv::IMREAD_COLOR);
  
  if(src.empty()){
    std::cout<<"FAiled to open image:"<<argv[1]<<std::endl;
    return -1;
  }
  
  cv::namedWindow("image",cv::WINDOW_AUTOSIZE);
  cv::imshow("image",src);
  cv::waitKey(0);
  cv::destroyAllWindows();
  
  return 0;
}
