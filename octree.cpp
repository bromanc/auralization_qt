#include "octree.h"
#include "ofxConvexHull/src/ofxConvexHull.h"
#include "ray.h"
#include "vector.h"

Octree::Octree() {
  m_Width = 0;
  for (int i = 0; i < 8; i++) {
    m_pOctreeNodes[i] = nullptr;
  }
}

// This sets the initial width, height and depth for the whole scene
void Octree::getSceneDimensions(std::vector<Element> roomTriangles) {
  // We pass in the list of triangles and the triangle count to get the
  // center point and width of the whole scene.  We use this information
  // to subdivide our octree.
  // Initialize some temporary variables to hold the max dimensions found
  float maxWidth = 0, maxHeight = 0, maxDepth = 0;

  // Below we calculate the center point of the scene.  To do this, all you
  // need to do is add up ALL the vertices, then divide that total by the
  // number of vertices added up.  So all the X's get added up together, then
  // Y's, etc.. This doesn't mean in a single number, but 3 separate floats
  // (totalX, totalY, totalZ). Notice that we are adding 2 vectors together.  If
  // you look in the CVector3 class I overloaded the + and - operator to handle
  // it correctly.  It cuts down on code instead of added the x, then the y,
  // then the z separately.  If you don't want to use operator overloading just
  // make a function called CVector AddVector(), etc... Go through all of the
  // vertices and add them up to eventually find the center

  // Establesing points maximum and minimum for calculate of center room

  double maxX = 0, maxY = 0, maxZ = 0, minX = 0, minY = 0, minZ = 0;

  // For once triangle calculate of cartesian coord in x in y in z

  for (int i = 0; i < roomTriangles.size(); i++) {
    if (maxX < roomTriangles[i].t.vertexes[0].x())
      maxX = roomTriangles[i].t.vertexes[0].x();
    if (minX > roomTriangles[i].t.vertexes[0].x())
      minX = roomTriangles[i].t.vertexes[0].x();
    if (maxX < roomTriangles[i].t.vertexes[1].x())
      maxX = roomTriangles[i].t.vertexes[1].x();
    if (minX > roomTriangles[i].t.vertexes[1].x())
      minX = roomTriangles[i].t.vertexes[1].x();
    if (maxX < roomTriangles[i].t.vertexes[2].x())
      maxX = roomTriangles[i].t.vertexes[2].x();
    if (minX > roomTriangles[i].t.vertexes[2].x())
      minX = roomTriangles[i].t.vertexes[2].x();

    if (maxY < roomTriangles[i].t.vertexes[0].y())
      maxY = roomTriangles[i].t.vertexes[0].y();
    if (minY > roomTriangles[i].t.vertexes[0].y())
      minY = roomTriangles[i].t.vertexes[0].y();
    if (maxY < roomTriangles[i].t.vertexes[1].y())
      maxY = roomTriangles[i].t.vertexes[1].y();
    if (minY > roomTriangles[i].t.vertexes[1].y())
      minY = roomTriangles[i].t.vertexes[1].y();
    if (maxY < roomTriangles[i].t.vertexes[2].y())
      maxY = roomTriangles[i].t.vertexes[2].y();
    if (minY > roomTriangles[i].t.vertexes[2].y())
      minY = roomTriangles[i].t.vertexes[2].y();

    if (maxZ < roomTriangles[i].t.vertexes[0].z())
      maxZ = roomTriangles[i].t.vertexes[0].z();
    if (minZ > roomTriangles[i].t.vertexes[0].z())
      minZ = roomTriangles[i].t.vertexes[0].z();
    if (maxZ < roomTriangles[i].t.vertexes[1].z())
      maxZ = roomTriangles[i].t.vertexes[1].z();
    if (minZ > roomTriangles[i].t.vertexes[1].z())
      minZ = roomTriangles[i].t.vertexes[1].z();
    if (maxZ < roomTriangles[i].t.vertexes[2].z())
      maxZ = roomTriangles[i].t.vertexes[2].z();
    if (minZ > roomTriangles[i].t.vertexes[2].z())
      minZ = roomTriangles[i].t.vertexes[2].z();
  }

  // Calculate cartesian coord of point center room
  m_vCenter.setX((maxX + minX) / 2.0f);
  m_vCenter.setY((maxY + minY) / 2.0f);
  m_vCenter.setZ((maxZ + minZ) / 2.0f);

  // With the cartesian coord establesh the width height and deph of cubo thath
  // on room
  maxWidth = fabs(maxX) + fabs(minX);
  maxHeight = fabs(maxZ) + fabs(minZ);
  maxDepth = fabs(maxY) + fabs(minY);

  // Check if the width is the highest value and assign that for the cube
  // dimension
  if (maxWidth > maxHeight && maxWidth > maxDepth)
    m_Width = maxWidth;

  // Check if the height is the heighest value and assign that for the cube
  // dimension
  else if (maxHeight > maxWidth && maxHeight > maxDepth)
    m_Width = maxHeight;

  // Else it must be the depth or it's the same value as some of the other ones
  else
    m_Width = maxDepth;
}

int Octree::getPointNode(QVector3D vPoint, QVector3D vCenter) {
  QVector3D vCtr = vCenter;

  // Check if the point lines within the TOP LEFT FRONT node
  if ((vPoint.x() <= vCtr.x()) && (vPoint.y() >= vCtr.y()) &&
      (vPoint.z() >= vCtr.z()))
    return TOP_LEFT_FRONT;

  // Check if the point lines within the TOP LEFT BACK node
  if ((vPoint.x() <= vCtr.x()) && (vPoint.y() >= vCtr.y()) &&
      (vPoint.z() <= vCtr.z()))
    return TOP_LEFT_BACK;

  // Check if the point lines within the TOP RIGHT BACK node
  if ((vPoint.x() >= vCtr.x()) && (vPoint.y() >= vCtr.y()) &&
      (vPoint.z() <= vCtr.z()))
    return TOP_RIGHT_BACK;

  // Check if the point lines within the TOP RIGHT FRONT node
  if ((vPoint.x() >= vCtr.x()) && (vPoint.y() >= vCtr.y()) &&
      (vPoint.z() >= vCtr.z()))
    return TOP_RIGHT_FRONT;

  // Check if the point lines within the BOTTOM LEFT FRONT node
  if ((vPoint.x() <= vCtr.x()) && (vPoint.y() <= vCtr.y()) &&
      (vPoint.z() >= vCtr.z()))
    return BOTTOM_LEFT_FRONT;

  // Check if the point lines within the BOTTOM LEFT BACK node
  if ((vPoint.x() <= vCtr.x()) && (vPoint.y() <= vCtr.y()) &&
      (vPoint.z() <= vCtr.z()))
    return BOTTOM_LEFT_BACK;

  // Check if the point lines within the BOTTOM RIGHT BACK node
  if ((vPoint.x() >= vCtr.x()) && (vPoint.y() <= vCtr.y()) &&
      (vPoint.z() <= vCtr.z()))
    return BOTTOM_RIGHT_BACK;

  // Check if the point lines within the BOTTOM RIGHT FRONT node
  if ((vPoint.x() >= vCtr.x()) && (vPoint.y() <= vCtr.y()) &&
      (vPoint.z() >= vCtr.z()))
    return BOTTOM_RIGHT_FRONT;

  return -1;
}

void Octree::createNewNode(std::vector<Element> triList, QVector3D vCenter,
                           float width, int nodeID, int numSubD) {
  // This function helps us set up the new node that is being created.  We only
  // want to create a new node if it found triangles in it's area.  If there
  // were no triangle found in this node's cube, then we ignore it and don't
  // create a node. Check if the first node found some triangles in it
  if (triList.size()) {
    // Now comes the initialization of the node.  First we allocate memory for
    // our node and then get it's center point.  Depending on the nodeID,
    // getNewNodeCenter() knows which center point to pass back (TOP_LEFT_FRONT,
    // etc..)

    // Allocate a new node for this octree
    m_pOctreeNodes[nodeID] = new Octree;

    // Get the new node's center point depending on the nodexIndex (which of the
    // 8 subdivided cubes).
    QVector3D vNodeCenter = getNewNodeCenter(vCenter, width, nodeID);

    // Below, before and after we recurse further down into the tree, we keep
    // track of the level of subdivision that we are in.  This way we can
    // restrict it.

    // Recurse through this node and subdivide it if necessary
    m_pOctreeNodes[nodeID]->createNode(triList, vNodeCenter, width / 2,
                                       numSubD);
  }
}

QVector3D Octree::getNewNodeCenter(QVector3D vCenter, float width, int nodeID) {
  // I created this function which takes an enum ID to see which node's center
  // we need to calculate.  Once we find that we need to subdivide a node we
  // find the centers of each of the 8 new nodes.  This is what that function
  // does. We just tell it which node we want. Initialize the new node center
  QVector3D vNodeCenter;

  // Create a dummy variable to cut down the code size
  QVector3D vCtr = vCenter;

  // Switch on the ID to see which subdivided node we are finding the center
  switch (nodeID) {
  case TOP_LEFT_FRONT:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() - width / 4, vCtr.y() + width / 4,
                            vCtr.z() + width / 4);
    break;

  case TOP_LEFT_BACK:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() - width / 4, vCtr.y() + width / 4,
                            vCtr.z() - width / 4);
    break;

  case TOP_RIGHT_BACK:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() + width / 4, vCtr.y() + width / 4,
                            vCtr.z() - width / 4);
    break;

  case TOP_RIGHT_FRONT:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() + width / 4, vCtr.y() + width / 4,
                            vCtr.z() + width / 4);
    break;

  case BOTTOM_LEFT_FRONT:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() - width / 4, vCtr.y() - width / 4,
                            vCtr.z() + width / 4);
    break;

  case BOTTOM_LEFT_BACK:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() - width / 4, vCtr.y() - width / 4,
                            vCtr.z() - width / 4);
    break;

  case BOTTOM_RIGHT_BACK:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() + width / 4, vCtr.y() - width / 4,
                            vCtr.z() - width / 4);
    break;

  case BOTTOM_RIGHT_FRONT:
    // Calculate the center of this new node
    vNodeCenter = QVector3D(vCtr.x() + width / 4, vCtr.y() - width / 4,
                            vCtr.z() + width / 4);
    break;
  }

  // Return the new node center
  return vNodeCenter;
}

void Octree::createNode(std::vector<Element> triangles, QVector3D vCenter,
                        float width, int numSubD) {
  // This is our main function that creates the octree.  We will recurse through
  // this function until we finish subdividing.  Either this will be because we
  // subdivided too many levels or we divided all of the triangles up.
  // Create a variable to hold the number of triangles
  // int numberOfTriangles = numberOfVerts / 3;
  // Initialize this node's center point.  Now we know the center of this node.
  m_vCenter = vCenter;
  // Initialize this nodes cube width.  Now we know the width of this current
  // node.
  m_Width = width;

  QVector3D vc1, vc2;

  vc1.setX(m_vCenter.x() + (m_Width / 2.0f));
  vc1.setY(m_vCenter.y() + (m_Width / 2.0f));
  vc1.setZ(m_vCenter.z() + (m_Width / 2.0f));
  vertexs1.push_back(vc1);

  vc2.setX(m_vCenter.x() - (m_Width / 2.0f));
  vc2.setY(m_vCenter.y() - (m_Width / 2.0f));
  vc2.setZ(m_vCenter.z() - (m_Width / 2.0f));
  vertexs1.push_back(vc2);
  vertexs.resize(8);

  /*
   Vertices cubo
   */
  vertexs[0].setX(m_vCenter.x() + (m_Width / 2.0f));
  vertexs[0].setY(m_vCenter.y() + (m_Width / 2.0f));
  vertexs[0].setZ(m_vCenter.z() + (m_Width / 2.0f));

  vertexs[1].setX(m_vCenter.x() + (m_Width / 2.0f));
  vertexs[1].setY(m_vCenter.y() - (m_Width / 2.0f));
  vertexs[1].setZ(m_vCenter.z() + (m_Width / 2.0f));

  vertexs[2].setX(m_vCenter.x() - (m_Width / 2.0f));
  vertexs[2].setY(m_vCenter.y() - (m_Width / 2.0f));
  vertexs[2].setZ(m_vCenter.z() + (m_Width / 2.0f));

  vertexs[3].setX(m_vCenter.x() - (m_Width / 2.0f));
  vertexs[3].setY(m_vCenter.y() + (m_Width / 2.0f));
  vertexs[3].setZ(m_vCenter.z() + (m_Width / 2.0f));

  vertexs[4].setX(m_vCenter.x() + (m_Width / 2.0f));
  vertexs[4].setY(m_vCenter.y() + (m_Width / 2.0f));
  vertexs[4].setZ(m_vCenter.z() - (m_Width / 2.0f));

  vertexs[5].setX(m_vCenter.x() + (m_Width / 2.0f));
  vertexs[5].setY(m_vCenter.y() - (m_Width / 2.0f));
  vertexs[5].setZ(m_vCenter.z() - (m_Width / 2.0f));

  vertexs[6].setX(m_vCenter.x() - (m_Width / 2.0f));
  vertexs[6].setY(m_vCenter.y() - (m_Width / 2.0f));
  vertexs[6].setZ(m_vCenter.z() - (m_Width / 2.0f));

  vertexs[7].setX(m_vCenter.x() - (m_Width / 2.0f));
  vertexs[7].setY(m_vCenter.y() + (m_Width / 2.0f));
  vertexs[7].setZ(m_vCenter.z() - (m_Width / 2.0f));

  // Check if we have too many triangles in this node and we haven't subdivided
  // above our max subdivisions.  If so, then we need to break this node into
  // 8 more nodes (hence the word OCTree).  Both must be true to divide this
  // node.
  if (numSubD > 0) {
    // Since we need to subdivide more we set the divided flag to true.
    // This let's us know that this node does NOT have any vertices assigned to
    // it, but nodes that perhaps have vertices stored in them (Or their nodes,
    // etc....) We will querey this variable when we are drawing the octree.

    // Create a list for each new node to store if a triangle should be stored
    // in it's triangle list.  For each index it will be a true or false to tell
    // us if that triangle is in the cube of that node.  Below we check every
    // point to see where it's position is from the center (I.E. if it's above
    // the center, to the left and back it's the TOP_LEFT_BACK node).  Depending
    // on the node we set the pList index to true.  This will tell us later
    // which triangles go to which node. You might catch that this way will
    // produce doubles in some nodes.  Some triangles will intersect more than 1
    // node right?  We won't split the triangles in this tutorial just to keep
    // it simple, but the next tutorial we will.

    std::vector<Element> pList[8];

    // Go through all of the vertices and check which node they belong too.  The
    // way we do this is use the center of our current node and check where the
    // point lies in relationship to the center.  For instance, if the point is
    // above, left and back from the center point it's the TOP_LEFT_BACK node.
    // You'll see we divide by 3 because there are 3 points in a triangle.
    // If the vertex index 0 and 1 are in a node, 0 / 3 and 1 / 3 is 0 so it
    // will just set the 0'th index to TRUE twice, which doesn't hurt anything.
    // When we get to the 3rd vertex index of pVertices[] it will then be
    // checking the 1st index of the pList*[] array.  We do this because we want
    // a list of the triangles in the node, not the vertices.

    QVector3D centro;
    int pNode = -1;

    for (int i = 0; i < triangles.size(); i++) {
      centro.setX((triangles[i].t.vertexes[0].x() +
                   triangles[i].t.vertexes[1].x() +
                   triangles[i].t.vertexes[2].x()) /
                  3);
      centro.setY((triangles[i].t.vertexes[0].y() +
                   triangles[i].t.vertexes[1].y() +
                   triangles[i].t.vertexes[2].y()) /
                  3);
      centro.setZ((triangles[i].t.vertexes[0].z() +
                   triangles[i].t.vertexes[1].z() +
                   triangles[i].t.vertexes[2].z()) /
                  3);

      pNode = getPointNode(centro, vCenter);
      pList[pNode].push_back(triangles[i]);
    }

    // assignVerticesToNode(actualNodeTriangles);

    // Next we do the dirty work.  We need to set up the new nodes with the
    // triangles that are assigned to each node, along with the new center point
    // of the node. Through recursion we subdivide this node into 8 more nodes.
    // Create the subdivided nodes if necessary and then recurse through them.
    // The information passed into CreateNewNode() are essential for creating
    // the new nodes.  We pass the 8 ID's in so it knows how to calculate it's
    // new center.

    numSubD--;

    createNewNode(pList[TOP_LEFT_FRONT], vCenter, width, TOP_LEFT_FRONT,
                  numSubD);
    createNewNode(pList[TOP_LEFT_BACK], vCenter, width, TOP_LEFT_BACK, numSubD);
    createNewNode(pList[TOP_RIGHT_BACK], vCenter, width, TOP_RIGHT_BACK,
                  numSubD);
    createNewNode(pList[TOP_RIGHT_FRONT], vCenter, width, TOP_RIGHT_FRONT,
                  numSubD);
    createNewNode(pList[BOTTOM_LEFT_FRONT], vCenter, width, BOTTOM_LEFT_FRONT,
                  numSubD);
    createNewNode(pList[BOTTOM_LEFT_BACK], vCenter, width, BOTTOM_LEFT_BACK,
                  numSubD);
    createNewNode(pList[BOTTOM_RIGHT_BACK], vCenter, width, BOTTOM_RIGHT_BACK,
                  numSubD);
    createNewNode(pList[BOTTOM_RIGHT_FRONT], vCenter, width, BOTTOM_RIGHT_FRONT,
                  numSubD);
  } else {
    // If we get here we must either be subdivided past our max level, or our
    // triangle count went below the minimum amount of triangles so we need to
    // store them.

    // Assign the vertices to this node since we reached the end node.
    // This will be the end node that actually gets called to be drawn.
    // We just pass in the vertices and vertex count to be assigned to this
    // node.
    // AssignVerticesToNode(pVertices, numberOfVerts);
    assignVerticesToNode(triangles);
  }
}

void Octree::assignVerticesToNode(std::vector<Element> triList) {
  for (int i = 0; i < triList.size(); i++) {
    nodeTriangles.push_back(triList[i]);
    if (i != 0) {
      bool aux = true;
      for (int j = 0; j < ids.size(); j++) {
        if (ids[j].equal(triList[i].layerID, triList[i].planeID,
                         triList[i].triangleID)) {
          aux = false;
          break;
        }
      }

      if (aux) {
        ids.push_back(Identifiers(triList[i].layerID, triList[i].planeID,
                                  triList[i].triangleID));
      }
    } else {
      ids.push_back(Identifiers(triList[i].layerID, triList[i].planeID,
                                triList[i].triangleID));
    }
  }
}

float Octree::fabs(float v) { return v * ((v < 0) * (-1) + (v > 0)); }

bool Octree::intersect(Ray &r) {
  // Caso en que el origen del rayo este dentro del cubo
  /*if (r.startPos.x() >= vertexs1[1].x()  && r.startPos.x() <= vertexs1[0].x())
      if (r.startPos.y() >= vertexs1[1].y()  && r.startPos.y() <=
  vertexs1[0].y()) if (r.startPos.z() >= vertexs1[1].z()  && r.startPos.z() <=
  vertexs1[0].z()) return true;

  float t;

  // lb is the corner of AABB with minimal coordinates - left bottom, rt is
  maximal corner
  // r.org is origin of ray
  float t1 = (vertexs1[1].x() - r.startPos.x())*(1.0 / r.direction.x());
  float t2 = (vertexs1[0].x() - r.startPos.x())*(1.0 / r.direction.x());
  float t3 = (vertexs1[1].y() - r.startPos.y())*(1.0 / r.direction.y());
  float t4 = (vertexs1[0].y() - r.startPos.y())*(1.0 / r.direction.y());
  float t5 = (vertexs1[1].z() - r.startPos.z())*(1.0 / r.direction.z());
  float t6 = (vertexs1[0].z() - r.startPos.z())*(1.0 / r.direction.z());

  float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)),
  std::min(t5, t6)); float tmax = std::min(std::min(std::max(t1, t2),
  std::max(t3, t4)), std::max(t5, t6));

  // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
  if (tmax < 0)
  {
      t = tmax;
      return false;
  }

  // if tmin > tmax, ray doesn't intersect AABB
  if (tmin > tmax)
  {
      t = tmax;
      return false;
  }

  t = tmin;
  return true;*/

  float tmin, tmax, tymin, tymax, tzmin, tzmax;
  float invX = (1.0 / r.direction.x()), invY = (1.0 / r.direction.y()),
        invZ = (1.0 / r.direction.z());

  tmin = (vertexs1[1 - (invX < 0)].x() - r.startPos.x()) * invX;
  tmax = (vertexs1[invX < 0].x() - r.startPos.x()) * invX;
  tymin = (vertexs1[1 - (invY < 0)].y() - r.startPos.y()) * invY;
  tymax = (vertexs1[invY < 0].y() - r.startPos.y()) * invY;
  if ((tmin > tymax) || (tymin > tmax))
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;
  tzmin = (vertexs1[1 - (invZ < 0)].z() - r.startPos.z()) * invZ;
  tzmax = (vertexs1[invZ < 0].z() - r.startPos.z()) * invZ;
  if ((tmin > tzmax) || (tzmin > tmax))
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;
  return ((tmin < +FLT_MAX) && (tmax > 0.0));

  /*for (int i = 0; i < boundingTriangles.size(); i++)
  {
      double dist = -1;
      Vec3f intersection;
      if (boundingTriangles[i].intersectsTriangle(&r, dist, intersection))
      {
          return true;
      }
  }
  return false;*/
}

// This fills the octree with the triangles from the room
std::vector<Octree *> Octree::fillOctree(std::vector<Element> roomTriangles,
                                         int numSubD) {
  // Obtain the dimensions for the room
  getSceneDimensions(roomTriangles);

  // Obtain a vector with the planes to cut the room's triangles
  std::vector<CutPlane> cutPlanes =
      createCutPlanesVector(m_vCenter, m_Width / 2, numSubD);
  std::vector<Element> cutTriangles;

  // We have to cut the original triangles with all the cutting planes
  for (int i = 0; i < cutPlanes.size(); i++) {
    // We create the vector of triangles generated by each of the cutting planes
    cutTriangles = createTriangleVector(roomTriangles, cutPlanes[i]);

    // clear the original vector of triangles to fill it with the ones generated
    // in the cutting process
    roomTriangles.clear();
    for (int j = 0; j < cutTriangles.size(); j++) {
      roomTriangles.push_back(cutTriangles[j]);
    }

    cutTriangles.clear();
  }

  // We fill in the octree with the new triangles in this case we subdivide
  // recursively the octree 3 times
  createNode(roomTriangles, m_vCenter, m_Width, numSubD);

  // return an array of not null octrees
  std::vector<Octree *> octreeArray;
  recursiveFillOctreeArray(octreeArray, numSubD);
  return octreeArray;
}

void Octree::recursiveFillOctreeArray(std::vector<Octree *> &octreeArray,
                                      int numSubD) {
  for (int i = 0; i < 8; i++) {
    if (m_pOctreeNodes[i] != NULL) {
      if (numSubD > 1) {
        int actualDiv = numSubD - 1;
        m_pOctreeNodes[i]->recursiveFillOctreeArray(octreeArray, actualDiv);
      }
      if (numSubD == 1) {
        octreeArray.push_back(m_pOctreeNodes[i]);
      }
    }
  }
}

// This creates a new vector of triangles given a cutting plane
std::vector<Element>
Octree::createTriangleVector(std::vector<Element> triangles,
                             CutPlane cutPlane) {
  std::vector<Element> newTriangles, tempTriangles;

  for (int i = 0; i < triangles.size(); i++) {
    // We check if exists intersection between cutPlane and the actual triangle
    if (checkIntersection(triangles[i], cutPlane)) {
      // We create the triangles generated by the cutting plane
      tempTriangles = cutTriangles(triangles[i], cutPlane);
      for (int j = 0; j < tempTriangles.size(); j++) {
        // We store the generated triangles in the vector to return
        newTriangles.push_back(tempTriangles[j]);
      }
      tempTriangles.clear();
    }
    // If there is no intersection we store the original triangle
    else {
      newTriangles.push_back(triangles[i]);
    }
  }

  return newTriangles;
}

// This creates the vector of cutting planes of the room
std::vector<CutPlane>
Octree::createCutPlanesVector(QVector3D center, float width, int cutNumber) {
  // Since we have to cut each axis of the room depending on the cut number,
  // we need to calculate the number of cuts.
  // For example if we have a cutNumber '2', the axisCuts is 2 because we
  // have the center cut and a positive and a negative, having in total 3. But
  // being at the same distance from the center we only need one of them the
  // other is just the negative.
  //
  // |------|------|------|------|
  //       (-)   center  (+)
  //
  int axisCuts = int(pow(2.0, cutNumber - 1.0));

  // We calculate move from the center to each of the sides
  float axisMove = width / axisCuts;
  std::vector<CutPlane> cutPlanes;

  // We do this for each of the axis (x, y, z)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < axisCuts; j++) {
      // For each of the axisCuts we create the cutting plane in that position.
      // When we are in the first axisCuts we only create one that is in the
      // center of the axis
      cutPlanes.push_back(createCutPlane(center, axisMove, i, j));

      // Otherwise we need to create the cutting plane in the respective
      // negative position
      if (j != 0) {
        cutPlanes.push_back(createCutPlane(center, axisMove, i, -j));
      }
    }
  }

  return cutPlanes;
}

// This creates a cutting plane given the center point of the room
CutPlane Octree::createCutPlane(QVector3D center, float width, int axisID,
                                int cutID) {
  CutPlane cutPlane;

  // We create the point that defines the cutting plane
  cutPlane.planePoint = createCutPoint(axisID, cutID, width, center);

  // Depending on the axis we define the normal vector of the plane
  switch (axisID) {
  case 0:
    cutPlane.normal = QVector3D(1.0, 0, 0);
    break;
  case 1:
    cutPlane.normal = QVector3D(0, 1.0, 0);
    break;
  case 2:
    cutPlane.normal = QVector3D(0, 0, 1.0);
    break;
  }

  return cutPlane;
}

// This creates the point of the cutting plane depending on the axis and the cut
QVector3D Octree::createCutPoint(int axisID, int cutID, float width,
                                 QVector3D center) {
  QVector3D cutPoint;

  // If the cutID is 0 we return the same center point
  if (cutID == 0) {
    cutPoint = center;
  } else {
    // If not, it depends on the axisID. For example if the axis is X
    // the point moves the x coordinate and so on.
    switch (axisID) {
    case 0:
      cutPoint =
          QVector3D(center.x() + (cutID * width), center.y(), center.z());
      break;
    case 1:
      cutPoint =
          QVector3D(center.x(), center.y() + (cutID * width), center.z());
      break;
    case 2:
      cutPoint =
          QVector3D(center.x(), center.y(), center.z() + (cutID * width));
      break;
    }
  }

  return cutPoint;
}

// This creates the triangles generated by cutting with the plane
std::vector<Element> Octree::cutTriangles(Element triangle, CutPlane cutPlane) {
  std::vector<Element> newTriangles;
  std::vector<IntersecPoint> intersecPoints;
  std::vector<std::vector<QVector3D>> points;
  ofxConvexHull ofx;
  points.resize(2);

  // We create a vector of points generated by the intersection
  // between the triangle and the cutting plane
  intersecPoints = createIntersecPointsVec(triangle, cutPlane);

  //
  //		 p1
  //	      /\
    //	   1 /  \ 0
  //	  --/----\--
  //	   /      \
    // p2 /________\ p0
  //
  switch (intersecPoints[0].lineID) {
  case 0:
    points[0].push_back(triangle.t.vertexes[0]);
    points[0].push_back(intersecPoints[0].p);
    points[0].push_back(intersecPoints[1].p);

    if (intersecPoints[1].lineID == 1 &&
        !Vector::compareVectors(intersecPoints[1].p, triangle.t.vertexes[2])) {
      points[0].push_back(triangle.t.vertexes[2]);
    }

    points[1].push_back(intersecPoints[0].p);

    if (!Vector::compareVectors(intersecPoints[0].p, triangle.t.vertexes[1])) {
      points[1].push_back(triangle.t.vertexes[1]);
    } else {
      points[1].push_back(triangle.t.vertexes[2]);
    }

    if (intersecPoints[1].lineID == 2 &&
        !Vector::compareVectors(intersecPoints[0].p, triangle.t.vertexes[1])) {
      points[1].push_back(triangle.t.vertexes[2]);
      points[1].push_back(intersecPoints[1].p);
    } else {
      points[1].push_back(intersecPoints[1].p);
    }
    break;

  case 1:
    points[0].push_back(triangle.t.vertexes[0]);
    points[0].push_back(triangle.t.vertexes[1]);
    points[0].push_back(intersecPoints[0].p);

    if (!Vector::compareVectors(intersecPoints[1].p, triangle.t.vertexes[0])) {
      points[0].push_back(intersecPoints[1].p);
    }

    points[1].push_back(intersecPoints[0].p);
    points[1].push_back(triangle.t.vertexes[2]);
    points[1].push_back(intersecPoints[1].p);
    break;

  default:
    break;
  }

  Element e;
  e.layerID = triangle.layerID;
  e.planeID = triangle.planeID;
  e.triangleID = triangle.triangleID;
  e.normal = triangle.normal;
  for (int i = 0; i < 2; i++) {
    if (points[i].size() == 4) {
      ofx.generateConvexHull(points[i]);
      e.t = Triangle(ofx.getTrianglePoint(0), ofx.getTrianglePoint(1),
                     ofx.getTrianglePoint(2));
      newTriangles.push_back(e);
      e.t = Triangle(ofx.getTrianglePoint(9), ofx.getTrianglePoint(10),
                     ofx.getTrianglePoint(11));
      newTriangles.push_back(e);
    } else {
      e.t = Triangle(points[i][0], points[i][1], points[i][2]);
      newTriangles.push_back(e);
    }
  }

  return newTriangles;
}

bool Octree::checkIntersection(Element t1, CutPlane p2) {
  QVector3D inter;
  std::vector<QVector3D> aux;
  bool temp = false;

  if (createInterPointLinePlane(inter, t1.t.vertexes[0], t1.t.vertexes[1],
                                p2.planePoint, p2.normal)) {
    aux.push_back(inter);
    temp = true;
  }

  if (createInterPointLinePlane(inter, t1.t.vertexes[1], t1.t.vertexes[2],
                                p2.planePoint, p2.normal)) {
    aux.push_back(inter);
    temp = true;
  }

  if (createInterPointLinePlane(inter, t1.t.vertexes[0], t1.t.vertexes[2],
                                p2.planePoint, p2.normal)) {
    aux.push_back(inter);
    temp = true;
  }

  switch (aux.size()) {
  case 1:
    temp = false;
    break;
  default:
    if (temp) {
      if (Vector::compareVectors(aux[0], aux[1])) {
        if (aux.size() == 3) {
          aux[1] = aux[2];
        } else {
          temp = false;
        }
      }

      if (Vector::compareVectors(aux[0], t1.t.vertexes[0]) ||
          Vector::compareVectors(aux[0], t1.t.vertexes[1]) ||
          Vector::compareVectors(aux[0], t1.t.vertexes[2])) {
        if (Vector::compareVectors(aux[1], t1.t.vertexes[0]) ||
            Vector::compareVectors(aux[1], t1.t.vertexes[1]) ||
            Vector::compareVectors(aux[1], t1.t.vertexes[2])) {
          temp = false;
        }
      }
    }
    break;
  }

  return temp;
}

std::vector<IntersecPoint> Octree::createIntersecPointsVec(Element t1,
                                                           CutPlane p2) {
  QVector3D inter;
  std::vector<IntersecPoint> aux;
  IntersecPoint temp;

  if (createInterPointLinePlane(inter, t1.t.vertexes[0], t1.t.vertexes[1],
                                p2.planePoint, p2.normal)) {
    temp.p = inter;
    temp.lineID = 0;
    aux.push_back(temp);
  }

  if (createInterPointLinePlane(inter, t1.t.vertexes[1], t1.t.vertexes[2],
                                p2.planePoint, p2.normal)) {
    temp.p = inter;
    temp.lineID = 1;
    aux.push_back(temp);
  }

  if (createInterPointLinePlane(inter, t1.t.vertexes[0], t1.t.vertexes[2],
                                p2.planePoint, p2.normal)) {
    temp.p = inter;
    temp.lineID = 2;
    aux.push_back(temp);
  }

  if (Vector::compareVectors(aux[0].p, aux[1].p) && aux.size() == 3) {
    aux[1].p = aux[2].p;
    aux[1].lineID = aux[2].lineID;
    aux.pop_back();
  }

  return aux;
}

bool Octree::createInterPointLinePlane(QVector3D &inter, QVector3D pR0,
                                       QVector3D pR1, QVector3D pP,
                                       QVector3D normalP) {
  double epsilon = 1e-6, dot, fac;
  QVector3D u, w;

  u = pR1 - pR0;
  dot = QVector3D::dotProduct(normalP, u);

  if (abs(dot) > epsilon) {
    w = pR0 - pP;
    fac = QVector3D::dotProduct(normalP, w) / dot;
    u = u * fac;

    inter = pR0 + u;

    if (isBetween(pR0, pR1, inter)) {
      return true;
    } else {
      return false;
    }

  } else {
    return false;
  }
}

bool Octree::isBetween(QVector3D a, QVector3D b, QVector3D c) {
  QVector3D u, w;

  u = b - a;
  w = c - a;

  if (QVector3D::dotProduct(u, w) >= 0 &&
      QVector3D::dotProduct(u, w) <= QVector3D::dotProduct(u, u)) {
    return true;
  }

  return false;
}

/*void Octree::drawRecursive(bool box, bool trian)
{
    if (box && trian)
    {
        drawBoundingBox();
        drawBoundingTriangles();
    }
    else if (box)
    {
        drawBoundingBox();
    }
    else if (trian)
    {
        drawBoundingTriangles();
    }
    else
    {
        return;
    }

    for (int i = 0; i<8; i++)
    {
        if (m_pOctreeNodes[i] != NULL)
        {
            m_pOctreeNodes[i]->drawRecursive(box, trian);
        }
    }
}

void Octree::drawBoundingBox()
{
    glColor3f(0.11, 0.5, 0.14);

    glBegin(GL_LINE_LOOP);

    glVertex3f(vertexs[0].x(), vertexs[0].y(), vertexs[0].z());
    glVertex3f(vertexs[1].x(), vertexs[1].y(), vertexs[1].z());
    glVertex3f(vertexs[2].x(), vertexs[2].y(), vertexs[2].z());
    glVertex3f(vertexs[3].x(), vertexs[3].y(), vertexs[3].z());
    glVertex3f(vertexs[0].x(), vertexs[0].y(), vertexs[0].z());
    glVertex3f(vertexs[4].x(), vertexs[4].y(), vertexs[4].z());
    glVertex3f(vertexs[5].x(), vertexs[5].y(), vertexs[5].z());
    glVertex3f(vertexs[6].x(), vertexs[6].y(), vertexs[6].z());
    glVertex3f(vertexs[7].x(), vertexs[7].y(), vertexs[7].z());
    glVertex3f(vertexs[4].x(), vertexs[4].y(), vertexs[4].z());
    glVertex3f(vertexs[5].x(), vertexs[5].y(), vertexs[5].z());
    glVertex3f(vertexs[1].x(), vertexs[1].y(), vertexs[1].z());
    glVertex3f(vertexs[2].x(), vertexs[2].y(), vertexs[2].z());
    glVertex3f(vertexs[6].x(), vertexs[6].y(), vertexs[6].z());
    glVertex3f(vertexs[7].x(), vertexs[7].y(), vertexs[7].z());
    glVertex3f(vertexs[3].x(), vertexs[3].y(), vertexs[3].z());

    glEnd();
}

void Octree::drawBoundingTriangles()
{
    for (int i = 0; i < nodeTriangles.size(); i++)
    {
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(nodeTriangles[i].t.vertexes[0].x(),
nodeTriangles[i].t.vertexes[0].y(), nodeTriangles[i].t.vertexes[0].z());
        glVertex3f(nodeTriangles[i].t.vertexes[1].x(),
nodeTriangles[i].t.vertexes[1].y(), nodeTriangles[i].t.vertexes[1].z());
        glVertex3f(nodeTriangles[i].t.vertexes[2].x(),
nodeTriangles[i].t.vertexes[2].y(), nodeTriangles[i].t.vertexes[2].z());
        glEnd();
    }
}*/
