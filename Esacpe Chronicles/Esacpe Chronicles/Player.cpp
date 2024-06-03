#include"Player.h"

int Player::getCimageSize() const{ 
	switch (status)
	{
	case DEFAULT_R:
		return sizeof(_default_r) / sizeof(_default_r[0]);
		break;
	case DEFAULT_L:
		return sizeof(_default_l) / sizeof(_default_l[0]);
		break;
	case LEFT:
		return sizeof(_left) / sizeof(_left[0]);
		break;
	case RIGHT:
		return sizeof(_right) / sizeof(_right[0]);
		break;
	case JUMP_R:
		return sizeof(_jump_r) / sizeof(_jump_r[0]);
		break;
	case JUMP_L:
		return sizeof(_jump_l) / sizeof(_jump_l[0]);
		break;
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}
}

void Player::print(HDC& mDC) const {
    if (!cImage->IsNull()) {
        cImage->Draw(mDC, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, cImage->GetWidth(), cImage->GetHeight());
    }
    else {
        //MessageBox(NULL, L"��ȿ���� ���� ĳ���� �̹���", L"����", MB_OK);
    }
}

int Player::getImgNum()const {
	return img_num;
}

void Player::setImg(int img_num) {
	this->img_num = img_num;

	
	// main character
	if (img_num >= getCimageSize()) {
		this->img_num = 0;
	}

	cImage->Destroy();

	switch (status)
	{
	case DEFAULT_L:
		cImage->Load(_default_l[this->img_num]);
		break;
	case DEFAULT_R:
		cImage->Load(_default_r[this->img_num]);
		break;
	case LEFT:
		cImage->Load(_left[this->img_num]);
		break;
	case RIGHT:
		cImage->Load(_right[this->img_num]);
		break;
	case JUMP_R:
		cImage->Load(_jump_r[this->img_num]);
		break;
	case JUMP_L:
		cImage->Load(_jump_l[this->img_num]);
		break;
	case ATTACK:
		break;
	case DEFENSE:
		break;
	default:
		break;
	}

}

void Player::setKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case 65: //a
		status = PlayerStatus::LEFT;
		break;
	case 87: //w
		if (status == PlayerStatus::RIGHT || status == PlayerStatus::DEFAULT_R)
			status = PlayerStatus::JUMP_R;

		if (status == PlayerStatus::LEFT || status == PlayerStatus::DEFAULT_L)
			status = PlayerStatus::JUMP_L;
		break;
	case 83: //s
		break;
	case 68: //d
		status = PlayerStatus::RIGHT;
		break;
	default:
		break;
	}
}

void Player::setKeyUp(WPARAM wParam) {
	if (status == PlayerStatus::DEFAULT_R || status == PlayerStatus::RIGHT || status == PlayerStatus::JUMP_R) {
		status = PlayerStatus::DEFAULT_R;
		return;
	}

	if (status == PlayerStatus::DEFAULT_L || status == PlayerStatus::LEFT || status == PlayerStatus::JUMP_L) {
		status = PlayerStatus::DEFAULT_L;
		return;
	}


}

void Player::move() {

}