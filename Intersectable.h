// Object abstract base class.
class Intersectable
{
protected:
	Material* material;
public:
	Intersectable(Material* material):material(material) {}
    virtual Hit intersect(const Ray& ray)=0;
};

class CheckeredObject : public Intersectable
{
protected:
	Intersectable* object;
	Material* material;
public:  
	CheckeredObject(Intersectable* object, Material* altMaterial):
		Intersectable(material), material(altMaterial), object(object) {}
    virtual Hit intersect(const Ray& ray){
    	Hit hit = object->intersect(ray);
		if(hit.t > 0 && fmod(hit.uv.x, .1)<.05 != fmod(hit.uv.y, .1)<.05 ){
			hit.material = material;			
		}
		return hit;
    }
};

class StripedObject : public Intersectable
{
protected:
	Intersectable* object;
	Material* material;
public:  
	StripedObject(Intersectable* object, Material* altMaterial):
		Intersectable(material), material(altMaterial), object(object) {}
    virtual Hit intersect(const Ray& ray){
    	Hit hit = object->intersect(ray);
		if(hit.t > 0 && fmod(hit.uv.x, .1)<.05){
			hit.material = material;
		}
		return hit;
    }
};

class SpiralObject : public Intersectable
{
protected:
	Intersectable* object;
	Material* material;
public:  
	SpiralObject(Intersectable* object, Material* altMaterial):
		Intersectable(material), material(altMaterial), object(object) {}
    virtual Hit intersect(const Ray& ray){
    	Hit hit = object->intersect(ray);
		if(hit.t > 0 && fmod(hit.uv.x+hit.uv.y, .2)<.1){
			hit.material = material;
		}
		return hit;
    }
};