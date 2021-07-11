#include "QuadTree.h"
#include "Define.h"
#include "Utils.h"

CQuadTree::CQuadTree(int level, RECT bound)
{
	//chia lam 4

	this->Bound = bound;
	this->mLevel = level;

    //DebugOut(L"level = %d\n", level);
}

CQuadTree::~CQuadTree()
{
}

void CQuadTree::Clear()
{
    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (Nodes[i])
            {
                Nodes[i]->Clear();
                delete Nodes[i];
                Nodes[i] = nullptr;
            }
        }

        delete[] Nodes;
    }
}

void CQuadTree::insertEntity(LPGAMEOBJECT obj)
{
    RECT bound;

    float l, t, r, b;

    obj->GetBoundingBox(l, t, r, b);

    bound.left = l;
    bound.top = t;
    bound.right = r;
    bound.bottom = b;
    
    int index = getIndex(bound);

    //neu node ta ton tai thi insert vao node con
    if (Nodes != NULL)
    {
        if (index != -1)
        {
            Nodes[index]->insertEntity(obj);
            return;
        }
    }

    //luc nay entity nam giua 2 Bound nen se add vao node nay luon
    if (index == -1)
    {
        this->mListEntity.push_back(obj);
    }
    else
    {
        //node chua dc tao nen se tao va split roi moi insert
        if (Nodes == NULL)
        {
            split();
        }

        Nodes[index]->insertEntity(obj);
    }
}

void CQuadTree::getEntitiesCollideAble(std::vector<LPGAMEOBJECT>& entitiesOut, LPGAMEOBJECT obj)
{
    RECT bound;

    float l, t, r, b;

    obj->GetBoundingBox(l, t, r, b);

    bound.left = l;
    bound.top = t;
    bound.right = r;
    bound.bottom = b;

    int index = this->getIndex(bound);

    if (index != -1)
    {
        //nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
        for (auto child : mListEntity)
        {
            entitiesOut.push_back(child);
        }

        if (Nodes != NULL)
        {
            //kiem tra va lay cac node trong node con
            Nodes[index]->getEntitiesCollideAble(entitiesOut, obj);
        }
    }
    else
    {
        getAllEntities(entitiesOut);
    }
}

void CQuadTree::getAllEntitiesOnCam(vector<LPGAMEOBJECT>& entitiesOut, float camX, float camY)
{
    RECT bound;

    bound.left = camX;
    bound.top = camY + SCREEN_HEIGHT_MAP;
    bound.right = camX + SCREEN_WIDTH;
    bound.bottom = camY;

    /*DebugOut(L" top = %d\n", bound.top);
    DebugOut(L" bottom = %d\n", bound.bottom);*/

    int index = this->getIndex(bound);

    if (index != -1)
    {
        //nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
        for (auto child : mListEntity)
        {
            entitiesOut.push_back(child);
        }

        if (Nodes != NULL)
        {
            //kiem tra va lay cac node trong node con
            Nodes[index]->getAllEntitiesOnCam(entitiesOut, camX, camY);
        }
    }
    else
    {
        getAllEntities(entitiesOut);
    }
}

void CQuadTree::getAllEntities(std::vector<LPGAMEOBJECT>& entitiesOut)
{
    for (auto child : mListEntity)
    {
        entitiesOut.push_back(child);
    }

    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            Nodes[i]->getAllEntities(entitiesOut);
        }
    }
}

int CQuadTree::getTotalEntities()
{
    int total = mListEntity.size();

    if (Nodes)
    {
        for (size_t i = 0; i < 4; i++)
        {
            total += Nodes[i]->getTotalEntities();
        }
    }

    return total;
}

int CQuadTree::getIndex(RECT body)
{
    /*lay vi tri cua Entity
    0: nam trong Node con goc trai tren
    1: nam trong Node con goc phai tren
    2: nam trong Node con goc trai duoi
    3: nam trong Node con goc phai duoi
    -1: bi dinh > 2 node con*/

    float middleVerticle = Bound.left + (Bound.right - Bound.left) / 2.0f;
    float middleHorizontal = Bound.top - (Bound.top - Bound.bottom) / 2.0f;

    if (body.top <= Bound.top && body.bottom >= middleHorizontal)
    {
        //nam phia ben tren
        if (body.left >= Bound.left && body.right <= middleVerticle)
        {
            //nam phia ben trai
            return 0;
        }
        else if (body.left >= middleVerticle && body.right <= Bound.right)
        {
            //nam phia ben phai
            return 1;
        }
    }
    else if (body.top <= middleHorizontal && body.bottom >= Bound.bottom)
    {
        //nam phia ben duoi
        if (body.left >= Bound.left && body.right <= middleVerticle)
        {
            //nam phia ben trai
            return 2;
        }
        else if (body.left >= middleVerticle && body.right <= Bound.right)
        {
            //nam phia ben phai
            return 3;
        }
    }

    return -1;
}

void CQuadTree::split()
{
    //cat phan region (ranh gioi) ra thanh 4 phan bang nhau
    Nodes = new CQuadTree * [4];

    RECT bound;

    int width = (Bound.right - Bound.left) / 2;
    int height = (Bound.top - Bound.bottom) / 2;

    //phan goc trai tren
    bound.left = Bound.left;
    bound.right = bound.left + width;
    bound.top = Bound.top;
    bound.bottom = bound.top - height;
    Nodes[0] = new CQuadTree(mLevel + 1, bound);

    //phan goc phai tren
    bound.left = Bound.left + width;
    bound.right = bound.left + width;
    bound.top = Bound.top;
    bound.bottom = bound.top - height;
    Nodes[1] = new CQuadTree(mLevel + 1, bound);

    //phan goc trai duoi
    bound.left = Bound.left;
    bound.right = bound.left + width;
    bound.top = Bound.top - height;
    bound.bottom = bound.top - height;
    Nodes[2] = new CQuadTree(mLevel + 1, bound);

    //phan goc phai duoi
    bound.left = Bound.left + width;
    bound.right = bound.left + width;
    bound.top = Bound.top - height;
    bound.bottom = bound.top - height;
    Nodes[3] = new CQuadTree(mLevel + 1, bound);
}

bool CQuadTree::isContain(LPGAMEOBJECT obj)
{
    RECT bound;

    float l, t, r, b;

    obj->GetBoundingBox(l, t, r, b);

    bound.left = l;
    bound.top = t;
    bound.right = r;
    bound.bottom = b;

    if (bound.left >= Bound.left && bound.right <= Bound.right && bound.top <= Bound.top && bound.bottom >= Bound.bottom)
    {
        return true;
    }

    return false;
}
