/*!
 *@brief	�Q�[�����ԁB
 */
#pragma once
class GameTime
{
public:
	GameTime();
	~GameTime();

	static GameTime& GetInstance()
	{
		static GameTime t;
		return t;
	}
	/*!
	 *@brief	1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)�B
	 */
	const float GetFrameDeltaTime() const
	{
		//�Œ�FPS�ɂ���B�ς͗v�����B
		//return 1.0f / 30.0f;
		
	}
	void PushFrameDeltaTime(float deltaTime)
	{

	}
private:
	
};

