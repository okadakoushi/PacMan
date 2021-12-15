#include "stdafx.h"
#include "StageLoader.h"
#include "SceneGame.h"
#include <fstream>
#include <sstream>

using namespace std;

void StageLoader::Init(std::vector<std::vector<int>>& outStageData, int w, int h, const char* bgFilePath, const char* obstacleFilePath, const char* itemFilePath)
{
    for (int i = 0; i < w * h; i++) 
    {
        //番兵設置。
        outStageData[i / w][i % h] = -1;
    }
    //レイヤーが高いものからロードしていくこと。
    LoadData(bgFilePath, outStageData, w, h);
    LoadData(obstacleFilePath, outStageData, w, h);
    LoadData(itemFilePath, outStageData, w, h);
}

void StageLoader::LoadData(const char* FilePath, std::vector<std::vector<int>>& outStageData, int w, int h)
{
    ifstream ifs(FilePath);
    string str;
    int i;

    //読めなかったとき
    if (!ifs)
    {
        OutputDebugString("WARNING: StageLoader / StageData FilePath is invalid.\n");
        return;
    }

    i = 0;
    while (getline(ifs, str))
    {
        string token;
        istringstream stream(str);
        //1行のうち、文字列とコンマを分解する
        while (getline(stream, token, ','))
        {
            //すべて文字列として読み込まれるため
            //数値は変換が必要
            if (outStageData[i / h][i % w] == -1) 
            {
                //番兵の場合はオブジェクトが設置可能。
                outStageData[i / h][i % w] = stoi(token.c_str());
            }

            i++;
        }
    }

    int hoge = 0;
}
