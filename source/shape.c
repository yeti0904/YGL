#include "shape.h"
#include "error.h"

YGL_Shape* YGL_CreateShape(size_t n) {
	YGL_Shape* ret = (YGL_Shape*) malloc(sizeof(YGL_Shape));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}

	ret->points = (YGL_FVec2*) malloc(n * sizeof(YGL_FVec2));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}
	
	ret->n = n;

	return ret;
}

YGL_Shape YGL_CreateStaticShape(size_t n, YGL_FVec2* points) {
	return (YGL_Shape) {
		.points = points,
		.n      = n
	};
}

void YGL_FreeShape(YGL_Shape* shape) {
	free(shape->points);
	free(shape);
}

void YGL_DrawShape(YGL_Canvas* canvas, YGL_Shape* shape, YGL_Colour colour) {
	if (shape->n < 2) {
		return;
	}
	
	for (size_t i = 0; i < shape->n - 1; ++ i) {
		YGL_DrawLine(
			canvas, YGL_FVec2ToInt(shape->points[i]),
			YGL_FVec2ToInt(shape->points[i + 1]), colour
		);
	}

	YGL_DrawLine(
		canvas, YGL_FVec2ToInt(shape->points[0]),
		YGL_FVec2ToInt(shape->points[shape->n - 1]), colour
	);
}

YGL_Shape* YGL_RectToShape(YGL_Rect rect) {
	YGL_Shape* ret = YGL_CreateShape(4);

	if (ret == NULL) {
		return NULL;
	}

	ret->points[0] = YGL_Vec2ToFloat(
		(YGL_Vec2) {rect.x, rect.y}
	);
	ret->points[1] = YGL_Vec2ToFloat(
		(YGL_Vec2) {rect.x + rect.w - 1, rect.y}
	);
	ret->points[2] = YGL_Vec2ToFloat(
		(YGL_Vec2) {rect.x, rect.y + rect.h - 1}
	);
	ret->points[3] = YGL_Vec2ToFloat(
		(YGL_Vec2) {rect.x + rect.w - 1, rect.y + rect.h - 1}
	);

	return ret;
}

YGL_Shape* YGL_CreateTriangle(YGL_FVec2 p1, YGL_FVec2 p2, YGL_FVec2 p3) {
	YGL_Shape* ret = YGL_CreateShape(3);

	if (ret == NULL) {
		return NULL;
	}

	ret->points[0] = p1;
	ret->points[1] = p2;
	ret->points[2] = p3;

	return ret;
}

YGL_FVec2 YGL_GetTriangleCenter(YGL_Shape* shape) {
	return (YGL_FVec2) {
		(shape->points[0].x + shape->points[1].x + shape->points[2].x) / 3.0,
		(shape->points[0].y + shape->points[1].y + shape->points[2].y) / 3.0
	};
}

void YGL_MoveShape(YGL_Shape* shape, YGL_FVec2 offset) {
	for (size_t i = 0; i < shape->n; ++ i) {
		shape->points[i].x += offset.x;
		shape->points[i].y += offset.y;
	}
}

void YGL_RotateShape(YGL_Shape* shape, YGL_FVec2 origin, double deg) {
	for (size_t i = 0; i < shape->n; ++ i) {
		shape->points[i] = YGL_RotatePoint(shape->points[i], origin, deg);
	}
}

YGL_3DShape* YGL_Create3DShape(size_t n) {
	YGL_3DShape* ret = (YGL_3DShape*) malloc(sizeof(YGL_3DShape));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}

	ret->points = (YGL_FVec3*) malloc(n * sizeof(YGL_FVec3));

	if (ret == NULL) {
		YGL_SetError("malloc failed");
		return NULL;
	}
	
	ret->n = n;

	return ret;
}

void YGL_Free3DShape(YGL_Shape* shape) {
	free(shape->points);
	free(shape);
}

void YGL_Draw3DPlane(YGL_Canvas* canvas, YGL_3DShape* shape, YGL_Colour colour) {
	if (shape->n != 4) {
		return;
	}

	YGL_FVec2 wallPoints[4];
	YGL_Shape wall = YGL_CreateStaticShape(4, wallPoints);

	for (size_t i = 0; i < shape->n; ++ i) {
		YGL_FVec2 point;

		double z = shape->points[i].z;

		if (z == 0) {
			z = 0.0001;
		}

		z /= 10.0f;
		
		point.x  = shape->points[i].x / z;
		point.y  = shape->points[i].y / z;
		point.x += canvas->size.x / 2;
		point.y += canvas->size.y / 2;

		wall.points[i] = point;
	}

	YGL_DrawShape(canvas, &wall, colour);
}

void YGL_Move3DShape(YGL_3DShape* shape, YGL_FVec3 offset) {
	for (size_t i = 0; i < shape->n; ++ i) {
		shape->points[i].x += offset.x;
		shape->points[i].y += offset.y;
		shape->points[i].z += offset.z;
	}
}

void YGL_Spin3DShape(YGL_3DShape* shape, YGL_FVec2 origin, double deg) {
	for (size_t i = 0; i < shape->n; ++ i) {
		YGL_FVec2 point    = {shape->points[i].x, shape->points[i].z};
		YGL_FVec2 newPoint = YGL_RotatePoint(point, origin, deg);
		shape->points[i].x = newPoint.x;
		shape->points[i].z = newPoint.y;
	}
}
