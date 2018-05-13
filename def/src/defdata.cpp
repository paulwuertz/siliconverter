#include "defdata.h"
#include "defscanner.h"

namespace def {
	DEFData::DEFData(string filename) :
		lexer(NULL),
		parser(NULL),
		trace_scanning(true),
		trace_parsing(true),
		distanceMicrons(false),
		m_BBLowerX(0),
		m_BBLowerY(0),
		m_BBUpperX(0),
		m_BBUpperY(0)
	{
		std::ifstream input;
		std::string stdfilename = filename;

		streamname = filename;
		input.open(stdfilename, std::ios::in);

		lexer = new DEFScanner(&input, &std::cout);
		lexer->set_debug(trace_scanning);

		parser = new DEFParser(this);
		//parser->set_debug_level(trace_parsing);
		parser->parse();
		input.close();
	}

	void DEFData::setAmountComponents(int i)
	{
		amountComponents = i;
	}

	void DEFData::startRoutedInfo(std::string s)
	{
		m_mainRoutes[m_recentNetName] = DEFRouteInfo();
		m_mainRoutes[m_recentNetName].setLayer(s);
	}

	void DEFData::setRoutedInfoVia(std::string s)
	{
		m_mainRoutes[m_recentNetName].setVia(s);
	}

	void DEFData::addRoutedInfoPoint(int x, int y)
	{
		m_lastPoint = PointF(x,y);
		m_mainRoutes[m_recentNetName].addPoint(x,y);
	}

	void DEFData::shiftRoutedInfoPointX(int d)
	{
		m_lastPoint = PointF(d,m_lastPoint.y());
		m_mainRoutes[m_recentNetName].addPoint(d,m_lastPoint.y());
	}

	void DEFData::shiftRoutedInfoPointY(int d)
	{
		m_lastPoint = PointF(m_lastPoint.x(),d);
		m_mainRoutes[m_recentNetName].addPoint(m_lastPoint.x(),d);
	}

	void DEFData::startNewMetalInfo(std::string s)
	{
		m_recentRoutedInfo = DEFRouteInfo();
		m_recentRoutedInfo.setLayer(s);
	}

	void DEFData::setNewMetalInfoVia(std::string s)
	{
		m_recentRoutedInfo.setVia(s);
	}

	void DEFData::storeNewMetalInfo()
	{
		m_secondaryRoutes[m_recentNetName].push_back(m_recentRoutedInfo);
	}

	void DEFData::addNewMetalPoint(int x, int y)
	{
		m_lastPoint = PointF(x,y);
		m_recentRoutedInfo.addPoint(x,y);
	}

	void DEFData::shiftNewMetalPointX(int d)
	{
		m_lastPoint = PointF(d,m_lastPoint.y());
		m_recentRoutedInfo.addPoint(d,m_lastPoint.y());
	}

	void DEFData::shiftNewMetalPointY(int d)
	{
		m_lastPoint = PointF(m_lastPoint.x(),d);
		m_recentRoutedInfo.addPoint(m_lastPoint.x(),d);
	}

	void DEFData::startNetConnection(std::string s)
	{
		string net = s;
		m_netList.push_back(net);
		m_recentNetName = net;
	}

	void DEFData::addToNetConnection(std::string c, std::string p)
	{
	}

	void DEFData::addUsedModuleNames(std::string instance_name, std::string macro_name)
	{
		m_recentModule.macro_name = macro_name;
		m_recentModule.instance_name = instance_name;
	}

	void DEFData::addUsedModulePlacement(double x, double y)
	{
		m_recentModule.x = x;
		m_recentModule.y = y;
	}

	void DEFData::addUsedModuleOrientation(std::string orient)
	{
		m_recentModule.orient = orient;
	}

	void DEFData::addUsedModule()
	{
		m_parsedModules.push_back(m_recentModule);
	}

	void DEFData::addUsedPin()
	{
		m_parsedPins.push_back(m_recentPin);
	}

	DEFScanner *DEFData::getLexer()
	{
		return lexer;
	}

	pins_t DEFData::getPins()
	{
		return m_parsedPins;
	}

	mods_t DEFData::getModules()
	{
		return m_parsedModules;
	}

	void DEFData::setDistanceUnitMicrons(int t)
	{
		distanceMicrons = true;
		distanceMicronsValue = t;
	}

	void DEFData::addPin(std::string s)
	{
		m_recentPin = DEFDataPin();
		m_recentPin.m_name = s;
	}

	void DEFData::setPinPosition(double x, double y)
	{
		m_recentPin.m_x += x;
		m_recentPin.m_y += y;
	}

	void DEFData::setPinArea(double x1, double y1, double x2, double y2)
	{
		m_recentPin.m_w = x2 - x1;
		m_recentPin.m_h = y2 - y1;

		m_recentPin.m_x = x1;
		m_recentPin.m_y = y1;
	}

	void DEFData::setPinLayer(std::string s)
	{
		m_recentPin.m_layer = s;
	}

	int DEFData::getLowerX()
	{
		return m_BBLowerX;
	}

	int DEFData::getLowerY()
	{
		return m_BBLowerY;
	}

	int DEFData::getUpperX()
	{
		return m_BBUpperX;
	}

	int DEFData::getUpperY()
	{
		return m_BBUpperY;
	}

	void DEFData::setDieArea(double x1, double y1, double x2, double y2)
	{
		m_BBLowerX = x1;
		m_BBUpperX = x2;
		m_BBLowerY = y1;
		m_BBUpperY = y2;
	}

	int DEFData::getDistanceUnit()
	{
		return distanceMicronsValue;
	}

	vector<string> DEFData::getNetList()
	{
		return m_netList;
	}

	map<string,DEFRouteInfo> DEFData::getMainRoutes()
	{
		return m_mainRoutes;
	}

	map<string,vector<DEFRouteInfo>> DEFData::getSecondaryRoutes()
	{
		return m_secondaryRoutes;
	}

}
