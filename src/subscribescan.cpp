#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <lcmtypes/lidar/lidar_t.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>

class Handler
{
public:
    Handler(){

        std::cout << "Handle()" << std::endl;
    }
    ~Handler(){

    }
    void handleMessage(const lcm::ReceiveBuffer* rbuf,
                       const std::string & chan,
                       const lidar::lidar_t *msg)
    {
        std::cout << msg->timestamp << std::endl;
        cv::Mat scanImg(1001, 1001, CV_8UC3, cv::Scalar(255,255,255));
        int centx = 500;
        int centy = 500;
        for(uint16_t i=0; i < msg->num_ranges; i++)
        {

            int col = centx + (int)msg->ranges[i] / 20 * cos(i*M_PI/180);
            int row = centy + (int)msg->ranges[i] / 20 * sin(i*M_PI/180);

            scanImg.at<cv::Vec3b>(row, col) = cv::Vec3b(0,0,255);
//            scanImg->at(y, x)[0] = 255;
//            scanImg->at(y, x)[1] = 0;
//            scanImg->at(y, x)[2] = 0;
        }
        cv::imshow("scan1", scanImg);
        cv::waitKey(20);

    }

private:

};

int main(int argc, char ** argv)
{
    lcm::LCM lcm;
    if(!lcm.good())
        return 1;
    Handler handlerObj;
    lcm.subscribe("/scan", &Handler::handleMessage, &handlerObj);
    while(0 == lcm.handle());
    return 0;
}
