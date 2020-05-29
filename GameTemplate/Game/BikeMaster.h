#pragma once
#include "GameObjectManager.h"

class Game;
class Goal;
class BikeMaster : public IGameObject
{
public:
	BikeMaster();
	~BikeMaster();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �p�X�ړ��Ɋւ���֐��Ɣz��
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	/// <summary>
	/// �I�����ꂽ�ԍ����󂯎��B
	/// </summary>
	/// <returns></returns>
	int GetBikeNo()
	{
		return m_bikesentakuNo;
	}
	/// <summary>
	/// �K�v�ȃo�C�N���������ꂽ���̃t���O�̒l��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetbikesetFlag()
	{
		return m_bikeSetFlag;
	}
	/// <summary>
	/// �I�����ꂽ�o�C�N�̔ԍ��ɕς���B
	/// </summary>
	/// <param name="No"></param>
	void SetSentakuNo(int No)
	{
		m_bikesentakuNo = No;
	}
	/// <summary>
	/// Game�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
	}
	/// <summary>
	/// Goal�̃|�C���^��n���B
	/// </summary>
	/// <param name="goal"></param>
	void SetGoal(Goal* goal)
	{
		m_goal = goal;
	}
	
private:
	void Render();
	void Draw();
	GameCamera* gamecamera = nullptr;   //�Q�[���J�����̃|�C���^
	AlphaBike* alphabike = nullptr;     //�A���t�@�o�C�N�̃|�C���^
	BetaBike* betabike = nullptr;       //�x�[�^�o�C�N�̃|�C���^
	GammaBike* gammabike = nullptr;     //�K���}�o�C�N�̃|�C���^
	DeltaBike* deltabike = nullptr;     //�f���^�o�C�N�̃|�C���^
	EpsilonBike* epsilonbike = nullptr;//�C�v�V�����o�C�N�̃|�C���^
	Goal* m_goal = nullptr;             //Goal�̃|�C���^
	
	int m_bikesentakuNo;          //�o�C�N�̑I��ԍ�
	bool m_bikeSetFlag = false;   //�K�v�ȃo�C�N���������ꂽ���̃t���O
	Game* m_game;                 //Game�̃|�C���^

	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n
};

