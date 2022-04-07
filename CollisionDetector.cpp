#include "CollisionDetector.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
using namespace std;


Plane* WinColDet::FindPlane() const
{
    std::unique_ptr<SBomber> sbomb;
    std::vector<DynamicObject*>& vecDynamicObj = sbomb->GetdynObj();
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* WinColDet::FindLevelGUI() const
{
    std::unique_ptr<SBomber> sbomb;
    std::vector<GameObject*>& vecStaticObj = sbomb->GetstatObj();
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}



vector<Bomb*> WinColDet::FindAllBombs() const
{
    vector<Bomb*> vecBombs;
    std::unique_ptr<SBomber> sbomb;
    std::vector<DynamicObject*>& vecDynamicObj = sbomb->GetdynObj();
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}



void WinColDet::CheckPlaneAndLevelGUI1()
{
    std::unique_ptr<SBomber> sbomb;
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        sbomb->setflag();
    }
}

Ground* WinColDet::FindGround() const
{
    Ground* pGround;
    std::unique_ptr<SBomber> sbomb;
    std::vector<GameObject*>& vecStaticObj = sbomb->GetstatObj();
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

void WinColDet::CheckBombsAndGround1()
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects1(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

vector<DestroyableGroundObject*> WinColDet::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    std::unique_ptr<SBomber> sbomb;
    std::vector<GameObject*>& vecStaticObj = sbomb->GetstatObj();
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

void WinColDet::DeleteDynamicObj(DynamicObject* pObj)
{
    std::unique_ptr<SBomber> sbomb;
    std::vector<DynamicObject*>& vecDynamicObj = sbomb->GetdynObj();
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void WinColDet::DeleteStaticObj(GameObject* pObj)
{
    std::unique_ptr<SBomber> sbomb;
    std::vector<GameObject*>& vecStaticObj = sbomb->GetstatObj();
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}

void WinColDet::CheckDestoyableObjects1(Bomb* pBomb)
{
    std::unique_ptr<SBomber> sbomb;
    int16_t *score = sbomb->getscore();
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}