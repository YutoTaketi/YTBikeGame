/*!
 *@brief	ゲーム時間。
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
	 *@brief	1フレームの経過時間を取得(単位・秒)。
	 */
	const float GetFrameDeltaTime() const
	{
		//固定FPSにする。可変は要検討。
		//return 1.0f / 30.0f;
		
	}
	void PushFrameDeltaTime(float deltaTime)
	{

	}
private:
	
};

