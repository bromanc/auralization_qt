#include "ofxConvexHull.h"

void ofxConvexHull::generateConvexHull(std::vector<QVector3D> points) {
  quickhull::QuickHull<float> qh; // Could be double as well
  std::vector<quickhull::Vector3<float>> pointCloud;

  for (int i = 0; i < points.size(); i++) {
    quickhull::Vector3<float> aux;
    aux.x = points[i].x();
    aux.y = points[i].y();
    aux.z = points[i].z();
    pointCloud.push_back(aux);
  }

  auto hull = qh.getConvexHull(pointCloud, true, false);
  auto indexBuffer = hull.getIndexBuffer();
  auto vertexBuffer = hull.getVertexBuffer();

  for (int i = 0; i < indexBuffer.size(); i++)
    triangles.push_back(QVector3D(vertexBuffer[indexBuffer[i]].x,
                                  vertexBuffer[indexBuffer[i]].y,
                                  vertexBuffer[indexBuffer[i]].z));
}

QVector3D ofxConvexHull::getTrianglePoint(int index) {
  return triangles[index];
}

int ofxConvexHull::getTrianglePointCount() { return triangles.size(); }
