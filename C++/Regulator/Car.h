#pragma once

#include "Geometry.h"

enum class eDirection 
{
    UP,
    LEFT,
    RIGHT,
    DOWN
};

inline bool isOpossiteDirection(eDirection dir, eDirection anotherDir)
{
    return (dir == eDirection::UP && anotherDir == eDirection::DOWN)
        || (dir == eDirection::DOWN && anotherDir == eDirection::UP)
        || (dir == eDirection::LEFT && anotherDir == eDirection::RIGHT)
        || (dir == eDirection::RIGHT && anotherDir == eDirection::LEFT);
}

struct sCar 
{
    sCar(const sRect& rect, eDirection dir, int speed)
        : m_rect(rect)
        , m_dir(dir)
        , m_speed(speed)
    { }

    virtual ~sCar() = default;

    virtual void move() 
    {
        switch (m_dir) {
        case eDirection::UP:
            m_rect.m_pos.m_y -= m_speed;
            break;
        case eDirection::DOWN:
            m_rect.m_pos.m_y += m_speed;
            break;
        case eDirection::RIGHT:
            m_rect.m_pos.m_x += m_speed;
            break;
        case eDirection::LEFT:
            m_rect.m_pos.m_x -= m_speed;
            break;
        }
    }
    virtual int getFuel() const = 0;
    virtual void refill(int count) = 0;

    sRect getFuturePos() 
    {
        switch (m_dir) {
        case eDirection::UP:
            return sRect(m_rect.m_pos.m_x, m_rect.m_pos.m_y - m_speed, m_rect.m_size.m_width, m_rect.m_size.m_height);
        case eDirection::DOWN:
            return sRect(m_rect.m_pos.m_x, m_rect.m_pos.m_y + m_speed, m_rect.m_size.m_width, m_rect.m_size.m_height);
        case eDirection::RIGHT:
            return sRect(m_rect.m_pos.m_x + m_speed, m_rect.m_pos.m_y, m_rect.m_size.m_width, m_rect.m_size.m_height);
        case eDirection::LEFT:
            return sRect(m_rect.m_pos.m_x - m_speed, m_rect.m_pos.m_y, m_rect.m_size.m_width, m_rect.m_size.m_height);
        default:
            return sRect(m_rect.m_pos.m_x, m_rect.m_pos.m_y, m_rect.m_size.m_width, m_rect.m_size.m_height);
        }
    }

    sRect getCurrentPos() const
    {
        return m_rect;
    }

    bool needPassOtherCar(sCar* otherCar) const
    {
        auto result = false;
        auto& otherCarDir = otherCar->m_dir;

        switch (m_dir) {
        case eDirection::UP:
            if (otherCarDir == eDirection::LEFT)
                result = true;
            break;
        case eDirection::DOWN:
            if (otherCarDir == eDirection::RIGHT)
                result = true;
            break;
        case eDirection::RIGHT:
            if (otherCarDir == eDirection::UP)
                result = true;
            break;
        case eDirection::LEFT:
            if (otherCarDir == eDirection::DOWN)
                result = true;
            break;
        }

        return result;
    }

    sRect m_rect;
    eDirection m_dir;
    int m_speed;
};

struct sGasEngine : public virtual sCar 
{
    sGasEngine(const sRect& rect, eDirection dir, int speed, int fuel)
        : sCar(rect, dir, speed)
        , m_fuel(fuel)
    { }

    void move() 
    { 
        if (m_fuel > 0) {
            m_fuel--;
            sCar::move();
        }
    }

    int getFuel() const override 
    { 
        return m_fuel; 
    }

    void refill(int count) override 
    {
        m_fuel += count; 
    }

    int m_fuel;
};

struct sElectroCar : public virtual sCar
{
    sElectroCar(const sRect& rect, eDirection dir, int speed, int charge)
        : sCar(rect, dir, speed)
        , m_charge(charge)
    { }
    
    void move() 
    { 
        if (m_charge > 0) {
            m_charge--;
            sCar::move();
        }
    }

    int getFuel() const override 
    { 
        return m_charge; 
    }

    void refill(int count) override 
    {
        m_charge += count; 
    }

    int m_charge;
};

struct sHybrid : public sGasEngine, public sElectroCar
{
    sHybrid(const sRect& rect, eDirection dir, int speed, int fuel, int charge)
        : sCar(rect, dir, speed)
        , sGasEngine(rect, dir, speed, fuel)
        , sElectroCar(rect, dir, speed, charge)

    { }

    void move() 
    {
        if (m_fuel > 0 && m_charge > 0) {
            if (rand() % 2 == 0) {
                m_charge--;
            }
            else {
                m_fuel--;
            }
            sCar::move();
        } 
        else if (m_fuel > 0 || m_charge > 0) {
            // Если остался один тип топлива - используем именно его
            if (m_fuel > 0) {
                m_fuel--;
            }
            else {
                m_charge--;
            }
            sCar::move();
        }
    }

    int getFuel() const override 
    { 
        return m_charge + m_fuel; 
    }

    void refill(int count) override 
    { 
        m_charge += count / 2; 
        m_fuel += count / 2; 
    }
};