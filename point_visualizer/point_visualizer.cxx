#include <iostream>

#include <lasreader.hpp>

int main() {
    std::cout << "Hello World!" << std::endl;
    LASreadOpener las_read_opener;
    las_read_opener.set_file_name("old/MLN1-1100_2_MLSPCD_20230119_fc48_sweep_272.laz");
    // las_read_opener.set_file_name("/media/jack/Cordel_JJ/Nextcore Customer Support/NSD-419/Exports/Apr-03 000844_deci.laz");
    LASreader *las_reader = las_read_opener.open();

    if (!las_reader)
    {
        std::cerr << "Error opening LAS file" << std::endl;
        return 1;
    }
    std::cout << las_reader->npoints << std::endl;
}