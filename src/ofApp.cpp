#include "ofApp.h"

int posRedX, posRedY, redDx, redDy;
int posBlueX, posBlueY, blueDx, blueDy;
int posShimaX, posShimaY, shimaDx, shimaDy;
float scale;

int width, height;
int displayWidth, displayHeight;
bool over;

std::string text;
const std::string menu = "MousePressed:No_Print\nRightClickDragged:Move_RedRectangle\nLeftClickDragged:Move_BlueRectangle\nPressed_key[c]:close/open_menu";

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetBackgroundColor(200, 200, 200);

    posRedX = 100, posRedY = 250;
    redDx = 3, redDy = 3;

    posBlueX = 600, posBlueY = 300;
    blueDx = -5, blueDy = -5;

    posShimaX = 500, posShimaY = 350, scale = 0.5;
    shimaDx = 5, shimaDy = 5;

    width = 100, height = 100;

    displayWidth = ofGetWidth();
    displayHeight = ofGetHeight();

    over = false;

    text = menu;
}

//--------------------------------------------------------------
void ofApp::update()
{
    // x軸の移動
    posRedX += redDx;
    posBlueX += blueDx;
    posShimaX += shimaDx;

    // 赤の正方形
    if (displayWidth - width < posRedX)
    {
        redDx = -6;
    }
    if (posRedX < 0)
    {
        redDx = 3;
    }

    // 青の正方形
    if (displayWidth - width < posBlueX)
    {
        blueDx = -2;
    }
    if (posBlueX < 0)
    {
        blueDx = 5;
    }

    // シマエナガ
    if (displayWidth - scale * 150 < posShimaX)
    {
        shimaDx = -4;
    }
    if (posShimaX < scale * 150)
    {
        shimaDx = 5;
    }

    // y軸の移動
    posRedY += redDy;
    posBlueY += blueDy;
    posShimaY += shimaDy;

    // 赤の正方形
    if (displayHeight - height < posRedY)
    {
        redDy = -7;
    }
    if (posRedY < 0)
    {
        redDy = 3;
    }

    // 青の正方形
    if (displayHeight - height < posBlueY)
    {
        blueDy = -2;
    }
    if (posBlueY < 0)
    {
        blueDy = 5;
    }

    // シマエナガ
    if (displayHeight - scale * 235 < posShimaY)
    {
        shimaDy = -3;
    }
    if (posShimaY < scale * 100)
    {
        shimaDy = 5;
    }

    // 図形が重なったときにbool値を変更
    over = false;
    if (((posBlueX <= posRedX && posRedX <= posBlueX + width) || (posRedX <= posBlueX && posBlueX <= posRedX + width)) && ((posBlueY <= posRedY && posRedY <= posBlueY + height) || (posRedY <= posBlueY && posBlueY <= posRedY + height)))
    {
        over = true;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // マウス押下時に塗りを削除
    (ofGetMousePressed()) ? ofNoFill() : ofFill();

    // 赤の正方形の描画
    (over) ? ofSetColor(0, 255, 0) : ofSetColor(255, 0, 0);
    ofDrawRectangle(posRedX, posRedY, width, height);

    // 青の正方形の描画
    (over)
        ? ofSetColor(0, 255, 0)
        : ofSetColor(0, 0, 255);
    ofDrawRectangle(posBlueX, posBlueY, width, height);

    // シマエナガの描画
    // 羽と尾の描画
    ofSetColor(28, 28, 32);
    ofDrawTriangle(posShimaX - scale * 155, posShimaY + scale * 10, posShimaX - scale * 125, posShimaY - scale * 10, posShimaX - scale * 150, posShimaY + scale * 100);
    ofDrawTriangle(posShimaX + scale * 125, posShimaY - scale * 10, posShimaX + scale * 160, posShimaY + scale * 10, posShimaX + scale * 150, posShimaY + scale * 100);
    ofDrawTriangle(posShimaX, posShimaY + scale * 170, posShimaX + scale * 180, posShimaY + scale * 230, posShimaX + scale * 230, posShimaY + scale * 200);

    // 頭と体の描画
    ofSetColor(255, 255, 255);
    ofDrawEllipse(posShimaX, posShimaY, scale * 250, scale * 200);
    ofDrawEllipse(posShimaX, posShimaY + scale * 80, scale * 300, scale * 310);

    // 目と嘴の描画
    ofSetColor(0, 0, 0);
    ofDrawCircle(posShimaX - scale * 50, posShimaY - scale * 30, scale * 15);
    ofDrawCircle(posShimaX + scale * 50, posShimaY - scale * 30, scale * 15);
    ofDrawTriangle(posShimaX - scale * 20, posShimaY - scale * 15, posShimaX, posShimaY - scale * 30, posShimaX + scale * 20, posShimaY - scale * 15);

    // テキストを表示
    ofDrawBitmapString(text, 10, 20);
}

//--------------------------------------------------------------
void ofApp::exit()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // cを押下時にテキスト表示を切り替え
    if (key == 'c')
    {
        if (text != " ")
        {
            text = " ";
        }
        else
        {
            text = menu;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    // マウスドラッグ時の処理
    if (button == 0)
    {
        // 左クリックのときにマウスの位置に赤正方形を追従
        posRedX = x - width / 2;
        posRedY = y - height / 2;
    }
    else
    {
        // 右クリックのときにマウスの位置に青正方形を追従
        posBlueX = x - width / 2;
        posBlueY = y - height / 2;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
