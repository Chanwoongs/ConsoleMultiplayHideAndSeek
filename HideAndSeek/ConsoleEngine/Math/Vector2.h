﻿#pragma once

#include "Core.h"

enum class ENGINE_API Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class ENGINE_API Vector2
{
public:
    Vector2(int x = 0, int y = 0);
    ~Vector2() = default;

    // 연산자 오버로딩
    // 앞에 friend가 없으면 기준이 나
    // friend를 붙이면 나가 없으니까 인자가 2개가 된다.
    Vector2 operator+(const Vector2& other);
    Vector2 operator-(const Vector2& other);
    bool operator==(const Vector2& other);
    bool operator!=(const Vector2& other);

    // 직렬화 함수
    void Serialize(char* buffer, size_t& size);

    // 역직렬화 함수
    void Deserialize(const char* buffer, size_t& size);

public:
    // x좌표, y좌표
    int32_t x = 0;
    int32_t y = 0;

};