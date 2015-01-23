class LightSource 
{ 
public: 
 virtual float3 getRadianceAt ( float3 x )=0; 
 virtual float3 getLightDirAt ( float3 x )=0; 
 virtual float getDistanceFrom( float3 x )=0; 
}; 

class DirectionalLight : public LightSource {
private:
	float3 radiance;
	float3 direction;
public:
	DirectionalLight(float3 radiance, float3 direction):radiance(radiance),direction(direction){}

	float3 getRadianceAt( float3 x ){
		return radiance;
	}

	float3 getLightDirAt( float3 x ){
		return direction;
	}

	float getDistanceFrom( float3 x ){
		return FLT_MAX;
	}
};

class PointLight : public LightSource {
private:
	float3 power;
	float3 position;
public:
	PointLight(float3 power, float3 position):power(power),position(position){}

	float3 getRadianceAt( float3 x ){
		float3 d = (x-position);
		return power/(4*M_PI*d.norm()*d.norm());
	}

	float3 getLightDirAt( float3 x ){
		return (position-x).normalize();
	}

	float getDistanceFrom( float3 x ){
		return (position-x).norm(); 
	}
};