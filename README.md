# -
数码宝贝 butterfly 字符动画
注⚠️：仅mac用户可以运行程序，include了ncurses.h以代替windows.h的一些功能，不支持windows平台。


1.安装一些需要的东西：

安装homebrew：  
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    
安装opencv：
    brew install opencv
    
安装pkg-config：
    brew install pkg-config
    
安装ncurses：
    brew install ncurses
    
2.运行注意事项：
    打开terminal，进入文件所在目录
    调整terminal的分辨率！！！！！如果过小会导致显示不完整（当然可以去程序里调参数使其符合你terminal的分辨率->下面第三步）
        输入 g++ $(pkg-config --cflags --libs opencv) -std=c++11 -lncurses main1.cpp -o main1    （-lncurses 会link ncurses）
    输入./main
    
   进入程序后会白屏，因为我用了getch（）等待user输入才会执行下面的代码。
        按任意键开始主程序
   会继续白屏一会，取决于读的视频的大小。
   播放～
   结束后白屏，按任意键退出
   
3.替换视频和修改分辨率帧率：

static const int HEIGHT = 193;                      // 分辨率y（数值应小于terminal分辨率y-15，因为需要留空间给进度条）
static const int WIDTH = 830;                       // 分辨率x （数值应小于terminal分辨率x）
static const int FRAMERATE = 60;                    // 帧率 （每秒播放帧数）
static const string FILEPATH = "butterfly.mp4" ;    //视频文件路径
    
HEIGHT 应小于terminal y方向的分辨率 - 15，  因为进度条占10行，与播放窗口差5行

WIDTH  小于terminal x方向分辨率即可

eg： terminal：835 * 208
    HEIGHT 应小于 193
    WIDTH 应小于  835 
    
FRAMERATE   没有限制，我还没测过过大会怎么样（之后更新）
FILEPATE   视频路径

        待更新～～
    
