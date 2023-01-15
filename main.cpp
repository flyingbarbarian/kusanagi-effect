#include <iostream>
#include <string>

// opencvのコアモジュール
#include <opencv2/core.hpp>
// 画像の処理
#include <opencv2/imgproc.hpp>
// window制御の制御とか
#include <opencv2/highgui.hpp>
// videoの制御
#include <opencv2/videoio.hpp>

// 動画に炎を重ねる関数の宣言
cv::Mat combineImageWithFire(cv::Mat frame);

// argcにはコマンドライン引数の個数が渡される。
// argv[]にはコマンドライン引数が渡される
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        // argv[0]にはプログラム名が格納されている
        std::cout << "動画パスを指定して下さい" << std::endl;
        return 1;
    }

    // 動画を読み込む
    const std::string filePath = argv[1];
    cv::VideoCapture cap(filePath, cv::CAP_FFMPEG);
    if (!cap.isOpened())
    {
        std::cout << "動画を開けません" << std::endl;
        return 1;
    }

    // 動画を表示するウィンドウ
    cv::namedWindow("kusanagi-window", cv::WINDOW_AUTOSIZE);

    // 動画を再生する
    cv::Mat frame;
    for (;;)
    {
        cap >> frame;
        if (frame.empty())
        {
            // 動画が終了したらループを抜ける
            break;
        }

        // 動画の各コマを表示する
        cv::Mat imageWithFire = combineImageWithFire(frame);
        cv::imshow("kusanagi-window", imageWithFire);
        if (cv::waitKey(50) != -1)
        {
            // 50ミリ秒毎に次のコマに進む
            // 50ミリ秒以内に何らかのキーが押された場合は、動画を終了する
            break;
        }
    }
    return 0;
}

// 動画に炎を重ねる関数
cv::Mat combineImageWithFire(cv::Mat frame)
{
    cv::Mat grey;
    cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY);
    return grey;
}
