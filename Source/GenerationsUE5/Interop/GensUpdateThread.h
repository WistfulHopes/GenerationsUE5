#pragma once
#include "GenerationsUE5/Utility/Event.h"
#include "GenerationsUE5/Utility/Message.h"
#include "GenerationsUE5/Utility/MessageReceiver.h"

class UGensCommon;

class FGensUpdateThread : FRunnable
{
public:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static FGensUpdateThread* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	
private:
	TObjectPtr<UGensCommon> GensCommon;
	
	FMessageReceiver m_messageReceiver;

	FMsgSonicInit InitMessage;
	FMsgSonicUpdate UpdateMessage;
	FMsgCameraUpdate CameraMessage;
	
	FGensEvent m_cpuEvent{FGensEvent::s_cpuEventName};
	FGensEvent m_gpuEvent{FGensEvent::s_gpuEventName};

	uint32 m_frame = 0;
	uint32 m_nextFrame = 1;
	uint32 m_Timeout = 0;
	bool m_shouldPresent = false;
	
	void processMessages();
	bool processUEMessage();
	
	void procMsgPadding();
	void procMsgCreateSwapChain();
	void procMsgSetRenderTarget();
	void procMsgCreateVertexDeclaration();
	void procMsgCreatePixelShader();
	void procMsgCreateVertexShader();
	void procMsgSetRenderState();
	void procMsgCreateTexture();
	void procMsgSetTexture();
	void procMsgSetDepthStencilSurface();
	void procMsgClear();
	void procMsgSetVertexShader();;
	void procMsgSetPixelShader();
	void procMsgSetPixelShaderConstantF();
	void procMsgSetVertexShaderConstantF();
	void procMsgSetVertexShaderConstantB();
	void procMsgSetSamplerState();
	void procMsgSetViewport();
	void procMsgSetScissorRect();
	void procMsgSetVertexDeclaration();
	void procMsgDrawPrimitiveUP();
	void procMsgSetStreamSource();
	void procMsgSetIndices();
	void procMsgPresent();
	void procMsgCreateVertexBuffer();
	void procMsgWriteVertexBuffer();
	void procMsgCreateIndexBuffer();
	void procMsgWriteIndexBuffer();
	void procMsgWriteTexture();
	void procMsgMakeTexture();
	void procMsgDrawIndexedPrimitive();
	void procMsgSetStreamSourceFreq();
	void procMsgReleaseResource();
	void procMsgDrawPrimitive();
	void procMsgCopyVertexBuffer();
	void procMsgSetPixelShaderConstantB();
	void procMsgSaveShaderCache();
	void procMsgDrawIndexedPrimitiveUP();
	void procMsgShowCursor();
	void procMsgCopyHdrTexture();
	void procMsgSonicInit();
	void procMsgSonicUpdate();
	void procMsgCameraUpdate();

public:
	FGensUpdateThread(UGensCommon* InGensCommon);
	virtual ~FGensUpdateThread() override;

	virtual uint32 Run() override;
	
	static FGensUpdateThread* GensUpdateInit(UGensCommon* InGensCommon);
};
