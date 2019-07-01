#include "SC_PlugIn.h"
#include <stdio.h>
using namespace std;

static InterfaceTable *ft;

struct SpringD : public Unit {
  float stiffness, damping, dV, dX, interference;
};

extern "C"
{
  static void SpringD_Ctor(SpringD *unit);
  static void SpringD_next_a(SpringD *unit, int inNumSamples);
  //static void SpringD_next_k(SpringD *unit, int inNumSamples);
}

//Constructor
void SpringD_Ctor (SpringD *unit) {
  unit->stiffness = ZIN0(1);
  unit->damping = ZIN0(2);
  unit->interference = ZIN0(3);
  unit->dV = 0.f;
  unit->dX = 0.f;
  // if(INRATE(1) == calc_FullRate){
  //
  // } else {

  //}
  SETCALC(SpringD_next_a);
  SpringD_next_a(unit, 1);

}

void SpringD_next_a(SpringD *unit, int inNumSamples)
{
  float *in = ZIN(0);
  float *out = ZOUT(0);
  float dX = unit->dX;
  float dV = unit->dV;
  float stiffness = ZIN0(1)*SAMPLERATE;
  float damping = ZIN0(2);
  float in_signal = ZIN0(3);
  float step = SAMPLEDUR;

  LOOP1(inNumSamples,
    dX += (dV*step*0.5);
    dV += -(stiffness*(dX*step))-((dV*step)*damping)+(ZXP(in)*sqrt(stiffness))+in_signal;
    ZXP(out) = dX + (dV*step*0.5);
  );
  //printf("dX1 = %f\n", in_signal);
  unit->dX = zapgremlins(dX);
  unit->dV = zapgremlins(dV);
}

PluginLoad(SpringDUgens)
{
	ft = inTable;
	DefineSimpleUnit(SpringD);

}
