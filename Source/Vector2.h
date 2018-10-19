//
// Created by k2-bakov on 19/10/2018.
//

#ifndef BASICREB0RN_VECTOR2_H
#define BASICREB0RN_VECTOR2_H


#pragma once
struct vector2
{
    // construction
    vector2(float x_, float y_);
    vector2(const vector2& rhs);

    // operations
    vector2 operator*(float scalar);
    void normalise();

    // data
    float x = 0;
    float y = 0;
};

#endif //BASICREB0RN_VECTOR2_H
