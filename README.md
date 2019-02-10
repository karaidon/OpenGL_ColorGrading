# OpenGL_ColorGrading
Sample Code to implement realtime colour grading using look up tables in OpenGL

SaveColourGradingScreenshot:
Takes a screenshot of your game world, and overlays the lookup table in the top right corner.

LoadColourGradingScreenshot:
Loads a lookup table from a screenshot taken using the previous function.

General Steps:
1. Implement a render-to-texture pipeline for your scene, so that your scene is rendered first to a texture,
and the texture is rendered onto a quad that occupies the whole screen. Info on how to do this can be found online.
2. Use SaveColourGradingScreenshot to take a screenshot with a lookup table overlayed.
3. Tweak screenshot as desired in your image editing tool.
4. Load the lookup table in the screenshot as a texture with LoadColourGradingScreenshot.
5. Bind the texture before rendering the final image on the fullscreen quad.
6. In your fragment shader for rendering the fullscreen quad, lookup the fragment color from the texture your scene is rendered to.
Use that as coordinates to lookup the final fragment color in the lookup table texture. See shader.frag for an example.



Copyright 2019 Benedict Lee

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
