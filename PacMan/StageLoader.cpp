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
        //�ԕ��ݒu�B
        outStageData[i / w][i % h] = -1;
    }
    //���C���[���������̂��烍�[�h���Ă������ƁB
    LoadData(bgFilePath, outStageData, w, h);
    LoadData(obstacleFilePath, outStageData, w, h);
    LoadData(itemFilePath, outStageData, w, h);
}

void StageLoader::LoadData(const char* FilePath, std::vector<std::vector<int>>& outStageData, int w, int h)
{
    ifstream ifs(FilePath);
    string str;
    int i;

    //�ǂ߂Ȃ������Ƃ�
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
        //1�s�̂����A������ƃR���}�𕪉�����
        while (getline(stream, token, ','))
        {
            //���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
            //���l�͕ϊ����K�v
            if (outStageData[i / h][i % w] == -1) 
            {
                //�ԕ��̏ꍇ�̓I�u�W�F�N�g���ݒu�\�B
                outStageData[i / h][i % w] = stoi(token.c_str());
            }

            i++;
        }
    }

    int hoge = 0;
}
