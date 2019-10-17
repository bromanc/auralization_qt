#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QMessageBox>
#include <QVector3D>
#include <atomic>
#include <impulseresponse.h>
#include <mutex>
#include <omp.h>
#include <string>

#define DEBUG_RAYOS 1

class RayTracer {

public:
  static enum auralizationMethod { neural, hrtf, impulse };

  RayTracer() {
    isTracing = false;

    omniSource.setPosition(QVector3D(3, 3, 3));

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    roomTemp = 21;
  }

  ~RayTracer() {}

  void run() override {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    int numberThreads = omp_get_max_threads();
    const int size = 256;
    double sinTable[size];

#pragma omp parallel for
    for (int n = 0; n < size; ++n)
      sinTable[n] = std::sin(2 * M_PI * n / size);

    room.setTemperature(roomTemp);
    room.calculateRoomParams();
    sourceCollisions.clear();
    collisions.clear();

    setStatusMessage("Tracing...");

    std::lock_guard<std::mutex> lck(mtx);
    omniSource.generateRays(rayNumber, initialEnergy);
    int lostRays = 0;
    int numRays = omniSource.getNumRays();

    /*std::ofstream fss("puntosesfera.txt");
    for (int r = 0; r < numRays; r++)
    {
        sourceCollisions.push_back(Vec3f());
        sourceCollisions[r].x = omniSource.rays[r].direction.x;
        fss << omniSource.rays[r].direction.x << ",";
    }
    fss << "\n";
    for (int r = 0; r < numRays; r++)
    {
        sourceCollisions[r].y = omniSource.rays[r].direction.y;
        fss << omniSource.rays[r].direction.y << ",";
    }
    fss << "\n";
    for (int r = 0; r < numRays; r++)
    {
        sourceCollisions[r].z = omniSource.rays[r].direction.z;
        fss << omniSource.rays[r].direction.z << ",";
    }
    fss.close();*/

    isTracing = true;

    std::vector<float> minEnergy;
    for (int i = 0; i < 6; i++) {
      minEnergy.push_back(omniSource.rays[0].bands.getEnegy(i) * pow(10, -6));
    }

    for (int r = 0; r < rayNumber; r++) {
      double progress = (r * (rayNumber / 100.0f)) / numRays;
      setProgress(progress); // setting a value beyond the range 0 -> 1 will
                             // show a spinning bar..
      omniSource.rays[r].distance = 0;

      // Collision triangle

      Ray currentRay = omniSource.rays[r];

      sourceCollisions.push_back(std::vector<Vec3f>());
      sourceCollisions[r].push_back(currentRay.startPos);

      if (!octreeSwitch) {
        sequencialRayTracing(r, numRays, currentRay, minEnergy, lostRays);
      } else {
        // octree
        octreeRayTracing(r, numRays, currentRay, minEnergy, lostRays);
      }
    }

    end = std::chrono::system_clock::now();

    tracingTime =
        std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

#ifdef DEBUG_RAYOS
    std::ofstream fss("rayosLlegada.txt");
    Ray temporal;
    for (int i = 0; i < receiver.receptedRays.size(); i++) {
      temporal = receiver.receptedRays[i];
      fss << "Rayo " << i << ":\n";
      fss << "\tStart Posicion:\n";
      fss << "\t\tx: " << temporal.startPos.x
          << "\n\t\ty: " << temporal.startPos.y
          << "\n\t\tz: " << temporal.startPos.z << "\n";
      fss << "\tDirection:\n";
      fss << "\t\tx: " << temporal.direction.x
          << "\n\t\ty: " << temporal.direction.y
          << "\n\t\tz: " << temporal.direction.z << "\n";
      fss << "\Energy Bands:\n";
      fss << "\t\t" << temporal.bands.getEnegy(0) << "\n\t\t"
          << temporal.bands.getEnegy(1) << "\n\t\t"
          << temporal.bands.getEnegy(2) << "\n\t\t"
          << temporal.bands.getEnegy(3) << "\n\t\t"
          << temporal.bands.getEnegy(4) << "\n\t\t"
          << temporal.bands.getEnegy(5) << "\n\n";
    }
    fss.close();

    std::ofstream time("tiempo.txt");
    time << "Tiempo " << tracingTime << " segundos\n";
    time.close();
#endif

    isTracing = false;

    if (!threadShouldExit()) {
      start = std::chrono::system_clock::now();

      setStatusMessage("Auralizaing...");
      auralize();
      setStatusMessage("Finished");
      // thumbComponent->loadFile();
      sendChangeMessage();

      end = std::chrono::system_clock::now();

      auralizationTime =
          std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }
  }
  //----------------------------------------------------------------------------------------------
  void sequencialRayTracing(int &r, int numRays, Ray currentRay,
                            std::vector<float> minEnergy, int &lostRays) {
    Vec3f auxIntersection;
    int counter = 0;
    bool stop = false;
    int triangleIndex = -1;
    double nearDistance = std::numeric_limits<double>::max();
    int planeIndex = -1;
    int layerIndex = -1;
    for (int i = 0; i < room.layers.size(); i++) {
      if (threadShouldExit()) {
        r = numRays;
        stop = true;
        sourceCollisions.clear();
        collisions.clear();
        break;
      }

      for (int j = 0; j < room.layers[i].planes.size(); j++) {
        for (int k = 0; k < room.layers[i].planes[j].triangles.size(); ++k) {
          double dist = -1;
          Vec3f intersection;

          if (room.layers[i].planes[j].triangles[k].intersectsTriangle(
                  &currentRay, dist, intersection)) {
            // Check if this triangle is nearer than the last
            if (dist < nearDistance) {
              auxIntersection = intersection;
              nearDistance = dist;
              triangleIndex = k;
              planeIndex = j;
              layerIndex = i;
            }
          }

          // No intersection
          if (i == room.layers.size() - 1 &&
              j == room.layers[room.layers.size() - 1].planes.size() - 1 &&
              k == room.layers[room.layers.size() - 1]
                           .planes[room.layers[room.layers.size() - 1]
                                       .planes.size() -
                                   1]
                           .triangles.size() -
                       1 &&
              nearDistance == std::numeric_limits<double>::max()) {
            lostRays++;
            stop = true; // End
          }
          // Intersection nearest triangle update ray
          else if (i == room.layers.size() - 1 &&
                   j == room.layers[room.layers.size() - 1].planes.size() - 1 &&
                   k == room.layers[room.layers.size() - 1]
                                .planes[room.layers[room.layers.size() - 1]
                                            .planes.size() -
                                        1]
                                .triangles.size() -
                            1) {
            updateRay(r, auxIntersection, nearDistance, currentRay,
                      triangleIndex, planeIndex, layerIndex, minEnergy, stop);

            if (!stop) // If reflection order is not reached check triangles
            {
              counter++;
              i = 0;
              j = -1;
              break;
            }
          }
        }
      }
    }
  }
  //----------------------------------------------------------------------------------------------
  void octreeRayTracing(int &r, int numRays, Ray currentRay,
                        std::vector<float> minEnergy, int &lostRays) {
    Vec3f auxIntersection;
    int counter = 0;
    bool stop = false;
    int triangleIndex = -1;
    double nearDistance = std::numeric_limits<double>::max();
    int planeIndex = -1;
    int layerIndex = -1;
    for (int i = 0; i < octreeArray.size(); i++) {
      if (threadShouldExit()) {
        r = numRays;
        stop = true;
        sourceCollisions.clear();
        collisions.clear();
        break;
      }

      int nTrian = 1;
      if (octreeArray[i]->intersect(currentRay)) {
        nTrian = octreeArray[i]->ids.size();
      }

      for (int j = 0; j < nTrian; j++) {
        Identifiers id = octreeArray[i]->ids[j];
        double dist = -1;
        Vec3f intersection;

        if (room.layers[id.idLayer]
                .planes[id.idPlane]
                .triangles[id.idTrian]
                .intersectsTriangle(&currentRay, dist, intersection)) {
          // Check if this triangle is nearer than the last
          if (dist < nearDistance) {
            auxIntersection = intersection;
            nearDistance = dist;
            triangleIndex = id.idTrian;
            planeIndex = id.idPlane;
            layerIndex = id.idLayer;
          }
        }

        // No intersection
        if (i == octreeArray.size() - 1 && j == nTrian - 1 &&
            nearDistance == std::numeric_limits<double>::max()) {
          lostRays++;
          stop = true; // End
        }
        // Intersection nearest triangle update ray
        else if (i == octreeArray.size() - 1 && j == nTrian - 1) {
          updateRay(r, auxIntersection, nearDistance, currentRay, triangleIndex,
                    planeIndex, layerIndex, minEnergy, stop);

          if (!stop) // If reflection order is not reached check triangles
          {
            counter++;
            i = -1;
            break;
          }
        }
      }
    }
  }
  //----------------------------------------------------------------------------------------------
  void updateRay(int r, Vec3f auxIntersection, double &nearDistance,
                 Ray currentRay, int triangleIndex, int planeIndex,
                 int layerIndex, std::vector<float> minEnergy, bool &stop) {
    omniSource.rays[r].distance += nearDistance;
    // Revisar si hay colision con el receptor
    IntersectionInfo intersectionInfo; // ray intersection
                                       // calculate intersection with receiver
    bool intersec = receiver.sphereReceiver.getIntersection(
        new Ray(currentRay.startPos, auxIntersection - currentRay.startPos,
                omniSource.getNumRays(), 1.0f),
        intersectionInfo);
    // if gets a sphere nearest the triangle

    // if (counter != 0)
    {
      double distanceSum = 0;
      for (int d = 0; d < sourceCollisions[r].size() - 1; d++) {
        distanceSum += std::abs(
            sourceCollisions[r][d].distance(sourceCollisions[r][d + 1]));
      }

      distanceSum +=
          std::abs(sourceCollisions[r][sourceCollisions[r].size() - 1].distance(
              intersectionInfo.intersPoint));

      if (intersectionInfo.distance < nearDistance && intersec) {
        omniSource.rays[r].distance += intersectionInfo.distance;

        // aux ray to add into receiver recepted rays vector
        Ray aux =
            Ray(currentRay.startPos, auxIntersection - currentRay.startPos,
                omniSource.getNumRays(), 1.0f);
        for (int b = 0; b < 6; b++)
          aux.bands.setBandEnergy(b, omniSource.rays[r].bands.getEnegy(b));

        receiver.addReceptedRay(aux);
        // adds the intersection to check if its colliding
        // intersecciones.push_back(intersection);
        // adds into receiver colisions array previous ray collisions and the
        // intersection point with sphere as last collision

        receiver.receptedRays[receiver.getNumInterceptedRays() - 1]
            .receptionTime = distanceSum / room.getSoundVelocity();
      }
    }

    currentRay.startPos = auxIntersection;
    currentRay.direction =
        currentRay.getReflectionVector(room.layers[layerIndex]
                                           .planes[planeIndex]
                                           .triangles[triangleIndex]
                                           .getNormal());

    Vec3f temp = currentRay.getStochasticReflectionVector(
        room.layers[layerIndex].planes[planeIndex].triangles[triangleIndex],
        auxIntersection, room.layers[layerIndex].material.scattering);

    sourceCollisions[r].push_back(currentRay.startPos);

    omniSource.rays[r].bands.calculateEnergyAbsortion(
        room.layers[layerIndex].material.absortion,
        room.layers[layerIndex].material.scattering);

    // Reset nearDistance
    nearDistance = std::numeric_limits<double>::max();
    stop = true;
    for (int b = 0; b < 6; b++) {
      if (omniSource.rays[r].bands.getEnegy(b) > minEnergy[b]) {
        stop = false;
      }
    }
  }
  //----------------------------------------------------------------------------------------------
  void auralize() {
    // std::lock_guard<std::mutex> lck(mtx);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    DBG("Auralizing");
    start = std::chrono::system_clock::now();
    // auralizer.auralize(&receiver, room.name);
    auralizer.auralize(&receiver, &omniSource, room.name, auralizeType,
                       artificialReverb);
    end = std::chrono::system_clock::now();
    elapsedMilis =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();
    DBG("Auralization  Ended");
    DBG("Elapsed Time Milis" + String(elapsedMilis));
  }

  void setTriangleFile(std::string fullPath, std::string fileName) {
    isTracing = true;
    std::lock_guard<std::mutex> lck(mtx);
    room.layers.clear();
    sourceCollisions.clear();
    collisions.clear();
    room.parseRoomTriangleFile(fullPath, fileName);
    room.writeMaterialsFile();

    roomLoaded = true;
    isTracing = false;
  }

  void setReflectionOrder(int reflectionsNumber) {
    reflectionNumber = reflectionsNumber;
  }

  bool isRaytracing() { return isTracing.load(); }

  void changePlaneLayer(int id0, int id1, int layer) {
    std::lock_guard<std::mutex> lck(mtx);
    Plane temp = room.layers[id0].planes[id1];
    room.layers[id0].planes.erase(room.layers[id0].planes.begin() + id1);
    room.layers[layer].planes.push_back(temp);
  }

  Room *getRoom() {
    std::lock_guard<std::mutex> lck(mtx);
    return &room;
  }

  Octree *getOctree() {
    std::lock_guard<std::mutex> lck(mtx);
    return &octree;
  }

  int getLayersSize() {
    std::lock_guard<std::mutex> lck(mtx);
    return room.layers.size();
  }

  int getPlanesSize(int i) {
    std::lock_guard<std::mutex> lck(mtx);
    return room.layers[i].planes.size();
  }

  int getTrianglesSize(int i, int j) {
    std::lock_guard<std::mutex> lck(mtx);
    return room.layers[i].planes[j].triangles.size();
  }

  Triangle getTriangle(int i, int j, int k) {
    std::lock_guard<std::mutex> lck(mtx);
    Triangle t = room.layers[i].planes[j].triangles[k];
    return t;
  }

  std::vector<Vec3f> *getCollisions() {
    std::lock_guard<std::mutex> lck(mtx);
    return &collisions;
  }

  SoundSource *getSoundSource() {
    std::lock_guard<std::mutex> lck(mtx);
    return &omniSource;
  }

  SoundReceiver *getSoundReceiver() {
    std::lock_guard<std::mutex> lck(mtx);
    return &receiver;
  }

  Vec3f getSourceCollisions(int rayIndex, int index) {
    std::lock_guard<std::mutex> lck(mtx);
    return sourceCollisions[rayIndex][index];
  }

  int getSourceRayCollisionsCounter(int rayIndex) {
    std::lock_guard<std::mutex> lck(mtx);
    return sourceCollisions[rayIndex].size();
  }

  int getSourceCollisionsCounter() {
    std::lock_guard<std::mutex> lck(mtx);
    return sourceCollisions.size();
  }

  void setRayNumber(int rayNum) { rayNumber = rayNum; }

  int getRayNumber() { return rayNumber; }

  void setAuralizeType(int type) { auralizeType = type; }

  void setReverb(bool option) { artificialReverb = option; }

  void setEnergy(float energy) { initialEnergy = energy; }

  void setTemperature(float temp) { roomTemp = temp; }

  void setHumidity(float humid) { roomHumidity = humid; }

  void setStopDecay(float stpDec) { stopDecay = stpDec; }

  void setPressure(float press) { roomPressure = press; }

  void setOctreeSubDiv(int subD) {
    roomLoaded = false;
    octreeArray.clear();
    octreeArray = octree.fillOctree(room.elements, subD);
    roomLoaded = true;
  }

  void setOctreeSwitch(bool oct) { octreeSwitch = oct; }

  void setOctreeBoxes(bool octB) {
    std::lock_guard<std::mutex> lck(mtx);
    drawOctreeBoxes = octB;
  }

  void setOctreeTrian(bool octT) {
    std::lock_guard<std::mutex> lck(mtx);
    drawOctreeTriangles = octT;
  }

  float getTracingTime() { return tracingTime; }

  float getAuralizationTime() { return auralizationTime; }

  std::atomic<bool> roomLoaded = false;
  std::atomic<bool> drawOctreeBoxes;
  std::atomic<bool> drawOctreeTriangles;

private:
  std::vector<std::vector<Vec3f>> sourceCollisions;
  SoundReceiver receiver;
  SoundSource omniSource;
  std::vector<Vec3f> collisions;
  std::mutex mtx;
  Room room;

  // Octree
  Octree octree;
  std::vector<Octree *> octreeArray;
  std::atomic<bool> octreeSwitch;

  std::vector<Vec3f> *receiverCollisions;
  std::atomic<bool> isTracing;

  String results;

  int currentRay = 0;
  int elapsedMilis;

  Auralizer auralizer;
  std::atomic<int> reflectionNumber;

  std::atomic<int> rayNumber;
  std::atomic<int> auralizeType;
  std::atomic<bool> artificialReverb;
  std::atomic<float> initialEnergy;

  std::atomic<float> roomTemp = 21;
  std::atomic<float> roomHumidity;
  std::atomic<float> stopDecay;
  std::atomic<float> roomPressure;
  std::atomic<float> tracingTime;
  std::atomic<float> auralizationTime;
};

#endif // RAYTRACER_H
