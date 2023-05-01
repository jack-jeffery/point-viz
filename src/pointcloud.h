#ifndef POINTCLOUD_H
#define POINT_CLOUD_H

#include <LASlib/lasreader.hpp>

class PointCloud {
    public:
        PointCloud(const char* filepath);
        float get_max_intensity() const;
        int get_npoints() const;
        void read_points_into_buffer(double* buffer) const;
    private:
        LASreader* las_reader_;
        float max_intensity_;
};

#endif