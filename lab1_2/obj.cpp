#include "obj.h"
#include <cmath>


PhysObj::PhysObj(uint32_t mass, double rx, double ry, double vx, double vy, double wx, double wy) {
	this->m = mass;

	this->rx = rx;
	this->ry = ry;

	this->vx = vx;
	this->vy = vy;

	this->wx = wx;
	this->wy = wy;
}


void PhysObj::pos_check() {
	double size = 500.0;
	if (this->rx > size) {
        this->rx = 0;
	}
	if (this->ry > size) {
        this->ry = 0;
	}
	if (this->rx < 0) {
        this->rx = size;
	}
	if (this->ry < 0) {
        this->ry = size;
	}
}


void PhysObj::vel_check() {
    double lim = 40.0;
    if (this->vx > lim) {
        this->vx = lim;
        this->wx = 0;
    }
    if (this->vy > lim) {
        this->vy = lim;
        this->wy = 0;
    }
}


void PhysObj::w_calc(uint32_t m1, uint32_t m2, double rx1, double ry1, double rx2, double ry2, double grav) {
	double dx1 = rx1 - this->rx;
	double dy1 = ry1 - this->ry;

	double dx2 = rx2 - this->rx;
	double dy2 = ry2 - this->ry;

	double vect_norm1 = sqrt(dx1 * dx1 + dy1 * dy1);
	double vect_norm2 = sqrt(dx2 * dx2 + dy2 * dy2);

	this->wx = grav * m1 * (dx1 / (pow(vect_norm1, 3))) + grav * m2 * (dx2 / (pow(vect_norm2, 3)));
	this->wy = grav * m1 * (dy1 / (pow(vect_norm1, 3))) + grav * m2 * (dy2 / (pow(vect_norm2, 3)));
}


void PhysObj::step(double grav, uint32_t m1, uint32_t m2, double rx1, double ry1, double rx2, double ry2) {
	this->w_calc(m1, m2, rx1, ry1, rx2, ry2, grav);
	this->vx += this->wx;
	this->vy += this->wy;

	this->rx += this->vx;
	this->ry += this->vy;

	this->pos_check();
    this->vel_check();
}
