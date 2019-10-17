#ifndef ofxConvexHull_hpp
#define ofxConvexHull_hpp

#include "../libs/QuickHull.hpp"
#include <QVector3D>

class ofxConvexHull {

public:
  void generateConvexHull(std::vector<QVector3D> points);
  QVector3D getTrianglePoint(int index);
  int getTrianglePointCount();
  void clean() { triangles.clear(); }

private:
  std::vector<QVector3D> triangles;
};

#endif /* ofxConvexHull_hpp */
