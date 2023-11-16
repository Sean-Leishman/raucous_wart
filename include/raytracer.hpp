#pragma once

#include "camera.hpp"
#include "image.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "scene.hpp"


class Raytracer
{
  public:
  virtual ~Raytracer() = default;

  Scene* scene;
  Camera* camera;

  Raytracer(Scene* scene, Camera* camera) : scene(scene), camera(camera){};

  virtual PPMColor trace_ray(Ray& ray) = 0;
};

class BinaryRaytracer : public Raytracer
{
  public:
  BinaryRaytracer(Scene* scene, Camera* camera) : Raytracer(scene, camera){};
  PPMColor trace_ray(Ray& ray) override;
};

class PhongRaytracer : public Raytracer
{
  public:
  int max_depth;

  PhongRaytracer(Scene* scene, Camera* camera, int nbounces)
      : Raytracer(scene, camera), max_depth(nbounces)
  {
  }
  PPMColor trace_ray(Ray& ray) override;
  Vec3 trace_ray(Ray& ray, int depth);
  Vec3 calculate_direct(Intersection& hit_info);
  Ray calculate_reflection_ray(Ray& ray, Intersection& hit_info);
  Ray calculate_refraction_ray(Ray& ray, Intersection& hit_info);
};
