#pragma once

class ISum :public IUnknown
{
public:

	virtual HRESULT __stdcall  SumOfTwoInteger(int ,int ,int *)=0;

};

class ISubtract :public IUnknown
{
public:

	virtual HRESULT __stdcall SubtractionOfTwoInteger (int,int,int *)=0;

};

// {1614A526-BD6C-4C8D-9F4B-F408B5059B7A}
static const CLSID CLSID_SumSubtract =
{ 0x1614a526, 0xbd6c, 0x4c8d,  0x9f, 0x4b, 0xf4, 0x8, 0xb5, 0x5, 0x9b, 0x7a  };


// {5AF692FC-E753-4504-9E7F-96A8C375F4C8}
static const IID IID_ISum =
{ 0x5af692fc, 0xe753, 0x4504, 0x9e, 0x7f, 0x96, 0xa8, 0xc3, 0x75, 0xf4, 0xc8 };


// {FCF9A53C-36D8-4264-A36D-02F6C0AE6977}
static const IID IID_ISubtract =
{ 0xfcf9a53c, 0x36d8, 0x4264, { 0xa3, 0x6d, 0x2, 0xf6, 0xc0, 0xae, 0x69, 0x77 } };


