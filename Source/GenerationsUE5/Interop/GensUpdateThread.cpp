#include "GensUpdateThread.h"

#include "GenerationsUE5/Actors/PlayerPawn.h"
#include "GenerationsUE5/Game/GensCommon.h"
#include "GenerationsUE5/Utility/Message.h"

static constexpr size_t NUM_FRAMES = 2;
static FMatrix s_TransformMat = FMatrix(FPlane(0, -1, 0, 0), FPlane(0, 0, 1, 0), FPlane(1, 0, 0, 0),
                                        FPlane(0, 0, 0, 1));
FGensUpdateThread* FGensUpdateThread::Runnable = nullptr;

void FGensUpdateThread::processMessages()
{
	if (!m_cpuEvent.waitImm())
		return;

	m_cpuEvent.reset();
	m_messageReceiver.receiveMessages();
	m_gpuEvent.set();

	while (m_messageReceiver.hasNext())
	{
		switch (m_messageReceiver.getId())
		{
		case FMsgPadding::s_id: procMsgPadding();
			break;
		case FMsgCreateSwapChain::s_id: procMsgCreateSwapChain();
			break;
		case FMsgSetRenderTarget::s_id: procMsgSetRenderTarget();
			break;
		case FMsgCreateVertexDeclaration::s_id: procMsgCreateVertexDeclaration();
			break;
		case FMsgCreatePixelShader::s_id: procMsgCreatePixelShader();
			break;
		case FMsgCreateVertexShader::s_id: procMsgCreateVertexShader();
			break;
		case FMsgSetRenderState::s_id: procMsgSetRenderState();
			break;
		case FMsgCreateTexture::s_id: procMsgCreateTexture();
			break;
		case FMsgSetTexture::s_id: procMsgSetTexture();
			break;
		case FMsgSetDepthStencilSurface::s_id: procMsgSetDepthStencilSurface();
			break;
		case FMsgClear::s_id: procMsgClear();
			break;
		case FMsgSetVertexShader::s_id: procMsgSetVertexShader();
			break;
		case FMsgSetPixelShader::s_id: procMsgSetPixelShader();
			break;
		case FMsgSetPixelShaderConstantF::s_id: procMsgSetPixelShaderConstantF();
			break;
		case FMsgSetVertexShaderConstantF::s_id: procMsgSetVertexShaderConstantF();
			break;
		case FMsgSetVertexShaderConstantB::s_id: procMsgSetVertexShaderConstantB();
			break;
		case FMsgSetSamplerState::s_id: procMsgSetSamplerState();
			break;
		case FMsgSetViewport::s_id: procMsgSetViewport();
			break;
		case FMsgSetScissorRect::s_id: procMsgSetScissorRect();
			break;
		case FMsgSetVertexDeclaration::s_id: procMsgSetVertexDeclaration();
			break;
		case FMsgDrawPrimitiveUP::s_id: procMsgDrawPrimitiveUP();
			break;
		case FMsgSetStreamSource::s_id: procMsgSetStreamSource();
			break;
		case FMsgSetIndices::s_id: procMsgSetIndices();
			break;
		case FMsgPresent::s_id: procMsgPresent();
			break;
		case FMsgCreateVertexBuffer::s_id: procMsgCreateVertexBuffer();
			break;
		case FMsgWriteVertexBuffer::s_id: procMsgWriteVertexBuffer();
			break;
		case FMsgCreateIndexBuffer::s_id: procMsgCreateIndexBuffer();
			break;
		case FMsgWriteIndexBuffer::s_id: procMsgWriteIndexBuffer();
			break;
		case FMsgWriteTexture::s_id: procMsgWriteTexture();
			break;
		case FMsgMakeTexture::s_id: procMsgMakeTexture();
			break;
		case FMsgDrawIndexedPrimitive::s_id: procMsgDrawIndexedPrimitive();
			break;
		case FMsgSetStreamSourceFreq::s_id: procMsgSetStreamSourceFreq();
			break;
		case FMsgReleaseResource::s_id: procMsgReleaseResource();
			break;
		case FMsgDrawPrimitive::s_id: procMsgDrawPrimitive();
			break;
		case FMsgCopyVertexBuffer::s_id: procMsgCopyVertexBuffer();
			break;
		case FMsgSetPixelShaderConstantB::s_id: procMsgSetPixelShaderConstantB();
			break;
		case FMsgSaveShaderCache::s_id: procMsgSaveShaderCache();
			break;
		case FMsgDrawIndexedPrimitiveUP::s_id: procMsgDrawIndexedPrimitiveUP();
			break;
		case FMsgShowCursor::s_id: procMsgShowCursor();
			break;
		case FMsgCopyHdrTexture::s_id: procMsgCopyHdrTexture();
			break;
		case FMsgSonicInit::s_id:
			procMsgSonicInit();
			break;
		case FMsgSonicUpdate::s_id:
			procMsgSonicUpdate();
			break;
		case FMsgCameraUpdate::s_id:
			procMsgCameraUpdate();
			break;
		default:
			if (!processUEMessage())
				check(!"Unknown message type");
			break;
		}
	}

	m_frame = m_nextFrame;
	m_nextFrame = (m_frame + 1) % NUM_FRAMES;
}

bool FGensUpdateThread::processUEMessage()
{
	/*switch (m_messageReceiver.getId())
	{
	default:
		return false;
	}*/

	return true;
}

void FGensUpdateThread::procMsgPadding()
{
	const auto& message = m_messageReceiver.getMessage<FMsgPadding>();
}

void FGensUpdateThread::procMsgCreateSwapChain()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateSwapChain>();
}

void FGensUpdateThread::procMsgSetRenderTarget()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetRenderTarget>();
}

void FGensUpdateThread::procMsgCreateVertexDeclaration()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateVertexDeclaration>();
}

void FGensUpdateThread::procMsgCreatePixelShader()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreatePixelShader>();
}

void FGensUpdateThread::procMsgCreateVertexShader()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateVertexShader>();
}

void FGensUpdateThread::procMsgSetRenderState()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetRenderState>();
}

void FGensUpdateThread::procMsgCreateTexture()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateTexture>();
}

void FGensUpdateThread::procMsgSetTexture()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetTexture>();
}

void FGensUpdateThread::procMsgSetDepthStencilSurface()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetDepthStencilSurface>();
}

void FGensUpdateThread::procMsgClear()
{
	const auto& message = m_messageReceiver.getMessage<FMsgClear>();
}

void FGensUpdateThread::procMsgSetVertexShader()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetVertexShader>();
}

void FGensUpdateThread::procMsgSetPixelShader()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetPixelShader>();
}

void FGensUpdateThread::procMsgSetPixelShaderConstantF()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetPixelShaderConstantF>();
}

void FGensUpdateThread::procMsgSetVertexShaderConstantF()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetVertexShaderConstantF>();
}

void FGensUpdateThread::procMsgSetVertexShaderConstantB()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetVertexShaderConstantB>();
}

void FGensUpdateThread::procMsgSetSamplerState()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetSamplerState>();
}

void FGensUpdateThread::procMsgSetViewport()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetViewport>();
}

void FGensUpdateThread::procMsgSetScissorRect()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetScissorRect>();
}

void FGensUpdateThread::procMsgSetVertexDeclaration()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetVertexDeclaration>();
}

void FGensUpdateThread::procMsgDrawPrimitiveUP()
{
	const auto& message = m_messageReceiver.getMessage<FMsgDrawPrimitiveUP>();
}

void FGensUpdateThread::procMsgSetStreamSource()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetStreamSource>();
}

void FGensUpdateThread::procMsgSetIndices()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetIndices>();
}

void FGensUpdateThread::procMsgPresent()
{
	const auto& message = m_messageReceiver.getMessage<FMsgPresent>();
}

void FGensUpdateThread::procMsgCreateVertexBuffer()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateVertexBuffer>();
}

void FGensUpdateThread::procMsgWriteVertexBuffer()
{
	const auto& message = m_messageReceiver.getMessage<FMsgWriteVertexBuffer>();
}

void FGensUpdateThread::procMsgCreateIndexBuffer()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCreateIndexBuffer>();
}

void FGensUpdateThread::procMsgWriteIndexBuffer()
{
	const auto& message = m_messageReceiver.getMessage<FMsgWriteIndexBuffer>();
}

void FGensUpdateThread::procMsgWriteTexture()
{
	const auto& message = m_messageReceiver.getMessage<FMsgWriteTexture>();
}

void FGensUpdateThread::procMsgMakeTexture()
{
	const auto& message = m_messageReceiver.getMessage<FMsgMakeTexture>();
}

void FGensUpdateThread::procMsgDrawIndexedPrimitive()
{
	const auto& message = m_messageReceiver.getMessage<FMsgDrawIndexedPrimitive>();
}

void FGensUpdateThread::procMsgSetStreamSourceFreq()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetStreamSourceFreq>();
}

void FGensUpdateThread::procMsgReleaseResource()
{
	const auto& message = m_messageReceiver.getMessage<FMsgReleaseResource>();
}

void FGensUpdateThread::procMsgDrawPrimitive()
{
	const auto& message = m_messageReceiver.getMessage<FMsgDrawPrimitive>();
}

void FGensUpdateThread::procMsgCopyVertexBuffer()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCopyVertexBuffer>();
}

void FGensUpdateThread::procMsgSetPixelShaderConstantB()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSetPixelShaderConstantB>();
}

void FGensUpdateThread::procMsgSaveShaderCache()
{
	const auto& message = m_messageReceiver.getMessage<FMsgSaveShaderCache>();
}

void FGensUpdateThread::procMsgDrawIndexedPrimitiveUP()
{
	const auto& message = m_messageReceiver.getMessage<FMsgDrawIndexedPrimitiveUP>();
}

void FGensUpdateThread::procMsgShowCursor()
{
	const auto& message = m_messageReceiver.getMessage<FMsgShowCursor>();
}

void FGensUpdateThread::procMsgCopyHdrTexture()
{
	const auto& message = m_messageReceiver.getMessage<FMsgCopyHdrTexture>();
}

void FGensUpdateThread::procMsgSonicInit()
{
	InitMessage = m_messageReceiver.getMessage<FMsgSonicInit>();

	AsyncTask(ENamedThreads::GameThread, [&]
	{
		if (!IsValid(GensCommon) && IsValid(GensCommon->GetWorld()) && GensCommon->GetWorld()->IsGameWorld()) return;
		GensCommon->SpawnPlayer(InitMessage.bIsModern);
	});
}

void FGensUpdateThread::procMsgSonicUpdate()
{
	UpdateMessage = m_messageReceiver.getMessage<FMsgSonicUpdate>();

	AsyncTask(ENamedThreads::GameThread, [&]
	{
		if (!IsValid(GensCommon) && IsValid(GensCommon->GetWorld()) && GensCommon->GetWorld()->IsGameWorld()) return;
		if (!IsValid(GensCommon->PlayerPawn) && IsValid(GensCommon)) GensCommon->SpawnPlayer(InitMessage.bIsModern);

		const auto WorldMatrix = FMatrix(
			FPlane(UpdateMessage.matrix[0], UpdateMessage.matrix[4], UpdateMessage.matrix[8], UpdateMessage.matrix[12]),
			FPlane(UpdateMessage.matrix[1], UpdateMessage.matrix[5], UpdateMessage.matrix[9], UpdateMessage.matrix[13]),
			FPlane(UpdateMessage.matrix[2], UpdateMessage.matrix[6], UpdateMessage.matrix[10], UpdateMessage.matrix[14]),
			FPlane(UpdateMessage.matrix[3], UpdateMessage.matrix[7], UpdateMessage.matrix[11], UpdateMessage.matrix[15]));

		const auto Position = s_TransformMat.TransformPosition(
			FVector(UpdateMessage.matrix[12], UpdateMessage.matrix[13], UpdateMessage.matrix[14])) * 100;
		auto Rotation = (s_TransformMat * WorldMatrix).Rotator();
		Rotation = FRotator(-Rotation.Yaw - 90, -Rotation.Roll, Rotation.Pitch);

		TArray<FTransform> BoneTransforms;
		TMap<int, FString> BoneIndicesToNames;

		for (int i = 0; i < UpdateMessage.boneCount; i++)
		{
			const auto BoneMatrix = FMatrix(
				FPlane(UpdateMessage.boneMatrices[i][0], UpdateMessage.boneMatrices[i][4], UpdateMessage.boneMatrices[i][8], UpdateMessage.boneMatrices[i][12]),
				FPlane(UpdateMessage.boneMatrices[i][1], UpdateMessage.boneMatrices[i][5], UpdateMessage.boneMatrices[i][9], UpdateMessage.boneMatrices[i][13]),
				FPlane(UpdateMessage.boneMatrices[i][2], UpdateMessage.boneMatrices[i][6], UpdateMessage.boneMatrices[i][10], UpdateMessage.boneMatrices[i][14]),
				FPlane(UpdateMessage.boneMatrices[i][3], UpdateMessage.boneMatrices[i][7], UpdateMessage.boneMatrices[i][11], UpdateMessage.boneMatrices[i][15]));

			auto Pos = FVector(UpdateMessage.boneMatrices[i][12], UpdateMessage.boneMatrices[i][13], UpdateMessage.boneMatrices[i][14]) * 100;
			auto Rot = BoneMatrix.Rotator();

			BoneTransforms.Push(FTransform(Rot, Pos, FTransform(BoneMatrix).GetScale3D()));
			BoneIndicesToNames.Add(i, FString(UpdateMessage.boneNames[i]));
		}

		GensCommon->PlayerPawn->SetActorLocationAndRotation(Position, Rotation);
		GensCommon->PlayerPawn->SetBoneTransforms(BoneTransforms);
		GensCommon->PlayerPawn->SetBoneIndicesToNames(BoneIndicesToNames);
	});
}

void FGensUpdateThread::procMsgCameraUpdate()
{
	const auto tmpMessage = m_messageReceiver.getMessage<FMsgCameraUpdate>();

	if (tmpMessage.posX != 0 && tmpMessage.posY != 0 && tmpMessage.posZ != 0
		&& tmpMessage.tgtX != 0 && tmpMessage.tgtY != 0 && tmpMessage.tgtZ != 0)
	{
		CameraMessage = tmpMessage;
	}

	AsyncTask(ENamedThreads::GameThread, [&]
	{
		if (!IsValid(GensCommon) && IsValid(GensCommon->GetWorld()) && GensCommon->GetWorld()->IsGameWorld()) return;
		
		const auto Pos = s_TransformMat.TransformPosition(
			FVector(CameraMessage.posX * 100, CameraMessage.posY * 100, CameraMessage.posZ * 100));
		const auto Tgt = s_TransformMat.TransformPosition(
			FVector(CameraMessage.tgtX * 100, CameraMessage.tgtY * 100, CameraMessage.tgtZ * 100));
		const auto Up = s_TransformMat.TransformPosition(
			FVector(CameraMessage.upX, CameraMessage.upY, CameraMessage.upZ));

		const auto HFov = FMath::Atan(FMath::Tan(CameraMessage.fov / 2)) * 2 * CameraMessage.aspectRatio;

		GensCommon->UpdateCamera(Pos, Tgt, Up, FMath::RadiansToDegrees(HFov));
	});
}

FGensUpdateThread::FGensUpdateThread(UGensCommon* InGensCommon) : GensCommon(InGensCommon)
{
	Thread = FRunnableThread::Create(this, TEXT("FGensUpdateThread"), 0, TPri_Normal);
}

FGensUpdateThread::~FGensUpdateThread()
{
	delete Thread;
	Thread = nullptr;
}

uint32 FGensUpdateThread::Run()
{
	while (m_Timeout < 60)
	{
		processMessages();

		if (!(IsValid(GensCommon) && IsValid(GensCommon->GetWorld()) && GensCommon->GetWorld()->IsGameWorld()))
		{
			m_Timeout++;
			FPlatformProcess::Sleep(0.016);
		}
	}

	return 0;
}

FGensUpdateThread* FGensUpdateThread::GensUpdateInit(UGensCommon* InGensCommon)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FGensUpdateThread(InGensCommon);
	}
	return Runnable;
}
