# renderer
A rendering engine written in CPP.

## Code

There are two main `.cpp` files included. `Drawing.cpp`runs an interactive window which makes use of the controls as listed below. `Animation.cpp` is the file used to render out an animation with a certain number of frames. The `make`commands use the interactive version by default.

###Parameters

There are several paramters which can be changed in the `Drawing.cpp` file (towards the top). These affect the quality of the render and the time taken to render.

- `DIF_SAMPLES`- `int`value which determines the number of monte carlo samples to use for global illumination (only available on the phong mode). A value of `1`uses standard ambient lighting instead of global illumination.
- `AA_MODE` - The sampling mode to be used for anti-aliasing. Can be: `NO_AA`,`TWOBYTWO`,`RGSS`or `FOURBYFOUR`
- `CELLS` - The number of cells for each direct light (along each side), value of `1` results in hard shadows.
- `DEPTH`- Maximum number of bounces for a given ray (when handling mirrors, glass etc.)

## Controls

### Rendering Mode
- 1 - Wireframe (Default)
- 2 - Rasterised (No shdaing)
- 3 - Raytraced (Flat)
- 4 - Raytraced (Gouraud)
- 5 - Raytraced (Phong)

### Camera Controls
- W - Forward
- A - Left
- S - Back
- D - Right
- E - Up
- Q - Down
- Left/Right - Pan
- Up/Down - Tilt
- Z/X - Roll

- L - LookAt()

### Other
- P - export
- J - Line Anti-Aliasing
- K - Super Sampling

## Indicative marking features

The list below aims to provide an indication of the kinds of features required for each degree classification.
The final grade awarded will depend upon the exact combination and features and how well they have been implemented.


### 40 - all of
- [x] OBJ loading (geometry and materials)
- [x] Wireframe rendering
- [x] Flat shaded rasterising
- [x] Moving camera (position only)
- [x] Saving of PPM files

### 50 - some of
- [x] Changing camera orientation (via orientation matrix)
- [x] LookAt
- [ ] Some form of generative geometry
- [x] Ambient lighting
- [x] Diffuse lighting (proximity and angle-of-incidence)

### 60 - some of
- [x] Hard Shadow
- [x] Gouraud shading
- [x] Naive (non-perspective corrected) texture mapping
- [x] Simple animation (e.g. fly-through)
- [ ] Some form of Physics (gravity, friction, bounce etc)
- [x] Basic culling (far-plane, near-plan, back-face)
- [x] Basic anti-aliasing

### 70 - some of
- [x] Phong Shading
- [x] Fairly “interesting” materials (e.g. mirrors)
- [x] Super Sampling anti-aliasing
- [x] Perspective corrected texture mapping
- [ ] “Fancy” animation
- [x] Soft shadow
- [x] Bump maps
- [x] Basic clipping (bounding box)

### 80 - some of
- [ ] Environment maps
- [x] Complex “interesting” materials (e.g. glass)
- [ ] Line drawing optimisations (e.g. Bresenham)
- [ ] Advance clipping (frustum)
- [x] Photon maps and caustics
- [ ] “Intelligent” model simplification

### Extras
- [ ] Thin film simulation (bubbles)
- [ ] Volumetric Lightin
