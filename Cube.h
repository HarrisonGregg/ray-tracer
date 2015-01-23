
// Object realization.
class Cube : public Intersectable
{
	float3 x;
	float3 size;
    float3 rotation;
	vector<Intersectable*> planes;
public:
    Cube(const float3& x, const float3& size, float3 rotation, Material* material):
		Intersectable(material),
		x(x),
		size(size),
        rotation(rotation)
	{
		planes.push_back(new Plane(float3(size.x/2,0,0),float3(size.x/2,0,0),material));
		planes.push_back(new Plane(float3(-size.x/2,0,0),float3(-size.x/2,0,0),material));
		planes.push_back(new Plane(float3(0,size.y/2,0),float3(0,size.y/2,0),material));
		planes.push_back(new Plane(float3(0,-size.y/2,0),float3(0,-size.y/2,0),material));
		planes.push_back(new Plane(float3(0,0,size.z/2),float3(0,0,size.z/2),material));
		planes.push_back(new Plane(float3(0,0,-size.z/2),float3(0,0,-size.z/2),material));
    }

    Hit intersect(const Ray& ray)
    {
        Ray newRay = ray.localize(x, rotation);

    	Hit bestHit;
    	Hit hit = planes[0]->intersect(newRay);
    	float3 localPos = hit.position;
    	if(localPos.y < size.y/2 && localPos.y > -size.y/2 && localPos.z < size.z/2 && localPos.z > -size.z/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;
    	hit = planes[1]->intersect(newRay);
    	localPos = hit.position;
    	if(localPos.y < size.y/2 && localPos.y > -size.y/2 && localPos.z < size.z/2 && localPos.z > -size.z/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;
    	hit = planes[2]->intersect(newRay);
    	localPos = hit.position;
    	if(localPos.x < size.x/2 && localPos.x > -size.x/2 && localPos.z < size.z/2 && localPos.z > -size.z/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;
    	hit = planes[3]->intersect(newRay);
    	localPos = hit.position;
    	if(localPos.x < size.x/2 && localPos.x > -size.x/2 && localPos.z < size.z/2 && localPos.z > -size.z/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;
    	hit = planes[4]->intersect(newRay);
    	localPos = hit.position;
    	if(localPos.x < size.x/2 && localPos.x > -size.x/2 && localPos.y < size.y/2 && localPos.y > -size.y/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;
    	hit = planes[5]->intersect(newRay);
    	localPos = hit.position;
    	if(localPos.x < size.x/2 && localPos.x > -size.x/2 && localPos.y < size.y/2 && localPos.y > -size.y/2)
    		if(hit.t > 0 && hit.t < bestHit.t || bestHit.t < 0)
	    		bestHit = hit;

        return bestHit.delocalize(x, rotation);
    }
}; 
