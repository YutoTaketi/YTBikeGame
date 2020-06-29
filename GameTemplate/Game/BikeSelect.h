#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class BikeMaster;
class Signal;
class BikeSelect : public  IGameObject
{
public:
	BikeSelect();
	~BikeSelect();

	/// <summary>
	/// BikeMaster�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetBikeMaster(BikeMaster* bikemaster)
	{
		m_bikemaster = bikemaster;
		
	}
	void SetSignal(Signal* signal)
	{
		m_signal = signal;
	}

	/// <summary>
	/// �o�C�N���I�����ꂽ���̔����Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetSelectFlag()
	{
		return m_select;
	}
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	//�I����ʃX�v���C�g�p
	CVector3 m_position = CVector3::Zero();   //���W
	CVector3 m_scale = CVector3::One();       //�X�P�[��
	CQuaternion m_rotation = CQuaternion::Identity(); //��]

	//�I��g�X�v���C�g�p
	CVector3 m_wakupos = { 300.0f, 170.0f, 0.0f};    //�o�C�N�O
	CVector3 m_wakupos2 = { -80.0f, 170.0f, 0.0f };  //�o�C�N�P
	CVector3 m_wakupos3 = { 330.0f, -160.0f, 0.0f }; //�o�C�N�Q
	CVector3 m_wakupos4 = { 0.0f, -160.0f, 0.0f }; //�o�C�N�R
	CVector3 m_wakupos5 = { -340.0f, -160.0f, 0.0f }; //�o�C�N�S

	int wakuNo = 0;
	int sentakuNo;

	CVector3 m_sentakupos;
	CVector3 m_wakuscale = { 0.6f, 0.5f, 1.0f};
	CQuaternion m_wakurot = CQuaternion::Identity();


	Sprite m_sprite;                             //�I����ʃX�v���C�g
	Sprite m_sentakuwaku;                        //�I��g�̃X�v���C�g
	BikeMaster* m_bikemaster = nullptr;          //�o�C�N�}�X�^�[�̃|�C���^
	Signal* m_signal = nullptr;
	bool m_select = false;                    //�Z���N�g���ꂽ���̃t���O
};

