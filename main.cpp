#include <iostream>
//
#include <string>

#include <opencv2/core.hpp>
// window制御とか
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

// argcにはコマンドライン引数の個数が渡される。
// argv[]にはコマンドライン引数が渡される
int main(int argc, char *argv[])
{
    // 動画を表示するウィンドウ
    cv::namedWindow("kusanagi-window", cv::WINDOW_AUTOSIZE);

    // 動画を読み込む
    const std::string filePath = "../hand.mp4";
    cv::VideoCapture cap(filePath, cv::CAP_FFMPEG);

    std::cout << filePath << std::endl;

    if (!cap.isOpened())
    {
        std::cout << "動画を開けません" << std::endl;
        return -1;
    }

    // 動画を再生する
    cv::Mat frame;
    for(;;) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cv::imshow("kusanagi-window", frame);
        if ((char)cv::waitKey(33) >= 0) {
            break;
        }
    }
    return 0;
}
