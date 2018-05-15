#include "leflayerinfo.h"

LEFLayerInfo::LEFLayerInfo() :
	m_pitch_x(0),
	m_pitch_y(0)
{
}

void LEFLayerInfo::setName(string s)
{
	m_name = s;
}

void LEFLayerInfo::setType(string s)
{
	m_type = s;
}

void LEFLayerInfo::setPitch(double i, double j)
{
	m_pitch_x = i;
	m_pitch_y = j;
}

string LEFLayerInfo::getName()
{
	return m_name;
}

string LEFLayerInfo::getType()
{
	return m_type;
}

pair<double,double> LEFLayerInfo::getPitch()
{
	return pair<double,double>(m_pitch_x, m_pitch_y);
}
