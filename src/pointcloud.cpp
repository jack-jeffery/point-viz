#include <iostream>

#include "pointcloud.h"

PointCloud::PointCloud(const char *filepath)
    : las_reader_(nullptr), max_intensity_(0.0f)
{
    LASreadOpener las_read_opener;
    las_read_opener.set_file_name(filepath);
    las_reader_ = las_read_opener.open();

    if (!las_reader_)
    {
        std::cerr << "Error opening LAS file" << std::endl;
    }

    std::cout << las_reader_->get_min_x() << std::endl;
    std::cout << las_reader_->get_min_y() << std::endl;
    std::cout << las_reader_->get_min_z() << std::endl;
}

float PointCloud::get_max_intensity() const
{
    if (!las_reader_)
    {
        std::cerr << "Error: LASreader is not initialized" << std::endl;
        return 0.0f;
    }

    if (max_intensity_ != 0.0f)
    {
        return max_intensity_;
    }

    float max_intensity = 0.0f;

    for (int i = 0; i < las_reader_->npoints; ++i)
    {
        las_reader_->read_point();

        if (las_reader_->point.intensity > max_intensity)
        {
            max_intensity = las_reader_->point.intensity;
        }
    }

    return max_intensity;
}

int PointCloud::get_npoints() const {
    if (!las_reader_)
    {
        return -1;
    }
    return las_reader_->npoints;
}

void PointCloud::read_points_into_buffer(double *buffer) const
{
    if (!las_reader_)
    {
        return;
    }

    float max_intensity = this->get_max_intensity() * 0.2;

    las_reader_->seek(0);
    for (int i = 0; i < las_reader_->npoints; ++i)
    {
        las_reader_->read_point();

        buffer[i * 6] = las_reader_->point.get_x();
        buffer[i * 6 + 1] = las_reader_->point.get_y();
        buffer[i * 6 + 2] = las_reader_->point.get_z();
        
        float set_intensity = las_reader_->point.intensity/max_intensity;
        buffer[i * 6 + 3] = set_intensity;
        buffer[i * 6 + 4] = set_intensity;
        buffer[i * 6 + 5] = set_intensity;
    }
}