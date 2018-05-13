#include "PointF.hpp"
#include "defrouteinfo.h"


namespace def {

DEFRouteInfo::DEFRouteInfo()
{

}

void DEFRouteInfo::addPoint(double x, double y)
{
	m_pointList.push_back(PointF(x,y));
}

void DEFRouteInfo::setLayer(string s)
{
	m_layer = s;
}

vector<PointF> DEFRouteInfo::getPoints()
{
	return m_pointList;
}

string DEFRouteInfo::getLayer()
{
	return m_layer;
}

void DEFRouteInfo::setVia(string s)
{
	m_viaName = s;
}

string DEFRouteInfo::getViaName()
{
	return m_viaName;
}

}
