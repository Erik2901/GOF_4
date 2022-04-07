#pragma once

#include <memory>
#include <vector>
#include "CollisionDetector.h"
#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class SBomber
{
protected:
    std::unique_ptr<CollisionDetector> impl_;
public:

    SBomber(std::unique_ptr<CollisionDetector> impl);
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();
    std::vector<DynamicObject*>& GetdynObj();
    std::vector<GameObject*>& GetstatObj();
    void setflag();
    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    int16_t* getscore();
private:
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);

    //Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    //std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    //std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};