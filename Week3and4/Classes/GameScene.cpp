#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;


Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Hunter.mp3",true);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::touchBegin, this);
    
    getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);
    
    schedule(schedule_selector(Game::tick));
    
    auto btnPND = MenuItemImage::create("Button#.png","Button#.png",CC_CALLBACK_1(Game::menuButtonPNDCallback, this));
    auto btn0 = MenuItemImage::create("Button0.png","Button0.png",CC_CALLBACK_1(Game::menuButton0Callback, this));
    auto btn1 = MenuItemImage::create("Button1.png","Button1.png",CC_CALLBACK_1(Game::menuButton1Callback, this));
    auto btn2 = MenuItemImage::create("Button2.png","Button2.png",CC_CALLBACK_1(Game::menuButton2Callback, this));
    auto btn3 = MenuItemImage::create("Button3.png","Button3.png",CC_CALLBACK_1(Game::menuButton3Callback, this));
    auto btn4 = MenuItemImage::create("Button4.png","Button4.png",CC_CALLBACK_1(Game::menuButton4Callback, this));
    auto btn5 = MenuItemImage::create("Button5.png","Button5.png",CC_CALLBACK_1(Game::menuButton5Callback, this));
    auto btn6 = MenuItemImage::create("Button6.png","Button6.png",CC_CALLBACK_1(Game::menuButton6Callback, this));
    auto btn7 = MenuItemImage::create("Button7.png","Button7.png",CC_CALLBACK_1(Game::menuButton7Callback, this));
    auto btn8 = MenuItemImage::create("Button8.png","Button8.png",CC_CALLBACK_1(Game::menuButton8Callback, this));
    auto btn9 = MenuItemImage::create("Button9.png","Button9.png",CC_CALLBACK_1(Game::menuButton9Callback, this));
    auto btnAST = MenuItemImage::create("ButtonAST.png","ButtonAST.png",CC_CALLBACK_1(Game::menuButtonASTCallback, this));
    
    btn1->cocos2d::Node::setPosition(64, visibleSize.height - 200);
    btn2->cocos2d::Node::setPosition(64 + 128 + 10, visibleSize.height - 200);
    btn3->cocos2d::Node::setPosition(64 + 256 + 20, visibleSize.height - 200);
    btn4->cocos2d::Node::setPosition(64, visibleSize.height - 200 - 128 - 10);
    btn5->cocos2d::Node::setPosition(64 + 128 + 10,  visibleSize.height - 200 - 128 - 10);
    btn6->cocos2d::Node::setPosition(64 + 256 + 20,  visibleSize.height - 200 - 128 - 10);
    btn7->cocos2d::Node::setPosition(64, visibleSize.height - 200 - 256 - 20);
    btn8->cocos2d::Node::setPosition(64 + 128 + 10,  visibleSize.height - 200 - 256 - 20);
    btn9->cocos2d::Node::setPosition(64 + 256 + 20,  visibleSize.height - 200 - 256 - 20);
    btnAST->cocos2d::Node::setPosition(64, visibleSize.height - 200 - 384 - 30);
    btn0->cocos2d::Node::setPosition(64 + 128 + 10,  visibleSize.height - 200 - 384 - 30);
    btnPND->cocos2d::Node::setPosition(64 + 256 + 20,  visibleSize.height - 200 - 384 - 30);
    
    auto menu1 = Menu::create(btn1, NULL);
    auto menu2 = Menu::create(btn2, NULL);
    auto menu3 = Menu::create(btn3, NULL);
    auto menu4 = Menu::create(btn4, NULL);
    auto menu5 = Menu::create(btn5, NULL);
    auto menu6 = Menu::create(btn6, NULL);
    auto menu7 = Menu::create(btn7, NULL);
    auto menu8 = Menu::create(btn8, NULL);
    auto menu9 = Menu::create(btn9, NULL);
    auto menuAST = Menu::create(btnAST, NULL);
    auto menu0 = Menu::create(btn0, NULL);
    auto menuPND = Menu::create(btnPND, NULL);
    

    
    
    menu1->setPosition(Point::ZERO);
    menu2->setPosition(Point::ZERO);
    menu3->setPosition(Point::ZERO);
    menu4->setPosition(Point::ZERO);
    menu5->setPosition(Point::ZERO);
    menu6->setPosition(Point::ZERO);
    menu7->setPosition(Point::ZERO);
    menu8->setPosition(Point::ZERO);
    menu9->setPosition(Point::ZERO);
    menuAST->setPosition(Point::ZERO);
    menu0->setPosition(Point::ZERO);
    menuPND->setPosition(Point::ZERO);
    this->addChild(menu1);
    this->addChild(menu2);
    this->addChild(menu3);
    this->addChild(menu4);
    this->addChild(menu5);
    this->addChild(menu6);
    this->addChild(menu7);
    this->addChild(menu8);
    this->addChild(menu9);
    this->addChild(menuAST);
    this->addChild(menu0);
    this->addChild(menuPND);
    
    
    
    return true;
}

bool Game::touchBegin(Touch *touch, Event *event)
{
    Game::createItem(touch->getLocation());
    
    return true;
}

void Game::createItem(Point p)
{
    auto bballSprite = Sprite::create("basketBall.png");
    
    bballSprite->setPosition(p);
    bballSprite->setScale(.25f);
    
    this->addChild(bballSprite,0);
    
    }
void Game::tick(float dTime)
{
}
void Game::menuButton1Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton2Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton3Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton4Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton5Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton6Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton7Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton8Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton9Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButtonASTCallback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton0Callback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButtonPNDCallback(Ref* pSender)
{
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
