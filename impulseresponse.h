#ifndef IMPULSERESPONSE_H
#define IMPULSERESPONSE_H
#include <QVector3D>
#include <QVector>
#include <iostream>

struct ImpulseResponse {
  std::vector<std::vector<std::vector<float>>>
      specularIR, // specular impulse response
      diffuseIR,  // diffuse impulse response
      hybridIR,   // hybrid impulse response
      lfir,       // lateral Fraction impulse response
      lfcir,      // lateral Fraction Cosine impulse response
      decayCurve; // decay curve
};

struct Transition {
  std::vector<std::vector<float>>
      transitionTimeMatrix,         // transition time between elements [ms]
      transitionTimeReceiverMatrix; // transition time between diffuse element
                                    // and receptor [ms]
  std::vector<std::vector<std::vector<float>>>
      transitionMatrix,         // energy transition matrix
      transitionReceiverMatrix; // energy transition between triangle element
                                // and receptor
  std::vector<std::vector<std::vector<std::vector<float>>>>
      elementsEnergy; // elements energy matrix
  std::vector<std::vector<QVector3D>>
      transitionVector; // transition incidence direction
};

#endif // IMPULSERESPONSE_H
