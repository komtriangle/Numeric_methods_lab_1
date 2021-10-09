#include <iostream>
#include <cmath>


 double X0=0, Y0=0, X1=0, Y1=0, X2=0, Y2=0;
 double f(double x, double y)
 {
   return tan(x) - y;
 }
 double g(double x, double y)
 {
   return x*y-1.5;
 }

 double f1(double x, double y)
{
   return sin(x) + cos(x)-y;
}
 double g1(double x, double y)
{
   return 3 * x-y;
}
 std::pair<double, double> InitialPointChoice(double Xm, double Ym, double Xp, double Yp, int area)
{
  std::pair<double, double> point = std::pair<double, double>(0.0, 0.0);
  double dl = 0.1;
  double curmin = 100000;
  while (curmin > 99999)
  {
    for (double x = Xm; x < Xp; x += dl)
    {
      for (double y = Ym; y < Yp; y += dl)
      {
        double fc = f(x, y);
        double gc = g(x, y);
        switch (area)
        {
        case 1:
          if (fc <= 0 || gc <= 0)
            continue;
          break;
        case 2:
          if (fc >= 0 || gc >= 0)
            continue;
          break;
        case 3:
          if (fc <= 0 || gc >= 0)
            continue;
          break;
        case 4:
          if (fc >= 0 || gc <= 0)
            continue;
          break;
        default:
          break;
        }
        double dv = abs(fc) + abs(gc);
        if (dv > curmin)
          continue;
        point.first = x;
        point.second = y;
        curmin = dv;

      }

    }
    if (curmin <= 99999)
      break;
    dl /= 2;
  }
  return point;
}
 double stri(double x1, double y1, double x2, double y2, double x3, double y3)
{
  return 0.5 *abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}
 void TwoDemetnialLinearInterpolation(double(*f)(double, double), double(*g)(double, double), double epsilon)
{
  double x = 10, y = 10;
  double xls = 100000;
  double yls = 100000;
  double dv = abs(x - xls) + abs(y - yls);
  while (dv > epsilon)
  {
    double zf0 = f(X0, Y0);
    double zg0 = g(X0, Y0);

    double zf1 = f(X1, Y1);
    double zg1 = g(X1, Y1);

    double zf2 = f(X2, Y2);
    double zg2 = g(X2, Y2);

    double Af = (Y1 - Y0) * (zf2 - zf0) - (Y2 - Y0) * (zf1 - zf0);
    double Bf = (X2 - X0) * (zf1 - zf0) - (X1 - X0) * (zf2 - zf0);
    double Cf = (X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - Y0);
    double Df = -1 * X0 * Af - Y0 * Bf - zf0 * Cf;

    double Ag = (Y1 - Y0) * (zg2 - zg0) - (X2 - Y0) * (zg1 - zg0);
    double Bg = (X2 - X0) * (zg1 - zg0) - (X1 - X0) * (zg2 - zg0);
    double Cg = (X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - Y0);
    double Dg = -1 * X0 * Ag - Y0 * Bg - zg0 * Cg;

    double dt = Af * Bg - Ag * Bf;
    if (abs(dt) < 0.000001)
      break;
    x = (-1 * Df * Bg + Dg * Bf) / dt;
    y = (-1 * Af * Dg + Ag * Df) / dt;

    double zfc = f(x, y);
    double zgc = g(x, y);

    dv = abs(x - xls) + abs(y - yls);

    xls = x;
    yls = y;

    double s0 = stri(X1, Y1, X2, Y2, x, y);
    double s1 = stri(X0, Y0, X2, Y2, x, y);
    double s2 = stri(X0, Y0, X1, Y1, x, y);

    if (s0 >= s1 && s0 >= s2)
    {
      X0 = X1;
      Y0 = Y1;
      X1 = X2;
      Y1 = Y2;
      X2 = x;
      Y2 = y;
      continue;
    }
    if (s1 >= s0 && s1 >= s2)
    {
      X1 = X2;
      Y1 = Y2;
      X2 = x;
      Y2 = y;
      continue;
    }
    if (s2 >= s0 && s2 >= s1)
    {
      X2 = x;
      Y2 = y;
      continue;
    }
  }

}
 std::pair<double, double> MinValuesfAndg()
{
  double val0 = abs(f(X0, Y0)) + abs(g(X0, Y0));
  double val1 = abs(f(X1, Y1)) + abs(g(X1, Y1));
  double val2 = abs(f(X2, Y2)) + abs(g(X2, Y2));

  if (val0 < val1 && val0 < val2)
    return std::pair<double, double>(X0, Y0);
  if (val1 < val2)
    return std::pair<double, double>(X1, Y1);
  else
    return std::pair<double, double>(X2, Y2);

}

 void Solve(double xp0, double yp1, double xp1, double yp2, double xp2, double yp3, double xp3, double yp4, double(*f)(double, double), double(*g)(double, double), double epsilon) {
   

   std::pair<double, double> point1 = InitialPointChoice(xp0, yp1, xp2, yp3, 1);
   std::pair<double, double> point2 = InitialPointChoice(xp0, yp1, xp2, yp3, 2);
   std::pair<double, double> point3 = InitialPointChoice(xp0, yp1, xp2, yp3, 3);
   X0 = point1.first;
   Y0 = point1.first;
   X1 = point2.first;
   Y1 = point2.second;
   X2 = point3.first;
   Y2 = point3.second;

   for (int i = 0; i < 10; i++)
   {
     TwoDemetnialLinearInterpolation(f, g, epsilon);
     std::pair<double, double> point = MinValuesfAndg();
     std::cout << "x:" << point.first << ", y: " << point.second << " f(x,y): " << f(point.first, point.second) << " g(x,y): " << g(point.first, point.second) << std::endl;
   }
   std::cout << std::endl;
 }

int main()
{
  
  double epsilon = 0.0000005;
  double const PI = 3.1415926535;
  double xp0 = 0, yp1 = 0;
  double xp1 = 0, yp2 = 5;
  double xp2 = PI / 2, yp3 = 5;
  double xp3 = PI / 2, yp4 = 0;
  std::cout << "f(x,y) = tan(x) - y; g(x,y) = x*y - 1.5;" << std::endl;

  Solve(xp0, yp1, xp1, yp2, xp2, yp3, xp3, yp4, f, g, epsilon);


  xp0 = 0, yp1 = 0;
  xp1 = 0, yp2 = 5;
  xp2 = 5, yp3 = 5;
  xp3 = 5, yp4 = 0;

  std::cout << "f(x,y) = sin(x) + cos(x); g(x,y) = 3*x;" << std::endl;
  Solve(xp0, yp1, xp1, yp2, xp2, yp3, xp3, yp4, f1, g1, epsilon);
  int a;
  std::cin >>a;

}
