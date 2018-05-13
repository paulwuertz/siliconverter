#include "leflayer.h"

namespace lef {
	string LEFLayer::getName()
	{
		return m_name;
	}

	vector<rect_t> LEFLayer::getRects()
	{
		return m_rects;
	}

	LEFLayer::LEFLayer(string n) :
		m_name(n)
	{
	}

	void LEFLayer::addRectangle(double x, double y, double w, double h)
	{
		rect_t obj;
		obj.x = x;
		obj.y = y;
		obj.w = w;
		obj.h = h;
		m_rects.push_back(obj);
	}
}
