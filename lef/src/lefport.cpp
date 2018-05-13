#include "lefport.h"

namespace lef {
	LEFPort::LEFPort()
	{
	}

	LEFLayer* LEFPort::getLayer(string n)
	{
		LEFLayer *ret = NULL;
		for(LEFLayer *l: m_layers)
			if(l->getName()==n)
				ret=l;
		return ret;
	}

	void LEFPort::addLayer(string n)
	{
		m_layers.push_back(new LEFLayer(n));
	}

	bool LEFPort::layerExists(string n)
	{
		for(lef::LEFLayer *layer: m_layers)
			if(layer->getName()==n)
				return true;
		return false;
	}

	vector<string> LEFPort::getLayerNames()
	{
		vector<string> ret;
		for(LEFLayer *l: m_layers) ret.push_back(l->getName());
		return ret;
	}

	vector<LEFLayer*> LEFPort::getLayers()
	{
		return m_layers;
	}
}
