#pragma once
#include "SBomber.h"
#include <vector>
#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
class CollisionDetector
{
    virtual void CheckPlaneAndLevelGUI1() = 0;
    virtual void CheckBombsAndGround1() = 0;
    virtual void __fastcall CheckDestoyableObjects1(Bomb* pBomb) = 0;
    friend class SBomber;
};

class WinColDet : public CollisionDetector {
protected :
    std::unique_ptr<CollisionDetector> impl_;
public:
    void CheckPlaneAndLevelGUI1() override;
    void CheckBombsAndGround1() override;
    void __fastcall CheckDestoyableObjects1(Bomb* pBomb) override;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    Ground* FindGround() const;
    std::vector<Bomb*> FindAllBombs() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    void __fastcall DeleteDynamicObj(DynamicObject* pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);
};
