// ☕ Привет
#pragma once

#include <string_view>
#include <fstream>
#include <memory>

#include "../Geometry/RectangleSize.h"
#include "../Geometry/Point.h"

namespace Shared
{
	namespace BmpHelper
	{
		using BmpSize = Shared::Geometry::RectangleSize<int>;
		using Point = Shared::Geometry::Point<int>;

#pragma pack(1)
		struct PixelColor
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
		};
#pragma pack()

		static bool operator==(const PixelColor& p1, const PixelColor& p2)
		{
			return p1.r == p2.r && p1.g == p2.g && p1.b == p2.b;

		}

		namespace PixelColors
		{
			static const Shared::BmpHelper::PixelColor Black{ 0,   0, 0 };
			static const Shared::BmpHelper::PixelColor White{ 255, 255, 255 };
			static const Shared::BmpHelper::PixelColor   Red{ 0,   0, 255 };
			static const Shared::BmpHelper::PixelColor Green{ 0, 255, 0 };
			static const Shared::BmpHelper::PixelColor  Blue{ 255,   0, 0 };
		};

		class Bmp
		{
#pragma pack(2)
			struct
			{
				unsigned short bfType;           /* Magic number for file */
				unsigned int   bfSize;           /* Size of file */
				unsigned short bfReserved1;      /* Reserved */
				unsigned short bfReserved2;      /* ... */
				unsigned int   bfOffBits;        /* Offset to bitmap data */
			} _file_header;
#pragma pack()

			struct
			{
				unsigned int   biSize;           /* Size of info header */
				int            biWidth;          /* Width of image */
				int            biHeight;         /* Height of image */
				unsigned short biPlanes;         /* Number of color planes */
				unsigned short biBitCount;       /* Number of bits per pixel */
				unsigned int   biCompression;    /* Type of compression to use */
				unsigned int   biSizeImage;      /* Size of image data */
				int            biXPelsPerMeter;  /* X pixels per meter */
				int            biYPelsPerMeter;  /* Y pixels per meter */
				unsigned int   biClrUsed;        /* Number of colors used */
				unsigned int   biClrImportant;   /* Number of important colors */
			} _info_header;

			std::unique_ptr<PixelColor[]> _pixels;

		public:
			Bmp(const std::string& file_name)
			{
				std::ifstream ifs(file_name, std::ios::binary);

				if (!ifs.is_open())
				{
					throw std::logic_error("Cannot open bmp file: " + file_name);
				}

				ifs.read((char*)(&_file_header), sizeof(_file_header));
				ifs.read((char*)(&_info_header), sizeof(_info_header));

				// Данные строки битмапа выравниваются по 4 байта
				const int width_offset = 4 - ((_info_header.biWidth * 3) % 4);
				int dummy;

				_pixels = std::make_unique<PixelColor[]>(_info_header.biWidth * _info_header.biHeight);

				const auto line_size_bytes = _info_header.biWidth * sizeof(PixelColor);

				for (int i = 0; i < _info_header.biHeight; i++)
				{
					ifs.read((char*)(_pixels.get() + (_info_header.biHeight - i - 1) * _info_header.biWidth), line_size_bytes);
					ifs.read((char*)(&dummy), width_offset);
				}
			}

			BmpSize Size() const { return { _info_header.biWidth,_info_header.biHeight }; }

			const PixelColor& Pixel(Point point) const { return _pixels[point._y * _info_header.biWidth + point._x]; }
		};
	}
}