
// Ray structure.
class Ray
{
public:
    float3 origin;
    float3 dir;
    Ray(float3 o, float3 d)
    {
        origin = o;
        dir = d.normalize();
    }

    Ray localize(float3 center, float3 rotation) const
    {
        float4x4 translationMatrix = float4x4::translation(center * -1);
        float4x4 xRotationMatrix = float4x4::rotation(float3(1,0,0), rotation.x);
        float4x4 yRotationMatrix = float4x4::rotation(float3(0,1,0), rotation.y);
        float4x4 zRotationMatrix = float4x4::rotation(float3(0,0,1), rotation.z);
        float3 newOrigin = origin;
        newOrigin = translationMatrix.transform(newOrigin);
        newOrigin = xRotationMatrix.transform(newOrigin);
        newOrigin = yRotationMatrix.transform(newOrigin);
        newOrigin = zRotationMatrix.transform(newOrigin);
        float3 newDir = dir;
        // newDir = translationMatrix.transform(newDir);
        newDir = xRotationMatrix.transform(newDir);
        newDir = yRotationMatrix.transform(newDir);
        newDir = zRotationMatrix.transform(newDir);
        return Ray(newOrigin, newDir);
    }
};
