#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Game.h"
#include "GameObject.h"
#include "Camera.h"

class CQuadTree
{
public:

    static CQuadTree* __instance;
    static CQuadTree* GetInstance(int level, RECT r);

    CQuadTree(int level, RECT bound);
    ~CQuadTree();
    void Clear();
    void insertEntity(LPGAMEOBJECT obj);

    /*lay danh sach nhung Entity co kha nang xay ra va cham
    tra ve danh sach cac phan tu nam trong vung va cham */
    void getEntitiesCollideAble(std::vector<LPGAMEOBJECT>& entitiesOut, LPGAMEOBJECT obj);

    void getAllEntitiesOnCam(vector<LPGAMEOBJECT>& entitiesOut, float camX, float camY);

    void getAllEntities(std::vector<LPGAMEOBJECT>& entitiesOut);

    int getTotalEntities();

    RECT Bound;

    void Unload();

protected:
    CQuadTree** Nodes;
    vector<LPGAMEOBJECT> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)

    /*lay vi tri cua Entity
    0: nam trong Node con goc trai tren
    1: nam trong Node con goc phai tren
    2: nam trong Node con goc trai duoi
    3: nam trong Node con goc phai duoi
    -1: bi dinh > 2 node con*/
    int getIndex(RECT body);

    void split(); //thuc hien chia ra cac node

    bool isContain(LPGAMEOBJECT obj);
    int mLevel; //tuong ung voi so node
};

