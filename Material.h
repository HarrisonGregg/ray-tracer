// Skeletal Material class. Feel free to add methods e.g. for illumination computation (shading).
class Material
{
public:
	bool reflective;
	bool refractive;
	bool textured;
	float3 f0;			// Fresnel coefficient
	float n;			// index of refraction
	float3 kd;			// diffuse reflection coefficient
	float3 ks;			// specular reflection coefficient
	float3 k_a;			// ambient light coefficient
	float shininess;	// specular exponent
	float3 glow; 		// glow

	Material()
	{
		reflective = false;
		refractive = false;
		textured = false;
		f0 = float3(0.93, 0.85, 0.4);
		n = 1;
		kd = float3(0.5, 0.5, 0.5) + kd * 0.5;
		ks = float3(1, 1, 1);
		k_a = float3(1.0,1.0,1.0);
		shininess = 50;
		glow = float3(0,0,0);
	}

	Material(bool reflective, bool refractive, bool textured, float3 f0, int n, float3 kd, float3 ks, float3 k_a, float shininess) : 
		reflective(reflective),refractive(refractive),textured(textured),f0(f0),n(n),kd(kd),ks(ks),k_a(k_a),shininess(shininess){}

	virtual float3 getKs(Hit hit){
		return ks;		
	}

	virtual float3 getKd(Hit hit){
		return kd;		
	}

	static float getf0(float n, float k){
		return ((n-1)*(n-1)+k*k)/((n+1)*(n+1)+k*k);
	}

	static Material* white(){
		Material* m = new Material();
		m->kd = float3(1,1,1);
		return m;
	}

	static Material* red(){
		Material* m = new Material();
		m->kd = float3(1,0,0);
		return m;
	}

	static Material* green(){
		Material* m = new Material();
		m->kd = float3(0,1,0);
		return m;
	}

	static Material* blue(){
		Material* m = new Material();
		m->kd = float3(0,0,1);
		return m;
	}

	static Material* purple(){
		Material* m = new Material();
		m->kd = float3(1,0,1);
		return m;
	}

	static Material* clear(){
		Material* m = new Material();
		m->refractive = true;
		m->f0 = float3(0,0,0);
		m->ks = float3(0, 0, 0);
		m->kd = float3(0, 0, 0);
		return m;
	}

	static Material* glass(){
		Material* m = new Material();
		m->refractive = true;
		m->reflective = true;
		m->f0 = float3(.3, .3, .3);
		m->n = 1.33;
		m->ks = float3(1,1,1);
		m->kd = float3(.5,.5,.5);
		return m;
	}

	static Material* gold(){
		Material* m = new Material();
		m->reflective = true;
		m->f0 = float3(
			getf0(.206, 3.07),
			getf0(.402, 2.54), 
			getf0(1.562, 1.904)); 
		m->ks = float3(0, 0, 0);
		m->kd = float3(0, 0, 0);
		return m;
	}

	static Material* silver(){
		Material* m = new Material();
		m->reflective = true;
		m->f0 = float3(
			getf0(.05,3.929),
			getf0(.06,3.498), 
			getf0(.04,2.744)); 
		m->ks = float3(0, 0, 0);
		m->kd = float3(0, 0, 0);
		return m;
	}

	static Material* copper(){
		Material* m = new Material();
		m->reflective = true;
		m->f0 = float3(
			getf0(.46818,2.80877),
			getf0(1.0379,2.59176), 
			getf0(1.16797,2.36308)); 
		m->ks = float3(0, 0, 0);
		m->kd = float3(0, 0, 0);
		return m;
	}

	static Material* platinum(){
		Material* m = new Material();
		m->reflective = true;
		m->f0 = float3(
			getf0(2.27,4.0),
			getf0(2.13,3.69), 
			getf0(1.84,3.05)); 
		m->ks = float3(0, 0, 0);
		m->kd = float3(0, 0, 0);
		return m;
	}
};

class Marble : public Material{
	Perlin perlin;

	virtual float3 getKd(Hit hit){
		return float3(3,3,3) * perlin.marble(hit.position)-float3(2,2,2);
	}

	virtual float3 getKs(Hit hit){
		return float3(3,3,3) * perlin.marble(hit.position)-float3(2,2,2);
	}
};