#pragma once
#include "GameObjectManager.h"

class Game;
class BikeMaster : public IGameObject
{
public:
	BikeMaster();
	~BikeMaster();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// パス移動に関する関数と配列
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	/// <summary>
	/// 選択された番号を受け取る。
	/// </summary>
	/// <returns></returns>
	int GetBikeNo()
	{
		return m_bikesentakuNo;
	}
	/// <summary>
	/// 必要なバイクが生成されたかのフラグの値を返す。
	/// </summary>
	/// <returns></returns>
	bool GetbikesetFlag()
	{
		return m_bikeSetFlag;
	}
	/// <summary>
	/// Gameのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
	}
	/// <summary>
	/// 選択されたバイクの番号に変える。
	/// </summary>
	/// <param name="No"></param>
	void SetSentakuNo(int No)
	{
		m_bikesentakuNo = No;
	}
private:
	void Render();
	void Draw();
	GameCamera* gamecamera = nullptr;
	AlphaBike* alphabike = nullptr;
	BetaBike* betabike = nullptr;
	GammaBike* gammabike = nullptr;
	DeltaBike* deltabike = nullptr;
	EpsilonBike* epsilonbike = nullptr;

	
	int m_bikesentakuNo;          //バイクの選択番号
	bool m_bikeSetFlag = false;   //必要なバイクが生成されたかのフラグ
	Game* m_game;

	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
};

