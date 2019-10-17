#ifndef BANDENERGY_H
#define BANDENERGY_H

#include <iostream>

#define NUMBER_BANDS 6

struct Material {
  std::string name;
  float absortion[NUMBER_BANDS];
  float scattering[NUMBER_BANDS];
  float transmision[NUMBER_BANDS];
};

class BandEnergy {
public:
  BandEnergy(int numRays, float initialEnergy) {
    // Initial band frecuency
    float firstFrec = 62.5;
    // Initial energy
    double initialEn = initialEnergy / (numRays * NUMBER_BANDS);

    frecuencies[0] = firstFrec;

    for (int i = 1; i < NUMBER_BANDS; i++) {
      firstFrec *= 2;
      frecuencies[i] = firstFrec;
    }
    for (int i = 0; i < NUMBER_BANDS; i++) {
      energy[i] = initialEn;
    }
  }
  BandEnergy() {
    // Initial band frecuency
    float firstFrec = 62.5;
    // Initial energy
    float initialEnergy = 1;

    frecuencies[0] = firstFrec;

    for (int i = 1; i < NUMBER_BANDS; i++) {
      firstFrec *= 2;
      frecuencies[i] = firstFrec;
    }
    for (int i = 0; i < NUMBER_BANDS; i++) {
      energy[i] = initialEnergy;
    }
  }

  void setBandEnergy(int bandNumber, float value) {
    energy[bandNumber] = value;
  }

  void multiplyBandEnergy(int bandNumber, float factor) {
    frecuencies[bandNumber] *= factor;
  }

  void calculateEnergyAbsortion(float absortionMaterialCoef[],
                                float scatteringMaterialCoef[]) {
    for (int k = 0; k < NUMBER_BANDS; k++)
      energy[k] *=
          (1 - absortionMaterialCoef[k]) * (1 - scatteringMaterialCoef[k]);
  }

  float getEnegy(int index) { return energy[index]; }

  float getFrecuencies(int index) { return frecuencies[index]; }

private:
  float frecuencies[NUMBER_BANDS];
  double energy[NUMBER_BANDS];
};

#endif // BANDENERGY_H
