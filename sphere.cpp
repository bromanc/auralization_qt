#include "sphere.h"
#include "vector.h"

Sphere::Sphere() {
  center = QVector3D(0, 0, 0);
  radius = 0;
}

Sphere::Sphere(const QVector3D &center, float radius) {
  setCenter(center);
  setRadius(radius);
}

bool Sphere::getIntersection(Ray *ray, IntersectionInfo &info) {
  QVector3D m = ray->startPos - center;
  float b = QVector3D::dotProduct(m, ray->direction);
  float c = QVector3D::dotProduct(m, m) - radius * radius;

  if (c > 0.0f && b > 0.0f) {
    return false;
  }

  float discr = b * b - c;

  if (discr < 0.0f) {
    return false;
  }

  float t = -b - sqrt(discr);
  if (t < 0.0f) {
    t = 0.0f;
  }

  info.intersPoint = ray->startPos + t * ray->direction;
  info.object = this;
  info.distance = t;

  return true;
}

int Sphere::classifySphere(QVector3D &normal, QVector3D &point,
                           float &distance) {
  // First we need to find the distance our polygon plane is from the origin.
  // We need this for the distance formula below.
  float d = point.distanceToPlane(point, normal);

  // Here we use the famous distance formula to find the distance the center
  // point of the sphere is from the polygon's plane. Remember that the formula
  // is Ax + By + Cz + d = 0 with ABC = Normal, XYZ = Point
  distance = (normal.x() * center.x() + normal.y() * center.y() +
              normal.z() * center.z() + d);

  // Now we query the information just gathered.  Here is how Sphere Plane
  // Collision works: If the distance the center is from the plane is less than
  // the radius of the sphere, we know that it must be intersecting the plane.
  // We take the absolute value of the distance when we do this check because
  // once the center of the sphere goes behind the polygon, the distance turns
  // into negative numbers (with 0 being that the center is exactly on the
  // plane).  What do I mean when I say "behind" the polygon?  How do we know
  // which side is the front or back side?  Well, the side with the normal
  // pointing out from it is the front side, the other side is the back side.
  // This is all dependant on the direction the vertices stored.  I recommend
  // drawing them counter-clockwise. if you go clockwise the normal with then
  // point the opposite way and will screw up everything. So, if we want to find
  // if the sphere is in front of the plane, we just make sure the distance is
  // greater than or equal to the radius.  let's say we have a radius of 5, and
  // the distance the center is from the plane is 6; it's obvious that the
  // sphere is 1 unit away from the plane.
  // If the sphere isn't intersecting or in front of the plane, it HAS to be
  // BEHIND it.

  // If the absolute value of the distance we just found is less than the
  // radius, the sphere intersected the plane.
  if (fabs(distance) < radius)
    return INTERSECTS;
  // Else, if the distance is greater than or equal to the radius, the sphere is
  // completely in FRONT of the plane.
  else if (distance >= radius)
    return FRONT;

  // If the sphere isn't intersecting or in FRONT of the plane, it must be
  // BEHIND
  return BEHIND;
}

bool Sphere::getEdgeSphereCollision(Triangle triangle, bool useHalfRadius) {
  QVector3D point;
  // This function takes in the sphere's center, the polygon's vertices, the
  // vertex count and the radius of the sphere.  We will return true from this
  // function if the sphere is intersecting any of the edges of the polygon. How
  // it works is, every edge line segment finds the closest point on that line
  // to the center of the sphere.  If the distance from that closest point is
  // less than the radius of the sphere, there was a collision.  Otherwise, we
  // are definately out of reach of the polygon.  This works for triangles,
  // quads, and any other convex polygons. Go through all of the vertices in the
  // polygon

  for (int i = 0; i < 3; i++) {
    // This returns the closest point on the current edge to the center of the
    // sphere. Notice that we mod the second point of the edge by our vertex
    // count.  This is so that when we get to the last edge of the polygon, the
    // second vertex of the edge is the first vertex that we starting with.
    point = Vector::getClosestPointOnLine(center, triangle.vertexes[i],
                                          triangle.vertexes[i]);
    // point = center.getClosestPointOnLine(triangle.vertexes[i],
    // triangle.vertexes[(i + 1) % 3]); Now, we want to calculate the distance
    // between the closest point and the center
    float distance = Vector::distanceBetweenVectors(point, center);
    // float distance = point.distanceBetweenVectors(center);
    // If the distance is less than the radius, there must be a collision so
    // return true
    if (useHalfRadius) {
      if (distance < radius / 2) {
        return true;
      }
    } else {
      if (distance < radius) {
        return true;
      }
    }
  }
  // The was no intersection of the sphere and the edges of the polygon
  return false;
}

void Sphere::setRadius(float rad) {
  // std::lock_guard<std::mutex> lck(mtx);
  radius = rad;
}

float Sphere::getRadius() {
  // std::lock_guard<std::mutex> lck(mtx);
  return radius;
}

void Sphere::setCenter(QVector3D newCenter) {
  // std::lock_guard<std::mutex> lck(mtx);
  center.setX(newCenter.x());
  center.setY(newCenter.y());
  center.setZ(newCenter.z());
}

QVector3D Sphere::getCenter() {
  // std::lock_guard<std::mutex> lck(mtx);
  return center;
}
