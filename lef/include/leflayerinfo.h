#ifndef LEFLAYERINFO_H
#define LEFLAYERINFO_H

#include <string>

using namespace std;

class LEFLayerInfo
{
public:
	LEFLayerInfo();
	void setName(string s);
	void setType(string s);
	void setPitch(double i, double j);

	string getName();
	string getType();
	pair<double,double> getPitch();

	double minArea;
private:
	string m_name;
	string m_type;
	double m_pitch_x, m_pitch_y;
};

#endif // LEFLAYERINFO_H
