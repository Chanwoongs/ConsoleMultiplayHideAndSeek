﻿#pragma once

#include "Level/Level.h"

#include <queue>
#include <unordered_map>

class DrawableActor;
class Player;
class Vector2;

class ENGINE_API GameLevel : public Level
{
    RTTI_DECLARATIONS(GameLevel, Level)

public:
    GameLevel();
    ~GameLevel();

    virtual void AddActor(Actor* newActor) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void LoadMap();

    void SerializeGameState(char* buffer, size_t bufferSize, size_t& outSize);
    void DeserializeGameState(const char* buffer);

    void SerializePath(int id, char* buffer, size_t& outSize, size_t& pathCount);
    void DeserializePath(const char* buffer);

    bool CanPlayerMove(const class Vector2& position);

    const Vector2& GetRandomEmptyPosition();

	inline void SetClientId(int id) { clientId = id; }

    void MovePlayer(int playerId, enum class Direction direction);
	void RemovePlayer(int playerId);

    void ProcessCollision();

    std::vector<Vector2*> FindPath(const int playerId, const Vector2& end);
    void RequestClientPlayerPathChange(std::vector<Vector2*>&& path);

    inline std::unordered_map<int, std::vector<Vector2*>> GetAllPlayersPath() { return allPlayersPath; }
    void SetPlayerPath(int id, std::vector<Vector2*>&& path) { allPlayersPath[id] = std::move(path); }
    
private:
    bool CheckGameClear();

private:

    DrawableActor* map = nullptr;

    std::vector<Player*> players;

    std::vector<Vector2*> wallPositions;

    std::vector<Vector2*> emptyPositions;

    std::vector<Vector2*> clientPlayerPath;

    std::vector<Vector2*> pendingPlayerPath;
    bool setPathRequested;

    std::unordered_map<int, std::vector<Vector2*>> allPlayersPath;
     
    bool isGameClear = false;

    bool isMapInitialized = false;

    DrawableActor* tempMap = nullptr;

    std::vector<Player*> tempPlayers;

    bool isThreadWriting = false;

    HANDLE mutex = 0;

    int clientId = 0;

    int mapWidth = 0;

    int mapHeight = 0;
};