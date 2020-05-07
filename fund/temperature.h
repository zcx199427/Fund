#ifndef _H_TEMPERATURE_H
#define _H_TEMPERATURE_H
#define TEMPERATURETHRES 60 // degree
class Temperature
{
public:
	Temperature();
	~Temperature();
	unsigned int m_unLen;
	float *m_nfPE_TTM;
	float *m_nfPB;
	float m_nfTemperature;
	bool m_bIsHighTemperature;
	void process();
};
#endif // !_H_TEMPERATURE_H
