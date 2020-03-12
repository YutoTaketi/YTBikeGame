/*!
 * @brief   �S�[�X�g�I�u�W�F�N�g
 */
#pragma once
#include "BoxCollider.h"
#include "physics/ICollider.h"
 /*!
	  * @brief	�S�[�X�g�I�u�W�F�N�g
	  *@detail
	  * �S�[�X�g�I�u�W�F�N�g�͍��̂����蔲���邠���蔻��̃I�u�W�F�N�g�ł��B
	  * �L�����N�^�[�̃`�F�b�N�|�C���g�ʉߔ���A�N���A����Ȃǂ�
	  * �L�����N�^�[�����蔲����K�v�̂��邠���蔻��Ɏg���܂��B
	  */
class PhysicsGhostObject
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject();
	
	/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
    */
	void Release();																																		

	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	
	/// <summary>
	/// �S�[�X�g�쐬�̋��ʏ���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void CreateCommon(CVector3 pos, CQuaternion rot);

	/// <summary>
	/// �����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g������
	/// </summary>
	/// <param name="ghost">�S�[�X�g�I�u�W�F�N�g</param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	
private:
	
private:
	bool     m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g
	std::unique_ptr<ICollider> m_collider;      //�R���C�_�[
	
	
};

