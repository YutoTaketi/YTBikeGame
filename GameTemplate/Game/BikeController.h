#pragma once

class BikeController
{
public:
	BikeController();
	~BikeController();

	/// <summary>
	///�o�C�N�̉����x���v�Z
	/// </summary>
	const CVector3 BikeAccel(CVector3 movespeed, float accelnum)const
	{
		CVector3 v = movespeed * accelnum;
		return v;
	}
	//�o�C�N�̉�]����
	//�o�C�N�̑O�x�N�g���A�i�s�����x�N�g����ݒ�
	float BikeTurn(CVector3& mae, CVector3 sinkouhoukou)
	{
		//�i�s�����x�N�g����Y����������
		sinkouhoukou.y = 0.0f;
		//�i�s�����x�N�g���𐳋K��
		sinkouhoukou.Normalize();
		//���ς��v�Z
		float cosTheata = mae.Dot(sinkouhoukou);
		//�Ƃɕϊ�
		float angle = acos(cosTheata);
		//�O�ς��v�Z
		CVector3 kaitenjiku;
		kaitenjiku.Cross(mae, sinkouhoukou);
		kaitenjiku.Normalize();
	}

	/// <summary>
	///
	/// </summary>
	/// <param name="mae"></param>
	/// <param name="sinkouhoukou"></param>
	/// <returns>���ς̃�</returns>
	float NaisekiTheata(CVector3 mae, CVector3 sinkouhoukou)
	{
		//�i�s�����x�N�g����Y����������
		sinkouhoukou.y = 0.0f;
		//�i�s�����x�N�g���𐳋K��
		sinkouhoukou.Normalize();
		//���ς��v�Z
		float cosTheata = mae.Dot(sinkouhoukou);
		//�Ƃɕϊ�
		float angle = acos(cosTheata);
		return angle;
	}

	/// <summary>
	/// �O��
	/// </summary>
	/// <param name="mae"></param>
	/// <param name="sinkouhoukou"></param>
	/// <returns>Z����]�p�̎�</returns>
	const CVector3 KatamukiJiku(CVector3 mae, CVector3 sinkouhoukou)const
	{
		sinkouhoukou.y = 0.0f;
		CVector3 kaitenjiku;
		kaitenjiku.Cross(mae, sinkouhoukou);
		kaitenjiku.Normalize();
		return kaitenjiku;
	}

	
	

	

	

	
};

