#include "triangle.h"
#include "ray.h"
#include "vector.h"

Triangle::Triangle(QVector3D vec1, QVector3D vec2, QVector3D vec3) {
  vertexes[0] = vec1;
  vertexes[1] = vec2;
  vertexes[2] = vec3;
}

Triangle::Triangle() {
  vertexes[0].setX(0);
  vertexes[0].setY(0);
  vertexes[0].setZ(0);

  vertexes[1].setX(0);
  vertexes[1].setY(0);
  vertexes[1].setZ(0);

  vertexes[2].setX(0);
  vertexes[2].setY(0);
  vertexes[2].setZ(0);
}

Triangle::~Triangle() {}

bool Triangle::intersectsTriangle(Ray *ray, double *distance,
                                  QVector3D &intersection) {
  double e = 0.000001;

  QVector3D v1 = vertexes[0];
  QVector3D v2 = vertexes[1];
  QVector3D v3 = vertexes[2];

  QVector3D e1 = v2 - v1;
  QVector3D e2 = v3 - v1;

  // Begin calculating determinant - also used to calculate u parameter
  QVector3D p = QVector3D::crossProduct(ray->direction, e2);
  float det = QVector3D::dotProduct(e1, p);

  // If determinant is near zero, ray lies in plane of triangle
  if (det > -e && det < e) {
    return false;
  }

  double inv_det = 1.0 / det;

  QVector3D t = ray->startPos - v1;
  double u = QVector3D::dotProduct(t, p) * inv_det;
  // The intersection lies outside of the triangle
  if (u < 0.0 || u > 1.0) {
    return false;
  }

  QVector3D q = QVector3D::crossProduct(t, e1);
  double v = QVector3D::dotProduct(ray->direction, q) * inv_det;
  // The intersection lies outside of the triangle
  if (v < 0.0 || u + v > 1.0) {
    return false;
  }

  double a = QVector3D::dotProduct(e2, q);
  // http://gamedev.stackexchange.com/questions/114955/m%C3%B6ller-trumbore-intersection-point
  // intersection = v1+u*e2+v*e1;
  intersection = ray->startPos + ray->direction * a;
  if (a > e) {
    distance = &a;
    return true;
  }
  return false;
}

QVector3D Triangle::getNormal() {
  QVector3D vec1 = vertexes[2] - vertexes[0];
  QVector3D vec2 = vertexes[1] - vertexes[0];

  QVector3D normal = QVector3D::crossProduct(vec1, vec2);
  return normal.normalized();
}

bool Triangle::isInside(QVector3D vertex) {
  const double MATCH_FACTOR = 0.99;
  float angle = 0.0;
  QVector3D vecA, vecB;

  for (int i = 0; i < 3; i++) {
    vecA = vertexes[i] - vertex;
    vecB = vertexes[(i + 1) % 3] - vertex;
    float dot = QVector3D::dotProduct(vecA, vecB);
    float lenSqvA = vecA.lengthSquared();
    float lenSqvB = vecB.lengthSquared();
    angle += acos(dot / sqrt(lenSqvA * lenSqvB));
  }

  if (angle >= (MATCH_FACTOR * (2.0 * M_PI))) {
    return true;
  }

  return false;
}

double Triangle::getArea() {
  QVector3D vecA = vertexes[2] - vertexes[0];
  QVector3D vecB = vertexes[1] - vertexes[0];
  float dot = QVector3D::dotProduct(vecA, vecB);
  float lenSqvA = vecA.lengthSquared();
  float lenSqvB = vecB.lengthSquared();
  float angle = acos(dot / sqrt(lenSqvA * lenSqvB));
  return 0.5 * (vecA.length() * vecB.length() * sin(angle));
}
