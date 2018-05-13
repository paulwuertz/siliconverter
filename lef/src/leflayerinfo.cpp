#include "leflayerinfo.h"

LEFLayerInfo::LEFLayerInfo() :
	m_pitch(0)
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

void LEFLayerInfo::setPitch(double i)
{
	m_pitch = i;
}

string LEFLayerInfo::getName()
{
	return m_name;
}

string LEFLayerInfo::getType()
{
	return m_type;
}

double LEFLayerInfo::getPitch()
{
	return m_pitch;
}
