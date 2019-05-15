
#include "../../GameSystem/DrawManager.h"
class ResultBackGorund
{
public:  
	ResultBackGorund();
	~ResultBackGorund();

	void Initilize();
	void Update();
	void Render();
private:

	System::DrawData m_data;

};