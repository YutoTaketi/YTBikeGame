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
	/// BikeMasterのポインタを渡す。
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
	//選択画面スプライト用
	CVector3 m_position = CVector3::Zero();   //座標
	CVector3 m_scale = CVector3::One();       //スケール
	CQuaternion m_rotation = CQuaternion::Identity(); //回転

	//選択枠スプライト用
	CVector3 m_wakupos = { 300.0f, 170.0f, 0.0f};    //バイク０
	CVector3 m_wakupos2 = { -80.0f, 170.0f, 0.0f };  //バイク１
	CVector3 m_wakupos3 = { 330.0f, -160.0f, 0.0f }; //バイク２
	CVector3 m_wakupos4 = { 0.0f, -160.0f, 0.0f }; //バイク３
	CVector3 m_wakupos5 = { -340.0f, -160.0f, 0.0f }; //バイク４

	int wakuNo = 0;
	int sentakuNo;

	CVector3 m_sentakupos;
	CVector3 m_wakuscale = { 0.6f, 0.5f, 1.0f};
	CQuaternion m_wakurot = CQuaternion::Identity();


	Sprite m_sprite;                             //選択画面スプライト
	Sprite m_sentakuwaku;                        //選択枠のスプライト
	BikeMaster* m_bikemaster = nullptr;          //バイクマスターのポインタ
	Signal* m_signal = nullptr;
	bool m_select = false;                    //セレクトされたかのフラグ
};

