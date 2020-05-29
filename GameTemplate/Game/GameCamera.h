#pragma once
#include "GameObjectManager.h"
#include "graphics/Camera.h"

class Player;
class BikeMove_Player;
class AlphaBike;
class BetaBike;
class GammaBike;
class DeltaBike;
class EpsilonBike;
class Game;
class BikeMaster;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	
	void Update();
	void Render();

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	
	/// <summary>
	/// AlphaBike�̃|�C���^��n���B
	/// </summary>
	/// <param name="alphabike"></param>
	void SetBike(AlphaBike* alphabike)
	{
		m_alphabike = alphabike;
	}
	/// <summary>
	/// BetaBike�̃|�C���^��n���B
	/// </summary>
	/// <param name="betabike"></param>
	void SetBike(BetaBike* betabike)
	{
		m_betabike = betabike;
	}
	/// <summary>
	///GammaBike�̃|�C���^��n���B
	/// </summary>
	/// <param name="betabike"></param>
	void SetBike(GammaBike* gammabike)
	{
		m_gammabike = gammabike;
	}
	/// <summary>
	/// DeltaBike�̃|�C���^��n���B
	/// </summary>
	/// <param name="betabike"></param>
	void SetBike(DeltaBike* deltabike)
	{
		m_deltabike = deltabike;
	}

	/// <summary>
	/// EpsilonBike�̃|�C���^�n���B
	/// </summary>
	/// <param name="epsilon"></param>
	void SetBike(EpsilonBike* epsilon)
	{
		m_epsilonbike = epsilon;
	}
	
	/// <summary>
	/// Game�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		///m_bikeMove->SetGame(game);
	}
	/// <summary>
	/// BikeMaster�̃|�C���^��n���B
	/// </summary>
	void SetBikeMaster(BikeMaster* bikemaster)
	{
		m_bikemaster = bikemaster;	
	}
private:
	
	Player* m_player = nullptr;           //�v���C���[�̃|�C���^
	AlphaBike* m_alphabike = nullptr;     //�A���t�@�o�C�N�̃|�C���^
	BetaBike* m_betabike = nullptr;       //�x�[�^�o�C�N�̃|�C���^
	GammaBike* m_gammabike = nullptr;     //�K���}�o�C�N�̃|�C���^
	DeltaBike* m_deltabike = nullptr;     //�f���^�o�C�N�̃|�C���^
	EpsilonBike* m_epsilonbike = nullptr; //�C�v�V�����o�C�N�̃|�C���^
	BikeMove_Player* m_bikemove_Player = nullptr; //�o�C�N���[�u�v���C���[�̃|�C���^

	CVector3 m_position = CVector3::Zero();           //���W
	CVector3 m_target = CVector3::Zero();             //�^�[�Q�b�g
	CVector3 m_toCameraPos = CVector3::Zero();         //�J�������W
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	CVector3 m_finishposition = CVector3::Zero();     //�v�Z��̃J�������W
	
	Game* m_game;                        //Game�̃|�C���^
	BikeMaster* m_bikemaster;            //�o�C�N�}�X�^�[�̃|�C���^
	bool m_PlayerBikeSetFlag = false;    //�I�����ꂽ�o�C�N�̃Z�b�g�t���O
};

