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

// argcにはコマンドライン引数の個数が渡される。
// argv[]にはコマンドライン引数が渡される
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // argv[0]にはプログラム名が格納されている
        // 引数が一つ以外ならプログラム終了
        std::cout << "入力動画パスを1つ指定して下さい" << std::endl;
        return 1;
    }

    // 入力動画を読み込む
    const std::string filePath = argv[1];
    cv::VideoCapture cap(filePath, cv::CAP_FFMPEG);
    if (!cap.isOpened())
    {
        std::cout << "入力動画を開けません" << std::endl;
        return 1;
    }

    // 炎の動画を読み込む
    const std::string firefilePath = "../fire.mp4";
    cv::VideoCapture capFire(firefilePath, cv::CAP_FFMPEG);
    if (!capFire.isOpened())
    {
        std::cout << "炎の動画を開けません" << std::endl;
        return 1;
    }

    // 動画を表示するウィンドウ
    cv::namedWindow("kusanagi-window", cv::WINDOW_AUTOSIZE);

    // 作成する動画
    cv::VideoWriter outputVideo;
    // フォーマット
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    // サイズ
    cv::Size outputVideoSize = cv::Size((int) cap.get(cv::CAP_PROP_FRAME_WIDTH), (int) cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    // FPS
    int fps = cap.get(cv::CAP_PROP_FPS);
    outputVideo.open("../result.mp4", fourcc, fps, outputVideoSize);

    // 動画を再生する
    cv::Mat frame;
    cv::Mat frameFire;
    for (;;)
    {
        cap >> frame;
        capFire >> frameFire;

        if (frame.empty() || frameFire.empty())
        {
            // 動画が終了したらループを抜ける
            break;
        }

        // 炎の動画の各コマを入力画像に合うようにアファイン変換する
        float width = frame.cols;
        float height = frame.rows;
        cv::Point2f center = cv::Point2f((width / 2), (height / 2));
        double degree = 90.0;
        double scale = 1.0;
        cv::Mat affined = cv::getRotationMatrix2D(center, degree, scale);
        cv::warpAffine(frameFire, frameFire, affined, frame.size());

        // 入力画像と炎の画像を合成する
        double alpha = 0.5;
        double beta = 1.0 - alpha;
        cv::Mat dst;
        cv::addWeighted(frame, alpha, frameFire, beta, 0.0, dst);

        // 合成された画像を表示する
        cv::imshow("kusanagi-window", dst);

        // 動画を書き込む
        outputVideo << dst; 

        if (cv::waitKey(50) != -1)
        {
            // 50ミリ秒毎に次のコマに進む
            // 50ミリ秒以内に何らかのキーが押された場合は、動画を終了する
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
