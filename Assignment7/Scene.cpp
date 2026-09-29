//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emitAreaSum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emitAreaSum += objects[k]->getArea();
        }
    }
    if (emitAreaSum <= 0) {
        pdf = 0;
        return;
    }

    const float p = get_random_float() * emitAreaSum;
    float accumulatedArea = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            accumulatedArea += objects[k]->getArea();
            if (p <= accumulatedArea){
                objects[k]->Sample(pos, pdf);
                pdf = 1.0f / emitAreaSum;
                return;
            }
        }
    }

    pdf = 0;
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    const Intersection inter = intersect(ray);
    if (!inter.happened)
        return backgroundColor;

    if (inter.m->hasEmission())
        return inter.emit;

    const Vector3f hitPoint = inter.coords;
    const Vector3f normal = inter.normal;
    const Vector3f wo = -ray.direction;
    const Vector3f rayOrigin = dotProduct(ray.direction, normal) < 0 ?
        hitPoint + normal * EPSILON : hitPoint - normal * EPSILON;

    Vector3f directLighting(0.0f);
    Intersection lightSample;
    float lightPdf = 0;
    sampleLight(lightSample, lightPdf);
    if (lightPdf > EPSILON) {
        const Vector3f toLight = lightSample.coords - hitPoint;
        const float distanceSquared = dotProduct(toLight, toLight);
        const Vector3f lightDirection = normalize(toLight);
        const Intersection shadowHit = intersect(Ray(rayOrigin, lightDirection));

        if (shadowHit.happened && shadowHit.distance * shadowHit.distance >= distanceSquared - EPSILON) {
            const float cosSurface = std::max(0.0f, dotProduct(normal, lightDirection));
            const float cosLight = std::max(0.0f, dotProduct(lightSample.normal, -lightDirection));
            directLighting = lightSample.emit * inter.m->eval(wo, lightDirection, normal) *
                             cosSurface * cosLight / distanceSquared / lightPdf;
        }
    }

    Vector3f indirectLighting(0.0f);
    if (get_random_float() < RussianRoulette) {
        const Vector3f wi = inter.m->sample(wo, normal);
        const float materialPdf = inter.m->pdf(wo, wi, normal);
        const float cosSurface = std::max(0.0f, dotProduct(normal, wi));

        if (materialPdf > EPSILON && cosSurface > 0.0f) {
            const Intersection nextHit = intersect(Ray(rayOrigin, wi));
            if (nextHit.happened && !nextHit.m->hasEmission()) {
                indirectLighting = castRay(Ray(rayOrigin, wi), depth + 1) *
                                   inter.m->eval(wo, wi, normal) * cosSurface /
                                   materialPdf / RussianRoulette;
            }
        }
    }

    return directLighting + indirectLighting;
}
