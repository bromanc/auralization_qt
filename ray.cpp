#include "ray.h"
#include "triangle.h"

Ray::Ray() {
  startPos = QVector3D(0, 0, 0);
  direction = QVector3D(0, 0, 0);
  receptionTime = -1;
}

// incomplete
Ray::Ray(const QVector3D newStartPos, const QVector3D newDirection,
         int numGeneratedRays, float initialEnergy)
    : startPos(newStartPos), direction(newDirection),
      bands(numGeneratedRays, initialEnergy) {
  direction.normalize();
  receptionTime = -1;
}

bool Ray::intersectedPlane(QVector3D planeNormal, QVector3D planeVertex,
                           float &originDistance) {
  float distance1 = 0,
        distance2 =
            0; // The distances from the 2 points of the line from the plane
  // Let's find the distance our plane is from the origin.  We can find this val
  // from the normal to the plane (polygon) and any point that lies on that
  // plane (Any vertex)
  originDistance = planeVertex.distanceToPlane(planeVertex, planeNormal);
  // Get the distance from point1 from the plane using: Ax + By + Cz + D = (The
  // distance from the plane)
  distance1 = ((planeNormal.x() * startPos.x()) + // Ax +
               (planeNormal.y() * startPos.y()) + // Bx +
               (planeNormal.z() * startPos.z())) +
              originDistance; // Cz + D

  // Get the distance from point2 from the plane using Ax + By + Cz + D = (The
  // distance from the plane)
  distance2 = ((planeNormal.x() * direction.x()) + // Ax +
               (planeNormal.y() * direction.y()) + // Bx +
               (planeNormal.z() * direction.z())) +
              originDistance; // Cz + D

  // Now that we have 2 distances from the plane, if we times them together we
  // either get a positive or negative number.  If it's a negative number, that
  // means we collided! This is because the 2 points must be on either side of
  // the plane (IE. -1 * 1 = -1).

  if (distance1 * distance2 >= 0) // Check to see if both point's distances are
                                  // both negative or both positive
    return false; // Return false if each point has the same sign.  -1 and 1
                  // would mean each point is on either side of the plane.  -1
                  // -2 or 3 4 wouldn't...

  return true;
}

// Snell Law
QVector3D Ray::getReflectionVect(QVector3D normal) {
  QVector3D aux(direction.x(), direction.y(), direction.z());
  float Vi_nt = QVector3D::dotProduct(aux, normal);
  float arccos = acos(Vi_nt);
  float sen = sin(arccos - (M_PI) / 2) * 2;
  aux += normal * sen;
  aux += aux;
  return aux;
}

QVector3D Ray::getStochasticReflectionVect(Triangle tri, QVector3D intersection,
                                           float scattering[]) {
  float s = 0;
  for (int m = 0; m < 6; m++) {
    s += scattering[m];
  }
  s /= 6;

  QVector3D direction;
  QVector3D vect1 = tri.vertexes[0] - intersection;
  QVector3D vect2 = tri.vertexes[1] - intersection;
  QVector3D norm = QVector3D::crossProduct(vect1, vect2);
  QVector3D v1, v2, v3;

  float sin_th = sqrt(random.generateDouble());
  float cos_th = sqrt(1 - sin_th * sin_th);
  float rand_angle = 2 * M_PI * (random.generateDouble());

  float cmpA = sin_th * cos(rand_angle);
  float cmpB = sin_th * sin(rand_angle);
  float cmpC = cos_th;

  for (int j = 0; j < 3; j++) {
    v1[j] = cmpA * vect1[j];
    v2[j] = cmpB * vect2[j];
    v3[j] = cmpC * norm[j];
  }

  for (int k = 0; k < 3; k++) {
    direction[k] = v1[k] + v2[k] + v3[k];
  }

  QVector3D resultRay;
  resultRay = direction - intersection;
  resultRay = (s * resultRay) + ((1 - s) * getReflectionVect(norm));

  return resultRay;
}
