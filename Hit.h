class Material;

// Hit record structure. Contains all data that describe a ray-object intersection point.
class Hit
{
public:
	Hit()
	{
		t = -1;	// means no intersection found
	}
	float t;
	float3 position;
	float3 normal;
	float2 uv;
	Material* material;

	Hit delocalize(float3 center, float3 rotation) const
	{
        float4x4 translationMatrix = float4x4::translation(center);
        float4x4 zRotationMatrix = float4x4::rotation(float3(0,0,1), -rotation.z);
        float4x4 yRotationMatrix = float4x4::rotation(float3(0,1,0), -rotation.y);
        float4x4 xRotationMatrix = float4x4::rotation(float3(1,0,0), -rotation.x);

        float3 newPosition = position;
        newPosition = zRotationMatrix.transform(newPosition);
        newPosition = yRotationMatrix.transform(newPosition);
        newPosition = xRotationMatrix.transform(newPosition);
        newPosition = translationMatrix.transform(newPosition);

        float3 newNormal = normal;
        newNormal = zRotationMatrix.transform(newNormal);
        newNormal = yRotationMatrix.transform(newNormal);
        newNormal = xRotationMatrix.transform(newNormal);

        Hit *newHit = new Hit();
        newHit->t = t;
        newHit->position = newPosition;
        newHit->normal = newNormal;
        newHit->uv = uv;
        newHit->material = material;
        return *newHit;
	}
};

