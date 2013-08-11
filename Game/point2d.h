//
//  point2d.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_point2d_h
#define Game_point2d_h

// Standard dependencies
#include <array>

template<typename T>
class CPoint2D
{
public:
    CPoint2D();
    CPoint2D(const CPoint2D & point) = default;
    CPoint2D(CPoint2D && point) = default;
    CPoint2D & operator=(const CPoint2D & point) = default;
    ~CPoint2D() = default;
    CPoint2D(const T & x, const T & y);
    
    T X()const;
    T Y()const;
    T& X();
    T& Y();
    
private:
    std::array<T, 2> m_coordinates;
    
};

template<typename T>
CPoint2D<T>::CPoint2D()
{
    m_coordinates = {0,0};
}

template<typename T>
CPoint2D<T>::CPoint2D(const T & x, const T & y)
{
    m_coordinates = {x, y};
}

template<typename T>
T CPoint2D<T>::X()const
{
    return m_coordinates[0];
}

template<typename T>
T CPoint2D<T>::Y()const
{
    return m_coordinates[1];
}

template<typename T>
T & CPoint2D<T>::X()
{
    return m_coordinates[0];
}

template<typename T>
T & CPoint2D<T>::Y()
{
    return m_coordinates[1];
}

#endif
