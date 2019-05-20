#ifndef DIRECTX11_DEFINED
#define DIRECTX11_DEFINED

#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <SimpleMath.h>
#include <wrl.h>
#include <wrl/client.h>
#include "dx.h"

// Uncopyableクラス
class Uncopyable 
{
protected:
	Uncopyable() = default;
	~Uncopyable() = default;
private:
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable& operator =(const Uncopyable&) = delete;
};

// Graphicsクラス
class DirectX11 : private Uncopyable 
{
private:
	// コンストラクタ
	DirectX11() 
	{
	}

public:
	// DirectX11 Graphicsクラスのインスタンスを取得する 
	static DirectX11& Get() 
	{
		if (m_directX.get() == nullptr) 
		{
			m_directX.reset(new DirectX11());
		}
		return *m_directX.get();
	}
	// DirectX11 Graphicsオブジェクトを破棄する 
	static void Dispose() 
	{
		m_directX.reset();
	}
	// ウィンドウハンドルを取得する 
	HWND GetHWnd() const
	{
		return m_hWnd;
	}
	// ウィンドウハンドルを設定する 
	void SetHWnd(HWND hWnd) 
	{
		m_hWnd = hWnd;
	}
	// ウィンドウ幅を取得する 
	int GetWidth() const
	{
		return m_width;
	}
	// ウィンドウ幅を設定する 
	void SetWidth(int width) 
	{
		m_width = width;
	}
	// ウィンドウ高を取得する 
	int GetHeight() const
	{
		return m_height;
	}
	// ウィンドウ高を設定する 
	void SetHeight(int height) 
	{
		m_height = height;
	}
	// デバイスを取得する Get device object
	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() const
	{
		return m_device; 
	}
	// デバイスを設定する Set device object
	void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device) 
	{
		m_device = device;
	}
	// デバイスコンテキストを取得する 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() const
	{
		return m_context;
	}
	// デバイスコンテキストを設定する 
	void SetContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context) 
	{
		m_context = context;
	}

	// スワップチェインを取得する 
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() const
	{
		return m_swapChain;
	}
	// スワップチェインを設定する
	void SetSwapChain(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain) 
	{
		m_swapChain = swapChain;
	}
	// レンダーターゲットビューを取得する
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const
	{
		return m_renderTargetView;
	}
	// レンダーターゲットビューを設定する
	void SetRenderTargetView(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView) {
		m_renderTargetView = renderTargetView;
	}

	// デプスステンシルビューを取得する 
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const
	{
		return m_depthStencilView;
	}
	// デプスステンシルビューを設定する 
	void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) {
		m_depthStencilView = depthStencilView;
	}

	// デバイスを生成する 
	void CreateDevice();
	// リソースを生成する 
	void CreateResources();

	// デバイスロストが発生した場合 
	void OnDeviceLost();

private:
	static std::unique_ptr<DirectX11> m_directX;

	HWND m_hWnd;
	int  m_width;
	int  m_height;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device1;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>	m_context;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context1;
	D3D_FEATURE_LEVEL  m_featureLevel;

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
};

#endif	// DirectX11 GRAPHICS

