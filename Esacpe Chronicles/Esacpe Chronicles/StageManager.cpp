﻿#include "StageManager.h"
#include <stdexcept>
#include "GlobalVariables.h"

#define BLOCK_SIZE 70

void StageManager::setCurrent_stage(STAGE stage) {
	current_stage = stage;
}

void StageManager::setBackground_img(const LPCTSTR path) {
	destroyImg();
	background_img.Load(path);
}

STAGE StageManager::getCurrent_stage() const {
	return current_stage;
}

void StageManager::DrawBackground_img(HDC& mDC, const int& w) {

	if (!background_img.IsNull()) {

		background_img.Draw(mDC, rect.left, rect.top, (rect.right - rect.left) * w, rect.bottom - rect.top, 0, 0, background_img.GetWidth(), background_img.GetHeight()); //이미지 전체 화면

		//if (current_stage == STAGE::STAGE_1) {
			RECT r;
			for (int i = 0; i < blocks_stage1.size(); ++i) { //블럭 그리기
				if (IntersectRect(&r, &viewRect, &blocks_stage1[i].rect)) {
					blocks_stage1[i].print(mDC);
				}
			}
		//}
	}
	else {
		throw std::runtime_error("Background image is not loaded.");
	}
}

void StageManager::setMainBackGround(HDC& mDC, const RECT& rect) {
	if (!startBtnImg.IsNull()) {
		startBtnImg.Draw(mDC, startBtn.left, startBtn.top, 100, 100, 0, 0, startBtnImg.GetWidth(), startBtnImg.GetHeight());
	}
	else {
		throw std::runtime_error("Background image is not loaded.");
	}
}

void StageManager::destroyImg() {
	// 배경 이미지가 로드되어 있으면 파괴
	if (!background_img.IsNull()) {
		background_img.Destroy();
	}
}


void StageManager::setBlock(const int& h_percent, const COLORREF color) { // stageblock 바닥 1번생성!

	blocks_stage1.clear();

	int h = this->viewRect.bottom * h_percent / 100;

	for (int i = 0; i < (game_rect.right / BLOCK_SIZE) - 1; ++i) {
		if(i%35 <3){
			Block block;
			block.color = color;
			block.rect = { (i + 2) * BLOCK_SIZE, 0, (i + 3) * BLOCK_SIZE, BLOCK_SIZE };

			OffsetRect(&block.rect, 0, this->game_rect.bottom / 10 * (9 - (i%35)));
			OffsetRect(&block.rect, 0, -h);
			blocks_stage1.push_back(std::move(block));
		}
		else if (i % 7 != 1 && i % 11 != 1) {
			Block block;
			block.color = color;
			block.rect = { (i + 2) * BLOCK_SIZE, 0, (i + 3) * BLOCK_SIZE, BLOCK_SIZE };
			if(i % 17 < 7){
				OffsetRect(&block.rect, 0, this->game_rect.bottom / 10 * 6);
				OffsetRect(&block.rect, 0, -h);
			}
			else {
				OffsetRect(&block.rect, 0, this->game_rect.bottom / 10 * 5);
				OffsetRect(&block.rect, 0, -h);
			}
			blocks_stage1.push_back(std::move(block));
		}
	}
	
}

void StageManager::setLMBtnDown(LPARAM lParam) {
	POINT mP;
	mP.x = LOWORD(lParam);
	mP.y = HIWORD(lParam);

	if (PtInRect(&startBtn, mP)) {
		setBlock(0, RGB(62, 141, 215)); //block create
		current_stage = STAGE::STAGE_1;
		setBackground_img(background_img_path[0]);

		rect = viewRect;

		for (int i = 0; i < 10; ++i) {// 원하는 개수만큼 반복
			auto slime = std::make_unique<Slime>();
			slime->insert();
			monsters.push_back(std::move(slime));
		}

	}
}

void StageManager::setKeyDown(WPARAM wParam) {
	switch (wParam)
	{
	case VK_RETURN:
		intro_cnt++;
		if (intro_cnt >= 5) {
			current_stage = STAGE::MAIN;
			setBackground_img(main_img_path[2]);
			break;
		}
		setBackground_img(this->intro_img_path[intro_cnt]);
		break;
	default:
		break;
	}
}