#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <CCLabelBMFont.h>

using namespace cocos2d;

class Game : public cocos2d::Layer
{
public:
    
    char CurrGuess[13];
    char PrevGuesses[5][14];
    char CorrectNumberStr[13];
    int GuessCnt;
    int CurGuessPos;
    int CorrectNumber;
    bool ResetGame;
    bool GuessUpdated;
    LabelBMFont GuessLabel;
    LabelBMFont OldGuessLabel;
    int GameState;
    Menu * GameOverMenu;
    
    int numInCorrectPos[5];
    int numCorrect[5];
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void newGuess();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void menuButton1Callback(Ref* pSender);
    void menuButton2Callback(Ref* pSender);
    void menuButton3Callback(Ref* pSender);
    void menuButton4Callback(Ref* pSender);
    void menuButton5Callback(Ref* pSender);
    void menuButton6Callback(Ref* pSender);
    void menuButton7Callback(Ref* pSender);
    void menuButton8Callback(Ref* pSender);
    void menuButton9Callback(Ref* pSender);
    void menuButtonASTCallback(Ref* pSender);
    void menuButton0Callback(Ref* pSender);
    void menuButtonPNDCallback(Ref* pSender);
    void TitleCallback(Ref* pSender);
    void GameOverCallback(Ref* pSender);
    void LoadResources();
    
    void tick(float dTime);
    
    void MakeMagicString();
    
    void ExamineChoice();
    
    bool touchBegin(Touch* touch,Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    
};

#endif // __GAME_SCENE_H__
