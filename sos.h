/*
 *  Class for collecting second order statistics
 */

#ifndef __SOS__
#define __SOS__

#include <iostream>
using namespace std;

class Sos {
public:
  Sos() { zero(); }
  void zero() { aver = Q = n = 0.0; }
  void add(double x);
  double operator+=(double x) { add(x); return(x); }
  const Sos& operator+=(const Sos& e);
  double av() const { return(aver); }
  double var() const;
  double sd() const;
  double err() const;
  double sum() const;
  int number() const { return(int(n)); }
private:
  double aver;
  double Q;
  double n;
};

ostream& operator<<(ostream& out, const Sos& d);

#endif
