
// Object realization.
class Ellipsoid : public Intersectable
{
    float3 center;
	float3 rotation;
	float3 coeffs;
public:
    Ellipsoid(const float3& center, float3 coeffs, float3 rotation, Material* material):
		Intersectable(material),
		center(center),
        coeffs(coeffs),
		rotation(rotation)
    {}

    Hit intersect(const Ray& ray)
    {
    	// float3 center1 = 
        const Ray& newRay = ray.localize(center, rotation);

        float3 diff = ray.origin - center;
		// quadratic equation coefficients
        double a = (ray.dir/coeffs).dot(ray.dir/coeffs);
        double b = ((diff/coeffs).dot(ray.dir/coeffs) * 2.0);
        double c = ((diff/coeffs).dot(diff/coeffs)) - 1;
 
        double discr = b * b - 4.0 * a * c;
        if ( discr < 0 )			// line of ray does not intersect Ellipsoid
            return Hit();			// empty hit record with negative t
        double sqrt_discr = sqrt( discr );
        double t1 = (-b + sqrt_discr)/2.0/a;
        double t2 = (-b - sqrt_discr)/2.0/a;
 
		float t = (t1<t2)?t1:t2;	// take minimum
		if(t < 0)					// minimum is behind us
			t = (t1<t2)?t2:t1;		// take maximum
		if (t < 0)					// Ellipsoid not intersected
            return Hit();			// empty hit record with negative t

		Hit h;
		h.t = t;
		h.material = material;
		h.position = ray.origin + ray.dir * t;
		h.normal = (ray.origin + ray.dir * t - center)/(coeffs*coeffs);
		h.normal.normalize();
        h.uv = float2( h.normal.dot(float3(0, 1, 0)) * 0.5 + 0.5,  atan2(h.normal.z, h.normal.x) / (2 * M_PI) + 0.5 );

		return h.delocalize(center, rotation);

    }
}; 
 