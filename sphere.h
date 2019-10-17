#ifndef SPHERE_H
#define SPHERE_H

#include "intersectioninfo.h"
#include "ray.h"
#include "triangle.h"
#include <QVector3D>

#define BEHIND 0
#define INTERSECTS 1
#define FRONT 2

class Sphere {

public:
  Sphere();
  Sphere(const QVector3D &center, float radius);
  bool getIntersection(Ray *ray, IntersectionInfo &info);
  int classifySphere(QVector3D &normal, QVector3D &point, float &distance);
  bool getEdgeSphereCollision(Triangle triangle, bool useHalfRadius);
  bool getSpherePolygonCollision(Triangle triangle);
  void setRadius(float rad);
  float getRadius();
  void setCenter(QVector3D newCenter);
  QVector3D getCenter();
  QVector3D getClosestPointOnLine(QVector3D vecA, QVector3D vecB);
  // http://stackoverflow.com/questions/1568091/why-use-getters-and-setters

private:
  float radius;
  QVector3D center;
};

#endif // SPHERE_H
