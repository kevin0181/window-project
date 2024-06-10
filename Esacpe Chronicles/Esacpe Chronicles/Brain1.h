#pragma once
#pragma once
#include <atlimage.h>

#include "Monster.h"
#include "Collision.h"
#include "Gravity.h"
#include "StageManager.h"

class Brain1 : public Monster {
	int hp;
	CImage brain1_img;
	int imageNum;
	RECT rect;
	bool left;
	MonsterStatus status;
	Gravity gravity;

	LPCTSTR brain1_img_path_L[8] = {
		L"img/monster/brain1_L/brain1_move_1_L.png",
		L"img/monster/brain1_L/brain1_move_2_L.png",
		L"img/monster/brain1_L/brain1_move_3_L.png",
		L"img/monster/brain1_L/brain1_move_4_L.png",
		L"img/monster/brain1_L/brain1_move_5_L.png",
		L"img/monster/brain1_L/brain1_move_6_L.png",
		L"img/monster/brain1_L/brain1_move_7_L.png",
		L"img/monster/brain1_L/brain1_move_8_L.png"
	};

	LPCTSTR brain1_attack_img_path_L[7] = {
		L"img/monster/brain1_L/brain1_attack_1_L.png",
		L"img/monster/brain1_L/brain1_attack_2_L.png",
		L"img/monster/brain1_L/brain1_attack_3_L.png",
		L"img/monster/brain1_L/brain1_attack_4_L.png",
		L"img/monster/brain1_L/brain1_attack_5_L.png",
		L"img/monster/brain1_L/brain1_attack_6_L.png",
		L"img/monster/brain1_L/brain1_attack_7_L.png"
	};

	LPCTSTR brain1_die_img_path_L[5] = {
		L"img/monster/brain1_L/brain1_die_1_L.png",
		L"img/monster/brain1_L/brain1_die_2_L.png",
		L"img/monster/brain1_L/brain1_die_3_L.png",
		L"img/monster/brain1_L/brain1_die_4_L.png",
		L"img/monster/brain1_L/brain1_die_5_L.png"
	};

	LPCTSTR brain1_img_path_R[8] = {
		L"img/monster/brain1_R/brain1_move_1_R.png",
		L"img/monster/brain1_R/brain1_move_2_R.png",
		L"img/monster/brain1_R/brain1_move_3_R.png",
		L"img/monster/brain1_R/brain1_move_4_R.png",
		L"img/monster/brain1_R/brain1_move_5_R.png",
		L"img/monster/brain1_R/brain1_move_6_R.png",
		L"img/monster/brain1_R/brain1_move_7_R.png",
		L"img/monster/brain1_R/brain1_move_8_R.png"
	};

	LPCTSTR brain1_attack_img_path_R[7] = {
		L"img/monster/brain1_R/brain1_attack_1_R.png",
		L"img/monster/brain1_R/brain1_attack_2_R.png",
		L"img/monster/brain1_R/brain1_attack_3_R.png",
		L"img/monster/brain1_R/brain1_attack_4_R.png",
		L"img/monster/brain1_R/brain1_attack_5_R.png",
		L"img/monster/brain1_R/brain1_attack_6_R.png",
		L"img/monster/brain1_R/brain1_attack_7_R.png"
	};

	LPCTSTR brain1_die_img_path_R[5] = {
		L"img/monster/brain1_R/brain1_die_1_R.png",
		L"img/monster/brain1_R/brain1_die_2_R.png",
		L"img/monster/brain1_R/brain1_die_3_R.png",
		L"img/monster/brain1_R/brain1_die_4_R.png",
		L"img/monster/brain1_R/brain1_die_5_R.png"
	};

public:
	Brain1();

	RECT getRect() const; //�浹 üũ�� �� �ʿ��ұ�� �ص�

	void insert() override; // ������ ��(���� �ٲ� ��)�� ����
	void print(HDC& mDC) override;
	void move(StageManager& stageManager) override; // rect�� �����̰� insert�� ȣ���� ������ �ٲ���
	void attack() override;
	RECT& getRect() override {
		return rect;
	}
};

