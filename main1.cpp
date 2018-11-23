//#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>    //Mat,resize(),cvtColor(),
#include <opencv2/videoio.hpp>  //VideoCapture,release()
#include <vector>          //vector template
#include <stdlib.h>      // c_str()
#include <chrono>      //this_thread::sleep_for(std::chrono::milliseconds(int (1000 / FRAMERATE)));
#include <thread>      //this_thread::sleep_for(std::chrono::milliseconds(int (1000 / FRAMERATE)));
#include <ncurses.h>   //initscr(),cbreak(),noecho(),......

//g++ $(pkg-config --cflags --libs opencv) -std=c++11 -lncurses main1.cpp -o main1

using namespace std;
using namespace cv;

vector<Mat> readImg();      //读视频，return 一个包含图片的vector
vector<string> imgToString(Mat a);   //把一张图片转换成字符图片

//可自由设置部分
static const int HEIGHT = 193;  // 分辨率y（数值应小于terminal分辨率y-15，因为需要留空间给进度条）
static const int WIDTH = 830;   // 分辨率x （数值应小于terminal分辨率x）
static const int FRAMERATE = 60;    // 帧率 （每秒播放帧数）
static const string FILEPATH = "butterfly.mp4" ;    //视频文件路径
//

int main(){
    initscr();
    cbreak();
    noecho();
    getch();    //等待user输入（按任意键开始程序）
    
    vector<Mat> imgVec;
    imgVec = readImg();
    
    int xMax,yMax;
    getmaxyx(stdscr, yMax,xMax);
    int totalFrame = imgVec.size();
    int checkPoint = 1;
    
    WINDOW * win =  newwin(HEIGHT, WIDTH, 1, int((xMax - WIDTH) / 2));
    WINDOW * progress = newwin(10, WIDTH, HEIGHT+5, int((xMax - WIDTH) / 2));
    box(progress, 0, 0);
    
    for(int i = 0;i < imgVec.size();i++){
        vector<string> temp=imgToString(imgVec[i]);
        for(int j = 0;j < HEIGHT;j++)
            mvwprintw(win,j,0,temp[j].c_str());
        
        if((i*WIDTH/totalFrame) > checkPoint){
            checkPoint = (i*WIDTH/totalFrame);
            for(int p = 1;p < 9;p++){
                for(int k = 1;k<checkPoint;k++){
                    mvwprintw(progress,p,k+1,"#");
                }
            }
            wrefresh(progress);
        }
        
        wrefresh(win);
        this_thread::sleep_for(std::chrono::milliseconds(int (1000 / FRAMERATE)));
    }
    clear();
    getch();   //等待user输入 （按任意键结束程序）
    endwin();
    
    return 0;
}

vector<string> imgToString(Mat m){
    string a[13] = {" ",".","-","+","a","o","z","?","8","A","W","@","$"};
    int height,width;
    height = m.rows;
    width = m.cols;
    vector<string> displayVec;
    int temp[height][width];
    for(int i = 0;i < height;i++){
        for(int k = 0;k < width;k++){
            temp[i][k] = m.at<unsigned char>(i,k);
        }
    }
    
    for(int i = 0;i < height;i++){
        string line = "";
        for(int k = 0;k < width;k++){
            if(temp[i][k]<=15)
                line+=a[12];
            else if(temp[i][k]<=30)
                line+=a[11];
            else if(temp[i][k]<=45)
                line+=a[10];
            else if(temp[i][k]<=60)
                line+=a[9];
            else if(temp[i][k]<=75)
                line+=a[8];
            else if(temp[i][k]<=90)
                line+=a[7];
            else if(temp[i][k]<=110)
                line+=a[6];
            else if(temp[i][k]<=130)
                line+=a[5];
            else if(temp[i][k]<=150)
                line+=a[4];
            else if(temp[i][k]<=170)
                line+=a[3];
            else if(temp[i][k]<=190)
                line+=a[2];
            else if(temp[i][k]<=215)
                line+=a[1];
            else
                line+=a[0];
            
        }
        displayVec.push_back(line);
    }
    return displayVec;
}

vector<Mat> readImg(){
    VideoCapture cap;
    Mat frame;
    vector<Mat> vecImg;
    cap.open(FILEPATH);
    for(;;){
        cap.read(frame);
        if(frame.empty()){
            break;
        }
        cvtColor(frame,frame,COLOR_BGR2GRAY);
        resize(frame,frame,Size_<int>(WIDTH,HEIGHT));
        vecImg.push_back(frame);
    }
    
    cap.release();
    return vecImg;
}
