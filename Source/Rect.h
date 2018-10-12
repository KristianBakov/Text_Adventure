//
// Created by k2-bakov on 12/10/2018.
//

#ifndef BASICREB0RN_RECT_H
#define BASICREB0RN_RECT_H
#pragma once
    struct rect
    {
        float x = 0;
        float y = 0;
        float length = 0;
        float height = 0;
        bool  isInside(float x, float y) const;
        bool  isInside(const rect& rhs) const;
        bool  isBetween(float value, float min, float max) const;
    };

#endif //BASICREB0RN_RECT_H
