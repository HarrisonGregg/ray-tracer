
// Object realization.
class Plane : public Intersectable
{
	float3 x0;
	float3 n;
public:
    Plane(const float3& x0, const float3& n, Material* material):
		Intersectable(material),
		x0(x0),
		n(n)
    {
    }
    Hit intersect(const Ray& ray)
    {
		Hit h;
		h.t = (n.dot(x0)-n.dot(ray.origin))/n.dot(ray.dir);
		h.material = material;
		h.position = ray.origin + ray.dir * h.t;
		h.normal = n;
		h.normal.normalize();
		float3 T = n.cross(float3(1,0,0)).normalize();
		if(T==float3(0,0,0)){
			T = n.cross(float3(0,1,0)).normalize();
		}
		float3 B = T.cross(n);
		float3 x = n+n.cross(n+float3(0,1,0));
		h.uv = float2( 
			(x-x0).dot(T),
			(x-x0).dot(B));

		return h;

    }
}; 
