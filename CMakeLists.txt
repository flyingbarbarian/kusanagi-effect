# バージョンを指定する
cmake_minimum_required(VERSION 2.8)
# Project名
project( Kusanagi-effect )
# OpenCVを必須
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# 実行ファイルの名前
add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )