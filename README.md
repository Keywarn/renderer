# renderer
A rendering engine written in CPP.

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
- [ ] Changing camera orientation (via orientation matrix)
- [x] LookAt
- [ ] Hard Shadow
- [ ] Some form of generative geometry
- [ ] Ambient lighting
- [ ] Diffuse lighting (proximity and angle-of-incidence)

### 60 - some of
- [ ] Gouraud shading
- [ ] Naive (non-perspective corrected) texture mapping
- [ ] Simple animation (e.g. fly-through)
- [ ] Some form of Physics (gravity, friction, bounce etc)
- [ ] Basic culling (far-plane, near-plan, back-face)
- [ ] Basic anti-aliasing

### 70 - some of
- [ ] Phong Shading
- [ ] Fairly “interesting” materials (e.g. mirrors)
- [ ] Complex anti-aliasing
- [ ] Perspective corrected texture mapping
- [ ] “Fancy” animation
- [ ] Soft shadow
- [ ] Bump maps
- [ ] Environment maps
- [ ] Basic clipping (bounding box)

### 80 - some of
- [ ] Complex “interesting” materials (e.g. glass)
- [ ] Line drawing optimisations (e.g. Bresenham)
- [ ] Advance clipping (frustum)
- [ ] Photon maps and caustics
- [ ] “Intelligent” model simplification