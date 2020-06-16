#pragma once

class Game;
class Goal;
class CharacterController;
struct Point {
	CVector3 s_position;
	int s_number;
};
class BikeMove
{
public:
	BikeMove();
	~BikeMove();
	/// <summary>
	/// バイク制御に使う。
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	virtual void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction) = 0;

	Game* m_game;
	Goal* m_goal = nullptr;

	//CoursePath* m_coursepath;
	/// <summary>
	/// パス移動に関する関数と配列
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	//Gameのポインタを渡す
	void SetGame(Game* game)
	{
		m_game = game;
	}
	/// <summary>
	/// Goalのポインタをセットする
	/// </summary>
	/// <param name="goal"></param>
	void SetGoal(Goal* goal)
	{
		m_goal = goal;
	}
	/// <summary>
	/// 周回カウントを返す
	/// </summary>
	/// <returns></returns>
	int GetsyukaiCount()
	{
		return syukaicount;
	}

	
	double Syukaihantei = false;          //周回判定
	int syukaicount = 0;                 //周回カウント
	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
};

