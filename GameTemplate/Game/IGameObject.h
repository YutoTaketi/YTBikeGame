#pragma once
class IGameObject
{
public:
	/// <summary>
	/// 更新関数
	/// </summary>
	virtual void Update() = 0;
	virtual void Render() = 0;

	/// <summary>
	/// 削除リクエストを行う
	/// </summary>
	void RequestDelete()
	{
		isReqDelete = true;
	}
	/// <summary>
	/// 削除リクエストを受けているか調べる
	/// </summary>
	/// <returns>
	///trueが返ってきたら、リクエストを受けている
	/// </returns>
	bool IsRequestDelete()
	{
		return isReqDelete;
	}
	virtual void Draw(){}
private:
	bool isReqDelete = false;
	//IGameObject();
	//~IGameObject();
};

