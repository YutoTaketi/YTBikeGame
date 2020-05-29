#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class BikeMaster;
class BikeSelect : public  IGameObject
{
public:
	BikeSelect();
	~BikeSelect();

	/// <summary>
	/// BikeMasterのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetBikeMaster(BikeMaster* bikemaster)
	{
		m_bikemaster = bikemaster;
		
	}
	/// <summary>
	/// バイクが選択されたかの判定を返す。
	/// </summary>
	/// <returns></returns>
	bool GetSelectFlag()
	{
		return m_select;
	}
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();   //座標
	CVector3 m_scale = CVector3::One();       //スケール
	CQuaternion m_rotation = CQuaternion::Identity(); //回転
	Sprite m_sprite;                             //スプライト
	BikeMaster* m_bikemaster = nullptr;          //バイクマスターのポインタ

	bool m_select = false;                    //セレクトされたかのフラグ
};

