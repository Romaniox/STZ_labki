#pragma once
#include <cstdint>

class PhysObj {
public:
    uint32_t m = 0;

    double rx = 0;
    double ry = 0;
private:
    double vx = 0;
    double vy = 0;

    double wx = 0;
    double wy = 0;
public:
    PhysObj(uint32_t mass, double rx, double ry, double vx, double vy, double wx, double wy);
    ~PhysObj() = default;
public:
    void step(double grav, uint32_t m1, uint32_t m2, double rx1, double ry1, double rx2, double ry2);
private:
    void w_calc(uint32_t m1, uint32_t m2, double rx1, double ry1, double rx2, double ry2, double grav);
    void pos_check();
    void vel_check();
};