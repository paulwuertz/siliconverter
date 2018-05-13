#include "lefvia.h"

namespace lef {
	LEFVia::LEFVia(string s) :
		m_recentLayer(NULL),
		m_x1(0),
		m_x2(0),
		m_y1(0),
		m_y2(0)
	{
		m_name = s;
	}

	double LEFVia::x(){
		return m_x1;
	}

	double LEFVia::y()
	{
		return m_y1;
	}

	double LEFVia::width()
	{
		return m_x2-m_x1;
	}

	double LEFVia::height()
	{
		return m_y2-m_y1;
	}

	string LEFVia::getName()
	{
		return m_name;
	}

	vector<LEFLayer*> LEFVia::getLayers()
	{
		return m_layers;
	}

	void LEFVia::addLayer(string n)
	{
		m_recentLayer = new LEFLayer(n);
		m_layers.push_back(m_recentLayer);
	}

	void LEFVia::addRect(double x1, double y1, double x2, double y2)
	{
		if(m_x1 > x1) m_x1 = x1;
		if(m_y1 > y1) m_y1 = y1;
		if(m_x2 < x2) m_x2 = x2;
		if(m_y2 < y2) m_y2 = y2;
		if(m_recentLayer) {
			m_recentLayer->addRectangle(x1,y1,x2,y2);
		}
	}
}
