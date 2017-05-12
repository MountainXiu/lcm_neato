#include <iostream>
#include <boost/asio/io_service.hpp>
#include <lcmtypes/lidar/lidar_t.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <lcm/lcm-cpp.hpp>
#include <time.h>

int main(int argc, char ** argv)
{
    struct timeval ts;
    std::string port = "/dev/ttyUSB0";
    int baud_rate = 115200;
    boost::asio::io_service io;
    boost::asio::serial_port serial(io, port);
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));

    lcm::LCM lcm;
    if(!lcm.good())
        return 1;

    lidar::lidar_t scan = lidar::lidar_t();
    int index;
    uint8_t start_count = 0;
    boost::array<uint8_t, 1980> raw_bytes;
    while(1){
        boost::asio::read(serial, boost::asio::buffer(&raw_bytes[start_count], 1));
        if(start_count == 0){
            if(raw_bytes[start_count] == 0xFA){
                start_count = 1;
            }
        } else if (start_count == 1){
            if(raw_bytes[start_count] == 0xA0){
                start_count = 0;

                boost::asio::read(serial, boost::asio::buffer(&raw_bytes[2], 1978));
                scan.angle_min = 0.0;
                scan.angle_max = 2.0*M_PI;
                scan.range_min = 0.06;
                scan.range_max = 5.0;
                scan.num_ranges = 360;
                scan.ranges.resize(scan.num_ranges);
                scan.intensities.resize(scan.num_ranges);

                //read data in sets of 4
                for(uint16_t i = 0; i < raw_bytes.size(); i=i+22){
                    if(raw_bytes[i] == 0xFA && raw_bytes[i+1] == (0xA0+i/22)){
                        for(uint16_t j = i+4; j < i+20; j=j+4){
                            index = (4*i)/22 + (j-i-4)/4;
                            uint8_t byte0 = raw_bytes[j];
                            uint8_t byte1 = raw_bytes[j+1];
                            uint8_t byte2 = raw_bytes[j+2];
                            uint8_t byte3 = raw_bytes[j+3];

                            uint16_t range = ((byte1 & 0x3f) << 8) + byte0;
                            uint16_t intensity = (byte3 << 8) + byte2;
                            scan.ranges[index] = range;
                            scan.intensities[index] = intensity;
//                            std::cout << range << " " << intensity << std::endl;
                        }

                    }
                }
                gettimeofday(&ts, NULL);
                scan.timestamp = ts.tv_sec*1000 + ts.tv_usec/1000;
                std::cout << scan.timestamp << " " << scan.ranges[0] << std::endl;
                lcm.publish("/scan", &scan);
            }
        }
    }
    return 0;
}
