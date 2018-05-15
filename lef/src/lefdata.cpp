#include "lefdata.h"
#include "lefscanner.h"

namespace lef {

	LEFData::LEFData(string filename) :
		lexer(NULL),
		parser(NULL),
		trace_scanning(false),
		trace_parsing(false),
		m_recentLayer(NULL),
		m_recentVia(NULL),
		m_recentMacro(NULL)
	{
		std::ifstream input;
		std::string stdfilename = filename;

		streamname = filename;
		input.open(stdfilename, std::ios::in);

		lexer = new LEFScanner(&input, &std::cout);
		lexer->set_debug(trace_scanning);

		parser = new LEFParser(this);
		parser->set_debug_level(trace_parsing);
		parser->parse();
		input.close();
	}

	void LEFData::saveFile(string filename)
	{
		std::ofstream output;
		std::string stdfilename = filename;

		output.open(stdfilename, std::ios::out);
		output.close();
	}

	bool LEFData::isDefinedMacro(string name)
	{
		for(LEFMacro *m: m_macros)
			if(m->getName()==name)
				return true;
		return false;
	}

	bool LEFData::isDefinedVia(string name)
	{
		for(LEFVia *v: m_vias)
			if(v->getName()==name)
				return true;
		return false;
	}

	vector<LEFMacro*> LEFData::getMacros()
	{
		return m_macros;
	}

	vector<LEFVia*> LEFData::getVias()
	{
		return m_vias;
	}

	LEFMacro* LEFData::getMacro(string n)
	{
		LEFMacro *ret = NULL;
		for(LEFMacro *m: m_macros)
			if(m->getName()==n)
				ret = m;
		return ret;
	}

	LEFScanner *LEFData::getLexer()
	{
		return lexer;
	}

	void LEFData::addViaName(std::string s)
	{
		m_recentVia = new LEFVia(s);
		m_vias.push_back(m_recentVia);
	}

	void LEFData::addViaLayer(std::string s)
	{
		if(m_recentVia) m_recentVia->addLayer(s);
	}

	void LEFData::addViaLayerRectangle(double x1, double y1, double x2, double y2)
	{
		if(m_recentVia) m_recentVia->addRect(x1,y1,x2,y2);
	}

	void LEFData::setMacroSize(double w, double h)
	{
		m_recentMacro->setSize(w,h);
	}

	void LEFData::addMacroName(std::string s)
	{
		m_recentMacro = new LEFMacro(s);
		m_macros.push_back(m_recentMacro);
	}

	void LEFData::addMacroPinName(std::string s)
	{
		recentMacroPinName = s;
		m_recentMacro->addPin(recentMacroPinName);
	}

	void LEFData::setMacroClass(std::string s)
	{
		m_recentMacro->setClass(s);
	}

	void LEFData::setMacroSite(std::string s)
	{
		m_recentMacro->setSite(s);
	}

	void LEFData::addMacroPinPortRectangle(double x1, double y1, double x2, double y2)
	{
		double x = x1;
		double y = y1;
		double w = x2-x1;
		double h = y2-y1;

		lef::LEFPin *pin;
		lef::LEFPort *port;
		lef::LEFLayer *layer;

		if(!m_recentMacro->pinExists(recentMacroPinName))
			m_recentMacro->addPin(recentMacroPinName);

		pin = m_recentMacro->getPin(recentMacroPinName);
		port = pin->getPort();

		if(!port->layerExists(recentMacroPinPortLayer))
			port->addLayer(recentMacroPinPortLayer);

		layer = port->getLayer(recentMacroPinPortLayer);
		layer->addRectangle(x, y, w, h);
		pin->setBoundingBox(x1, y1, x2, y2);
	}

	void LEFData::addMacroPinPortLayer(std::string s)
	{
		lef::LEFPin *pin;
		lef::LEFPort *port;

		recentMacroPinPortLayer = s;
		if(!m_recentMacro->pinExists(recentMacroPinName))
			m_recentMacro->addPin(recentMacroPinName);

		pin = m_recentMacro->getPin(recentMacroPinName);
		port = pin->getPort();
		if(!port->layerExists(recentMacroPinPortLayer))
			port->addLayer(recentMacroPinPortLayer);
	}

	void LEFData::addMacroPinObstructionLayer(std::string s)
	{
		lef::LEFPin *pin;
		lef::LEFPort *port;

		recentMacroPinObstructionLayer = s;
	}

	void LEFData::setSubBitChar(std::string s)
	{
		m_subBitChar = s;
	}

	void LEFData::setDivideChar(std::string s)
	{
		m_divideChar = s;
	}

	string LEFData::getSubBitChar()
	{
		return m_subBitChar;
	}

	string LEFData::getDivideChar()
	{
		return m_divideChar;
	}

	void LEFData::setMacroPinDirection(std::string s)
	{
		LEFPin* pin = m_recentMacro->getPin(recentMacroPinName);
		pin->setDirection(s);
	}

	void LEFData::addMacroPinObstructionRectangle(double x1, double y1, double x2, double y2)
	{
		double x = x1;
		double y = y1;
		double w = x2-x1;
		double h = y2-y1;

		lef::LEFObstruction *obstruction;
		lef::LEFLayer *layer;
		obstruction = m_recentMacro->getObstruction();
		if(!obstruction->layerExists(recentMacroPinPortLayer))
			obstruction->addLayer(recentMacroPinPortLayer);

		layer = obstruction->getLayer(recentMacroPinPortLayer);
		layer->addRectangle(x, y, w, h);
	}

	void LEFData::setBaseUnitMicrons(int i)
	{
		units.databaseLEFconvertFactor = i;
	}

	int LEFData::getBaseUnits()
	{
		return units.databaseLEFconvertFactor;
	}

	void LEFData::setLayerType(std::string s)
	{
		if(m_recentLayer)
			m_recentLayer->setType(s);
	}

	void LEFData::addLayer(std::string s)
	{
		m_recentLayer = new LEFLayerInfo();
		m_layers.push_back(m_recentLayer);
		m_recentLayer->setName(s);
	}

	void LEFData::setLayerPitch(double i)
	{
		if(m_recentLayer)
			m_recentLayer->setPitch(i);
	}

	vector<LEFLayerInfo*> LEFData::getLayers()
	{
		return m_layers;
	}

}
