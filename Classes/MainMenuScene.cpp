/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* MainMenu::createScene(bool isReloadBgmNeed)
{
	if (isReloadBgmNeed) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/menu_levelselect_moon.wav", true);
	}
	return MainMenu::create();
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("pics/bg2_celeste.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(0, 0);
	this->addChild(background, -1);

	auto pressHint = Sprite::create("pics/press_c_x.png");
	pressHint->setAnchorPoint(Vec2(0, 0));
	pressHint->setPosition(2000, 40);
	auto delay = DelayTime::create(1.0f);
	auto move = MoveTo::create(2.0f, Vec2(1600, 40));
	pressHint->runAction(Sequence::createWithTwoActions(delay, EaseExponentialOut::create(move)));
	this->addChild(pressHint, 2);

	{
		auto func = []() {
			SimpleAudioEngine::getInstance()->playEffect("music/change_scene_2.wav", false, 1, 0, 0.3);
			};
		auto root = Node::create();
		auto things = Node::create();
		things->addChild(Sprite::create("pics/mountain2.png"));
		auto text = OptionsLabel::create("CLIMB", 72);
		text->setPosition(0, -150);
		things->addChild(text, 0, 114);
		root->addChild(things, 0, 514);
		list.emplace_back(root, func);
	}

	{
		auto func = []() {
			SimpleAudioEngine::getInstance()->playEffect("music/i_cant_grow_up_study.wav");
			};
		auto root = Node::create();
		auto things = Node::create();
		things->addChild(Sprite::create("pics/options.png"));
		auto text = OptionsLabel::create("Options", 48);
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setPosition(50, 0);
		things->addChild(text, 0, 114);
		root->addChild(things, 0, 514);
		list.emplace_back(root, func);
	}

	{
		auto func = []() {
			SimpleAudioEngine::getInstance()->playEffect("music/i_cant_grow_up_study.wav");
			};
		auto root = Node::create();
		auto things = Node::create();
		things->addChild(Sprite::create("pics/credits.png"));
		auto text = OptionsLabel::create("Credits", 48);
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setPosition(50, 0);
		things->addChild(text, 0, 114);
		root->addChild(things, 0, 514);
		;		list.emplace_back(root, func);
	}

	{
		auto func = [&]() {
			menuCloseCallback(this);
			};
		auto root = Node::create();
		auto things = Node::create();
		things->addChild(Sprite::create("pics/exit.png"));
		auto text = OptionsLabel::create("Exit", 48);
		text->setAnchorPoint(Vec2(0, 0.5));
		text->setPosition(50, 0);
		things->addChild(text, 0, 114);
		root->addChild(things, 0, 514);
		list.emplace_back(root, func);
	}

	auto slide = Node::create();
	{
		list[0].first->setPosition(333, 794);
		float y = 552;
		for (int i = 1;i < list.size();i++) {
			list[i].first->setPosition(213, y);
			y -= 78;
		}
		for (const auto& i : list) {
			slide->addChild(i.first);
		}
	}
	slide->setPosition(-1920, 0);
	this->addChild(slide, 1);
	slide->runAction(MoveBy::create(0.7f, Vec2(1920, 0)));
	this->scheduleOnce([](float) {
		SimpleAudioEngine::getInstance()->playEffect("music/paging.wav", false, 1, 0, 3);
		}, 0.5f,"paging_sound_effect");


	ticker = TickSender::createWithParas(this, 0.15f);
#define UPD_TICKER ticker->changeTarget((OptionsLabel*)list[index].first->getChildByTag(514)->getChildByTag(114))
	UPD_TICKER;
	auto listener = EventListenerKeyboard::create();
	auto actBack = [](Node* things) {
		things->stopAllActions();
		things->runAction(MoveTo::create(0.1f, Vec2::ZERO));
		};

	auto actForth = [](Node* things) {
		things->stopAllActions();
		things->runAction(MoveTo::create(0.1f, Vec2(31, 0)));
		};

	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_X:
			{
				auto targetScene = HelloWorld::createScene(false);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, targetScene));
			}break;
			case EventKeyboard::KeyCode::KEY_C:
				list[index].second();
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				SimpleAudioEngine::getInstance()->playEffect("music/click.wav",false,1,0,10);
				if (index) actBack(list[index].first->getChildByTag(514));
				index = (index == 0 ? list.size() - 1 : index - 1);
				if (index) actForth(list[index].first->getChildByTag(514));
				UPD_TICKER;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				SimpleAudioEngine::getInstance()->playEffect("music/click.wav",false,1,0,10);
				if (index) actBack(list[index].first->getChildByTag(514));
				index = (index == list.size() - 1 ? 0 : index + 1);
				if (index) actForth(list[index].first->getChildByTag(514));
				UPD_TICKER;
				break;
			default:
				break;
			}
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}