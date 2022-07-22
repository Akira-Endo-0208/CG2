#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include "ComPtr.h"
#include <vector>
#include <string>

#pragma comment(lib, "d3d12.lib") // d3d12ライブラリをリンクする
#pragma comment(lib, "dxgi.lib") // dxgiライブラリをリンクする

class Engine
{
public:

public:
	bool Init(HWND hwnd, const int window_Width, const int window_Height); // エンジン初期化

	void BeginRender(); // 描画の開始処理
	void EndRender(); // 描画の終了処理

public: // 外からアクセスしたいのでGetterとして公開するもの
	ComPtr<ID3D12Device> Device();
	ComPtr <ID3D12GraphicsCommandList> CommandList();


private: // DirectX12初期化に使う関数たち
	void CreateAdapters();
	bool CreateDevice(); // デバイスを生成
	bool CreateCommandQueue(); // コマンドキューを生成
	bool CreateSwapChain(); // スワップチェインを生成
	bool CreateCommandList(); // コマンドリストとコマンドアロケーターを生成
	bool CreateFence(); // フェンスを生成
	void CreateViewPort(); // ビューポートを生成
	void CreateScissorRect(); // シザー矩形を生成

private: // 描画に使うDirectX12のオブジェクトたち

	HRESULT result;
	ComPtr<ID3D12Device> device;
	ComPtr <IDXGIFactory7> dxgiFactory;
	ComPtr <IDXGISwapChain4> swapChain;
	ComPtr <ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr < ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

private: // 描画に使うオブジェクトとその生成関数たち


	
};

extern Engine* g_Engine; // どこからでも参照したいのでグローバルにする