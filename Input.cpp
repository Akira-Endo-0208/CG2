#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <D3dx9math.h>


#include "Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define MOUSE_ON_VALUE (0x80)					//!< �I����Ԃ̒l

static LPDIRECTINPUT8 g_InputInterface;			//!< DIRECTINPUT8�̃|�C���^
static LPDIRECTINPUTDEVICE8 g_MouseDevice;		//!< DIRECTINPUTDEVICE8�̃|�C���^
static DIMOUSESTATE2 g_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
static DIMOUSESTATE2 g_PrevMouseState;			//!< �}�E�X�̌��݂̓��͏��


//!< ���̓C���^�[�t�F�[�X�̍쐬
bool CreateInputInterface();

//!< �}�E�X�f�o�C�X�̍쐬
bool CreateMouseDevice();

//!< �}�E�X�̍X�V
void UpdateMouse();

//!< �������x���̐ݒ�
BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device);

//!< �}�E�X�̐���N��
BOOL StartMouseControl();

bool InitInput()
{
	// �C���^�[�t�F�[�X�쐬
	if (CreateInputInterface() == false)
	{
		return false;
	}

	// �f�o�C�X�쐬
	if (CreateMouseDevice() == false)
	{
		ReleaseInput();
		return false;
	}

	// ���͏��̏�����
	ZeroMemory(&g_CurrentMouseState, sizeof(DIMOUSESTATE2));
	ZeroMemory(&g_PrevMouseState, sizeof(DIMOUSESTATE2));

	return true;
}

void ReleaseInput()
{
	// �f�o�C�X�̉��
	if (g_MouseDevice != nullptr)
	{
		// ������~
		g_MouseDevice->Unacquire();
		g_MouseDevice->Release();
		g_MouseDevice = nullptr;
	}

	// �C���^�[�t�F�[�X�̉��
	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}
}

void UpdateInput()
{
	UpdateMouse();
}




bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}

	return false;
}

bool OnMousePush(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[MouseButton::SideDown] & MOUSE_ON_VALUE &&
		g_CurrentMouseState.rgbButtons[MouseButton::SideDown] & MOUSE_ON_VALUE)
	{
		return true;
	}

	if (g_PrevMouseState.rgbButtons[MouseButton::SideUp] & MOUSE_ON_VALUE &&
		g_CurrentMouseState.rgbButtons[MouseButton::SideUp] & MOUSE_ON_VALUE)
	{
		return true;
	}
	return false;
}

bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(g_CurrentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}

	return false;
}

bool CreateInputInterface()
{
	// �C���^�[�t�F�[�X�쐬
	HRESULT ret = DirectInput8Create(
		GetModuleHandle(nullptr),	// �C���X�^���X�n���h��
		DIRECTINPUT_VERSION,		// DirectInput�̃o�[�W����
		IID_IDirectInput8,			// �g�p����@�\
		(void**)&g_InputInterface,	// �쐬���ꂽ�C���^�[�t�F�[�X����p
		NULL						// NULL�Œ�
	);

	if (FAILED(ret))
	{
		return false;
	}

	return true;
}

bool CreateMouseDevice()
{
	g_MouseDevice = nullptr;

	// �f�o�C�X����
	HRESULT hr = g_InputInterface->CreateDevice(
		GUID_SysMouse,
		&g_MouseDevice,
		NULL);

	if (FAILED(hr))
	{
		return false;
	}

	// ���̓t�H�[�}�b�g�̎w��
	hr = g_MouseDevice->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		return false;
	}

	// �������x���̐ݒ�
	if (SetUpCooperativeLevel(g_MouseDevice) == false)
	{
		return false;
	}

	int count = 0;
	// ����J�n
	while (StartMouseControl() == false)
	{
		Sleep(100);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	return true;
}

void UpdateMouse()
{
	if (g_MouseDevice == nullptr)
	{
		return;
	}

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	g_PrevMouseState = g_CurrentMouseState;

	// �}�E�X�̏�Ԃ��擾���܂�
	HRESULT	hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &g_CurrentMouseState);
	if (FAILED(hr))
	{
		g_MouseDevice->Acquire();
		hr = g_MouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &g_CurrentMouseState);
	}


	POINT p;
	// �}�E�X���W(�X�N���[�����W)���擾����
	GetCursorPos(&p);



}

BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	// �������[�h�̐ݒ�
	if (FAILED(device->SetCooperativeLevel(
		FindWindow(L"DirectXGame", nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		return false;
	}

	return true;
}

BOOL StartMouseControl()
{
	// �f�o�C�X����������ĂȂ�
	if (g_MouseDevice == nullptr)
	{
		return false;
	}
	// ����J�n
	if (FAILED(g_MouseDevice->Acquire()))
	{
		return false;
	}

	DIDEVCAPS cap;
	g_MouseDevice->GetCapabilities(&cap);
	// �|�[�����O����
	if (cap.dwFlags & DIDC_POLLEDDATAFORMAT)
	{
		DWORD error = GetLastError();
		// �|�[�����O�J�n
		/*
			Poll��Acquire�̑O�ɍs���Ƃ���Ă������A
			Acquire�̑O�Ŏ��s����Ǝ��s�����̂�
			��Ŏ��s����悤�ɂ���
		*/
		if (FAILED(g_MouseDevice->Poll()))
		{
			return false;
		}
	}

	return true;
}
