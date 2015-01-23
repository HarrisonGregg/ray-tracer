class Scene
{
	Camera camera;
	vector<LightSource*> lightSources;
	vector<Intersectable*> objects;
	vector<Material*> materials;
	float3 L_ambient;
public:
	Scene()
	{
		L_ambient = float3(.05,.05,.05);

		const int SCENE = 1;

		if(SCENE == 1){
			//First scene:
			/*This scene exhibits several egg shapes.  The eggs are all plastic eggs, 
			constucted of half of a sphere and half of an ellipsoid.  First there is 
			a glass egg that demonstrates ideal refraction. Next, there is a 3d textured 
			marble egg, and a 2d textured painted egg with one half checkered and one
			half striped.  This was simply constructed from two eggs slightly offset.  
			Finally, there is a carved egg.  It is made out of two materials, just like 
			the painted egg, but one of the materials is ideally refractive with an index 
			of refraction of 0. There is a silver egg inside of it to demonstrate the 
			carved nature of the egg.  
			*/
			Material* glass = Material::glass();
			materials.push_back(glass);
			Material* clear = Material::clear();
			materials.push_back(clear);
			Material* marble = new Marble();
			materials.push_back(marble);
			Material* white = Material::white();
			materials.push_back(white);
			Material* redMaterial = Material::red();
			materials.push_back(redMaterial);
			Material* greenMaterial = Material::green();
			materials.push_back(greenMaterial);
			Material* blueMaterial = Material::blue();
			materials.push_back(blueMaterial);
			Material* purpleMaterial = Material::purple();
			materials.push_back(purpleMaterial);
			Material* silver = Material::silver();
			materials.push_back(silver);
			objects.push_back(new Egg(float3(-1.5,0,0), .5, float3(0,0,0),  glass));
			objects.push_back(new Egg(float3(-.5,0,0), .5, float3(0,0,0),  marble));
			objects.push_back(new StripedObject((Intersectable*)(new Egg(float3(.5,0.01,0), .5, float3(0,0,0), greenMaterial)), purpleMaterial));
			objects.push_back(new CheckeredObject((Intersectable*)(new Egg(float3(.5,0,0), .5, float3(0,0,0), redMaterial)), blueMaterial));
			objects.push_back(new SpiralObject((Intersectable*)(new Egg(float3(1.5,0,0), .5, float3(0,0,0), white)), clear));
			objects.push_back(new Egg(float3(1.5,0,0), .3, float3(0,0,0), silver));

			objects.push_back(new Plane(float3(0,1,0), float3(0,1,0), blueMaterial));
			objects.push_back(new Plane(float3(0,-1,0), float3(0,-1,0), greenMaterial));

			lightSources.push_back(new DirectionalLight(float3(1,1,1), float3(0, 1, 0)));
			lightSources.push_back(new DirectionalLight(float3(1,1,1), float3(0, -1, 0)));
			lightSources.push_back(new DirectionalLight(float3(.5,.5,.5), float3(0, 0, 1)));
			lightSources.push_back(new PointLight(float3(10,10,10), float3(1, 1, 1)));
		} else {
			//Second scene:
			/*
			This scene demonstrates golden eggs, with silver, copper, and platinum eggs for 
			comparison.  It also demonstrates egg rotation and cubes.
			*/

			Material* gold = Material::gold();
			materials.push_back(gold);
			Material* silver = Material::silver();
			materials.push_back(silver);
			Material* copper = Material::copper();
			materials.push_back(copper);
			Material* platinum = Material::platinum();
			materials.push_back(platinum);
			Material* white = Material::white();
			materials.push_back(white);
			Material* redMaterial = Material::red();
			materials.push_back(redMaterial);

			vector<Egg*> eggs;

			eggs.push_back(new Egg(float3(-1.5,1,0), .5, float3(0,0,0),  copper));
			eggs.push_back(new Egg(float3( -.5,1,0), .5, float3(0,0,0),  gold));
			eggs.push_back(new Egg(float3(  .5,1,0), .5, float3(0,0,0),  silver));
			eggs.push_back(new Egg(float3( 1.5,1,0), .5, float3(0,0,0),  platinum));
			
			for(int i = 0; i < eggs.size(); i++){
				float theta = -2*M_PI*i/(float)eggs.size() - M_PI/4.0;
				eggs[i]->center.x = 2.0*cos(theta);
				eggs[i]->center.y = 2.0*sin(theta);
				eggs[i]->rotation.z = -theta + M_PI/2.0;
				objects.push_back(eggs[i]);
			}

			objects.push_back(new Sphere(float3(0,0,0), 10, white));
			objects.push_back(new Cube(float3(0,0,0), float3(1,1,1), float3(0,M_PI/4.0,M_PI/4.0), redMaterial));

			lightSources.push_back(new PointLight(float3(40,40,40), float3(0, 0, 2)));
			lightSources.push_back(new DirectionalLight(float3(1,1,1), float3(0, 0, 1)));
			lightSources.push_back(new DirectionalLight(float3(1,1,1), float3(0, 0, -1)));
		}
	}
	~Scene()
	{
		for (LightSource* &iLightSource : lightSources)		
			delete iLightSource;
		for (Material* &iMaterial : materials)		
			delete iMaterial;
		for (Intersectable* &iObject : objects){
			delete iObject;
		}
	}

public:
	Hit firstIntersect(const Ray& ray)
	{
		Hit hit; 
		for(Intersectable* &o: objects){
			Hit h = o->intersect(ray);
			if(h.t > 0 && (h.t < hit.t || hit.t == -1)){
				hit = h;
			}
		}
		return hit;
	}

	Camera& getCamera()
	{
		return camera;
	}

	float3 trace(const Ray& ray, int depth)
	{
		if(depth > 8){
			return float3(0,0,0);
		}
		Hit hit = firstIntersect(ray);
		if(hit.t < 0)	// no intersection found
			return float3(0, 0, 0);	// background color
		else{
			float3 L_out; 
			if(hit.material->reflective && ray.dir.dot(hit.normal) < 0){
				float3 d = ray.dir;
				float3 N = hit.normal;
				Ray r = Ray(hit.position+hit.normal*.0001, d-N*(d.dot(N))*2);
				float cosTheta1 = ray.dir.cross(hit.normal).norm();
				float3 F = hit.material->f0 + (float3(1,1,1)-hit.material->f0)*pow(1-cosTheta1,5);
				L_out += F*trace(r, depth+1); 
			}
			for (LightSource* &l : lightSources){
				bool shadow = false;
				Ray toLight = Ray(hit.position+hit.normal*.0001, l->getLightDirAt(hit.position));
				for(Intersectable* &o: objects){
					Hit h = o->intersect(toLight);
					if(h.t > 0 && h.t < l->getDistanceFrom(hit.position)){
						shadow = true;
						break;
					}
				}
				// Hit h = firstIntersect(toLight);
				// if(h.t > 0 && h.t < l->getDistanceFrom(hit.position)){	
				if(!shadow){
					float3 L_in = l->getRadianceAt(hit.position);
					float3 L_l = l->getLightDirAt(hit.position);
					float3 kd = hit.material->getKd(hit);
					float3 N = hit.normal;
					float3 ks = hit.material->getKs(hit);
					float3 V = ray.dir*-1.0;
					float3 H_l = (L_l+V).normalize();
					float shininess = hit.material->shininess;
					L_out += L_in*ks*pow((H_l.dotplus(N)), shininess); 
					L_out += L_in*kd*(L_l.dotplus(N)); 
				}
			}
			if(hit.material->refractive){
				float n;
				float3 newPosition;
				if(hit.normal.dot(ray.dir) > 0){
					n = 1/hit.material->n;
					newPosition = hit.position + hit.normal * 0.0001;
				} else {
					n = hit.material->n;
					newPosition = hit.position - hit.normal * 0.0001;
				}
				float theta2 = asin(hit.normal.dot(ray.dir))/n;
				float sinTheta1Squared = pow(ray.dir.dot(hit.normal),2);
				float cosTheta1Squared = 1-sinTheta1Squared;
				float3 newDirection = ray.dir/n + hit.normal*(sqrt(cosTheta1Squared)/n-sqrt(1-sinTheta1Squared))/n/n;
				if(newDirection.dot(hit.normal)>0!=ray.dir.dot(hit.normal)>0){
					newDirection*=-1.0;
				}
				Ray newRay = Ray(newPosition, newDirection);
				float3 F = hit.material->f0 + (float3(1,1,1)-hit.material->f0)*pow(1-sqrt(cosTheta1Squared),5);
				L_out+=(float3(1,1,1)-F)*trace(newRay, depth+1);
			} else {
				L_out += hit.material->k_a*L_ambient;	
			}
			L_out += hit.material->glow;
			return L_out;
		}
	}
};
