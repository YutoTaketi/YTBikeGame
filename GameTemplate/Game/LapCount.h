#pragma once
#include "GameObjectManager.h"
#include "Font.h"
//class Font;
class BikeSelect;
class Game;

class LapCount : public IGameObject
{
public:
	LapCount();
	~LapCount();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
	/// <summary>
	/// BikeMasterのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetBikeSelect(BikeSelect* bikeselect)
	{
		m_bikeselect = bikeselect;

	}
	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
	}
private:
	void Render();
	void Draw();

	CVector2 m_Fontpos = CVector2::Zero();   //フォント座標
	CVector4 m_color = CVector4::White();    //カラー
	CVector2 m_Fontscale = CVector2::One();  //拡大率
	CVector2 pivot = CVector2::Zero();       //ピボット
	float rot = 0.0f;                        //回転

	//ラップ数で変わる
	CVector2 m_Fontpos2 = CVector2::Zero(); //フォント座標
	CVector4 m_color2 = CVector4::White();   //カラー
	CVector2 m_Fontscale2 = CVector2::One(); //拡大率
	CVector2 pivot2 = CVector2::Zero();      //ピボット
	float rot2 = 0.0f;                       //回転

	int lapcounter = 1;         //ラップカウント
	Font* m_font;               //フォント
	Font* m_font2;              //フォント
	BikeSelect* m_bikeselect;   //バイクセレクトのポインタ
	Game* m_game;               //Gameのポインタ
};

