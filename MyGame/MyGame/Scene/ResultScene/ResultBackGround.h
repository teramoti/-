
#include "../../GameSystem/DrawManager.h"
class ResultBackGround
{
public:  
	ResultBackGround();
	~ResultBackGround();

	void Initilize();
	void Update();
	void Render();
private:

	System::DrawData m_data;

};