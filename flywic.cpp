#pragma comment(lib, "ole32.lib")

#include "flypicture.hpp"
#include <wincodec.h>

IWICImagingFactory* WIC = 0;

bool picture_c::load(const char_t* name)
{
	if (WIC == 0)
	{
		if (SUCCEEDED( CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE) ))
		{
			CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&WIC));
		}
	}

	if (WIC)
	{
		IWICBitmapDecoder *decoder = nullptr;
		if (SUCCEEDED
		(
			WIC->CreateDecoderFromFilename
			(
				name,							// Image to be decoded
				nullptr,                        // Do not prefer a particular vendor
				GENERIC_READ,                   // Desired read access to the file
				WICDecodeMetadataCacheOnDemand,	// Cache metadata when needed
				&decoder						// Pointer to the decoder
			)
		))
		{
			IWICBitmapFrameDecode* frame = 0;
			if (SUCCEEDED( decoder->GetFrame(0, &frame) ))
			{
				IWICFormatConverter* bitmap;
				if (SUCCEEDED( WIC->CreateFormatConverter(&bitmap) ))
				{
					if (SUCCEEDED
					( 
						bitmap->Initialize
						(
							frame,							// Source bitmap to convert
							GUID_WICPixelFormat32bppRGBA,	// Destination pixel format
							WICBitmapDitherTypeNone,        // Specified dither pattern
							nullptr,                        // Specify a particular palette
							0.f,                            // Alpha threshold
							WICBitmapPaletteTypeCustom      // Palette translation type
						)
					))
					{
						if (SUCCEEDED( bitmap->GetSize((UINT*)&w, (UINT*)&h) ))
						{
							data = new uint8_t[w*h*4];
							if (data)
							{
								if (SUCCEEDED( bitmap->CopyPixels(0, w*4, w*h*4, data) ) == 0)
								{
									delete[] data;
									data = 0;
									w = 0;
									h = 0;
								}
							}
						}
					}
					bitmap->Release();
				}
				frame->Release();
			}
			decoder->Release();
		}
	}
	return data != 0;
}

uint8_t* Picture_Load(char_t* name, int* pw, int* ph)
{
	uint8_t* data = 0;

	if (WIC == 0)
	{
		if (SUCCEEDED( CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE) ))
		{
			CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&WIC));
		}
	}

	if (WIC)
	{
		IWICBitmapDecoder *decoder = nullptr;
		if (SUCCEEDED
		(
			WIC->CreateDecoderFromFilename
			(
				name,							// Image to be decoded
				nullptr,                        // Do not prefer a particular vendor
				GENERIC_READ,                   // Desired read access to the file
				WICDecodeMetadataCacheOnDemand,	// Cache metadata when needed
				&decoder						// Pointer to the decoder
			)
		))
		{
			IWICBitmapFrameDecode* frame = 0;
			if (SUCCEEDED( decoder->GetFrame(0, &frame) ))
			{
				IWICFormatConverter* bitmap;
				if (SUCCEEDED( WIC->CreateFormatConverter(&bitmap) ))
				{
					if (SUCCEEDED
					( 
						bitmap->Initialize
						(
							frame,							// Source bitmap to convert
							GUID_WICPixelFormat32bppRGBA,	// Destination pixel format
							WICBitmapDitherTypeNone,        // Specified dither pattern
							nullptr,                        // Specify a particular palette
							0.f,                            // Alpha threshold
							WICBitmapPaletteTypeCustom      // Palette translation type
						)
					))
					{
						UINT w, h;
						if (SUCCEEDED( bitmap->GetSize(&w, &h) ))
						{
							data = new BYTE[w*h*4];
							if (data)
							{
								if (SUCCEEDED( bitmap->CopyPixels(0, w*4, w*h*4, data) ))
								{
									*pw = w;
									*ph = h;
								}
								else
								{
									delete[] data;
									data = 0;
								}
							}
						}
					}
					bitmap->Release();
				}
				frame->Release();
			}
			decoder->Release();
		}
	}
	return data;
}