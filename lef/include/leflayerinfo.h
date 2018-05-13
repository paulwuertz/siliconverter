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
	void setPitch(double i);

	string getName();
	string getType();
	double getPitch();

private:
	string m_name;
	string m_type;
	double m_pitch;
};

#endif // LEFLAYERINFO_H
