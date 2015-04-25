#ifndef HIGGSTRIGGERWEIGHTPROVIDER_H
#define HIGGSTRIGGERWEIGHTPROVIDER_H

class HiggsTriggerEfficiencyProvider {
  public:

    HiggsTriggerEfficiencyProvider() {};
    ~HiggsTriggerEfficiencyProvider() {};

    float get_weight_isomu(float lept_pt, float lept_eta) const;
    float get_weight_isoel(float lept_pt, float lept_eta) const;

  private:

    float TRIGWEIGHTMU[21][3] = {{0.87,0.87,0.79},{0.87,0.87,0.79},{0.87,0.87,0.79},{0.87,0.87,0.79},{0.88,0.88,0.79},{0.88,0.88,0.79},{0.88,0.88,0.79},{0.89,0.89,0.79},{0.89,0.89,0.79},{0.89,0.89,0.80},{0.89,0.89,0.80},{0.89,0.89,0.81},{0.89,0.89,0.81},{0.90,0.90,0.82},{0.90,0.90,0.82},{0.90,0.90,0.83},{0.91,0.91,0.83},{0.91,0.91,0.84},{0.91,0.91,0.83},{0.92,0.92,0.84},{0.94,0.94,0.89},};
    float TRIGWEIGHTEL[18][2] = {{0.84,0.65},{0.87,0.67},{0.87,0.69},{0.88,0.70},{0.88,0.71},{0.89,0.73},{0.90,0.74},{0.90,0.75},{0.91,0.77},{0.91,0.77},{0.91,0.78},{0.92,0.79},{0.93,0.80},{0.93,0.81},{0.94,0.82},{0.94,0.83},{0.94,0.80},{0.94,0.79}};

};

#endif
