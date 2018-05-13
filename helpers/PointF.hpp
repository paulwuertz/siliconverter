#ifndef POINTF_
#define POINTF_

class PointF {
  double x_=0,y_=0;
  public:
    PointF();
    PointF(int x_, int y_);
    PointF(double x_, double y_);
    PointF(double x_, int y_);
    PointF(int x_, double y_);

    double x();
    double y();
};

class RectF {
  double x0_,x1_,y0_,y1_;
  public:
    RectF(int, int, int, int);
    RectF(double, double, double , double );
};

#endif
