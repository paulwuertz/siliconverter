#include "lefobstruction.h"

namespace lef {
	LEFObstruction::LEFObstruction()
	{
	}

	bool LEFObstruction::layerExists(string n)
	{
		for(lef::LEFLayer *layer: layers)
			if(layer->getName()==n)
				return true;
		return false;
	}

	vector<LEFLayer*> LEFObstruction::getLayers()
	{
		return layers;
	}

	void LEFObstruction::addLayer(string n)
	{
		layers.push_back(new LEFLayer(n));
	}

	LEFLayer* LEFObstruction::getLayer(string n)
	{
		LEFLayer *ret = NULL;
		for(LEFLayer *l: layers)
			if(l->getName()==n)
				ret=l;
		return ret;
	}
}
