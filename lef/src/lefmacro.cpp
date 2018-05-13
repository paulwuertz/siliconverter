#include "lefmacro.h"

namespace lef {
	LEFMacro::LEFMacro(string n) :
		m_sizeW(0),
		m_sizeH(0),
		m_name(n),
		m_obstructions(new LEFObstruction)
	{
	}

	string LEFMacro::getName()
	{
		return m_name;
	}

	void LEFMacro::addPin(string n)
	{
		m_pins.push_back(new LEFPin(n));
	}

	bool LEFMacro::pinExists(string n)
	{
		for(lef::LEFPin *pin: m_pins)
			if(pin->getName()==n)
				return true;
		return false;
	}

	vector<LEFPin*> LEFMacro::getPins()
	{
		return m_pins;
	}

	LEFPin* LEFMacro::getPin(string name)
  {
		for(LEFPin *p: m_pins)
			if(p->getName()==name)
				return p;
		return NULL;
	}

	vector<string> LEFMacro::getPinNames()
	{
		vector<string> ret;
		for(LEFPin *m: m_pins) ret.push_back(m->getName());
		return ret;
	}

	void LEFMacro::setSize(double w, double h)
	{
		m_sizeW = w;
		m_sizeH = h;
	}

	double LEFMacro::getWidth()
	{
		return m_sizeW;
	}

	double LEFMacro::getHeight()
	{
		return m_sizeH;
	}

	LEFObstruction *LEFMacro::getObstruction()
	{
		return m_obstructions;
	}

	string LEFMacro::getClass()
	{
		return m_class;
	}

	string LEFMacro::getSite()
	{
		return m_site;
	}

	void LEFMacro::setClass(string s)
	{
		m_class = s;
	}

	void LEFMacro::setSite(string s)
	{
		m_site = s;
	}

}
