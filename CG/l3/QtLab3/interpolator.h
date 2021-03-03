#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QObject>
#include <algorithm>

class Interpolator
{
public:
    Interpolator();
    Interpolator(std::vector<std::pair<double,double>>& _points);

    void setPoints(std::vector<std::pair<double,double>>& _points);

    double f(double x);


    double MinX();
    double MaxX();



private:
    static int _points_x_cmp(const std::pair<double,double>& a ,const std::pair<double,double>& b);
    std::vector<std::pair<double,double>> points;

};

#endif // INTERPOLATOR_H
