#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <pcl/registration/ndt.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>

using namespace std;


int
main(int argc, char** argv)
{

    /*//点云的旋转
    //创建点云指针
    pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud(new pcl::PointCloud<pcl::PointXYZ>());
    // 加载点云文件
    pcl::io::loadPCDFile("press.pcd", *source_cloud);
    std::cout << "source loaded!" << std::endl;

    *//* 提示: 变换矩阵工作原理 :
    |-------> 变换矩阵列
    | 1 0 0 x |  \
    | 0 1 0 y |   }-> 左边是一个3阶的单位阵(无旋转)
    | 0 0 1 z |  /
    | 0 0 0 1 |    -> 这一行用不到 (这一行保持 0,0,0,1)
    方法一 #1: 使用 Matrix4f
    这个是“手工方法”，可以完美地理解，但容易出错!
    *//*
    Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();

    // 定义一个旋转矩阵 (见 https://en.wikipedia.org/wiki/Rotation_matrix)
    float theta = M_PI / 4; // 弧度角
    transform_1(0, 0) = cos(theta);
    transform_1(0, 1) = -sin(theta);
    transform_1(1, 0) = sin(theta);
    transform_1(1, 1) = cos(theta);
    //(行, 列)

    //在 X 轴上定义一个 2.5 米的平移.
    transform_1(0, 3) = 2.5;//2.5

    //打印变换矩阵
    printf("Method #1: using a Matrix4f\n");
    std::cout << transform_1 << std::endl;

    // 执行变换，并将结果保存在新创建的 transformed_cloud 中
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::transformPointCloud(*source_cloud, *transformed_cloud, transform_1);

    //save
    pcl::io::savePCDFileASCII("press_1.pcd", *transformed_cloud); //将点云保存到PCD文件中*/


    //加载房间的第一次扫描
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("press.pcd", *target_cloud) == -1)
    {
        PCL_ERROR("Couldn't read file press.pcd \n");
        return (-1);
    }
    std::cout << "Loaded " << target_cloud->size() << " data points from press.pcd" << std::endl;

    //创建点云区块 6*6
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_00(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_01(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_02(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_03(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_04(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_05(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_10(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_11(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_12(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_13(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_14(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_15(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_20(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_21(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_22(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_23(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_24(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_25(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_30(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_31(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_32(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_33(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_34(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_35(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_40(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_41(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_42(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_43(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_44(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_45(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_50(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_51(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_52(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_53(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_54(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud_55(new pcl::PointCloud<pcl::PointXYZ>);

    //直通滤波进行区块赋值 x = 0;
    pcl::PassThrough<pcl::PointXYZ> pass_00;
    pass_00.setInputCloud(target_cloud);
    pass_00.setFilterFieldName("x");
    pass_00.setFilterLimits(-40.0,0.0);
    pass_00.filter(*target_cloud_00);
    pass_00.setInputCloud(target_cloud_00);
    pass_00.setFilterFieldName("y");
    pass_00.setFilterLimits(-40.0,0.0);
    pass_00.filter(*target_cloud_00);

    //pcl::io::savePCDFileASCII("target_cloud_00.pcd", *target_cloud_00);

    pcl::PassThrough<pcl::PointXYZ> pass_01;
    pass_01.setInputCloud(target_cloud);
    pass_01.setFilterFieldName("x");
    pass_01.setFilterLimits(0.0,25.0);
    pass_01.filter(*target_cloud_01);
    pass_01.setInputCloud(target_cloud_01);
    pass_01.setFilterFieldName("y");
    pass_01.setFilterLimits(-40.0,0.0);
    pass_01.filter(*target_cloud_01);

    pcl::PassThrough<pcl::PointXYZ> pass_02;
    pass_02.setInputCloud(target_cloud);
    pass_02.setFilterFieldName("x");
    pass_02.setFilterLimits(25.0,50.0);
    pass_02.filter(*target_cloud_02);
    pass_02.setInputCloud(target_cloud_02);
    pass_02.setFilterFieldName("y");
    pass_02.setFilterLimits(-40.0,0.0);
    pass_02.filter(*target_cloud_02);

    pcl::PassThrough<pcl::PointXYZ> pass_03;
    pass_03.setInputCloud(target_cloud);
    pass_03.setFilterFieldName("x");
    pass_03.setFilterLimits(50.0,75.0);
    pass_03.filter(*target_cloud_03);
    pass_03.setInputCloud(target_cloud_03);
    pass_03.setFilterFieldName("y");
    pass_03.setFilterLimits(-40.0,0.0);
    pass_03.filter(*target_cloud_03);

    pcl::PassThrough<pcl::PointXYZ> pass_04;
    pass_04.setInputCloud(target_cloud);
    pass_04.setFilterFieldName("x");
    pass_04.setFilterLimits(75.0,100.0);
    pass_04.filter(*target_cloud_04);
    pass_04.setInputCloud(target_cloud_04);
    pass_04.setFilterFieldName("y");
    pass_04.setFilterLimits(-40.0,0.0);
    pass_04.filter(*target_cloud_04);

    pcl::PassThrough<pcl::PointXYZ> pass_05;
    pass_05.setInputCloud(target_cloud);
    pass_05.setFilterFieldName("x");
    pass_05.setFilterLimits(100.0,140.0);
    pass_05.filter(*target_cloud_05);
    pass_05.setInputCloud(target_cloud_05);
    pass_05.setFilterFieldName("y");
    pass_05.setFilterLimits(-40.0,0.0);
    pass_05.filter(*target_cloud_05);

    //直通滤波进行区块赋值 x = 1;
    pcl::PassThrough<pcl::PointXYZ> pass_10;
    pass_10.setInputCloud(target_cloud);
    pass_10.setFilterFieldName("x");
    pass_10.setFilterLimits(-40.0,0.0);
    pass_10.filter(*target_cloud_10);
    pass_10.setInputCloud(target_cloud_10);
    pass_10.setFilterFieldName("y");
    pass_10.setFilterLimits(0.0,25.0);
    pass_10.filter(*target_cloud_10);

    pcl::PassThrough<pcl::PointXYZ> pass_11;
    pass_11.setInputCloud(target_cloud);
    pass_11.setFilterFieldName("x");
    pass_11.setFilterLimits(0.0,25.0);
    pass_11.filter(*target_cloud_11);
    pass_11.setInputCloud(target_cloud_11);
    pass_11.setFilterFieldName("y");
    pass_11.setFilterLimits(0.0,25.0);
    pass_11.filter(*target_cloud_11);

    //pcl::io::savePCDFileASCII("target_cloud_11.pcd", *target_cloud_11);

    pcl::PassThrough<pcl::PointXYZ> pass_12;
    pass_12.setInputCloud(target_cloud);
    pass_12.setFilterFieldName("x");
    pass_12.setFilterLimits(25.0,50.0);
    pass_12.filter(*target_cloud_12);
    pass_12.setInputCloud(target_cloud_12);
    pass_12.setFilterFieldName("y");
    pass_12.setFilterLimits(0.0,25.0);
    pass_12.filter(*target_cloud_12);

    pcl::PassThrough<pcl::PointXYZ> pass_13;
    pass_13.setInputCloud(target_cloud);
    pass_13.setFilterFieldName("x");
    pass_13.setFilterLimits(50.0,75.0);
    pass_13.filter(*target_cloud_13);
    pass_13.setInputCloud(target_cloud_13);
    pass_13.setFilterFieldName("y");
    pass_13.setFilterLimits(0.0,25.0);
    pass_13.filter(*target_cloud_13);

    pcl::PassThrough<pcl::PointXYZ> pass_14;
    pass_14.setInputCloud(target_cloud);
    pass_14.setFilterFieldName("x");
    pass_14.setFilterLimits(75.0,100.0);
    pass_14.filter(*target_cloud_14);
    pass_14.setInputCloud(target_cloud_14);
    pass_14.setFilterFieldName("y");
    pass_14.setFilterLimits(0.0,25.0);
    pass_14.filter(*target_cloud_14);

    pcl::PassThrough<pcl::PointXYZ> pass_15;
    pass_15.setInputCloud(target_cloud);
    pass_15.setFilterFieldName("x");
    pass_15.setFilterLimits(100.0,140.0);
    pass_15.filter(*target_cloud_15);
    pass_15.setInputCloud(target_cloud_15);
    pass_15.setFilterFieldName("y");
    pass_15.setFilterLimits(0.0,25.0);
    pass_15.filter(*target_cloud_15);

    //直通滤波进行区块赋值 x = 2;
    pcl::PassThrough<pcl::PointXYZ> pass_20;
    pass_20.setInputCloud(target_cloud);
    pass_20.setFilterFieldName("x");
    pass_20.setFilterLimits(-40.0,0.0);
    pass_20.filter(*target_cloud_20);
    pass_20.setInputCloud(target_cloud_20);
    pass_20.setFilterFieldName("y");
    pass_20.setFilterLimits(25.0,50.0);
    pass_20.filter(*target_cloud_20);

    pcl::PassThrough<pcl::PointXYZ> pass_21;
    pass_21.setInputCloud(target_cloud);
    pass_21.setFilterFieldName("x");
    pass_21.setFilterLimits(0.0,25.0);
    pass_21.filter(*target_cloud_21);
    pass_21.setInputCloud(target_cloud_21);
    pass_21.setFilterFieldName("y");
    pass_21.setFilterLimits(25.0,50.0);
    pass_21.filter(*target_cloud_21);

    pcl::PassThrough<pcl::PointXYZ> pass_22;
    pass_22.setInputCloud(target_cloud);
    pass_22.setFilterFieldName("x");
    pass_22.setFilterLimits(25.0,50.0);
    pass_22.filter(*target_cloud_22);
    pass_22.setInputCloud(target_cloud_22);
    pass_22.setFilterFieldName("y");
    pass_22.setFilterLimits(25.0,50.0);
    pass_22.filter(*target_cloud_22);

    pcl::PassThrough<pcl::PointXYZ> pass_23;
    pass_23.setInputCloud(target_cloud);
    pass_23.setFilterFieldName("x");
    pass_23.setFilterLimits(50.0,75.0);
    pass_23.filter(*target_cloud_23);
    pass_23.setInputCloud(target_cloud_23);
    pass_23.setFilterFieldName("y");
    pass_23.setFilterLimits(25.0,50.0);
    pass_23.filter(*target_cloud_23);

    pcl::PassThrough<pcl::PointXYZ> pass_24;
    pass_24.setInputCloud(target_cloud);
    pass_24.setFilterFieldName("x");
    pass_24.setFilterLimits(75.0,100.0);
    pass_24.filter(*target_cloud_24);
    pass_24.setInputCloud(target_cloud_24);
    pass_24.setFilterFieldName("y");
    pass_24.setFilterLimits(25.0,50.0);
    pass_24.filter(*target_cloud_24);

    pcl::PassThrough<pcl::PointXYZ> pass_25;
    pass_25.setInputCloud(target_cloud);
    pass_25.setFilterFieldName("x");
    pass_25.setFilterLimits(100.0,140.0);
    pass_25.filter(*target_cloud_25);
    pass_25.setInputCloud(target_cloud_25);
    pass_25.setFilterFieldName("y");
    pass_25.setFilterLimits(25.0,50.0);
    pass_25.filter(*target_cloud_25);

    //直通滤波进行区块赋值 x = 3;
    pcl::PassThrough<pcl::PointXYZ> pass_30;
    pass_30.setInputCloud(target_cloud);
    pass_30.setFilterFieldName("x");
    pass_30.setFilterLimits(-40.0,0.0);
    pass_30.filter(*target_cloud_30);
    pass_30.setInputCloud(target_cloud_30);
    pass_30.setFilterFieldName("y");
    pass_30.setFilterLimits(50.0,75.0);
    pass_30.filter(*target_cloud_30);

    pcl::PassThrough<pcl::PointXYZ> pass_31;
    pass_31.setInputCloud(target_cloud);
    pass_31.setFilterFieldName("x");
    pass_31.setFilterLimits(0.0,25.0);
    pass_31.filter(*target_cloud_31);
    pass_31.setInputCloud(target_cloud_31);
    pass_31.setFilterFieldName("y");
    pass_31.setFilterLimits(50.0,75.0);
    pass_31.filter(*target_cloud_31);

    pcl::PassThrough<pcl::PointXYZ> pass_32;
    pass_32.setInputCloud(target_cloud);
    pass_32.setFilterFieldName("x");
    pass_32.setFilterLimits(25.0,50.0);
    pass_32.filter(*target_cloud_32);
    pass_32.setInputCloud(target_cloud_32);
    pass_32.setFilterFieldName("y");
    pass_32.setFilterLimits(50.0,75.0);
    pass_32.filter(*target_cloud_32);

    pcl::PassThrough<pcl::PointXYZ> pass_33;
    pass_33.setInputCloud(target_cloud);
    pass_33.setFilterFieldName("x");
    pass_33.setFilterLimits(50.0,75.0);
    pass_33.filter(*target_cloud_33);
    pass_33.setInputCloud(target_cloud_33);
    pass_33.setFilterFieldName("y");
    pass_33.setFilterLimits(50.0,75.0);
    pass_33.filter(*target_cloud_33);

    pcl::PassThrough<pcl::PointXYZ> pass_34;
    pass_34.setInputCloud(target_cloud);
    pass_34.setFilterFieldName("x");
    pass_34.setFilterLimits(75.0,100.0);
    pass_34.filter(*target_cloud_34);
    pass_34.setInputCloud(target_cloud_34);
    pass_34.setFilterFieldName("y");
    pass_34.setFilterLimits(50.0,75.0);
    pass_34.filter(*target_cloud_34);

    pcl::PassThrough<pcl::PointXYZ> pass_35;
    pass_35.setInputCloud(target_cloud);
    pass_35.setFilterFieldName("x");
    pass_35.setFilterLimits(100.0,140.0);
    pass_35.filter(*target_cloud_35);
    pass_35.setInputCloud(target_cloud_35);
    pass_35.setFilterFieldName("y");
    pass_35.setFilterLimits(50.0,75.0);
    pass_35.filter(*target_cloud_35);

    //直通滤波进行区块赋值 x = 4;
    pcl::PassThrough<pcl::PointXYZ> pass_40;
    pass_40.setInputCloud(target_cloud);
    pass_40.setFilterFieldName("x");
    pass_40.setFilterLimits(-40.0,0.0);
    pass_40.filter(*target_cloud_40);
    pass_40.setInputCloud(target_cloud_40);
    pass_40.setFilterFieldName("y");
    pass_40.setFilterLimits(75.0,100.0);
    pass_40.filter(*target_cloud_40);

    pcl::PassThrough<pcl::PointXYZ> pass_41;
    pass_41.setInputCloud(target_cloud);
    pass_41.setFilterFieldName("x");
    pass_41.setFilterLimits(0.0,25.0);
    pass_41.filter(*target_cloud_41);
    pass_41.setInputCloud(target_cloud_41);
    pass_41.setFilterFieldName("y");
    pass_41.setFilterLimits(75.0,100.0);
    pass_41.filter(*target_cloud_41);

    pcl::PassThrough<pcl::PointXYZ> pass_42;
    pass_42.setInputCloud(target_cloud);
    pass_42.setFilterFieldName("x");
    pass_42.setFilterLimits(25.0,50.0);
    pass_42.filter(*target_cloud_42);
    pass_42.setInputCloud(target_cloud_42);
    pass_42.setFilterFieldName("y");
    pass_42.setFilterLimits(75.0,100.0);
    pass_42.filter(*target_cloud_42);

    pcl::PassThrough<pcl::PointXYZ> pass_43;
    pass_43.setInputCloud(target_cloud);
    pass_43.setFilterFieldName("x");
    pass_43.setFilterLimits(50.0,75.0);
    pass_43.filter(*target_cloud_43);
    pass_43.setInputCloud(target_cloud_43);
    pass_43.setFilterFieldName("y");
    pass_43.setFilterLimits(75.0,100.0);
    pass_43.filter(*target_cloud_43);

    pcl::PassThrough<pcl::PointXYZ> pass_44;
    pass_44.setInputCloud(target_cloud);
    pass_44.setFilterFieldName("x");
    pass_44.setFilterLimits(75.0,100.0);
    pass_44.filter(*target_cloud_44);
    pass_44.setInputCloud(target_cloud_44);
    pass_44.setFilterFieldName("y");
    pass_44.setFilterLimits(75.0,100.0);
    pass_44.filter(*target_cloud_44);

    pcl::PassThrough<pcl::PointXYZ> pass_45;
    pass_45.setInputCloud(target_cloud);
    pass_45.setFilterFieldName("x");
    pass_45.setFilterLimits(100.0,140.0);
    pass_45.filter(*target_cloud_45);
    pass_45.setInputCloud(target_cloud_45);
    pass_45.setFilterFieldName("y");
    pass_45.setFilterLimits(75.0,100.0);
    pass_45.filter(*target_cloud_45);

    //直通滤波进行区块赋值 x = 5;
    pcl::PassThrough<pcl::PointXYZ> pass_50;
    pass_50.setInputCloud(target_cloud);
    pass_50.setFilterFieldName("x");
    pass_50.setFilterLimits(-40.0,0.0);
    pass_50.filter(*target_cloud_50);
    pass_50.setInputCloud(target_cloud_50);
    pass_50.setFilterFieldName("y");
    pass_50.setFilterLimits(100.0,140.0);
    pass_50.filter(*target_cloud_50);

    pcl::PassThrough<pcl::PointXYZ> pass_51;
    pass_51.setInputCloud(target_cloud);
    pass_51.setFilterFieldName("x");
    pass_51.setFilterLimits(0.0,25.0);
    pass_51.filter(*target_cloud_51);
    pass_51.setInputCloud(target_cloud_51);
    pass_51.setFilterFieldName("y");
    pass_51.setFilterLimits(100.0,140.0);
    pass_51.filter(*target_cloud_51);

    pcl::PassThrough<pcl::PointXYZ> pass_52;
    pass_52.setInputCloud(target_cloud);
    pass_52.setFilterFieldName("x");
    pass_52.setFilterLimits(25.0,50.0);
    pass_52.filter(*target_cloud_52);
    pass_52.setInputCloud(target_cloud_52);
    pass_52.setFilterFieldName("y");
    pass_52.setFilterLimits(100.0,140.0);
    pass_52.filter(*target_cloud_52);

    pcl::PassThrough<pcl::PointXYZ> pass_53;
    pass_53.setInputCloud(target_cloud);
    pass_53.setFilterFieldName("x");
    pass_53.setFilterLimits(50.0,75.0);
    pass_53.filter(*target_cloud_53);
    pass_53.setInputCloud(target_cloud_53);
    pass_53.setFilterFieldName("y");
    pass_53.setFilterLimits(100.0,140.0);
    pass_53.filter(*target_cloud_53);

    pcl::PassThrough<pcl::PointXYZ> pass_54;
    pass_54.setInputCloud(target_cloud);
    pass_54.setFilterFieldName("x");
    pass_54.setFilterLimits(75.0,100.0);
    pass_54.filter(*target_cloud_54);
    pass_54.setInputCloud(target_cloud_54);
    pass_54.setFilterFieldName("y");
    pass_54.setFilterLimits(100.0,140.0);
    pass_54.filter(*target_cloud_54);

    pcl::PassThrough<pcl::PointXYZ> pass_55;
    pass_55.setInputCloud(target_cloud);
    pass_55.setFilterFieldName("x");
    pass_55.setFilterLimits(100.0,140.0);
    pass_55.filter(*target_cloud_55);
    pass_55.setInputCloud(target_cloud_55);
    pass_55.setFilterFieldName("y");
    pass_55.setFilterLimits(100.0,140.0);
    pass_55.filter(*target_cloud_55);




    //加载从新视角得到的房间的第二次扫描
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("press_1.pcd", *input_cloud) == -1)
    {
        PCL_ERROR("Couldn't read file press_1.pcd \n");
        return (-1);
    }
    std::cout << "Loaded " << input_cloud->size() << " data points from press_1.pcd" << std::endl;
    //将输入的扫描过滤到原始尺寸的大概10%以提高匹配的速度。
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
    approximate_voxel_filter.setLeafSize(0.5, 0.5, 0.5);
    approximate_voxel_filter.setInputCloud(input_cloud);
    approximate_voxel_filter.filter(*filtered_cloud);
    std::cout << "Filtered cloud contains " << filtered_cloud->size()
              << " data points from press_1.pcd" << std::endl;
    //初始化正态分布变换（NDT）
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;
    //设置依赖尺度NDT参数
    //为终止条件设置最小转换差异
    ndt.setTransformationEpsilon(0.01);
    //为More-Thuente线搜索设置最大步长
    ndt.setStepSize(0.1);
    //设置NDT网格结构的分辨率（VoxelGridCovariance）
    ndt.setResolution(1.0);
    //设置匹配迭代的最大次数
    ndt.setMaximumIterations(35);
    // 设置要配准的点云
    ndt.setInputSource(filtered_cloud);
    //设置点云配准目标
    ndt.setInputTarget(target_cloud);
    //设置使用机器人测距法得到的初始对准估计结果
    Eigen::AngleAxisf init_rotation(0.7850, Eigen::Vector3f::UnitZ());
    Eigen::Translation3f init_translation(2.5000, 0, 0);
    Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();
    //计算需要的刚体变换以便将输入的点云匹配到目标点云
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    ndt.align(*output_cloud, init_guess);
    std::cout << "Normal Distributions Transform has converged:" << ndt.hasConverged()
              << " score: " << ndt.getFitnessScore() << std::endl;

    //获取位姿
    Eigen::Matrix4f current_frame_pose = Eigen::Matrix4f::Identity();
    current_frame_pose = ndt.getFinalTransformation();
    std::cout << "当前的位姿为:" << std::endl << current_frame_pose << std::endl;

    //使用创建的变换对未过滤的输入点云进行变换
    pcl::transformPointCloud(*input_cloud, *output_cloud, ndt.getFinalTransformation());
    //保存转换的输入点云
    pcl::io::savePCDFileASCII("press_transformed.pcd", *output_cloud);
/*    // 初始化点云可视化界面
    boost::shared_ptr<pcl::visualization::PCLVisualizer>
            viewer_final(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer_final->setBackgroundColor(0, 0, 0);
    //对目标点云着色（红色）并可视化
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
            target_color(target_cloud, 255, 0, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(target_cloud, target_color, "target cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
                                                   1, "target cloud");
    //对转换后的目标点云着色（绿色）并可视化
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
            output_color(output_cloud, 0, 255, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(output_cloud, output_color, "output cloud");
    viewer_final->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,
                                                   1, "output cloud");
    // 启动可视化
    viewer_final->addCoordinateSystem(1.0);
    viewer_final->initCameraParameters();
    //等待直到可视化窗口关闭。
    while (!viewer_final->wasStopped())
    {
        viewer_final->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
    return (0);*/




}
