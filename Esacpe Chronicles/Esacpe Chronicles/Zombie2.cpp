#include "Zombie2.h"

using namespace std;

//srand(time(nullptr));

Zombie2::Zombie2() : Monster() {
	hp = 500; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { 1000, 300, 1300, 600 };
	left = false;
	status = MOVE_;
}

RECT Zombie2::getRect() const {
	return rect;
}

void Zombie2::insert() {
	if (!zombie2_img.IsNull()) {
		zombie2_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie2_img.Load(zombie2_img_path_L[imageNum]);
			break;
		case ATTACK_:
			zombie2_img.Load(zombie2_attack_img_path_L[imageNum]);
			break;
		case DIE_:
			zombie2_img.Load(zombie2_die_img_path_L[imageNum]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie2_img.Load(zombie2_img_path_R[imageNum]);
			break;
		case ATTACK_:
			zombie2_img.Load(zombie2_attack_img_path_R[imageNum]);
			break;
		case DIE_:
			zombie2_img.Load(zombie2_die_img_path_R[imageNum]);
			break;
		}
	}
}

void Zombie2::print(HDC& mDC) {
	if (!zombie2_img.IsNull() && (hp != 0 || imageNum != 5)) {
		zombie2_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie2_img.GetWidth(), zombie2_img.GetHeight());
	}
}

void Zombie2::move(StageManager& stageManager, RECT Rect) {
	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager.blocks_stage1))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 5)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 7)
			imageNum = 0;

		if (CheckClientRect(Rect, rect))
			left = !left;
	}
			  break;
	case ATTACK_:
		if (imageNum == 4)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 5)
			zombie2_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 5)
		insert();
}

void Zombie2::attack() {
	
}
