
// Object realization.
class Sphere : public Intersectable
{
	float3 center;
	float radius;
public:
    Sphere(const float3& center, float radius, Material* material):
		Intersectable(material),
		center(center),
		radius(radius)
    {
    }
    Hit intersect(const Ray& ray)
    {
        float3 diff = ray.origin - center;
		// quadratic equation coefficients
        double a = ray.dir.dot(ray.dir);
        double b = diff.dot(ray.dir) * 2.0;
        double c = diff.dot(diff) - radius * radius;
 
        double discr = b * b - 4.0 * a * c;
        if ( discr < 0 )			// line of ray does not intersect sphere
            return Hit();			// empty hit record with negative t
        double sqrt_discr = sqrt( discr );
        double t1 = (-b + sqrt_discr)/2.0/a;
        double t2 = (-b - sqrt_discr)/2.0/a;
 
		float t = (t1<t2)?t1:t2;	// take minimum
		if(t < 0)					// minimum is behind us
			t = (t1<t2)?t2:t1;		// take maximum
		if (t < 0)					// sphere not intersected
            return Hit();			// empty hit record with negative t

		Hit h;
		h.t = t;
		h.material = material;
		h.position = ray.origin + ray.dir * t;
		h.normal = h.position - center;
		h.normal.normalize();
		h.uv = float2( h.normal.dot(float3(0, 1, 0)) * 0.5 + 0.5,  atan2(h.normal.z, h.normal.x) / (2 * M_PI) + 0.5 );

		return h;

    }
}; 
