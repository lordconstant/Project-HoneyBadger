#include "Camera.h"


Camera::Camera(int x, int y, int w, int h){
	m_camera.x = x;
	m_camera.y = y;
	m_camera.w = w;
	m_camera.h = h;

	m_speed = 10;

	m_boundXLo = m_boundXHi = m_boundYLo = m_boundYHi = false;
	m_up = m_down = m_left = m_right = false;
	m_follow = false;
	m_xLo = x;
	m_xHi = w;
	m_yLo = y;
	m_yHi = h;
}

Camera::Camera(SDL_Rect cam){
	m_camera.x = cam.x;
	m_camera.y = cam.y;
	m_camera.w = cam.w;
	m_camera.h = cam.y;

	m_speed = 10;

	m_boundXLo = m_boundXHi = m_boundYLo = m_boundYHi = false;
	m_up = m_down = m_left = m_right = false;
	m_follow = false;
	m_xLo = cam.x;
	m_xHi = cam.w;
	m_yLo = cam.y;
	m_yHi = cam.h;
}

Camera::~Camera(void){
}

int Camera::x(){
	return m_camera.x;
}

int Camera::y(){
	return m_camera.y;
}

int Camera::w(){
	return m_camera.w;
}

int Camera::h(){
	return m_camera.h;
}

SDL_Rect Camera::cam(){
	return m_camera;
}

void Camera::l(bool l){
	m_left = l;
}

void Camera::r(bool r){
	m_right = r;
}

void Camera::u(bool u){
	m_up = u;
}

void Camera::d(bool d){
	m_down = d;
}

void Camera::follow(bool follow){
	m_follow = follow;
}

void Camera::follow(float x, float y){
	m_fX = x;
	m_fY = y;
}

void Camera::follow(){
	if(m_camera.x > m_fX +2.0f){
		l(true);
	}
	else{
		l(false);
	}
	if(m_camera.x < m_fX -2.0f){
		r(true);
	}
	else{
		r(false);
	}
	if(m_camera.y < m_fY -2.0f){
		d(true);
	}
	else{
		d(false);
	}
	if(m_camera.y > m_fY +2.0f){
		u(true);
	}
	else{
		u(false);
	}
}

void Camera::speed(int speed){
	m_speed = speed;
}

void Camera::xBound(int lo, int hi){
	m_xLo = lo;
	m_xHi = hi;
}

void Camera::yBound(int lo, int hi){
	m_yLo = lo;
	m_yHi = hi;
}

void Camera::bound(bool xLo, bool xHi, bool yLo, bool yHi){
	m_boundXLo = xLo;
	m_boundXHi = xHi;
	m_boundYLo = yLo;
	m_boundYHi = yHi;
}

void Camera::boundXLo(bool bound){
	m_boundXLo = bound;
}

void Camera::boundXHi(bool bound){
	m_boundXHi = bound;
}

void Camera::boundYLo(bool bound){
	m_boundYLo = bound;
}

void Camera::boundYHi(bool bound){
	m_boundYHi = bound;
}

void Camera::update(){
	move();
	if(m_follow){
		follow();
	}
}

void Camera::move(){
	if(m_up){
		if(m_boundYLo){
			if(m_camera.y > m_yLo){
				m_camera.y -= m_speed;
			}
		}
		else{
			m_camera.y -= m_speed;
		}
	}
	if(m_down){
		if(m_boundYHi){
			if(m_camera.y + m_camera.h < m_yHi){
				m_camera.y += m_speed;
			}
		}
		else{
			m_camera.y += m_speed;
		}
	}
	if(m_left){
		if(m_boundXLo){
			if(m_camera.x > m_xLo){
				m_camera.x -= m_speed;
			}
		}
		else{
			m_camera.x -= m_speed;
		}
	}
	if(m_right){
		if(m_boundXHi){
			if(m_camera.x + m_camera.w < m_xHi){
				m_camera.x += m_speed;
			}
		}
		else{
			m_camera.x += m_speed;
		}
	}
}