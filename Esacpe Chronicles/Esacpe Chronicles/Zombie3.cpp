#include "Zombie3.h"
using namespace std;

Zombie3::Zombie3() : Monster() {
	hp = 40; // 나중에 확정되면 바꾸기
	imageNum = 0;
	rect = { rect.left, 300, rect.left+200, 500 };
	left = false;
	status = MOVE_;
}

MonsterStatus Zombie3::getStatus() const {
	return status;
}

void Zombie3::insert() {
	if (!zombie3_img.IsNull()) {
		zombie3_img.Destroy();
	}

	if (left) {
		switch (status) {
		case MOVE_:
			zombie3_img.Load(zombie3_img_path_L[imageNum/5]);
			break;
		case ATTACK_:
			zombie3_img.Load(zombie3_attack_img_path_L[imageNum/5]);
			break;
		case DIE_:
			zombie3_img.Load(zombie3_die_img_path_L[imageNum/5]);
			break;
		}
	}
	else {
		switch (status) {
		case MOVE_:
			zombie3_img.Load(zombie3_img_path_R[imageNum/5]);
			break;
		case ATTACK_:
			zombie3_img.Load(zombie3_attack_img_path_R[imageNum/5]);
			break;
		case DIE_:
			zombie3_img.Load(zombie3_die_img_path_R[imageNum/5]);
			break;
		}
	}
}

void Zombie3::print(const HDC& mDC) {
	if (!zombie3_img.IsNull()) {
		if (attacked) {
			attacked_img.Draw(mDC, rect.left, rect.top - 56, 84, 56, 0, 0, attacked_img.GetWidth(), attacked_img.GetHeight());
			printAttack(mDC, rect);
		}
		zombie3_img.Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, zombie3_img.GetWidth(), zombie3_img.GetHeight());
	}
}

void Zombie3::move(const StageManager& stageManager) {

	//중력
	RECT temprect = rect;
	gravity.UpdatePhysics(rect);

	if (CheckBlockCollision(rect, stageManager))
		rect = temprect;

	//이미지
	if (status != DIE_ || imageNum != 25)
		++imageNum;

	switch (status) {
	case MOVE_: {
		int offset = left ? -4 : 4;
		OffsetRect(&rect, offset, 0);

		if (imageNum == 50)
			imageNum = 0;

		CheckClientRect(stageManager, rect, left);
	}
			  break;
	case ATTACK_:
		if (imageNum == 20)
			imageNum = 0;
		break;
	case DIE_:
		if (imageNum == 25)
			zombie3_img.Destroy();
		break;
	}

	if (status != DIE_ || imageNum != 25)
		insert();
}

bool Zombie3::checkBlock(const StageManager& stageManager) {
	RECT r;
	for (auto& block : stageManager.blocks_stage1) {
		if (IntersectRect(&r, &block.rect, &rect)) {
			if (rect.bottom <= block.rect.top + 20) {
				return true;
			}
		}
	}
	return false;
}

void Zombie3::MonsterPlayerCollision(Player& p) {
	if (status != MonsterStatus::DIE_) {
		RECT intersectRect;
		if (IntersectRect(&intersectRect, &p.getRECT(), &rect)) {
			Collisionplayer(p);
			p.collisionMonster(this);
		}
		else {
			status = MOVE_;
			attacked = false;
		}
		intersectRect = {};
		for (auto it = p.bullets.begin(); it != p.bullets.end(); ) {
			if (IntersectRect(&intersectRect, &it->rect, &rect)) {
				attacked = true;
				if (p.direction == PlayerStatus::RIGHT)
					OffsetRect(&rect, +20, -20);
				else
					OffsetRect(&rect, -20, -20);
				it = p.bullets.erase(it); // 해당 총알, 화살 제거

				hp -= p.power;
				attacksize = p.power;
				if (hp <= 0) {
					status = DIE_;
					imageNum = 0;
				}
			}
			else {
				++it;
			}
		}
	}
}

void Zombie3::Collisionplayer(const Player& p) { //플레이어랑 충돌했을때 몬스터의 대처
	switch (p.status) {
	case ATTACK:
		attacked = true;
		if (p.direction == PlayerStatus::RIGHT)
			OffsetRect(&rect, +20, -20);
		else
			OffsetRect(&rect, -20, -20);

		hp -= p.power;
		attacksize = p.power;
		if (hp <= 0) {
			status = DIE_;
			imageNum = 0;
		}
		break;
	default:
		status = ATTACK_;
		attacked = false;
		break;
	}
}