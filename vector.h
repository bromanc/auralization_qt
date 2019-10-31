#ifndef VECTOR_H
#define VECTOR_H

#include <QVector3D>
#include <math.h>

class Vector {
public:
  static float distanceBetweenVectors(QVector3D vecA, QVector3D vecB);
  static QVector3D getClosestPointOnLine(QVector3D tVector, QVector3D vA,
                                         QVector3D vB);
  static bool compareVectors(const QVector3D &vector1,
                             const QVector3D &vector2);
  static float angleBetweenVectors(QVector3D vecA, QVector3D vecB);
};

#endif // VECTOR_H
