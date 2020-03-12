/*!
 * @brief   ゴーストオブジェクト
 */
#pragma once
#include "BoxCollider.h"
#include "physics/ICollider.h"
 /*!
	  * @brief	ゴーストオブジェクト
	  *@detail
	  * ゴーストオブジェクトは剛体がすり抜けるあたり判定のオブジェクトです。
	  * キャラクターのチェックポイント通過判定、クリア判定などの
	  * キャラクターがすり抜ける必要のあるあたり判定に使えます。
	  */
class PhysicsGhostObject
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject();
	
	/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでゴーストオブジェクトを削除したい場合に呼び出してください。
    */
	void Release();																																		

	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	
	/// <summary>
	/// ゴースト作成の共通処理
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void CreateCommon(CVector3 pos, CQuaternion rot);

	/// <summary>
	/// 引数で渡されたゴーストオブジェクトが自分自身が判定
	/// </summary>
	/// <param name="ghost">ゴーストオブジェクト</param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	
private:
	
private:
	bool     m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
	btGhostObject				m_ghostObject;	//!<ゴースト
	std::unique_ptr<ICollider> m_collider;      //コライダー
	
	
};

