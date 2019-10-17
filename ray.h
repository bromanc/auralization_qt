#ifndef RAY_H
#define RAY_H

#include <QRandomGenerator>
#include <QVector3D>
#include <bandenergy.h>

class Triangle;

class Ray {

public:
  Ray(QVector3D newStartPos, QVector3D newDirection, int numGeneratedRays,
      float initialEnergy);
  Ray();
  bool intersectedPlane(QVector3D planeNormal, QVector3D planeVertex,
                        float &originDistance);
  QVector3D getReflectionVect(QVector3D planeNormal);
  QVector3D getStochasticReflectionVect(Triangle t, QVector3D intersection,
                                        float scattering[]);
  QVector3D startPos;
  QVector3D direction;
  QRandomGenerator random;
  BandEnergy bands;
  double receptionTime;
  float distance;
};

#endif // RAY_H
