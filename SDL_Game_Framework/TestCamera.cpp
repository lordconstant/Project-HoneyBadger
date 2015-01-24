#pragma once

#include "UnitTest++.h"
#include "Camera.h"

TEST(CameraTestClass){
	Camera* newCamera = new Camera(0, 0, 64, 64);

	CHECK(newCamera->cam().x == 0);
	CHECK(newCamera->cam().y == 0);
	CHECK(newCamera->cam().w == 64);
	CHECK(newCamera->cam().h == 64);
	newCamera->d(true);
	newCamera->r(true);
	newCamera->update();
	CHECK(newCamera->x() > 0);
	CHECK(newCamera->y() > 0);
	newCamera->d(false);
	newCamera->r(false);
	newCamera->u(true);
	newCamera->l(true);
	newCamera->update();
	newCamera->update();
	newCamera->update();
	newCamera->update();
	CHECK(newCamera->x() < 0);
	CHECK(newCamera->y() < 0);

	delete newCamera;
}