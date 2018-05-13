#include "PointF.hpp"

PointF::PointF(int x, int y){
  x_ = (double) x;
  y_ = (double) y;
}
PointF::PointF(double x, int y){
  x_ = x;
  y_ = (double) y;
}
PointF::PointF(int x, double y){
  x_ = (double) x;
  y_ = y;
}
PointF::PointF(double x, double y){
  x_ = x;
  y_ = y;
}

double PointF::x(){
  return x_;
}

double PointF::y(){
  return y_;
}

RectF::RectF(int x0, int x1,int y0, int y1){
  x0_ = double(x0);
  x1_ = double(x1);
  y0_ = double(y0);
  y1_ = double(y1);
}

RectF::RectF(double x0, double x1,double y0, double y1){
  x0_ = x0;
  x1_ = x1;
  y0_ = y0;
  y1_ = y1;
}
