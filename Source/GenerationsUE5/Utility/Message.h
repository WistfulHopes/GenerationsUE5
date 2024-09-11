#pragma once

#include <cstdint>

#define MSG_DEFINE_MESSAGE(PREVIOUS_MESSAGE) \
    static constexpr uint8 s_id = PREVIOUS_MESSAGE::s_id + 1; \
    uint8 id = s_id

#pragma pack(push, 1)

struct FMsgPadding
{
    static constexpr uint32 s_id = 0;
    uint8 id;
    uint8 dataSize;
    uint8 data[1u];
};

struct FMsgCreateSwapChain
{
    MSG_DEFINE_MESSAGE(FMsgPadding);
    uint32 postHandle;
    uint32 style;
    int32 x;
    int32 y;
    int32 width;
    int32 height;
    uint16 renderWidth;
    uint16 renderHeight;
    uint8 format;
    uint8 bufferCount;
    bool hdr;
    uint8 syncInterval;
    uint32 textureId;
};

struct FMsgSetRenderTarget
{
    MSG_DEFINE_MESSAGE(FMsgCreateSwapChain);
    uint8 renderTargetIndex;
    uint32 textureId;
    uint8 textureLevel;
};
struct FMsgCreateVertexDeclaration
{
    MSG_DEFINE_MESSAGE(FMsgSetRenderTarget);
    uint32 vertexDeclarationId;
    bool isFVF;
    uint16 dataSize;
    uint8 data[1u];
};
struct FMsgCreatePixelShader
{
    MSG_DEFINE_MESSAGE(FMsgCreateVertexDeclaration);
    uint32 pixelShaderId;
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};
struct FMsgCreateVertexShader
{
    MSG_DEFINE_MESSAGE(FMsgCreatePixelShader);
    uint32 vertexShaderId;
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};

struct FMsgSetRenderState
{
    MSG_DEFINE_MESSAGE(FMsgCreateVertexShader);
    uint8 state;
    uint32 value;
};

struct FMsgCreateTexture
{
    MSG_DEFINE_MESSAGE(FMsgSetRenderState);
    uint16 width;
    uint16 height;
    uint8 levels;
    uint32 usage;
    uint32 format;
    uint32 textureId;
};

struct FMsgSetTexture
{
    MSG_DEFINE_MESSAGE(FMsgCreateTexture);
    uint8 stage;
    uint32 textureId;
};

struct FMsgSetDepthStencilSurface
{
    MSG_DEFINE_MESSAGE(FMsgSetTexture);
    uint32 depthStencilSurfaceId;
    uint8 level;
};

struct FMsgClear
{
    MSG_DEFINE_MESSAGE(FMsgSetDepthStencilSurface);
    uint32 flags;
    uint32 color;
    float z;
    uint8 stencil;
};

struct FMsgSetVertexShader
{
    MSG_DEFINE_MESSAGE(FMsgClear);
    uint32 vertexShaderId;
};

struct FMsgSetPixelShader
{
    MSG_DEFINE_MESSAGE(FMsgSetVertexShader);
    uint32 pixelShaderId;
};

struct FMsgSetPixelShaderConstantF
{
    MSG_DEFINE_MESSAGE(FMsgSetPixelShader);
    uint8 startRegister;
    uint16 dataSize;
    uint8 data[1u];
};

struct FMsgSetVertexShaderConstantF
{
    MSG_DEFINE_MESSAGE(FMsgSetPixelShaderConstantF);
    uint8 startRegister;
    uint16 dataSize;
    uint8 data[1u];
};

struct FMsgSetVertexShaderConstantB
{
    MSG_DEFINE_MESSAGE(FMsgSetVertexShaderConstantF);
    uint32 startRegister;
    uint8 dataSize;
    uint8 data[1u];
};

struct FMsgSetSamplerState
{
    MSG_DEFINE_MESSAGE(FMsgSetVertexShaderConstantB);
    uint8 sampler;
    uint8 type;
    uint32 value;
};

struct FMsgSetViewport
{
    MSG_DEFINE_MESSAGE(FMsgSetSamplerState);
    uint16 x;
    uint16 y;
    uint16 width;
    uint16 height;
    float minZ;
    float maxZ;
};

struct FMsgSetScissorRect
{
    MSG_DEFINE_MESSAGE(FMsgSetViewport);
    uint16 left;
    uint16 top;
    uint16 right;
    uint16 bottom;
};

struct FMsgSetVertexDeclaration
{
    MSG_DEFINE_MESSAGE(FMsgSetScissorRect);
    uint32 vertexDeclarationId;
};

struct FMsgDrawPrimitiveUP
{
    MSG_DEFINE_MESSAGE(FMsgSetVertexDeclaration);
    uint8 primitiveType;
    uint32 vertexCount;
    uint8 vertexStreamZeroStride;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgSetStreamSource
{
    MSG_DEFINE_MESSAGE(FMsgDrawPrimitiveUP);
    uint8 streamNumber;
    uint32 streamDataId;
    uint32 offsetInBytes;
    uint8 stride;
};

struct FMsgSetIndices
{
    MSG_DEFINE_MESSAGE(FMsgSetStreamSource);
    uint32 indexDataId;
};

struct FMsgPresent
{
    MSG_DEFINE_MESSAGE(FMsgSetIndices);
};

struct FMsgCreateVertexBuffer
{
    MSG_DEFINE_MESSAGE(FMsgPresent);
    uint32 length;
    uint32 vertexBufferId;
    bool allowUnorderedAccess;
};

struct FMsgWriteVertexBuffer
{
    MSG_DEFINE_MESSAGE(FMsgCreateVertexBuffer);
    uint32 vertexBufferId;
    uint32 offset;
    bool initialWrite;
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};

struct FMsgCreateIndexBuffer
{
    MSG_DEFINE_MESSAGE(FMsgWriteVertexBuffer);
    uint32 length;
    uint32 format;
    uint32 indexBufferId;
};

struct FMsgWriteIndexBuffer
{
    MSG_DEFINE_MESSAGE(FMsgCreateIndexBuffer);
    uint32 indexBufferId;
    uint32 offset;
    bool initialWrite;
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};

struct FMsgWriteTexture
{
    MSG_DEFINE_MESSAGE(FMsgWriteIndexBuffer);
    uint32 textureId;
    uint32 width;
    uint32 height;
    uint32 level;
    uint32 pitch;
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};

struct FMsgMakeTexture
{
    MSG_DEFINE_MESSAGE(FMsgWriteTexture);
    uint32 textureId;
#ifdef _DEBUG
    char textureName[0x100];
#endif
    uint32 dataSize;
    alignas(0x10) uint8 data[1u];
};

struct FMsgDrawIndexedPrimitive
{
    MSG_DEFINE_MESSAGE(FMsgMakeTexture);
    uint8 primitiveType;
    int32 baseVertexIndex;
    uint32 startIndex;
    uint32 indexCount;
};

struct FMsgSetStreamSourceFreq
{
    MSG_DEFINE_MESSAGE(FMsgDrawIndexedPrimitive);
    uint8 streamNumber;
    uint32 setting;
};

struct FMsgReleaseResource
{
    MSG_DEFINE_MESSAGE(FMsgSetStreamSourceFreq);

    enum class ResourceType : uint8
    {
        Texture,
        IndexBuffer,
        VertexBuffer,
    };

    ResourceType resourceType;
    uint32 resourceId;
};

struct FMsgDrawPrimitive
{
    MSG_DEFINE_MESSAGE(FMsgReleaseResource);
    uint8 primitiveType;
    uint32 startVertex;
    uint32 vertexCount;
};

struct FMsgCreateBottomLevelAccelStruct
{
    MSG_DEFINE_MESSAGE(FMsgDrawPrimitive);

    struct FGeometryDesc
    {
        uint32 flags;
        uint32 indexBufferId;
        uint32 indexCount;
        uint32 indexOffset;
        uint32 vertexBufferId;
        uint32 vertexStride;
        uint32 vertexCount;
        uint32 vertexOffset;
        uint32 normalOffset;
        uint32 tangentOffset;
        uint32 binormalOffset;
        uint32 colorOffset;
        uint32 texCoordOffsets[4];
        uint32 materialId;
    };

    uint32 bottomLevelAccelStructId;
    bool allowUpdate;
    bool allowCompaction;
    bool preferFastBuild;
    bool asyncBuild;
    uint32 dataSize;
    uint8 data[1u];
};

enum class RaytracingResourceType : uint8
{
    BottomLevelAccelStruct,
    Material
};

struct FMsgReleaseRaytracingResource
{
    MSG_DEFINE_MESSAGE(FMsgCreateBottomLevelAccelStruct);

    RaytracingResourceType resourceType;
    uint32 resourceId;
};

struct FMsgCreateInstance
{
    MSG_DEFINE_MESSAGE(FMsgReleaseRaytracingResource);

    float transform[3][4];
    float prevTransform[3][4];
    float headTransform[3][4];
    uint32 bottomLevelAccelStructId;
    bool isMirrored;
    uint8 instanceMask;
    uint8 instanceType;
    float playableParam;
    float chrPlayableMenuParam;
    float forceAlphaColor;
    float edgeEmissionParam;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgTraceRays
{
    MSG_DEFINE_MESSAGE(FMsgCreateInstance);

    uint16 width;
    uint16 height;
    bool resetAccumulation;
    float diffusePower;
    float lightPower;
    float emissivePower;
    float skyPower;
    uint32 debugView;
    uint32 envMode;
    float skyColor[3];
    float groundColor[3];
    bool useSkyTexture;
    float backgroundColor[3];
    uint32 upscaler;
    uint32 qualityMode;
    uint32 adaptionLuminanceTextureId;
    float middleGray;
    bool skyInRoughReflection;
    bool enableExposureTexture;
    uint32 envBrdfTextureId;
};

struct FMsgCreateMaterial
{
    MSG_DEFINE_MESSAGE(FMsgTraceRays);

    struct FTexture
    {
        uint32 id;
        uint8 addressModeU;
        uint8 addressModeV;
        uint32 texCoordIndex;
    };

    uint32 materialId;
    uint32 shaderType;
    uint32 flags;
    float texCoordOffsets[8];
    uint32 textureCount;
    FTexture textures[16];
    uint32 parameterCount;
    float parameters[32];
};

struct FMsgComputePose
{
    MSG_DEFINE_MESSAGE(FMsgCreateMaterial);

    struct FGeometryDesc
    {
        uint32 vertexCount;
        uint32 vertexBufferId;
        uint32 vertexOffset;
        uint8 vertexStride;
        uint8 normalOffset;
        uint8 tangentOffset;
        uint8 binormalOffset;
        uint8 blendWeightOffset;
        uint8 blendIndicesOffset;
        uint8 blendWeight1Offset;
        uint8 blendIndices1Offset;
        uint8 nodeCount;
        bool visible;
    };

    uint32 vertexBufferId;
    uint8 nodeCount;
    uint32 geometryCount;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgBuildBottomLevelAccelStruct
{
    MSG_DEFINE_MESSAGE(FMsgComputePose);
    uint32 bottomLevelAccelStructId;
    bool performUpdate;
};

struct FMsgCopyVertexBuffer
{
    MSG_DEFINE_MESSAGE(FMsgBuildBottomLevelAccelStruct);
    uint32 dstVertexBufferId;
    uint32 dstOffset;
    uint32 srcVertexBufferId;
    uint32 srcOffset;
    uint32 numBytes;
};

struct FMsgRenderSky
{
    MSG_DEFINE_MESSAGE(FMsgCopyVertexBuffer);

    struct FGeometryDesc
    {
        uint32 flags;
        uint32 vertexBufferId;
        uint32 vertexOffset;
        uint32 vertexStride;
        uint32 vertexCount;
        uint32 indexBufferId;
        uint32 indexOffset;
        uint32 indexCount;
        uint32 vertexDeclarationId;
        bool isAdditive;
        bool enableVertexColor;
        FMsgCreateMaterial::FTexture diffuseTexture;
        FMsgCreateMaterial::FTexture alphaTexture;
        FMsgCreateMaterial::FTexture emissionTexture;
        float diffuse[4];
        float ambient[4];
    };

    float backgroundScale;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgCreateLocalLight
{
    MSG_DEFINE_MESSAGE(FMsgRenderSky);

    float position[3];
    float color[3];
    float inRange;
    float outRange;
    bool castShadow;
    bool enableBackfaceCulling;
    float shadowRange;
};

struct FMsgSetPixelShaderConstantB
{
    MSG_DEFINE_MESSAGE(FMsgCreateLocalLight);
    uint32 startRegister;
    uint8 dataSize;
    uint8 data[1u];
};

struct FMsgSaveShaderCache
{
    MSG_DEFINE_MESSAGE(FMsgSetPixelShaderConstantB);
};

struct FMsgComputeSmoothNormal
{
    MSG_DEFINE_MESSAGE(FMsgSaveShaderCache);
    uint32 indexBufferId;
    uint32 indexOffset;
    uint8 vertexStride;
    uint32 vertexCount;
    uint32 vertexOffset;
    uint8 normalOffset;
    uint32 vertexBufferId;
    uint32 adjacencyBufferId;
    bool isMirrored;
};

struct FMsgDrawIndexedPrimitiveUP
{
    MSG_DEFINE_MESSAGE(FMsgComputeSmoothNormal);
    uint8 primitiveType;
    uint32 vertexCount;
    uint32 indexCount;
    uint8 indexFormat;
    uint8 vertexStride;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgShowCursor
{
    MSG_DEFINE_MESSAGE(FMsgDrawIndexedPrimitiveUP);
    bool showCursor;
};

struct FMsgDispatchUpscaler
{
    MSG_DEFINE_MESSAGE(FMsgShowCursor);
    uint32 debugView;
    bool resetAccumulation;
};

struct FMsgDrawIm3d
{
    MSG_DEFINE_MESSAGE(FMsgDispatchUpscaler);

    struct FDrawList
    {
        uint8 primitiveType;
        uint32 vertexOffset;
        uint32 vertexCount;
    };

    float projection[4][4];
    float view[4][4];
    float viewportSize[2];
    uint32 depthStencilId;
    uint32 vertexSize;
    uint32 drawListCount;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgCopyHdrTexture
{
    MSG_DEFINE_MESSAGE(FMsgDrawIm3d);
};

struct FMsgComputeGrassInstancer
{
    MSG_DEFINE_MESSAGE(FMsgCopyHdrTexture);

    struct FLodDesc
    {
        uint32 instanceOffset;
        uint32 instanceCount;
        uint32 vertexOffset;
    };

    float instanceTypes[32][4];
    float misc;
    uint32 instanceBufferId;
    uint32 vertexBufferId;
    uint32 dataSize;
    uint8 data[1u];
};

struct FMsgSonicInit
{
    MSG_DEFINE_MESSAGE(FMsgComputeGrassInstancer);

    bool bIsModern;
};

struct FGensBoneTransform
{
    float posX;
    float posY;
    float posZ;
    
    float rotX;
    float rotY;
    float rotZ;
    float rotW;
    
    float sclX;
    float sclY;
    float sclZ;
};

struct FMsgSonicUpdate
{
    MSG_DEFINE_MESSAGE(FMsgSonicInit);
    
    bool bIsSuper;
    
    float matrix[16];

    int boneCount;
    char boneNames[0xFF][0x40];
    FGensBoneTransform boneTransforms[0xFF];
};

struct FMsgCameraUpdate
{
    MSG_DEFINE_MESSAGE(FMsgSonicUpdate);
    
    float posX;
    float posY;
    float posZ;
    
    float tgtX;
    float tgtY;
    float tgtZ;
    
    float upX;
    float upY;
    float upZ;

    float fov;
    float aspectRatio;
};

#pragma pack(pop)