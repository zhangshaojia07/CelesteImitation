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

#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene(bool isReloadBgmNeed)
{
	if (isReloadBgmNeed) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/menu_levelselect_moon.wav", true);
	}
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("pics/bg_celeste.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	this->addChild(background, -1);

	auto press_c = Sprite::create("pics/press_c.png");
	press_c->setPosition(Vec2(1800, 120));
	press_c->setOpacity(0);
	press_c->runAction(FadeIn::create(0.8f));
	this->addChild(press_c, 2);

	auto mount = Sprite::create("pics/mountain.png");
	mount->setPosition(Vec2(960, 650));
	mount->setOpacity(0);
	mount->runAction(FadeIn::create(0.8f));
	this->addChild(mount, 1);

	auto text = Sprite::create("pics/celeste_text.png");
	text->setPosition(Vec2(960, 130));
	text->setAnchorPoint(Vec2(0.5, 0));
	text->setOpacity(0);
	text->runAction(FadeIn::create(0.8f));
	this->addChild(text, 1);

	auto textReflection = Sprite::create("pics/celeste_text.png");
	textReflection->setPosition(Vec2(960, 130));
	textReflection->setAnchorPoint(Vec2(0.5, 0));
	textReflection->setScaleY(-1);
	textReflection->setOpacity(0);
	textReflection->runAction(FadeTo::create(0.8f, 100));
	auto effect = Waves::create(15, Size(15, 15), 5, 30.0f, false, true);
	auto layerBaseGrid = NodeGrid::create();
	layerBaseGrid->addChild(textReflection, 1);
	layerBaseGrid->runAction(RepeatForever::create(effect));
	this->addChild(layerBaseGrid, 1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
		{
			if (keyCode == EventKeyboard::KeyCode::KEY_C) {
				SimpleAudioEngine::getInstance()->playEffect("music/change_scene.wav",false,1,0,0.3);
				auto targetScene = MainMenu::createScene(false);
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, targetScene));
			}
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
