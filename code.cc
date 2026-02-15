/*
 *  Class for collecting second order statistics
 */

#include <iostream>
#include <math.h>
#include "sos.h"
#include <iomanip>

void Sos::add(double x)
{
  double delta = (x - aver)/(n+1.0);
  Q += n*delta*(x - aver);
  aver += delta;
  n++;
}

const Sos& Sos::operator+=(const Sos& rhs)
{
  double total = n + rhs.n;
  double diff = rhs.aver-aver;
  aver += rhs.n*diff/total;
  Q += rhs.Q + n*rhs.n*diff*diff/total;
  n = total;

  return rhs;
}


double Sos::var() const
{
  //  assert(n>1.0);
  return (n>1.0)? Q/(n-1.0):0.0;
}

double Sos::sd() const
{
  return sqrt(var());
}

double Sos::err() const
{
  return sqrt(var()/n);
}

double Sos::sum() const
{
  return aver*n;
}

ostream& operator<<(ostream& out, const Sos& d)
{
  double err = d.err();
  int precision = max(1, int(ceil(0.5+log10(d.av()/err))));

  out << std::setprecision(precision) << std::showpoint << d.av() << " ";
  out << std::setprecision(1) << d.err();

  return(out);
}
