#pragma once

#include "vector.hpp"

enum RayType {
  DIRECT,
  SHADOW,
  INDIRECT,
};
class Ray
{
  public:
  Vec3 origin;
  Vec3 direction;

  Ray()= default;
  Ray(Vec3, Vec3);

  Vec3 point_at_parameter(float dist) const;
  Vec3 point_at_parameter(Vec3 origin, Vec3 dir, float dist) const;
};

class LightRay: public Ray
{
  public:
      LightRay();
      LightRay(Vec3, Vec3);
};

class ShadowRay: public Ray
{
  public:
      ShadowRay();
      ShadowRay(Vec3, Vec3);
};