#pragma once

#include "intersection.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "vector.hpp"

struct Vec2
{
  float u;
  float v;

  Vec2 operator*(const float& f) const { return Vec2{u * f, v * f}; }
  Vec2 operator+(const Vec2& f) const { return Vec2{u + f.u, v + f.v}; }
};

class Intersection;

class Shape : public std::enable_shared_from_this<Shape>
{
  private:
  public:
  Shape();
  Shape(Material material);
  Material material;
  virtual ~Shape() = default;

  virtual std::shared_ptr<const Shape> get_shared_ptr() const = 0;
  virtual bool intersect(const Ray& ray, float tmin, float tmax,
                         Intersection* intersection) const = 0;
  virtual Vec2 interpolate_uv(const Intersection* hit_info) const = 0;
};

class Sphere : public Shape
{
  private:
  Vec3 center;
  double radius;

  public:
  Sphere(Vec3, float, Material);

  std::shared_ptr<const Shape> get_shared_ptr() const override
  {
    return shared_from_this();
  }
  Vec2 interpolate_uv(const Intersection* hit_info) const override;
  bool intersect(const Ray&, float, float, Intersection*) const override;
};

class Cylinder : public Shape
{
  private:
  Vec3 center;
  Vec3 axis;
  float radius;
  float height;

  public:
  Cylinder(Vec3, Vec3, float, float, Material);

  std::shared_ptr<const Shape> get_shared_ptr() const override
  {
    return shared_from_this();
  }

  Vec2 interpolate_uv(const Intersection* hit_info) const override;
  bool intersect_caps(const Vec3&, const Vec3&, float, Intersection*) const;
  bool intersect(const Ray& ray, float tmin, float tmax,
                 Intersection* intersection) const override;
};

class Triangle : public Shape
{
  private:
  Vec3 v0;
  Vec3 v1;
  Vec3 v2;

  Vec2 uv0;
  Vec2 uv1;
  Vec2 uv2;

  public:
  Triangle();
  Triangle(Vec3, Vec3, Vec3, Material);

  std::shared_ptr<const Shape> get_shared_ptr() const override
  {
    return shared_from_this();
  }

  Vec2 get_uv(const Vec3& point) const;
  bool intersect(const Ray& ray, float tmin, float tmax,
                 Intersection* intersection) const override;
  Vec2 interpolate_uv(const Intersection* hit_info) const override;
};
