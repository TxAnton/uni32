#include "interpolator.h"

Interpolator::Interpolator()
{

}

Interpolator::Interpolator(std::vector<std::pair<double, double> > &points)
{
    this->points = points;
    std::sort(points.begin(),points.end(),Interpolator::_points_x_cmp);
}

double Interpolator::f(double x)
{
    auto n = this->points.size();
    double result = 0;
    for (int i = 0; i < n; i++) {
        double term = this->points[i].second;
        for (int j = 0; j < n; j++) {
            if (j != i) term *= (x - this->points[j].first) / (this->points[i].first - this->points[j].first);
        }
        result += term;
    }
    return result;
}

double Interpolator::MinX()
{
    if(points.empty())return 0.0;
    return points.front().first;
}

double Interpolator::MaxX()
{
    if(points.empty())return 0.0;
    return points.back().first;
}

int Interpolator::_points_x_cmp(const std::pair<double, double> &a, const std::pair<double, double> &b)
{
    a.first < b.first;
}
