void SaveColourGradingScreenshot(const std::string& filename)
{
  GLint dims[4] = {0};
  glGetIntegerv(GL_VIEWPORT, dims);
  GLint imgWidth = dims[2];
  GLint imgHeight = dims[3];
  
	Render(); //Render game scene
	unsigned char* buf = new unsigned char[3 * imgHeight * imgWidth];

	//set glReadPixels to target front buffer
	glReadBuffer(GL_FRONT);
  
	//opengl uses bottom-left as origin, so we readpixels row by row,
	//but write from end to front of buffer so we end up with image right side up
	for (int y = 0; y < imgHeight; ++y)
	{
		glReadPixels(0, y, imgWidth, 1, GL_RGB, GL_UNSIGNED_BYTE, &buf[(imgHeight - 1 - y) * imgWidth * 3]);
	}

	//overlay the lookup table over the screenshot
	/* LUT is composed of 32 squares,
	for each square, r is mapped to x axis,
	g is mapped to y axis, and b increases by (256/8) over the 32
	squares, and is consistent within each square
	*/
	int w = LUT_FULL_WIDTH;
	int h = LUT_SQUARE_DIM;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int r = 8 * (x % LUT_SQUARE_DIM);
			int g = 8 * (y % LUT_SQUARE_DIM);
			int b = 8 * (x / LUT_SQUARE_DIM);
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			buf[(x + y * imgWidth) * 3 + 0] = (unsigned char)(r);
			buf[(x + y * imgWidth) * 3 + 1] = (unsigned char)(g);
			buf[(x + y * imgWidth) * 3 + 2] = (unsigned char)(b);
		}
	}

	SaveBMP(buf, filename);
	delete[] buf;
}

#define LUT_SQUARE_DIM 32
#define LUT_FULL_WIDTH LUT_SQUARE_DIM*LUT_SQUARE_DIM

GLuint LoadColourGradingScreenshot(const std::string& filename)
{
	//Load screenshot from file
	int imgWidth, imgHeight, imgChannels;
	unsigned char* buf = loadBMP(filename.c_str(), &imgWidth, &imgHeight, &imgChannels);
	if (buf == nullptr) return 0;
	unsigned char* lut = new unsigned char[LUT_FULL_WIDTH * LUT_SQUARE_DIM * 3];
	int w = LUT_SQUARE_DIM;
	int h = LUT_SQUARE_DIM;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_3D, texture);

	//we store LUT in GPU as a 3d texture, with each colour channel mapped to 1 axis
	//So even though LUT in the file is 2d, we read it as if it were 3d
	//with the blue channel mapped to z axis
	int pos = 0;
	for (int z = 0; z < h; ++z)
	{
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				lut[pos + 0] = buf[(x + z * w + y * imgWidth) * 3 + 0];
				lut[pos + 1] = buf[(x + z * w + y * imgWidth) * 3 + 1];
				lut[pos + 2] = buf[(x + z * w + y * imgWidth) * 3 + 2];
				pos += 3;
			}
		}
	}

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, h, h, h, 0, GL_RGB, GL_UNSIGNED_BYTE, lut);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_3D, 0);
	delete[] lut;
	freeBMP(buf);
	return texture;
}
