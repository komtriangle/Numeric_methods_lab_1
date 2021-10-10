#include <iostream>
#include <cmath>


float X0=0, Y0=0, X1=0, Y1=0, X2=0, Y2=0;
float f0(float x, float y)
 {
   return tan(x) - y;
 }
float g0(float x, float y)
 {
   return x*y-1.5;
 }

 float f1(float x, float y)
{
   return sin(x) + cos(x)-y;
}
 float g1(float x, float y)
{
   return 3 * x-y;
}
 std::pair<float, float> InitialPointChoice(float(*f)(float, float), float(*g)(float, float), float Xm, float Ym, float Xp, float Yp, int area)
{
  std::pair<float, float> point = std::pair<float, float>(0.0, 0.0);
  float dl = 0.1;
  float curmin = 1000000;
  while (curmin > 99999)
  {
    for (float x = Xm; x < Xp; x += dl)
    {
      for (float y = Ym; y < Yp; y += dl)
      {
        float fc = f(x, y);
        float gc = g(x, y);
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
        float dv = abs(fc) + abs(gc);
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
 double stri(float x1, float y1, float x2, float y2, float x3, float y3)
{
  return 0.5 *abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}

 std::pair<float, float> MinValuesfAndg(float(*f)(float, float), float(*g)(float, float))
 {
   float val0 = abs(f(X0, Y0)) + abs(g(X0, Y0));
   float val1 = abs(f(X1, Y1)) + abs(g(X1, Y1));
   float val2 = abs(f(X2, Y2)) + abs(g(X2, Y2));

   if (val0 < val1 && val0 < val2)
     return std::pair<float, float>(X0, Y0);
   if (val1 < val2)
     return std::pair<float, float>(X1, Y1);
   else
     return std::pair<float, float>(X2, Y2);

 }

 void TwoDemetnialLinearInterpolation(float(*f)(float, float), float(*g)(float, float), float epsilon)
{
   float x = 10, y = 10;
   float xls = 1000000;
   float yls = 1000000;
   float dv = abs(x - xls) + abs(y - yls);

  while (dv > epsilon)
  {
    float zf0 = f(X0, Y0);
    float zg0 = g(X0, Y0);

    float zf1 = f(X1, Y1);
    float zg1 = g(X1, Y1);

    float zf2 = f(X2, Y2);
    float zg2 = g(X2, Y2);

    float Af = (Y1 - Y0) * (zf2 - zf0) - (Y2 - Y0) * (zf1 - zf0);
    float Bf = (X2 - X0) * (zf1 - zf0) - (X1 - X0) * (zf2 - zf0);
    float Cf = (X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - Y0);
    float Df = -1 * X0 * Af - Y0 * Bf - zf0 * Cf;

    float Ag = (Y1 - Y0) * (zg2 - zg0) - (Y2 - Y0) * (zg1 - zg0);
    float Bg = (X2 - X0) * (zg1 - zg0) - (X1 - X0) * (zg2 - zg0);
    float Cg = (X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - Y0);
    float Dg = -1 * X0 * Ag - Y0 * Bg - zg0 * Cg;

    float dt = Af * Bg - Ag * Bf;
    if (abs(dt) < 0.000001)
      break;
    x = (-1 * Df * Bg + Dg * Bf) / dt;
    y = (-1 * Af * Dg + Ag * Df) / dt;

    float zfc = f(x, y);
    float zgc = g(x, y);

    dv = abs(x - xls) + abs(y - yls);

    xls = x;
    yls = y;

    float s0 = stri(X1, Y1, X2, Y2, x, y);
    float s1 = stri(X0, Y0, X2, Y2, x, y);
    float s2 = stri(X0, Y0, X1, Y1, x, y);



    if (s0 >= s1 && s0 >= s2)
    {
      X0 = X1;
      Y0 = Y1;
      X1 = X2;
      Y1 = Y2;
      X2 = x;
      Y2 = y;
    }
    else if (s1 >= s0 && s1 >= s2)
    {
      X1 = X2;
      Y1 = Y2;
      X2 = x;
      Y2 = y;
    }
    else  if (s2 >= s0 && s2 >= s1)
    {
      X2 = x;
      Y2 = y;
    }
    std::pair<float, float> point = MinValuesfAndg(f,g);
    std::cout << "x:" << point.first << ", y: " << point.second << " f(x,y): " << f(point.first, point.second) << " g(x,y): " << g(point.first, point.second) << std::endl;

  }
  std::pair<float, float> point = MinValuesfAndg(f,g);
  std::cout << "x:" << point.first << ", y: " << point.second << " f(x,y): " << f(point.first, point.second) << " g(x,y): " << g(point.first, point.second) << std::endl;

}


 void Solve(float xp0, float yp1, float xp1, float yp2, float xp2, float yp3, float xp3, float yp4, float(*f)(float, float), float(*g)(float, float), float epsilon) {
   

   std::pair<float, float> point1 = InitialPointChoice(f,g,xp0, yp1, xp2, yp3, 1);
   std::pair<float, float> point2 = InitialPointChoice(f,g,xp0, yp1, xp2, yp3, 2);
   std::pair<float, float> point3 = InitialPointChoice(f,g,xp0, yp1, xp2, yp3, 3);
   X0 = point1.first;
   Y0 = point1.first;
   X1 = point2.first;
   Y1 = point2.second;
   X2 = point3.first;
   Y2 = point3.second;

  TwoDemetnialLinearInterpolation(f, g, epsilon);
   std::cout << std::endl;
 }

int main()
{
  
  float epsilon = 0.0000005;
  float const PI = 3.1415926535;
  float xp0 = 0, yp1 = 0;
  float xp1 = 0, yp2 = 5;
  float xp2 = PI / 2, yp3 = 5;
  float xp3 = PI / 2, yp4 = 0;
  std::cout << "f(x,y) = tan(x) - y; g(x,y) = x*y - 1.5;" << std::endl;

  Solve(xp0, yp1, xp1, yp2, xp2, yp3, xp3, yp4, f0, g0, epsilon);


  xp0 = 0, yp1 = 0;
  xp1 = 0, yp2 = 5;
  xp2 = 5, yp3 = 5;
  xp3 = 5, yp4 = 0;

  std::cout << "f(x,y) = sin(x) + cos(x); g(x,y) = 3*x;" << std::endl;
  Solve(xp0, yp1, xp1, yp2, xp2, yp3, xp3, yp4, f1, g1, epsilon);
  int a;
  std::cin >>a;

}
