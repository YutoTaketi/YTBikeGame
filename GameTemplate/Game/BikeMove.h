#pragma once

class Game;
struct Point {
	CVector3 s_position;
	int s_number;
};
class BikeMove
{
public:
	BikeMove();
	~BikeMove();

	virtual void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction) = 0;

	Game* m_game;
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

	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
};

