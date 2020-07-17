#pragma once
#include "IGameObject.h"
#include <vector>


//ポストエフェクト関連
#include "graphics/RenderTarget.h"
#include "graphics/ShadowMap.h"
#include "graphics/Sprite.h"
#include "graphics/SkinModel.h"
//#include "graphics/ShadowMap.h"

class GameObjectManager
{
public:
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	template<class T>
	 T* NewGO()
	{
		//インスタンスを生成する。
		T* newObj = new T;
		//生成したインスタンスを可変長配列
		m_goList.push_back(newObj);
		return newObj;
	}
	 /// <summary>
	 /// /ゲームオブジェクトをリストから削除する。
	 /// </summary>
	 /// <param name="go"></param>
	void DeleteGameObject(IGameObject* go)
	{
      //引数で指定されたオブジェクトを検索
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			  if (*it == go) {
				//見つかったのでリストから削除
				//delete* it;
				//m_goList.erase(it);
				//インスタンス自体も削除
				//delete go;
				//削除できたので終わり
				//削除リクエストを送る。
				go->RequestDelete();
				return;
		      }
	     }
	}
	

	void Draw();
	void Render();

private:
	std::list<IGameObject*> m_goList;
	//GameObjectManager();
	//~GameObjectManager();

	/// <summary>
	/// プリレンダリング
	/// </summary>
	void PreRender();

	/// <summary>
	/// フォワードレンダリング
	/// </summary>
	void ForwordRender();

	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender();

	/// <summary>
	/// レンダリングターゲットの切り替え
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	
	RenderTarget m_mainRenderTarget;                                   //メインレンダリングターゲット。
	D3D11_VIEWPORT m_frameBufferViewports;                             //フレームバッファのビューポート。
	Sprite m_copyMainRtToFrameBufferSprite;                            //メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;   //フレームバァファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;   //フレームバァファのデプスステンシルビュー。
	//ShadowMap m_shadowMap;                                             //シャドウマップ
};

extern GameObjectManager g_goMgr;