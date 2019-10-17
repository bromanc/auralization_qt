#ifndef OCTREE_H
#define OCTREE_H

#include "triangle.h"
#include <QVector3D>

#define FLT_MAX 3.402823466e+38F

struct IntersecPoint {
  QVector3D p;
  int lineID;
};

struct CutPlane {
  QVector3D planePoint;
  QVector3D normal;
};

struct Identifiers {
  int idLayer, idPlane, idTrian;

  Identifiers(int idL, int idP, int idT) {
    idLayer = idL;
    idPlane = idP;
    idTrian = idT;
  }

  bool equal(int idL, int idP, int idT) {
    return idLayer == idL && idPlane == idP && idTrian == idT;
  }
};

class Octree {
public:
  Octree *m_pOctreeNodes[8];
  std::vector<Element> nodeTriangles;
  std::vector<Identifiers> ids;

public:
  Octree();
  enum eOctreeNodes {
    TOP_LEFT_FRONT, // 0
    TOP_LEFT_BACK,  // 1
    TOP_RIGHT_BACK, // etc...
    TOP_RIGHT_FRONT,
    BOTTOM_LEFT_FRONT,
    BOTTOM_LEFT_BACK,
    BOTTOM_RIGHT_BACK,
    BOTTOM_RIGHT_FRONT
  };
  bool intersect(Ray &r);
  std::vector<Octree *> fillOctree(std::vector<Element> aux_triangles,
                                   int numSubD);
  void drawRecursive(bool box, bool trian);
  void drawBoundingBox();

private:
  QVector3D m_vCenter;
  float m_Width;
  std::vector<QVector3D> vertexs, vertexs1;

private:
  void getSceneDimensions(std::vector<Element> roomTriangles);
  int getPointNode(QVector3D vPoint, QVector3D vCenter);
  void createNewNode(std::vector<Element> triList, QVector3D vCenter,
                     float width, int nodeID, int numSubD);
  QVector3D getNewNodeCenter(QVector3D vCenter, float width, int nodeID);
  void createNode(std::vector<Element> triangles, QVector3D vCenter,
                  float width, int numSubD);
  void assignVerticesToNode(std::vector<Element> triList);
  float fabs(float v);
  void recursiveFillOctreeArray(std::vector<Octree *> &octreeArray,
                                int numSubD);
  std::vector<Element> createTriangleVector(std::vector<Element> triangles,
                                            CutPlane pCorte);
  std::vector<CutPlane> createCutPlanesVector(QVector3D center, float width,
                                              int numCortes);
  CutPlane createCutPlane(QVector3D center, float width, int id, int idCorte);
  QVector3D createCutPoint(int idEje, int idCorte, float width,
                           QVector3D center);
  std::vector<Element> cutTriangles(Element t1, CutPlane p2);
  bool checkIntersection(Element t1, CutPlane p2);
  std::vector<IntersecPoint> createIntersecPointsVec(Element t1, CutPlane p2);
  bool createInterPointLinePlane(QVector3D &inter, QVector3D pR0, QVector3D pR1,
                                 QVector3D pP, QVector3D normalP);
  bool isBetween(QVector3D a, QVector3D b, QVector3D c);
  void drawBoundingTriangles();
};

#endif // OCTREE_H
