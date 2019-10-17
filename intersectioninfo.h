#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

#include <QVector3D>

class Sphere;

struct IntersectionInfo {
  Sphere *object;
  QVector3D intersPoint;
  float distance;
};

#endif // INTERSECTIONINFO_H
