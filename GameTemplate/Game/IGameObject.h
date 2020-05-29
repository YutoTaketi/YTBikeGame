#pragma once
class IGameObject
{
public:
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~IGameObject() {}
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	virtual void Update() = 0;
	virtual void Render() = 0;

	/// <summary>
	/// �폜���N�G�X�g���s��
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}
	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�
	/// </summary>
	/// <returns>
	///true���Ԃ��Ă�����A���N�G�X�g���󂯂Ă���
	/// </returns>
	bool IsRequestDelete()
	{
		return isReqDelete;
	}
	virtual void Draw(){}
private:
	bool isReqDelete = false;   //�f���[�g���N�G�X�g�̔���
	//IGameObject();
	//~IGameObject();
};

