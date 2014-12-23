#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include <opencv2/imgproc/imgproc.hpp>
#include "Minutiae.h"

namespace Filter {

    void filterMinutiae(std::vector<Minutiae>& minutiae);

    double euclideanDistance(int x1, int y1, int x2, int y2);

}

#endif // FILTER_H_INCLUDED
