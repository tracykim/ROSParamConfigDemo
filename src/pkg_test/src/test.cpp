#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>

template <typename T>T readParam(ros::NodeHandle &n, std::string name);
int main(int argc, char** argv)
{
    ros::init(argc, argv, "param_test");
    //全局命名空间
    ros::NodeHandle n;
    std::string n_arg;
    //n.param<std::string>("n_arg",n_arg,"default_arg1");
    n_arg = readParam<std::string>(n, "n_arg");

    //私有命名空间
    std::string pn_arg;
    ros::NodeHandle pn("~");
    //pn.param<std::string>("pn_arg",pn_arg,"default_arg2");
    pn_arg = readParam<std::string>(pn, "pn_arg");

    std::string config_file;
    //pn.param<std::string>("config_file",config_file,"default_arg3");
    config_file = readParam<std::string>(pn, "config_file");

    //create FileStorage
    cv::FileStorage fs(config_file.c_str(), cv::FileStorage::READ);

    //judge open
    if(!fs.isOpened())
    {
       std::cerr << "ERROR: Wrong path to settings" << std::endl;
       exit(-1);
    }

    //read data
    std::string id, name;
    int age;
    double weight;
    fs["id"] >> id;
    fs["name"] >> name;
    fs["age"] >> age;
    fs["weight"] >> weight;

    ROS_INFO("id:%s, name:%s", id.c_str(), name.c_str());
    ROS_INFO("age:%d, weight:%f", age, weight);

    //close FileStorage
    fs.release();
    return 0;
}

template <typename T>
T readParam(ros::NodeHandle &n, std::string name)
{
    T ans;
    if (n.getParam(name, ans))
    {
        ROS_INFO_STREAM("Loaded " << name << ": " << ans);
    }
    else
    {
        ROS_ERROR_STREAM("Failed to load " << name);
        n.shutdown();
    }
    return ans;
}
