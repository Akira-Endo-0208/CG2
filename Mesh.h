#pragma once
#include<Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include "Windows.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


using namespace DirectX;

class Mesh
{
public:
	Mesh();

	void init(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);
	void affinInit();
	void Update(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList,IDXGISwapChain4* swapChain);
	void affinUpdate();
	void Draw(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

public:
	HRESULT result;

	D3D12_VIEWPORT viewport{};

	ID3D12Resource* vertBuff = nullptr;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;

	ID3D12Resource* constBuffMaterial = nullptr;

	XMFLOAT3 vertices[3] = {
{ -0.5f, -0.5f, 0.0f }, // ����
{ -0.5f, +0.5f, 0.0f }, // ����
{ +0.5f, -0.5f, 0.0f }, // �E��
	};


	D3D12_RESOURCE_BARRIER barrierDesc{};



	XMFLOAT3* vertMap = nullptr;

	


	float transformX;
	float transformY;
	float rotation;
	float scale;

	float affin[3][3] = {
	   {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} };
	
};

