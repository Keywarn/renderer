# renderer
A rendering engine written in CPP.

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
- [ ] Soft shadow
- [x] Bump maps
- [x] Basic clipping (bounding box)

### 80 - some of
- [ ] Environment maps
- [ ] Complex “interesting” materials (e.g. glass)
- [ ] Line drawing optimisations (e.g. Bresenham)
- [ ] Advance clipping (frustum)
- [ ] Photon maps and caustics
- [ ] “Intelligent” model simplification
