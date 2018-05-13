#include "lefpin.h"

namespace lef {
	LEFPort* LEFPin::getPort()
	{
		return port;
	}

	LEFPin::LEFPin(string n) :
		port(new LEFPort()),
		m_x1(0),
		m_y1(0),
		m_x2(0),
		m_y2(0),
		m_bbox_set(false),
		m_direction(PIN_INOUT)
	{
		name = n;
	}

	void LEFPin::setDirection(string s)
	{
		if(s=="INPUT")
			m_direction = PIN_INPUT;
		if(s=="INOUT")
			m_direction = PIN_INOUT;
		if(s=="OUTPUT")
			m_direction = PIN_OUTPUT;
	}

	pin_direction LEFPin::getDirection()
	{
		return m_direction;
	}

	void LEFPin::setBoundingBox(double x1, double y1, double x2, double y2)
	{
		if(m_bbox_set) {
			if(x2>m_x2) m_x2 = x2;
			if(y2>m_y2) m_y2 = y2;
			if(x1<m_x1) m_x1 = x1;
			if(y1<m_y1) m_y1 = y1;
		} else {
			m_x2 = x2;
			m_y2 = y2;
			m_x1 = x1;
			m_y1 = y1;
			m_bbox_set = true;
		}
	}

	RectF LEFPin::getBoundingBox()
	{
		return RectF(m_x1,m_y1,m_x2-m_x1,m_y2-m_y1);
	}

	double LEFPin::width()
	{
		return (m_x2-m_x1);
	}

	double LEFPin::height()
	{
		return (m_y2-m_y1);
	}

	PointF LEFPin::getCenter()
	{
		double xp, yp;
		xp = m_x1+(m_x2-m_x1)/2;
		yp = m_y1+(m_y2-m_y1)/2;
		return PointF(xp,yp);
	}

	string LEFPin::getName()
	{
		return name;
	}

	vector<LEFLayer*> LEFPin::getPortLayers()
	{
		return port->getLayers();
	}
}
