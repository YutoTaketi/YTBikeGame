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
	/// �X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// BikeMaster�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetBikeSelect(BikeSelect* bikeselect)
	{
		m_bikeselect = bikeselect;

	}
	/// <summary>
	/// Game�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
	}
private:
	void Render();
	void Draw();

	CVector2 m_Fontpos = CVector2::Zero();   //�t�H���g���W
	CVector4 m_color = CVector4::White();    //�J���[
	CVector2 m_Fontscale = CVector2::One();  //�g�嗦
	CVector2 pivot = CVector2::Zero();       //�s�{�b�g
	float rot = 0.0f;                        //��]

	//���b�v���ŕς��
	CVector2 m_Fontpos2 = CVector2::Zero(); //�t�H���g���W
	CVector4 m_color2 = CVector4::White();   //�J���[
	CVector2 m_Fontscale2 = CVector2::One(); //�g�嗦
	CVector2 pivot2 = CVector2::Zero();      //�s�{�b�g
	float rot2 = 0.0f;                       //��]

	int lapcounter = 1;         //���b�v�J�E���g
	Font* m_font;               //�t�H���g
	Font* m_font2;              //�t�H���g
	BikeSelect* m_bikeselect;   //�o�C�N�Z���N�g�̃|�C���^
	Game* m_game;               //Game�̃|�C���^
};

