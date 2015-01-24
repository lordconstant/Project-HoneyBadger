// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "SDL.h"

class Camera{
private:
	SDL_Rect m_camera;
	bool m_left, m_right, m_up, m_down;
	bool m_boundXLo, m_boundXHi, m_boundYLo, m_boundYHi;
	bool m_follow;
	int m_xLo, m_xHi, m_yLo, m_yHi;
	int m_speed;
	float m_fX, m_fY;

	void move();

public:
	Camera(int x, int y, int w, int );
	Camera(SDL_Rect);
	~Camera(void);

	int x();
	int y();
	int w();
	int h();

	SDL_Rect cam();

	void l(bool l);
	void r(bool r);
	void u(bool u);
	void d(bool d);

	void follow(bool follow);
	void follow(float x, float y);
	void follow();

	void speed(int speed);

	void xBound(int lo, int hi);
	void yBound(int lo, int hi);

	void bound(bool xLo, bool xHi, bool yLo, bool yHi);
	void boundXLo(bool bound);
	void boundXHi(bool bound);
	void boundYLo(bool bound);
	void boundYHi(bool bound);

	void update();
};

