#pragma once

class BikeController
{
public:
	BikeController();
	~BikeController();

	/// <summary>
	///バイクの加速度を計算
	/// </summary>
	const CVector3 BikeAccel(CVector3 movespeed, float accelnum)const
	{
		CVector3 v = movespeed * accelnum;
		return v;
	}
	//バイクの回転処理
	//バイクの前ベクトル、進行方向ベクトルを設定
	float BikeTurn(CVector3& mae, CVector3 sinkouhoukou)
	{
		//進行方向ベクトルのY成分を除去
		sinkouhoukou.y = 0.0f;
		//進行方向ベクトルを正規化
		sinkouhoukou.Normalize();
		//内積を計算
		float cosTheata = mae.Dot(sinkouhoukou);
		//θに変換
		float angle = acos(cosTheata);
		//外積を計算
		CVector3 kaitenjiku;
		kaitenjiku.Cross(mae, sinkouhoukou);
		kaitenjiku.Normalize();
	}

	/// <summary>
	///
	/// </summary>
	/// <param name="mae"></param>
	/// <param name="sinkouhoukou"></param>
	/// <returns>内積のθ</returns>
	float NaisekiTheata(CVector3 mae, CVector3 sinkouhoukou)
	{
		//進行方向ベクトルのY成分を除去
		sinkouhoukou.y = 0.0f;
		//進行方向ベクトルを正規化
		sinkouhoukou.Normalize();
		//内積を計算
		float cosTheata = mae.Dot(sinkouhoukou);
		//θに変換
		float angle = acos(cosTheata);
		return angle;
	}

	/// <summary>
	/// 外積
	/// </summary>
	/// <param name="mae"></param>
	/// <param name="sinkouhoukou"></param>
	/// <returns>Z軸回転用の軸</returns>
	const CVector3 KatamukiJiku(CVector3 mae, CVector3 sinkouhoukou)const
	{
		sinkouhoukou.y = 0.0f;
		CVector3 kaitenjiku;
		kaitenjiku.Cross(mae, sinkouhoukou);
		kaitenjiku.Normalize();
		return kaitenjiku;
	}

	
	

	

	

	
};

