#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector3D>

class Ray;

class Triangle {
public:
  Triangle();
  Triangle(QVector3D vec1, QVector3D vec2, QVector3D vec3);
  ~Triangle();
  bool intersectsTriangle(Ray *ray, double *distance, QVector3D &intersection);
  bool isInside(QVector3D vertex);
  QVector3D getNormal();
  double getArea();
  QVector3D vertexes[3];
};

struct Element {
  Triangle t;
  QVector3D normal;
  int layerID;
  int planeID;
  int triangleID;
};

#endif // TRIANGLE_H
