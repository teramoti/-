#include "../../GameSystem/DrawManager.h"
class ResultRecord
{
public:
	ResultRecord();
	~ResultRecord();

	void Initilize();
	void Update();
	void Render();
private:

	System::DrawData m_data;

	bool m_Flag;
	int m_FlamNum;
};