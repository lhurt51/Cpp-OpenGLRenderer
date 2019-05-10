#include "Testing.h"

#include "Physics\BoundingSphere.h"
#include "Physics\AABB.h"
#include "Physics\Plane.h"

void Testing::RunAllTests()
{
	BoundingSphere::Test();
	AABB::Test();
	Plane::Test();
}
