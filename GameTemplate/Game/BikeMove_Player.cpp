#include "stdafx.h"
#include "BikeMove_Player.h"
#include "character/CharacterController.h"
#include "GameTime.h"
#include "Goal.h"
#include "PhysicsGhostObject.h"

BikeMove_Player::BikeMove_Player()
{
	m_bikecontroller = new BikeController();
	
}


BikeMove_Player::~BikeMove_Player()
{
	delete m_bikecontroller;
}

void BikeMove_Player::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{

	if (m_CharaConInitFlag == false)
	{
		//�L�����N�^�[�R���g���[���[�̏�����
		m_charaCon.Init(
		   45.0f,           //���a
		   100.0f,          //����
		   position
		);
		m_CharaConInitFlag = true;
	}
	
	   
		//�J�����̑O���������擾
		CVector3 cameraForward = g_camera3D.GetForward();

		//XZ���ʂł̑O�������A�E�����ɕϊ�����B
		cameraForward.y = 0.0f;
		cameraForward.Normalize();

		
			if (g_pad[0].IsPress(enButtonA))
			{
				//�����x���v�Z
				m_moveDirectionF = cameraForward;

				accel = m_bikecontroller->BikeAccel(m_moveDirectionF, accelnum);

			}
			else {
				accel = CVector3::Zero();
			}
		
		
		movespeed += accel;
		//���C�W������Z
		movespeed *= friction;
		//m_finishspeed = movespeed;
		//�ړ����x���v�Z
		
			position += movespeed;
	
		if (movespeed.LengthSq() >= 300.0f * 300.0f) {
			movespeed.Normalize();
			movespeed *= 300.0f;
		}

		//��]����
		//���X�e�B�b�N�Ńv���C���[����]
		CVector3 stick; //Y����]�p
		CVector3 stickyokokaitenn; //Z����]�p
		CQuaternion qRot = CQuaternion::Identity();  //Y����]�p

		stick.x = g_pad[0].GetLStickXF();
		stickyokokaitenn.x = g_pad[0].GetLStickXF();
		//�v���C���[�̑O�x�N�g���Ɛi�s�����̓��ς����߂�
		CVector3 playermae = { 0, 0, 1 };
		CVector3 sinkouhoukou = g_camera3D.GetForward();

		//���ς��v�Z
		float angle = m_bikecontroller->NaisekiTheata(playermae, sinkouhoukou);
		//�O�ς��v�Z

		CVector3 playerjiku;
		playerjiku = m_bikecontroller->KatamukiJiku(playermae, sinkouhoukou);

		if (playerjiku.Length() > 0.001f)
		{
			//�o�C�N��i�s�����Ɍ����邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
			qRot.SetRotation(playerjiku, angle);
			//�o�C�N���X���邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
			rotation.SetRotation(CVector3::AxisZ(), stickyokokaitenn.x * -1.0f);
		}
		rotation.Multiply(qRot, rotation);

	
		//�L�����N�^�[�R���g���[���[�̍X�V
		if (m_CharaConInitFlag == true)
		{
			position =  m_charaCon.Execute( movespeed, 
				//1.0f / 60.0f 
				GameTimeIns().GetFrameDeltaTime()
				);
		}
	
	//�S�[�X�g�I�u�W�F�N�g�Ƃ̓����蔻��
		if ( m_goal != nullptr) {

			g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject)
				{

					if (m_goal->GetGoalPoint().IsSelf(contactObject) == true) {
						Syukaihantei = true;
						if (Syukaihantei == true)
						{
							m_game->SyuukaiCount();
						}
						if (m_game->GetFinishHantei() == 4)
						{
							m_game->ChangeFinishFlag();
						}
					}
				});
		}
}