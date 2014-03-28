#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <string.h>


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

    GuessLabel.initWithString("noms!", "fancy-ipadhd.fnt");
    OldGuessLabel.initWithString("Om Nom Nom NOM!","fancy-ipadhd.fnt");
    
    // position the label on the center of the screen
    GuessLabel.setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - GuessLabel.getContentSize().height));
    
    OldGuessLabel.setPosition(Point(origin.x + visibleSize.width/2,300));
    
    this->addChild(&OldGuessLabel,1);
    // add the label as a child to this layer
    this->addChild(&GuessLabel, 1);

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
    
    LoadResources();

    
    GuessCnt = 0;
    CorrectNumber = rand() % 1000000;
    MakeMagicString();
    ResetGame = false;
    strcpy(CurrGuess, "* * * * * *");
   
    for(int i = 0; i < 5;i++){
        numInCorrectPos[i] = 0;
        numCorrect[i] = 0;
    }
    return true;
}
void Game::LoadResources()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto Title = MenuItemImage::create("Title.png","Title.png",CC_CALLBACK_1(Game::TitleCallback, this));
    auto GameOver = MenuItemImage::create("Game-Over.png","Game-Over.png",CC_CALLBACK_1(Game::GameOverCallback, this));

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
    
    GameOver->cocos2d::Node::setPosition(0,0);
    Title->cocos2d::Node::setPosition(0,0);
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
    
    auto Title1 = Menu::create(Title, NULL);
    GameOverMenu = Menu::create(GameOver,NULL);
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
    
    GameOverMenu->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    Title1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
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
    this->addChild(Title1,2);
    GameOverMenu->retain();
}

bool Game::touchBegin(Touch *touch, Event *event)
{
  
    
    return true;
}


void Game::tick(float dTime)
{
// build last choices string
    char buildstring[180];
    for(int i = 0; i < 180; i++)
        buildstring[i] = 0;
   
    sprintf(buildstring, "%s correct:%i in order:%i\n%s correct:%i in order:%i\n%s correct:%i in order:%i\n%s correct:%i in order:%i\n%s correct:%i in order:%i",PrevGuesses[0],numCorrect[0],numInCorrectPos[0],PrevGuesses[1],numCorrect[1],numInCorrectPos[1],PrevGuesses[2],numCorrect[2],numInCorrectPos[2],PrevGuesses[3],numCorrect[3],numInCorrectPos[3],PrevGuesses[4],numCorrect[4],numInCorrectPos[4]);
    OldGuessLabel.setString(buildstring);
    OldGuessLabel.setScale(0.8f);
    OldGuessLabel.draw();
    
// build current number
    GuessLabel.setString(CurrGuess);
    GuessLabel.draw();
        if ( CurGuessPos > 10) {
            CurGuessPos = 0;
            
            strcpy(PrevGuesses[GuessCnt], CurrGuess);
            ExamineChoice();
            if (std::strcmp(CorrectNumberStr, CurrGuess) == 0) {
                // winnar
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Harm.mp3");
              
                ResetGame = true;
            }
            strcpy(CurrGuess, "* * * * * *");
        //check for last attempt
        if (GuessCnt == 4) {
            // fail
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fail.mp3");
            ResetGame = true;
            this->addChild(GameOverMenu,2);
        } else {
            // not last
            GuessCnt++;
        }
            
            
        if (ResetGame == true ) {
            
            // erase previous attempt
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 14; j++) {
                    PrevGuesses[i][j] = 0;
                }
            }
            
            newGuess();
            GuessCnt = 0;
            CorrectNumber = rand() % 1000000;
            MakeMagicString();
            ResetGame = false;
            strcpy(CurrGuess, "* * * * * *");
            for(int i = 0; i < 5;i++){
                numInCorrectPos[i] = 0;
                numCorrect[i] = 0;
            }

            GuessLabel.setString(CurrGuess);
            GuessLabel.draw();
        }

    }
    

}

void Game::MakeMagicString()
{
    char ToStr[7] = {0,};
    int num = CorrectNumber;
    int hld = 0;
    
    for(int i = 0 ; i < 6;i++)
    {
        hld = num % 10;
        num = num / 10;
        ToStr[5-i] = '0' + hld;
    }
    int k = 0;
    for (int j = 0; j < 12; j++) {
        if (j%2) {
            CorrectNumberStr[j] = ' ';
        }
        else
            CorrectNumberStr[j] = ToStr[k++];
    }
    CorrectNumberStr[11]='\0';
}

void Game::newGuess()
{
    CurGuessPos = 0;
    for(int i = 0; i < 13;i++)
        CurrGuess[i] = 0;
    
    
}

void Game::ExamineChoice()
{
    numInCorrectPos[GuessCnt] = 0;
    numCorrect[GuessCnt] = 0;
    
    for (int i = 0; i < 12; i+=2) {
        if (CorrectNumberStr[i] == CurrGuess[i]) {
            numInCorrectPos[GuessCnt]++;
        }
    }
    //if (CorrectNumberStr[0] == CurrGuess[0]) {
    //    numCorrect++;
    //}
    char test[13];
    strcpy(test, CurrGuess);
    
    for (int i = 0; i < 12; i+=2) {
        for (int j = 0; j <12; j+=2) {
            if (CorrectNumberStr[i] == test[j]) {
                numCorrect[GuessCnt]++;
                test[j]='>';
                j=13;
            }

        }
    }
}
void Game::menuButton1Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '1';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton2Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '2';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton3Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '3';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton4Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '4';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton5Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '5';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");

    
}
void Game::menuButton6Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '6';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
}
void Game::menuButton7Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '7';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
    
}
void Game::menuButton8Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '8';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
   
}
void Game::menuButton9Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '9';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
   
}
void Game::menuButtonASTCallback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '*';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");

}
void Game::menuButton0Callback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '0';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
  
}
void Game::menuButtonPNDCallback(Ref* pSender)
{
    CurrGuess[CurGuessPos++] = '#';
    if (CurGuessPos < 11) {
        CurrGuess[CurGuessPos++] = ' ';
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");
   
}
void Game::TitleCallback(Ref* pSender){
    Menu * noms = (Menu *)pSender;
    noms->Menu::removeFromParent();
}
void Game::GameOverCallback(Ref* pSender){
    GameOverMenu->removeFromParent();
}
void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
