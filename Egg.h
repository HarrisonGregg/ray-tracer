class Egg : public Intersectable
{
public:
    float3 center;
    float size;
    float3 axis;
    float3 rotation;
    Ellipsoid* top;
    Ellipsoid* bottom;
    Egg(const float3& center, float size, float3 rotation, Material* material):
        Intersectable(material),
        size(size),
        center(center),
        rotation(rotation)
    {
        float3 topCoeffs = float3(1,1.5,1)*size;
        float3 bottomCoeffs = float3(1,1,1)*size;
        top = new Ellipsoid(float3(0,0,0),topCoeffs, float3(0,0,0), material);
        bottom = new Ellipsoid(float3(0,0,0),bottomCoeffs, float3(0,0,0), material);
    }

    Egg(const float3& center, float size, float3 rotation, Material* material1, Material* material2):
        Intersectable(material1),
        size(size),
        center(center),
        rotation(rotation)
    {
        float3 topCoeffs = float3(1,1.5,1)*size;
        float3 bottomCoeffs = float3(1,1,1)*size;
        top = new Ellipsoid(float3(0,0,0),topCoeffs, float3(0,0,0), material1);
        bottom = new Ellipsoid(float3(0,0,0),bottomCoeffs, float3(0,0,0), material2);
    }

    virtual Hit intersect(const Ray& ray)
    {
        Ray newRay = ray.localize(center, rotation);
        Hit hit;
        Hit topHit = top->intersect(newRay);
        Hit bottomHit = bottom->intersect(newRay);
        if(topHit.position.y > 0){
            hit = topHit;
        } else {
            hit = bottomHit;
        }
        hit = hit.delocalize(center, rotation);
        return hit;
    }
}; 