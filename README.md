# Guided-Missile-Modeling-Simulation
Guided air-to-air missile modeling and simulation project written in C++
This is a C++ port of https://github.com/bgin/Guided_Missile_Simulation projects written in Fortran.
T-Matrix models(by Mishchenko and by Xu) will be used to compute scattering coefficients returned by single particles and ensemble of particles. Large scatterers (targets) will be modelled as a OBJ,STL format files and later converted to format used by MGL-FastRCS program. Near, far fields and RCS will be computed by MGL-FastRCS program (FDTD method) Atmospheric quantities and wind will be based on WRF modules and WRF output files. Work in progress...

List of references:

Detection, Estimation, and Modulation Theory Part III: Radar-Sonar Signal Processing and Gaussian Signals in Noise Harry L. van Trees ISBN-10: 047110793X ISBN-13: 978-0471107934

Detection Estimation and Modulation Theory, Part I: Detection, Estimation, and Filtering Theory Harry L. van Trees ISBN-10: 9780470542965 ISBN-13: 978-0470542965 ASIN: 0470542969

Automatic Control of Aircraft and Missiles John H. Blakelock ASIN: B01FJ0JOU2

Generalized Moment Methods in Electromagnetics: Formulation and Computer Solution of Integral Equations Johnson J. H. Wang ISBN-10: 0471514438 ISBN-13: 978-0471514435

Principles of High-Resolution Radar (Artech House Radar Library), August W. Rihaczek ISBN-10: 089006900X
ISBN-13: 978-0890069004
