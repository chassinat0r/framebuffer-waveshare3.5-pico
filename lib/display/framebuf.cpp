#include <stdio.h>
#include <string.h>

#include "framebuf.hpp"

FrameBuffer::FrameBuffer() {

}

void FrameBuffer::fill(COLOR c) {
	fill_rect(0, 0, width, height, c);
}

void FrameBuffer::fill_rect(int x_start, int y_start, int w, int h, COLOR c) {
	int x_end = x_start + w;
	int y_end = y_start + h;

	if (x_end > width) {
		x_end = width;
	}
	if (y_end > height) {
		y_end = height;
	}

	if (x_start < 0) {
		x_start = 0;
	}
	if (y_start < 0) {
		y_start = 0;
	}

	for (int y = y_start; y < y_end; y++) {
		for (int x = x_start; x < x_end; x++) {
			int index = (x + y * stride) * 2;
			buffer[index] = c & 0XFF;
			buffer[index+1] = c  >> 8;
		}
	}
}

void FrameBuffer::pixel(int x, int y, COLOR c) {
	int index = (x + y * stride) * 2;
	buffer[index] = c & 0XFF;
	buffer[index+1] = c  >> 8;
}

COLOR FrameBuffer::get_pixel(int x, int y) {
	int index = (x + y * stride) * 2;
	return buffer[index];
}

void FrameBuffer::hline(int x, int y, int w, COLOR c) {
	fill_rect(x, y, w, 1, c);
}

void FrameBuffer::vline(int x, int y, int h, COLOR c) {
	fill_rect(x, y, 1, h, c);
}

void FrameBuffer::rect(int x, int y, int w, int h, COLOR c) {
	fill_rect(x, y, w, 1, c);
	fill_rect(x, y+h, w, 1, c);
	fill_rect(x, y, 1, h, c);
	fill_rect(x+w, y, 1, h, c); 
}

void FrameBuffer::text(char *string, int x0, int y0, COLOR c) {
	for (; *string; ++string) {
		int chr = *(uint8_t *)string;

		if (chr < 32 || chr > 127) {
			chr = 127;
		}

		const uint8_t *chr_data = &font_petme128_8x8[(chr - 32) * 8];

		for (int j = 0; j < 8; j++, x0++) {
			if (0 <= x0 && x0 < width) {
				uint vline_data = chr_data[j];

				for (int y = y0; vline_data; vline_data >>=1, y++) {
					if (vline_data & 1) {
						if (0 <= y && y < height) {
							pixel(x0, y, c);
						}
					}
				}
			}
		}
	}
}
