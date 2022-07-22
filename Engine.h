#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include "ComPtr.h"
#include <vector>
#include <string>

#pragma comment(lib, "d3d12.lib") // d3d12���C�u�����������N����
#pragma comment(lib, "dxgi.lib") // dxgi���C�u�����������N����

class Engine
{
public:

public:
	bool Init(HWND hwnd, const int window_Width, const int window_Height); // �G���W��������

	void BeginRender(); // �`��̊J�n����
	void EndRender(); // �`��̏I������

public: // �O����A�N�Z�X�������̂�Getter�Ƃ��Č��J�������
	ComPtr<ID3D12Device> Device();
	ComPtr <ID3D12GraphicsCommandList> CommandList();


private: // DirectX12�������Ɏg���֐�����
	void CreateAdapters();
	bool CreateDevice(); // �f�o�C�X�𐶐�
	bool CreateCommandQueue(); // �R�}���h�L���[�𐶐�
	bool CreateSwapChain(); // �X���b�v�`�F�C���𐶐�
	bool CreateCommandList(); // �R�}���h���X�g�ƃR�}���h�A���P�[�^�[�𐶐�
	bool CreateFence(); // �t�F���X�𐶐�
	void CreateViewPort(); // �r���[�|�[�g�𐶐�
	void CreateScissorRect(); // �V�U�[��`�𐶐�

private: // �`��Ɏg��DirectX12�̃I�u�W�F�N�g����

	HRESULT result;
	ComPtr<ID3D12Device> device;
	ComPtr <IDXGIFactory7> dxgiFactory;
	ComPtr <IDXGISwapChain4> swapChain;
	ComPtr <ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr < ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

private: // �`��Ɏg���I�u�W�F�N�g�Ƃ��̐����֐�����


	
};

extern Engine* g_Engine; // �ǂ�����ł��Q�Ƃ������̂ŃO���[�o���ɂ���