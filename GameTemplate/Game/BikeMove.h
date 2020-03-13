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
	/// <summary>
	/// �o�C�N����Ɏg���B
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	virtual void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction) = 0;

	Game* m_game;
	//CoursePath* m_coursepath;
	/// <summary>
	/// �p�X�ړ��Ɋւ���֐��Ɣz��
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	//Game�̃|�C���^��n��
	void SetGame(Game* game)
	{
		m_game = game;
	}

	int GetsyukaiCount()
	{
		return syukaicount;
	}
	double Syukaihantei = false;
	int syukaicount = 0;
	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n
};

