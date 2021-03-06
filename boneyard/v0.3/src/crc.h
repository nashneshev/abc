/*
MIT License

Copyright (c) 2018 Zlatko Michailov 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

#include <cstdint>


namespace abc {
	namespace crc {
		constexpr std::uint8_t	seed8	= 0x77;
		constexpr std::uint16_t	seed16	= 0x3692;
		constexpr std::uint32_t	seed32	= 0xffffffffUL;
	}


	template <typename Crc, typename ConstIterator>
	Crc _crc(ConstIterator begin, ConstIterator end, const Crc table[], Crc init, Crc xorOut) noexcept;


	template <typename ConstIterator>
	std::uint8_t crc8(ConstIterator begin, ConstIterator end, std::uint8_t seed = crc::seed8) noexcept;

	template <typename ConstIterator>
	std::uint16_t crc16(ConstIterator begin, ConstIterator end, std::uint16_t seed = crc::seed16) noexcept;

	template <typename ConstIterator>
	std::uint32_t crc32(ConstIterator begin, ConstIterator end, std::uint32_t seed = crc::seed32) noexcept;


	// --------------------------------------------------------------


	namespace crc {
		static constexpr std::uint8_t table8[] = {
			0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83,		0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
			0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e,		0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
			0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0,		0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
			0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d,		0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
			0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5,		0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
			0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58,		0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
			0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6,		0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
			0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b,		0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,

			0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f,		0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
			0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92,		0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
			0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c,		0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
			0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1,		0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
			0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49,		0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
			0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4,		0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
			0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a,		0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
			0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7,		0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
		};

		static constexpr std::uint16_t table16[] = {
			0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,		0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
			0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,		0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
			0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,		0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
			0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,		0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
			0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,		0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
			0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,		0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
			0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,		0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
			0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,		0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,

			0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,		0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
			0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,		0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
			0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,		0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
			0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,		0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
			0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,		0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
			0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,		0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
			0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,		0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
			0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,		0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78,
		};

		static constexpr std::uint32_t table32[] = {
			0x00000000UL, 0x77073096UL, 0xee0e612cUL, 0x990951baUL, 0x076dc419UL, 0x706af48fUL, 0xe963a535UL, 0x9e6495a3UL, 	0x0edb8832UL, 0x79dcb8a4UL, 0xe0d5e91eUL, 0x97d2d988UL, 0x09b64c2bUL, 0x7eb17cbdUL, 0xe7b82d07UL, 0x90bf1d91UL,
			0x1db71064UL, 0x6ab020f2UL, 0xf3b97148UL, 0x84be41deUL, 0x1adad47dUL, 0x6ddde4ebUL, 0xf4d4b551UL, 0x83d385c7UL,		0x136c9856UL, 0x646ba8c0UL, 0xfd62f97aUL, 0x8a65c9ecUL, 0x14015c4fUL, 0x63066cd9UL, 0xfa0f3d63UL, 0x8d080df5UL,
			0x3b6e20c8UL, 0x4c69105eUL, 0xd56041e4UL, 0xa2677172UL, 0x3c03e4d1UL, 0x4b04d447UL, 0xd20d85fdUL, 0xa50ab56bUL,		0x35b5a8faUL, 0x42b2986cUL, 0xdbbbc9d6UL, 0xacbcf940UL, 0x32d86ce3UL, 0x45df5c75UL, 0xdcd60dcfUL, 0xabd13d59UL,
			0x26d930acUL, 0x51de003aUL, 0xc8d75180UL, 0xbfd06116UL, 0x21b4f4b5UL, 0x56b3c423UL, 0xcfba9599UL, 0xb8bda50fUL,		0x2802b89eUL, 0x5f058808UL, 0xc60cd9b2UL, 0xb10be924UL, 0x2f6f7c87UL, 0x58684c11UL, 0xc1611dabUL, 0xb6662d3dUL,
			0x76dc4190UL, 0x01db7106UL, 0x98d220bcUL, 0xefd5102aUL, 0x71b18589UL, 0x06b6b51fUL, 0x9fbfe4a5UL, 0xe8b8d433UL,		0x7807c9a2UL, 0x0f00f934UL, 0x9609a88eUL, 0xe10e9818UL, 0x7f6a0dbbUL, 0x086d3d2dUL, 0x91646c97UL, 0xe6635c01UL,
			0x6b6b51f4UL, 0x1c6c6162UL, 0x856530d8UL, 0xf262004eUL, 0x6c0695edUL, 0x1b01a57bUL, 0x8208f4c1UL, 0xf50fc457UL,		0x65b0d9c6UL, 0x12b7e950UL, 0x8bbeb8eaUL, 0xfcb9887cUL, 0x62dd1ddfUL, 0x15da2d49UL, 0x8cd37cf3UL, 0xfbd44c65UL,
			0x4db26158UL, 0x3ab551ceUL, 0xa3bc0074UL, 0xd4bb30e2UL, 0x4adfa541UL, 0x3dd895d7UL, 0xa4d1c46dUL, 0xd3d6f4fbUL,		0x4369e96aUL, 0x346ed9fcUL, 0xad678846UL, 0xda60b8d0UL, 0x44042d73UL, 0x33031de5UL, 0xaa0a4c5fUL, 0xdd0d7cc9UL,
			0x5005713cUL, 0x270241aaUL, 0xbe0b1010UL, 0xc90c2086UL, 0x5768b525UL, 0x206f85b3UL, 0xb966d409UL, 0xce61e49fUL,		0x5edef90eUL, 0x29d9c998UL, 0xb0d09822UL, 0xc7d7a8b4UL, 0x59b33d17UL, 0x2eb40d81UL, 0xb7bd5c3bUL, 0xc0ba6cadUL,

			0xedb88320UL, 0x9abfb3b6UL, 0x03b6e20cUL, 0x74b1d29aUL, 0xead54739UL, 0x9dd277afUL, 0x04db2615UL, 0x73dc1683UL,		0xe3630b12UL, 0x94643b84UL, 0x0d6d6a3eUL, 0x7a6a5aa8UL, 0xe40ecf0bUL, 0x9309ff9dUL, 0x0a00ae27UL, 0x7d079eb1UL,
			0xf00f9344UL, 0x8708a3d2UL, 0x1e01f268UL, 0x6906c2feUL, 0xf762575dUL, 0x806567cbUL, 0x196c3671UL, 0x6e6b06e7UL,		0xfed41b76UL, 0x89d32be0UL, 0x10da7a5aUL, 0x67dd4accUL, 0xf9b9df6fUL, 0x8ebeeff9UL, 0x17b7be43UL, 0x60b08ed5UL,
			0xd6d6a3e8UL, 0xa1d1937eUL, 0x38d8c2c4UL, 0x4fdff252UL, 0xd1bb67f1UL, 0xa6bc5767UL, 0x3fb506ddUL, 0x48b2364bUL,		0xd80d2bdaUL, 0xaf0a1b4cUL, 0x36034af6UL, 0x41047a60,	0xdf60efc3UL, 0xa867df55UL, 0x316e8eefUL, 0x4669be79UL,
			0xcb61b38cUL, 0xbc66831aUL, 0x256fd2a0UL, 0x5268e236UL, 0xcc0c7795UL, 0xbb0b4703UL, 0x220216b9UL, 0x5505262fUL,		0xc5ba3bbeUL, 0xb2bd0b28UL, 0x2bb45a92UL, 0x5cb36a04UL, 0xc2d7ffa7UL, 0xb5d0cf31UL, 0x2cd99e8bUL, 0x5bdeae1dUL,
			0x9b64c2b0UL, 0xec63f226UL, 0x756aa39cUL, 0x026d930aUL, 0x9c0906a9UL, 0xeb0e363fUL, 0x72076785UL, 0x05005713UL,		0x95bf4a82UL, 0xe2b87a14UL, 0x7bb12baeUL, 0x0cb61b38UL, 0x92d28e9bUL, 0xe5d5be0dUL, 0x7cdcefb7UL, 0x0bdbdf21UL,
			0x86d3d2d4UL, 0xf1d4e242UL, 0x68ddb3f8UL, 0x1fda836eUL, 0x81be16cdUL, 0xf6b9265bUL, 0x6fb077e1UL, 0x18b74777UL,		0x88085ae6UL, 0xff0f6a70UL, 0x66063bcaUL, 0x11010b5cUL, 0x8f659effUL, 0xf862ae69UL, 0x616bffd3UL, 0x166ccf45UL,
			0xa00ae278UL, 0xd70dd2eeUL, 0x4e048354UL, 0x3903b3c2UL, 0xa7672661UL, 0xd06016f7UL, 0x4969474dUL, 0x3e6e77dbUL,		0xaed16a4aUL, 0xd9d65adcUL, 0x40df0b66UL, 0x37d83bf0UL, 0xa9bcae53UL, 0xdebb9ec5UL, 0x47b2cf7fUL, 0x30b5ffe9UL,
			0xbdbdf21cUL, 0xcabac28aUL, 0x53b39330UL, 0x24b4a3a6UL, 0xbad03605UL, 0xcdd70693UL, 0x54de5729UL, 0x23d967bfUL,		0xb3667a2eUL, 0xc4614ab8UL, 0x5d681b02UL, 0x2a6f2b94UL, 0xb40bbe37UL, 0xc30c8ea1UL, 0x5a05df1bUL, 0x2d02ef8dUL,
		};
	}


	template <typename Crc, typename ConstIterator>
	Crc _crc(ConstIterator begin, ConstIterator end, const Crc table[], Crc init, Crc xorOut) noexcept {
		Crc crc = init;

		for (ConstIterator it = begin; it != end; it++) {
			crc = table[(crc ^ *it) & 0xff] ^ (crc >> 8);
		}

		return crc ^ xorOut;
	}


	template <typename ConstIterator>
	std::uint8_t crc8(ConstIterator begin, ConstIterator end, std::uint8_t seed) noexcept {
		std::uint8_t crc = seed;

		for (ConstIterator it = begin; it != end; it++) {
			crc = crc::table8[(crc ^ *it) & 0xff];
		}

		return crc;
	}


	template <typename ConstIterator>
	std::uint16_t crc16(ConstIterator begin, ConstIterator end, std::uint16_t seed) noexcept {
		std::uint16_t crc = seed;

		for (ConstIterator it = begin; it != end; it++) {
			crc = crc::table16[(crc ^ *it) & 0xff] ^ (crc >> 8);
		}

		return crc;
	}


	template <typename ConstIterator>
	std::uint32_t crc32(ConstIterator begin, ConstIterator end, std::uint32_t seed) noexcept {
		std::uint32_t crc = seed;

		for (ConstIterator it = begin; it != end; it++) {
			crc = crc::table32[(crc ^ *it) & 0xff] ^ (crc >> 8);
		}

		return crc;
	}

}
