#pragma once
#include "GameObjectManager.h"

class Game;
class Goal;
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
	/// 選択されたバイクの番号に変える。
	/// </summary>
	/// <param name="No"></param>
	void SetSentakuNo(int No)
	{
		m_bikesentakuNo = No;
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
	/// Goalのポインタを渡す。
	/// </summary>
	/// <param name="goal"></param>
	void SetGoal(Goal* goal)
	{
		m_goal = goal;
	}
	
private:
	void Render();
	void Draw();
	GameCamera* gamecamera = nullptr;   //ゲームカメラのポインタ
	AlphaBike* alphabike = nullptr;     //アルファバイクのポインタ
	BetaBike* betabike = nullptr;       //ベータバイクのポインタ
	GammaBike* gammabike = nullptr;     //ガンマバイクのポインタ
	DeltaBike* deltabike = nullptr;     //デルタバイクのポインタ
	EpsilonBike* epsilonbike = nullptr;//イプシロンバイクのポインタ
	Goal* m_goal = nullptr;             //Goalのポインタ
	
	int m_bikesentakuNo;          //バイクの選択番号
	bool m_bikeSetFlag = false;   //必要なバイクが生成されたかのフラグ
	Game* m_game;                 //Gameのポインタ

	std::map<int, Point*> m_pointList;  //ポイント構造体の配列
	Point* m_point;                  //ポイントの構造体のポインタ、現在の目的地
};

