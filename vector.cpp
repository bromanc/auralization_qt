#include <vector.h>

float Vector::distanceBetweenVectors(QVector3D vecA, QVector3D vecB) {
  return sqrtf(pow(vecA.x() - vecB.x(), 2) + pow(vecA.y() - vecB.y(), 2) +
               pow(vecA.z() - vecB.z(), 2));
}

QVector3D Vector::getClosestPointOnLine(QVector3D tVector, QVector3D vA,
                                        QVector3D vB) {
  // Create the vector from end point vA to our point vPoint.
  QVector3D vVector1 = tVector - vA;
  // Create a normalized direction vector from end point vA to end point vB
  QVector3D vVector2 = (vB - vA).normalized();
  // Use the distance formula to find the distance of the line segment (or
  // magnitude)
  float d = Vector::distanceBetweenVectors(vA, vB);
  // Using the dot product, we project the vVector1 onto the vector vVector2.
  // This essentially gives us the distance from our projected vector from vA.
  float t = QVector3D::dotProduct(vVector2, vVector1);
  // If our projected distance from vA, "t", is less than or equal to 0, it must
  // be closest to the end point vA.  We want to return this end point.
  if (t <= 0)
    return vA;
  // If our projected distance from vA, "t", is greater than or equal to the
  // magnitude or distance of the line segment, it must be closest to the end
  // point vB.  So, return vB.
  if (t >= d)
    return vB;
  // Here we create a vector that is of length t and in the direction of
  // vVector2
  QVector3D vVector3 = vVector2 * t;
  // To find the closest point on the line segment, we just add vVector3 to the
  // original end point vA.
  QVector3D vClosestPoint = vA + vVector3;
  // Return the closest point on the line segment
  return vClosestPoint;
}

bool Vector::compareVectors(const QVector3D &vector1,
                            const QVector3D &vector2) {
  return (vector1.x() == vector2.x()) && (vector1.y() == vector2.y()) &&
         (vector1.z() == vector2.z());
}

float Vector::angleBetweenVectors(QVector3D vecA, QVector3D vecB){

    float aux = QVector3D::dotProduct(vecA, vecB);

    aux /= sqrt(QVector3D::dotProduct(vecA, vecA));
    aux /= sqrt(QVector3D::dotProduct(vecB, vecB));

    float angle = acos(aux) / M_PI * 180;

    return angle;

}
